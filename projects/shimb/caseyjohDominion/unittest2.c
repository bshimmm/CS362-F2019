#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "rngs.h"
#include "card_effects.h"

/*
cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
*/

/*
Unit Test #2: Minion Card
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
	bool discard, coin;
	int currPlayer;
	int r;
	int k[10] = { adventurer, baron, tribute, minion, great_hall, village, smithy, mine, feast, ambassador };
	struct gameState G;

	printf("TESTING minionCardEffect():\n");
	currPlayer = 0;
	coin = true;
	discard = false;

#if(NOISY_TEST == 1)
	printf("TEST: Player drawing 4 cards.\n");
#endif
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	int coins = G.coins;
	int cards = G.handCount[currPlayer];
	int actions = G.numActions;
	//r = minionCardEffect(&G, coin, discard, 1);
	r = minionEffect(currPlayer, &G, 0, coin, discard);
#if(NOSEY_TEST == 1)
	printf("G.handCount: %d, expected: %d\n", G.handCount[currPlayer], cards - 4);
#endif
	//check to see if hand count incremented by 4
	assertFunc(cards - 4 == G.handCount[currPlayer]);
#if(NOSEY_TEST == 1)
	printf("G.actions: %d, expected: %d\n", G.numActions, actions + 1);
#endif
	//check to see if actions was incremented by 1
	assertFunc(actions + 1 == G.numActions);
#if(NOSEY_TEST == 1)
	printf("G.coins: %d, expected: %d\n", G.coins, coins + 2);
#endif
	//check to see if the coins was incremented by 2
	assertFunc(coins + 2 == G.coins);
#if (NOISY_TEST == 1)
	printf("minionCardEffect() results = %d, expected results = 0\n", r);
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