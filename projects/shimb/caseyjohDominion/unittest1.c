#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "card_effects.h"

/*
cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
*/


/*
Unit Test #1: Baron Card
*/

//assert function
int testPass = 0;
int testFail = 0;

void assertFunc(bool test) {
	if (!test) {
		printf("Unit test has FAILED\n");
	}
	else {
		printf("Unit test has PASSED\n");
		testPass++;
	}
	testFail++;
}

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int seed = 10000;
	int numPlayer = 2;
	bool discard;
	int currPlayer, handCount, buys, coins, r;
	int k[10] = { adventurer, baron, tribute, minion, great_hall, village, smithy, mine, feast, ambassador };
	struct gameState G;

	printf("TESTING baronCardEffect():\n");
	currPlayer = 0;

	//TEST: Discarding an estate card
#if (NOISY_TEST == 1)
	printf("TEST: Player not discarding an estate card.\n");
#endif
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	discard = false;
	coins = G.coins;
	buys = G.numBuys;
	handCount = G.handCount[currPlayer];
	r = baronEffect(currPlayer, &G, discard);
	//TEST: Number of coins that is spent
#if (NOISY_TEST == 1)
	printf("G.coins = %d, expected = %d\n", G.coins, coins + 4);
#endif
	assertFunc(coins + 4 == G.coins);
	//TEST: Number of buys
#if (NOISY_TEST == 1)
	printf("G.numBuys = %d, expected = %d\n", G.numBuys, buys + 1);
#endif 
	assertFunc(buys + 1 == G.numBuys);

#if (NOISY_TEST == 1)
	printf("baronCardEffect() = %d, expected = 0\n", r);
#endif
	assertFunc(r == 0);

	if (testFail == 1) {
		printf("%d tests failed\n", testFail);
	}
	else {
		printf("All tests passed!\n");
	}




	return 0;
}
