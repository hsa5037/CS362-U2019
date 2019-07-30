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

//Tests the Baron card
int main(){
	printf("Initializing Baron Card Test.\n");
	//int discarded = 1;


	int *k = kingdomCards(ambassador, village, minion, gardens, smithy, tribute, baron, cutpurse, mine, outpost);
	struct gameState game;
	int players = 2;
	int seed = 1000;
	int handpos = 0;
	int bonus = 0;
	int firstPlayer = 0;
	int shuffledCards = 0;
    int handCount = 2;

	initializeGame(players, k, seed, &game);
    int p = whoseTurn(&game);
    game.handCount[0] = 2;
    int estates[2];
    estates[0] = estate;
    estates[1] = estate;
    memcpy(game.hand[0], estates, sizeof(int) * handCount);
    game.supplyCount[estate] = 10;
    

	//UNIT TEST 1: Choice1 = 1 = Buys increase by 1 and Estate card is discarded when found for +4 coins
	printf("UNIT TEST 1: Choice1 = 1 = Buys increase by 1 and Estate card is discarded when found for +4 coins\n");

	//copy game state into test case
	struct gameState test;
	memcpy(&test, &game, sizeof(struct gameState));
	int choice1 = 1;
	int choice2 = 0;
	int choice3 = 0;

	cardEffect(baron, choice1, choice2, choice3, &test, handpos, &bonus);

	int newCoins = 4;
	int buys = 1;

	printf("Hand Count = %d, Expected Count = %d\n", test.handCount[firstPlayer], game.handCount[firstPlayer] - 1);
	printf("Deck Count = %d, Expected Count = %d\n", test.deckCount[firstPlayer], game.deckCount[firstPlayer] + shuffledCards);
	printf("Coins = %d, Expected Coins = %d\n", test.coins, game.coins + newCoins);
	printf("Buys = %d, Expected Buys = %d\n", test.numBuys, game.numBuys + buys);
	ASSERT(test.handCount[firstPlayer] == game.handCount[firstPlayer]- 1, "Hand Count \n");
	ASSERT(test.deckCount[firstPlayer] == game.deckCount[firstPlayer] + shuffledCards, "Deck Count \n");
	ASSERT(test.coins == game.coins + newCoins, "Coins\n");
	ASSERT(test.numBuys == game.numBuys + buys, "Buys\n");

	printf("UNIT TEST 2: CHOICE1 = 2 = Player should gain an estate card\n");
	choice1 = 0;
	cardEffect(baron, choice1, choice2, choice3, &test, handpos, &bonus);
	int estateCount = 0;
	for (int i = 0; i <= 2; i++ ){
		if (test.hand[firstPlayer][i] == estate){
			estateCount++;
		}
	}

	printf("Estate Count = %d, Expected Count = 2\n", estateCount);
	ASSERT(estateCount == 2, "Gain Estate Card Test\n");


	printf("\n ~~~~~~~~~~~ BARON TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");


	return 0;
}
