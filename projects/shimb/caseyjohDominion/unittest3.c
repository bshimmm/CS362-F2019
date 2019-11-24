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
Unit Test #3: Ambassador Card
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
	int i;
	int seed = 10000;
	int numPlayer = 2;
	int r, discard, copies, supply, gain, currPlayer;
	int k[10] = { adventurer, baron, tribute, minion, great_hall, village, smithy, mine, feast, ambassador };
	struct gameState G;

	printf("TESTING ambassadorCardEffect():\n");
	currPlayer = 0;

#if (NOISY_TEST == 1)
	printf("TEST: Discarding cards will not return to supply\n");
#endif 
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	G.handCount[currPlayer] = 2;
	G.hand[currPlayer][0] = ambassador;
	G.hand[currPlayer][1] = gardens;
	for (i = 1; i <= 3; ++i) {
		G.handCount[i] = 0;
	}
	discard = 1;
	copies = 2;
	//r = ambassadorCardEffect(&G, discard, copies, 0);
	r = ambassadorEffect(currPlayer, &G, 0, discard, copies);
#if (NOISY_TEST == 1)
	printf("G.handCount: %d, expected: 1\n", G.handCount[currPlayer]);
#endif
	assertFunc(G.handCount[i] == 0);

#if (NOISY_TEST == 1)
	printf("ambassadorCardEffect(): %d, expected: 0\n", r);
#endif
	assertFunc(r == 0);

#if (NOISY_TEST == 1)
	printf("TSET: Discarding negative num of cards\n");
#endif
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	G.handCount[currPlayer] = 2;
	G.hand[currPlayer][0] = ambassador;
	G.hand[currPlayer][1] = gardens;
	discard = 1;
	copies = -1; //assign negative num of cards
	r = ambassadorEffect(currPlayer, &G, 0, discard, copies);
#if (NOISY_TEST == 1)
	printf("G.handCount: %d, expected: -1\n", r);
#endif
	assertFunc(r == -1);

#if (NOISY_TEST == 1)
	printf("TEST: Gaining a copy of revealed card\n");
#endif
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	G.handCount[currPlayer] = 2;
	G.hand[currPlayer][0] = ambassador;
	G.hand[currPlayer][1] = gardens;
	for (i = 1; i <= 3; ++i) {	//loop through the hand count
		G.handCount[i] = 0;
	}
	gain = 1;
	supply = G.supplyCount[gardens];
	r = ambassadorEffect(currPlayer, &G, 0, discard, copies);
#if (NOISY_TEST == 1)
	printf("G.gainCard: %d, expected: 1\n", r);
#endif
	assertFunc(r == 1);
	return 0;
}
