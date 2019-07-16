#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"
#include "interface.h"


int ASSERT(int x, char *str){
	if (!x){
		printf ("TEST FAILED: %s", str);
		return 1;
	}
	else {
		printf ("TEST SUCCESSFUL: %s", str);
		return 0;
	}
}

//Tests the Initialize Game function
int main(){
	printf("endTurn Function Test.\n");
	int discarded = 1;


	int *k = kingdomCards(adventurer, village, minion, mine, smithy, tribute, baron, cutpurse, mine, outpost);
	struct gameState game;
	int players = 2;
	int seed = 1000;
	int handpos = 0;
	int bonus = 0;
	int firstPlayer = 0;
	int shuffledCards = 0;

	int a = initializeGame(players, k, seed, &game);

	a = game.whoseTurn;
	endTurn(&game);

	//TESTS WHETHER THE ENDTURN FUNCTION CHANGES THE TURN TO THE NEXT PLAYER
	printf("It is %d's turn. Expected to be Player %d's turn\n", whoseTurn(&game), a);
	ASSERT(game.whoseTurn == 1, "Correct Player's Turn\n");


	printf("\n ~~~~~~~~~~~ endTurn Function TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");



	return 0;
}
