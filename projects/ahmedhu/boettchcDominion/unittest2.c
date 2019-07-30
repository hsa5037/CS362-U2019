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
	printf("Shuffle Function Test.\n");
	int discarded = 1;


	int *k = kingdomCards(ambassador, village, minion, gardens, smithy, tribute, baron, cutpurse, mine, outpost);
	struct gameState game;
	int players = 2;
	int seed = 1000;
	int handpos = 0;
	int bonus = 0;
	int firstPlayer = 0;
	int shuffledCards = 0;

	game.deckCount[firstPlayer] = 3;
	game.deck[firstPlayer][0] = gold;
	game.deck[firstPlayer][1] = silver;
	game.deck[firstPlayer][2] = copper;

	shuffle(firstPlayer, &game);

	//Shuffle unit test checks to make sure all cards remained in the deck
	int count = 0;
	for (int i =0; i < 3; i++){
		if (game.deck[firstPlayer][i] == copper || game.deck[firstPlayer][i] == silver || game.deck[firstPlayer][i] == gold){
			count++;
		}
	}
	if (count == 3){
		printf("Test passed! All cards remained in the deck");
	}
	else
		printf("Test Failed!");

	ASSERT(count == 3, "Cards remained in deck \n");


	printf("\n ~~~~~~~~~~~ shuffle Function TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");



	return 0;
}