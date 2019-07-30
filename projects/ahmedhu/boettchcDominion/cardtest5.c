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

//Tests the Mine card
int main(){
	printf("Initializing Mine Card Test.\n");
	int discarded = 1;


	int *k = kingdomCards(ambassador, village, minion, gardens, smithy, tribute, baron, cutpurse, mine, outpost);
	struct gameState game;
	int players = 2;
	int seed = 1000;
	int handpos = 0;
	int bonus = 0;
	int firstPlayer = 0;
	int secondPlayer  = 1;
	int shuffledCards = 0;

	initializeGame(players, k, seed, &game);

	//UNIT TEST 1: Choice1 = 1 = Trash Treasure card and receive treasure costing up to +3 coins more
	printf("UNIT TEST 1: Choice1 = Trash Treasure card and receive treasure costing up to +3 coins more\n");

	//copy game state into test case
	struct gameState test;
	game.hand[firstPlayer][0] = copper;
	game.hand[firstPlayer][1] = copper;
	game.hand[firstPlayer][2] = copper;
	game.hand[firstPlayer][3] = copper;


	memcpy(&test, &game, sizeof(struct gameState));
	int choice1 = 1;
	int choice2 = 0;
	int choice3 = 0;

	cardEffect(mine, choice1, choice2, choice3, &test, handpos, &bonus);

	int newCoins = 3;
	int buys = 1;

	printf("Hand Count = %d, Expected Count = %d\n", test.handCount[firstPlayer], game.handCount[firstPlayer]);
	printf("Deck Count = %d, Expected Count = %d\n", test.deckCount[firstPlayer], game.deckCount[firstPlayer] + shuffledCards);
	printf("Coins = %d, Expected Coins = %d\n", test.coins, game.coins + newCoins);
	ASSERT(test.handCount[firstPlayer] == game.handCount[firstPlayer], "Hand Count\n");
	ASSERT(test.deckCount[firstPlayer] == game.deckCount[firstPlayer] + shuffledCards, "Deck Count\n");
	ASSERT(test.coins == game.coins + newCoins, "Coins\n");

	//UNIT TEST 2: Choice1 and Choice2 switched to account for bug introduced in Assignment2
	printf("UNIT TEST 2: Choice1 and Choice2 switched to account for bug introduced in Assignment2\n");
	cardEffect(mine, 0, choice1, choice3, &test, handpos, &bonus);

	printf("Hand Count = %d, Expected Count = %d\n", test.handCount[firstPlayer], game.handCount[firstPlayer]);
	printf("Deck Count = %d, Expected Count = %d\n", test.deckCount[firstPlayer], game.deckCount[firstPlayer] + shuffledCards);
	printf("Coins = %d, Expected Coins = %d\n", test.coins, game.coins + newCoins);
	ASSERT(test.handCount[firstPlayer] == game.handCount[firstPlayer], "Hand Count\n");
	ASSERT(test.deckCount[firstPlayer] == game.deckCount[firstPlayer] + shuffledCards, "Deck Count\n");
	ASSERT(test.coins == game.coins + newCoins, "Coins\n");


	printf("\n ~~~~~~~~~~~ MINE TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");


	return 0;
}