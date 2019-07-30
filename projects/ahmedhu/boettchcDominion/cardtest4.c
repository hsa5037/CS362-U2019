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


//Tests the tribute card
int main(){
	printf("Initializing Tribute Card Test.\n");
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
    memcpy(&game.hand[1], estates, sizeof(int) * handCount);

	//UNIT TEST 1: Player chooses to discard too many cards
	printf("UNIT TEST 1: Player should gain an extra two cards \n");

	//copy game state into test case
	struct gameState test;
	memcpy(&test, &game, sizeof(struct gameState));
	int choice1 = 1;
	int choice2 = 3;
	int choice3 = 0;

	cardEffect(tribute, choice1, choice2, choice3, &test, handpos, &bonus);


	printf("Hand Count = %d, Expected Count = %d\n", test.handCount[firstPlayer], game.handCount[firstPlayer] + 2);
	printf("Deck Count = %d, Expected Count = %d\n", test.deckCount[firstPlayer], game.deckCount[firstPlayer] + shuffledCards);
	printf("Player 2 Hand Count = %d, Expected Count = %d\n", test.handCount[secondPlayer], game.handCount[secondPlayer]);
	printf("Coins = %d, Expected Coins = %d\n", test.coins, game.coins);
	printf("Actions = %d, Expected Actions = %d\n", test.numActions, game.numActions);

	ASSERT(test.handCount[firstPlayer] == game.handCount[firstPlayer] + 2, "Hand Count\n");
	ASSERT(test.deckCount[firstPlayer] == game.deckCount[firstPlayer] + shuffledCards, "Deck Count\n");
	ASSERT(test.handCount[secondPlayer] == game.handCount[secondPlayer], "Player 2 Hand Count\n");
	ASSERT(test.coins == game.coins, "Coins\n");
	ASSERT(test.numActions == game.numActions, "Actions\n");


	printf("\n ~~~~~~~~~~~ Tribute TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");


	return 0;
}