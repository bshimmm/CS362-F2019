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
Random Testing #1: Baron Card
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
	int i;
	for (i = 0; i < 10000; i++) {
		int numPlayers, seed;
		int k[10] = { adventurer, baron, tribute, minion, great_hall, village, smithy, mine, feast, ambassador };
		struct gameState G;
		int currPlayer, result, numCoins, handCount;
		bool discard;
		bool estate;

		printf("TESTING baronCardEffect():\n");

		//implementing random seed functionality
		seed = (rand() % 3) - 1;
		if (seed != -1) {
			seed = rand() % 10000; //choose a random seed between 0 and 10000
		}
		numPlayers = (rand() % (4 - 1)) + 2;	//choosing the number of random players(4)
		memset(&G, 23, sizeof(struct gameState));	
		result = initializeGame(numPlayers, k, seed, &G);	//initialize a new game
		currPlayer = 0;
		numCoins = G.coins;
		handCount = G.handCount[currPlayer];
		//result = baronCardEffect(&G, discard, currPlayer);
		result = baronEffect(currPlayer, &G, discard);
		discard = rand() % 2;	//randomize discard functionality
		if (discard) {
			estate = rand() % 2;	//randomize user selection whether they want to discard or not
			if (estate) {
#if (NOISY_TEST == 1)
				printf("TEST: Discarding an estate card\n");
#endif
				G.handCount[currPlayer] = 2;	//hold two cards
				G.hand[currPlayer][0] = baron;
				G.hand[currPlayer][1] = estate;
			}
			else {
#if (NOISY_TEST == 1)
				printf("TEST: discarding a non-existent estate card");
#endif
				G.handCount[currPlayer] = 1;
				G.hand[currPlayer][0] = baron;
			}

			
		}
		else {
#if (NOISY_TEST == 1)
			printf("TEST: Not discarding an estate card\n");
#endif
			estate = false;
			G.handCount[currPlayer] = 1;
			G.hand[currPlayer][0] = baron;
		}
		if (estate) {
#if (NOISY_TEST == 1)
			printf("TEST handCount: expected = %d, actual %d\n", handCount - 2, G.handCount[currPlayer]);
#endif
			assertFunc(G.handCount[currPlayer] == handCount - 2);
#if (NOISY_TEST == 1)
			printf("TEST numCoins: expected = %d, actual = %d\n", numCoins + 4, G.coins);
#endif
			assertFunc(numCoins + 4 == G.coins);
		}
		else {
#if (NOISY_TEST == 1)
			printf("TEST handCount: expected = %d, actual %d\n", handCount, G.handCount[currPlayer]);
#endif
			assertFunc(G.handCount[currPlayer] == handCount);
#if (NOISY_TEST == 1)
			printf("TEST estate: expected = %d, actual %d\n", estate, G.hand[currPlayer][G.handCount[currPlayer] - 1]);
#endif
			assertFunc(estate == G.hand[currPlayer][G.handCount[currPlayer] - 1]);
		}
			
//check to see if the return value is true
#if (NOISY_TEST == 1)
			printf("baronCardEffect(): %d, expected = 0\n", result);
#endif
			assertFunc(result == 0);

		
		

	}
	if (testFail == 1) {
		printf("%d tests failed\n", testFail);
	}
	else {
		printf("All tests passed!\n");
	}
	return 0;
}