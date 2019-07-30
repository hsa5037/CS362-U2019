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
	printf("InitializeGame Function Test.\n");
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

	//PLAYER Count 2 UNIT TEST tests whther all curse, victory, treasure card counts are correct
	printf("Curse Count = %d, Expected Count = %d\n", game.supplyCount[curse], 10);
	printf("Victory Count (Estate) = %d, Expected Count = %d\n", supplyCount(estate, &game), 8);
	printf("Victory Count (Duchy) = %d, Expected Count = %d\n", supplyCount(duchy, &game), 8);
	printf("Victory Count (Province) = %d, Expected Count = %d\n", supplyCount(province, &game), 8);
	printf("Treasure Count (Copper) = %d, Expected Count = %d\n", supplyCount(copper, &game), 46);
	printf("Treasure Count (Silver) = %d, Expected Count = %d\n", supplyCount(silver, &game), 40);
	printf("Treasure Count (Gold) = %d, Expected Count = %d\n", supplyCount(gold, &game), 30);
	ASSERT(supplyCount(curse, &game) == 10, "Curse Count\n");
	ASSERT(supplyCount(estate, &game) == 8, "Estate Count\n");
	ASSERT(supplyCount(duchy, &game) == 8, "Duchy Count\n");
	ASSERT(supplyCount(province, &game) == 8, "Province Count\n");
	ASSERT(supplyCount(copper, &game) == 46, "Copper Count\n");
	ASSERT(supplyCount(silver, &game) == 40, "Silver Count\n"); 
	ASSERT(supplyCount(gold, &game) == 30, "Gold Count\n");

	initializeGame(4, k, seed, &game);

	printf("\n ~~~~~~~~~~~ initializeGame TESTING COMPLETE ~~~~~~~~~~~~~ \n\n ");



	return 0;
}
