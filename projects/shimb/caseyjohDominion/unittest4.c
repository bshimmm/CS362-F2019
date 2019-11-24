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
Unit Test #4: Tribute Card
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
	int tributeRevealCards[2];
	int currPlayer, nextPlayer, actions, cards, coins, r;
	int k[10] = { adventurer, baron, tribute, minion, great_hall, village, smithy, mine, feast, ambassador };
	struct gameState G;

	printf("TESTING tributeCardEffect():\n");
	currPlayer = 0;
	nextPlayer = 1;

#if (NOISY_TEST == 1)
	printf("TEST: Player revealing duplicate cards.\n");
#endif
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	//duplicate tribute revealed cards; treasure cards
	tributeRevealCards[0] = silver;
	tributeRevealCards[1] = silver;
	//set the deckcount and discard count for the next player
	G.discardCount[nextPlayer] = 0;
	G.deckCount[nextPlayer] = 2;
	coins = G.coins;
	//r = tributeCardEffect(&G);
	r = tributeEffect(currPlayer, nextPlayer, &G);
#if (NOISY_TEST == 1)
	printf("nextPlayer discardCount: %d, expected: 1\n", G.discardCount[nextPlayer]);
#endif
	assertFunc(G.discardCount[nextPlayer] == 1);
#if (NOISY_TEST == 1)
	printf("nextPlayer deckCount: %d, expected: 1\n", G.deckCount[nextPlayer]);
#endif
	assertFunc(G.deckCount[nextPlayer] == 1);
#if (NOISY_TEST == 1)
	printf("nextPlayer coins: %d, expected: %d\n", G.coins, coins + 2);
#endif
	assertFunc(coins + 2 == G.coins);
#if (NOISY_TEST == 1)
	printf("TEST: Player reveal 0 cards.\n");
#endif
	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayer, k, seed, &G);
	//No revealed cards
	tributeRevealCards[0] = 0;
	tributeRevealCards[0] = 0;
	//set deckCount and discardCount to 0;
	G.deckCount[nextPlayer] = 0;
	G.discardCount[nextPlayer] = 0;
	r = tributeEffect(currPlayer, nextPlayer, &G);
#if (NOISY_TEST == 1)
	printf("Revealed cards: %d, expected: 0\n", r);
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
