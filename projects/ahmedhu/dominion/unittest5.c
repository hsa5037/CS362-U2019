#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "ASSERT.h"
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
	printf("drawCard Function Test.\n");
	int discarded = 1;


	int *k = kingdomCards(adventurer, village, minion, mine, smithy, tribute, baron, cutpurse, mine, outpost);
	struct gameState game;
	int players = 2;
	int seed = 1000;
	int handpos = 0;
	int bonus = 0;
	int firstPlayer = 0;
	int shuffledCards = 0;



	initializeGame(players, k, seed, &game);

	struct gameState test;
	memcpy(&test, &game, sizeof(struct gameState));


	//TESTS WHETHER THE drawCard FUNCTION increments the handCount and decrements the deck count
	drawCard(firstPlayer, &test);
	printf("Hand Count = %d, Expected Count = %d\n", test.handCount[firstPlayer], game.handCount[firstPlayer] + 1);
	printf("Deck Count = %d, Expected Count = %d\n", test.deckCount[firstPlayer], game.deckCount[firstPlayer] - 1);
	ASSERT(test.handCount[firstPlayer] == game.handCount[firstPlayer] + 1, "Hand Count \n");
	ASSERT(test.deckCount[firstPlayer] == game.deckCount[firstPlayer] - 1, "Deck Count \n");



	printf("\n ~~~~~~~~~~~ drawCard Function TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");



	return 0;
}
