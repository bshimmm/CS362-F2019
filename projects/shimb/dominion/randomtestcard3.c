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
Random Testing #1: Tribute Card
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
	int i, j;
	for (i = 0; i < 10000; i++) {
		int numPlayers, seed;
		int k[10] = { adventurer, baron, tribute, minion, great_hall, village, smithy, mine, feast, ambassador };
		struct gameState G;
		int currPlayer, result, nextPlayer, numAction, handCount, numCoins;
		int nextPlayerDiscard;
		int nextPlayerDeck;
		int reveal[2];

		printf("TESTING tributeCardEffect():\n");
		seed = (rand() % 3) - 1;
		if (seed != -1) {
			seed = rand() % 10000;
		}
		numPlayers = (rand() % (4 - 1)) + 2;
		memset(&G, 23, sizeof(struct gameState));
		result = initializeGame(numPlayers, k, seed, &G);
		currPlayer = 0;
		nextPlayer = 1;

		nextPlayerDeck = rand() % 3;	
		if (nextPlayerDeck <= 1) {
			nextPlayerDiscard = rand() % 2;	//if the player has less than one card in his deck
		}
		//if the player has no cards in his deck
		if (nextPlayerDeck == 0) {
			G.deckCount[nextPlayer] = 0;
			reveal[0] = -1;
			reveal[1] = -1;
		}
		else if (nextPlayerDiscard == 0 && nextPlayerDeck == 1) {
			G.discardCount[nextPlayer] = 0;
			G.deckCount[nextPlayer] = 1;
			reveal[0] = (rand() % 26) + 1;
			reveal[1] = -1;
		}
		else {
			if (nextPlayerDiscard == 1 && nextPlayerDeck == 1) {
				G.discardCount[nextPlayer] = 1;
				G.deckCount[nextPlayer] = 1;
			}
			else {
				nextPlayerDeck = G.deckCount[nextPlayer];
				nextPlayerDiscard = G.discardCount[nextPlayer];
			}
			reveal[0] = (rand() % 26) + 1;
			reveal[1] = (rand() % 26) + 1;
		}
		numAction = G.numActions;
		handCount = G.handCount[currPlayer];
		numCoins = G.coins;
		result = tributeCardEffect(&G);

		int tribute = reveal[0];	//tribute card functionality
		if (tribute != -1) {
			if (tribute <= 6 && tribute >= 4) {
				numCoins += 2;
			}
			else if ((tribute <= 3 && tribute >= 1) || tribute == 16 || tribute == 10) {
				handCount += 2;
			}
			else {
				numAction += 2;
			}
		}
#if (NOISY_TEST == 1)
		printf("TEST numActions: expected = %d, actual = %d\n", numAction, G.numActions);
#endif
		assertFunc(numAction == G.numActions);
#if (NOISY_TEST == 1)
		printf("TEST numCoins: expected = %d, actual = %d\n", numCoins, G.coins);
#endif
		assertFunc(numCoins == G.coins);
#if (NOISY_TEST == 1)
		printf("TEST nextPlayer Discard count: expected = 1, actual = %d\n", G.discardCount[nextPlayer]);
#endif
		assertFunc(G.discardCount[nextPlayer] == 1);
#if (NOISY_TEST == 1)
		printf("TEST nextPlayer Discard count: expected = %d, actual = %d\n", tribute, G.discard[nextPlayer]);
#endif
		assertFunc(G.discard[nextPlayer][0] == tribute);
#if (NOISY_TEST == 1)
		printf("TEST nextPlayer has less than two cards in deck: expected = %d, actual = %d\n", nextPlayerDeck - 2, G.deckCount[nextPlayer]);
#endif
		assertFunc(G.deckCount[nextPlayer] == nextPlayerDeck - 2);
#if (NOISY_TEST == 1)
		printf("TEST nextPlayer has two or more cards in deck: expected = %d, actual = %d\n", nextPlayerDeck + 2, G.deckCount[nextPlayer]);
#endif
		assertFunc(G.deckCount[nextPlayer] == nextPlayerDeck + 2);
	}
	if (testFail == 1) {
		printf("%d tests failed\n", testFail);
	}
	else {
		printf("All tests passed!\n");
	}
	return 0;
}