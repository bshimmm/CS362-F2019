#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

/*
cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
*/


/*
Random Testing #1: Minion Card
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

#define NOISY_TEST 0

int main() {
	int i, j, l;
	for (i = 0; i < 10000; i++) {
		int numPlayers, seed;
		int k[10] = { adventurer, baron, tribute, minion, great_hall, village, smithy, mine, feast, ambassador };
		struct gameState G;
		int currPlayer, result, numCoins, handCount, numAction;
		bool discard, coins;
		int four_cards[4] = { 0,0,0,0 };
		int old_four_cards[4] = { 0,0,0,0 };

		printf("TESTING minionCardEffect():\n");
		seed = (rand() % 3) - 1;
		if (seed != -1) {
			seed = rand() % 10000;
		}
		numPlayers = (rand() % (4 - 1)) + 2;
		memset(&G, 23, sizeof(struct gameState));
		result = initializeGame(numPlayers, k, seed, &G);
		currPlayer = 0;
		numAction = G.numActions;
		numCoins = G.coins;
		handCount = G.handCount[currPlayer];

		//randomize coin selection
		coins = rand() % 2;
		if (coins) {
			discard = false;
		}
		else {
			discard = true;
		}
		if (discard) {
			for (j = currPlayer; j < numPlayers; j++) {
				G.handCount[j] = rand() % 7;	//random selection from 7 cards
				if (j == 0 && (G.handCount[j] == 1 || G.handCount[j] == 0)) {
					G.handCount[j] = 2;	//2 coins
				}
				for (l = currPlayer; l < G.handCount[j]; l++) {
					G.hand[j][l] = minion;
				}
				if (G.handCount[j] >= 4 || j == 0) {	//+4 cards functionality
					four_cards[j] = 1;
				}
				old_four_cards[j] = G.handCount[j];
			}
			G.playedCardCount = 0;
		}
		//int minionCardEffect(struct gameState *state, int choice1, int choice2, int handPos, int currentPlayer)
		result = minionCardEffect(&G, coins, discard, 0, currPlayer);
		if (coins) {
#if (NOISY_TEST == 1)
			printf("TEST numCoins: expected = %d, actual = %d\n", numCoins + 2, G.coins);
#endif
			assertFunc(numCoins + 2 == G.coins);
#if (NOISY_TEST == 1)
			printf("TEST handCount: expected = %d, actual = %d\n", handCount - 1, G.handCount[currPlayer]);
#endif
			assertFunc(handCount - 1 == G.handCount[currPlayer]);
		}
		else {
#if (NOISY_TEST == 1)
			printf("TEST numAction: expected = %d, actual = %d\n", numAction + 1, G.numActions);
#endif
			assertFunc(numAction + 1 == G.numActions);

#if (NOISY_TEST == 1)
			printf("TEST minionCardEffect(): expected = 0, actual = %d\n", result);
#endif
			assertFunc(result == 0);
		}
		if (testFail == 1) {
			printf("%d tests failed\n", testFail);
		}
		else {
			printf("All tests passed!\n");
		}

	}
	return 0; 
}