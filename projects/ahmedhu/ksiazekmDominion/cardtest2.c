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


//Tests the minion card
int main(){
	printf("Initializing Minion Card Test.\n");
	int discarded = 1;


	int *k = kingdomCards(ambassador, village, minion, gardens, smithy, tribute, baron, cutpurse, mine, outpost);
	struct gameState game;
	int players = 2;
	int seed = 1000;
	int handpos = 0;
	int bonus = 0;
	int firstPlayer = 0;
	int shuffledCards = 0;

	initializeGame(players, k, seed, &game);

	//UNIT TEST 1: Choice1 = 1 = Action increase by 1 and +2 coins.
	printf("UNIT TEST 1: Choice1 = 1 = Action increase by 1 and +2 coins.\n");

	//copy game state into test case
	struct gameState test;
	memcpy(&test, &game, sizeof(struct gameState));
	int choice1 = 1;
	int choice2 = 0;
	int choice3 = 0;

	cardEffect(minion, choice1, choice2, choice3, &test, handpos, &bonus);

	int newCoins = 2;
	int actions = 1;

	printf("Hand Count = %d, Expected Count = %d\n", test.handCount[firstPlayer], game.handCount[firstPlayer] - discarded);
	printf("Deck Count = %d, Expected Count = %d\n", test.deckCount[firstPlayer], game.deckCount[firstPlayer] + shuffledCards);
	printf("Coins = %d, Expected Coins = %d\n", test.coins, game.coins + newCoins);
	printf("Actions = %d, Expected Actions = %d\n", test.numActions, game.numActions + actions);
	ASSERT(test.handCount[firstPlayer] == game.handCount[firstPlayer] - discarded, "Hand Count\n");
	ASSERT(test.deckCount[firstPlayer] == game.deckCount[firstPlayer] + shuffledCards, "Deck Count\n");
	ASSERT(test.coins == game.coins + newCoins, "Coins\n");
	ASSERT(test.numActions == game.numActions + actions, "Actions\n");

	//UNIT TEST 2: Choice2 = 1 = discard hand/redraw 4. other players with handCount > 5 discard hands
	choice1 = 0;
	choice2 = 1;
	test.handCount[1] = 6;
	cardEffect(minion, choice1, choice2, choice3, &test, handpos, &bonus);
	printf("Hand Count = %d, Expected Count = %d\n", test.handCount[firstPlayer], 4);
	printf("Other Player Hand Count = %d, Expected Count = 4\n", test.handCount[1]);
	ASSERT(test.handCount[firstPlayer] == 4, "Hand Count\n");
	ASSERT(test.handCount[1] == 4, "Hand Count\n");


	printf("\n ~~~~~~~~~~~ MINION TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");


	return 0;
}