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


//Tests the ambassador card
int main(){
	printf("Initializing Ambassador Card Test.\n");
	int discarded = 1;


	int *k = kingdomCards(ambassador, village, minion, gardens, smithy, tribute, baron, cutpurse, mine, outpost);
	struct gameState game;
	int players = 2;
	int seed = 1000;
	int handpos = 0;
	int bonus = 0;
	int firstPlayer = 0;
	int secondPlayer = 1;
	int shuffledCards = 0;
    int handCount = 2;

	initializeGame(players, k, seed, &game);
    int p = whoseTurn(&game);
    game.handCount[0] = 2;
    int estates[2];
    estates[0] = estate;
    estates[1] = estate;
    memcpy(&game.hand[0], estates, sizeof(int) * handCount);

	//UNIT TEST 1: Choice1 = 1 = Player has enough cards to discard, return copy to supply deck and give other players a copy
	printf("UNIT TEST 1: Player has enough cards to discard, return copy to supply deck and give other players a copy\n");

	//copy game state into test case
	struct gameState test;
	memcpy(&test, &game, sizeof(struct gameState));
	int choice1 = 1;
	int choice2 = 1;
	int choice3 = 0;

	cardEffect(ambassador, choice1, choice2, choice3, &test, handpos, &bonus);


	printf("Hand Count = %d, Expected Count = %d\n", test.handCount[firstPlayer], game.handCount[firstPlayer]- choice2);
	printf("Supply Count = %d, Expected Count = %d\n", test.supplyCount[test.hand[firstPlayer][choice1]], game.supplyCount[game.hand[firstPlayer][choice1]] + choice2);
	printf("Player 2 Hand Count = %d, Expected Count = %d\n", test.handCount[secondPlayer], game.handCount[secondPlayer] + 1);
	ASSERT(test.handCount[firstPlayer] == game.handCount[firstPlayer] - choice2, "Hand Count]\n");
	ASSERT(test.supplyCount[test.hand[firstPlayer][choice1]] == game.supplyCount[game.hand[firstPlayer][choice1]] + choice2, "Supply Count\n");
	ASSERT(test.handCount[secondPlayer] == game.handCount[secondPlayer] + 1, "Player 2 Hand Count\n");

	printf("\n ~~~~~~~~~~~ Ambassador TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");


	return 0;
}
