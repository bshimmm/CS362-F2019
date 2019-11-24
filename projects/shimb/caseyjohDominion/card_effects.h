//
// Created by John Casey on 10/9/2019.
//

#ifndef CS362_F2019_CARD_EFFECTS_H
#define CS362_F2019_CARD_EFFECTS_H

#include "dominion.h"

int baronEffect(int currentPlayer, struct gameState *state, int choice);
int minionEffect(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2);
int ambassadorEffect(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2);
int tributeEffect(int currentPlayer, int nextPlayer, struct gameState *state);
int mineEffect(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2);

#endif //CS362_F2019_CARD_EFFECTS_H
