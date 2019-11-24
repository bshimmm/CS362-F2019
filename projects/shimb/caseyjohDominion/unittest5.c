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
Unit Test #5: Mine Card
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
	int i, j;
	int discard, r;
	int handCount, expected;
	int k[10] = { adventurer, baron, tribute, minion, great_hall, village, smithy, mine, feast, ambassador };
	struct gameState G;

	printf("TESTING mineCardEffect():\n");
	int currPlayer = 0;
	//looping through the trash card and gain card 
	for (i = estate; i <= adventurer; i++) {
		for (j = estate; j <= adventurer; j++) {
#if (NOISY_TEST == 1)
			printf("TEST: trash a treasure card %d, gain a treasure card %d\n", i, j);
#endif
			memset(&G, 23, sizeof(struct gameState));
			r = initializeGame(numPlayer, k, seed, &G);
			handCount = G.handCount[currPlayer];
			discard = G.discardCount[currPlayer];
			//r = mineCardEffect(&G, i, j, 0);
			r = mineEffect(currPlayer, &G, 0, i, j);
			//if the cost of the gain card is greater than the trash card; decrement the expected value
			if (getCost(j) > getCost(i) + 3) {
				expected = -1;
			}
			else if (i < 4 || j < 4 || i > 6 || j > 6) {
				expected = -2;
			}
			else {
				expected = 0;   //
			}
#if (NOISY_TEST == 1)
			printf("G.handCount: %d, expected: %d\n", handCount - 1, G.handCount[currPlayer]);
#endif
			assertFunc(handCount - 1 == G.handCount[currPlayer]); //this tests for gaining a treasure card
#if (NOISY_TEST == 1)
			printf("G.discardCount: %d, expected: %d\n", discard + 1, G.discardCount[currPlayer]);
#endif
			assertFunc(discard + 1 == G.discardCount[currPlayer]); //this tests for discarding a treasure card
		}
	}

	if (testFail == 1) {
		printf("%d tests failed\n", testFail);
	}
	else {
		printf("All tests passed!\n");
	}
	return 0;
}