#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

// function prototypes added for assignment 2
// each of these functions is called within the cardEffect function
// and they get the card's effect rather than processing them
// in the switch statement
int adventurerEffect(struct gameState *);
int smithyEffect(struct gameState*, int);
int treasure_mapEffect(struct gameState*, int);
int great_hallEffect(struct gameState *, int);
int council_roomEffect(struct gameState *, int);



#endif
