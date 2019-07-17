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
	printf("getWinners Function Test.\n");
	int discarded = 1;


	int *k = kingdomCards(ambassador, village, minion, gardens, smithy, tribute, baron, cutpurse, mine, outpost);
	struct gameState game;
	int players = 2;
	int seed = 1000;
	int handpos = 0;
	int bonus = 0;
	int firstPlayer = 0;
	int shuffledCards = 0;

	int winners[4] = {0};

	game.hand[firstPlayer][0] = province;
	game.hand[firstPlayer][1] = province;
	game.hand[firstPlayer][2] = province;
	game.hand[firstPlayer][3] = province;
	game.hand[firstPlayer][4] = province;
	printf("Winner[0] = %d, Winner[1] %d\n", winners[0], winners[1]);
	
	getWinners(winners, &game);

	printf("Winner[0] = %d, Winner[1] %d\n", winners[0], winners[1]);

	//TESTS WHETHER THE getWinners FUNCTION returns the correct player
	int i = 0;
	int winner;

	for (i = 0; i < 2; i++){
		if(winners[i] == 1)
			winner = winners[i];
	}

	printf("%d is the winner! Expected Player 1 (0)\n", winner);
	ASSERT(winner == 0, "Correct Winner\n");


	printf("\n ~~~~~~~~~~~ getWinners Function TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");



	return 0;
}