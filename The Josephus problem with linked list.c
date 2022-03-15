#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 81

typedef struct SPlayer
{
	char *name;
	long int id;
	struct SPlayer *nextPlayer_p;
}Player;

Player* InitTheHungerGame();
void LetTheHungerGameBegin(Player *player);
Player* CreateNewPlayer();

int main()
{
	Player* player = InitTheHungerGame();
	LetTheHungerGameBegin(player);
	system("pause");
	return 0;
}

/*************************************************************************
Function name: NewPlayer
Input: none
Output: the pointer of the new player
The function operation: the function create a new player
************************************************************************/
Player* CreateNewPlayer()
{
	char tempName[MAX_NAME_SIZE];
	Player *newP = (Player*)malloc(sizeof(Player));
	if (newP == NULL)//dynamic allocation checking
		exit(1);

	printf("name:\n");
	fgets(tempName, MAX_NAME_SIZE, stdin);
	scanf("%[^\n]*c", tempName);
	newP->name = (char*)malloc((strlen(tempName) + 1) * sizeof(char));
	if (newP->name == NULL)//dynamic allocation checking
	{
		free(newP);
		exit(1);
	}
	strcpy(newP->name, tempName);
	printf("id:\n");
	scanf("%ld", &newP->id);
	newP->nextPlayer_p = NULL;
	return newP;
}

/*************************************************************************
Function name: InitTheHungerGame
Input: None
Output: the head of the player's list
The function operation: the function initialize the game - it creates the players according to the user
						choice and organize the players in a linked list.
************************************************************************/
Player* InitTheHungerGame()
{
	int stop;
	Player* player = NULL;
	Player* headKeeper = NULL;
	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &stop);
	if (stop == 0)//case there are 0 players
		exit(1);

	player = CreateNewPlayer();
	headKeeper = player;//saving the head of the list

	printf("Add a person to the game? 1 for yes, 0 for no\n");
	scanf("%d", &stop);
	while (stop != 0)
	{
		player->nextPlayer_p = CreateNewPlayer();//add new player to the game
		player = player->nextPlayer_p;//move player to be next player
		printf("Add a person to the game? 1 for yes, 0 for no\n");
		scanf("%d", &stop);
	}
	player->nextPlayer_p = headKeeper;//making the list circular 
	return headKeeper;
}

/*************************************************************************
Function name: LetTheHungerGameBegin
Input: Player pointer to the start of the list
Output: none
The function operation: the function plays the game according to the rules
						and prints the winner.
************************************************************************/
void LetTheHungerGameBegin(Player *player)
{
	Player* headKeeper = player;
	Player* tempPlayer = NULL;
	while (player->nextPlayer_p != headKeeper)
	{
		printf("%s kills %s\n", player->name, player->nextPlayer_p->name);
		tempPlayer = player->nextPlayer_p;
		player->nextPlayer_p = player->nextPlayer_p->nextPlayer_p;
		free(tempPlayer->name);//release memory of the player's name
		free(tempPlayer);//release memory of the player
		player = player->nextPlayer_p;//move player to be next player
		headKeeper = player;//update the new head
	}
	printf("%s stayin alive!!\n", player->name);//the winner
	free(player->name);//release memory of the player's name
	free(player);//release the last player
}