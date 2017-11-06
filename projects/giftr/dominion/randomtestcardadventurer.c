/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * Required Cards: ADVENTURER
 * Selected Cards: SMITHY, BARON, MINE, and VILLAGE
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

// set DEBUG_TEST to 0 to remove printfs from output
#define TEST_CARD "adventurer"
#define MAX 1000
#define NUMTESTS 9

int getInternalAdventurerEffect(int, int, int, int, struct gameState*);
int randomInt(int, int);
void printStr(int, int);

int main() 
{	
	srand(time(NULL));

	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                             %s TESTING                              |\n", TEST_CARD);
	printf("|_____________________________________________________________________________|\n\n");

	int errorArr[NUMTESTS];
	int index;
	for (index = 0; index < NUMTESTS; index++)
		errorArr[index] = 0;	

	int i;
	struct gameState currentG, copyOfG;	// game structs used for comparison
	int returnVal = 0;	// local variable to make sure function calls works
	int seed;
	int numPlayers = 2, currentPlayer = 0;
	int hcError = 0, hcTotal = 0;
	int drawnT = 0, z = 0, cardD = 0;
	int handP = 0, choice1 = 0, choice2 = 0, choice3 = 0;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	for (i = 0; i < MAX; i++)
	{
		index = 0;
		currentPlayer = 0;
		seed = randomInt(2000, 1000);
		numPlayers = randomInt(4, 2);

		//printf("Starting Test #%d\n", i + 1);
		returnVal = initializeGame(numPlayers, k, seed, &currentG);
		if (returnVal > 0)
		{
			errorArr[index] += 1;
			printf("Error Initializing Game Struct, Please Run Again!\n");
		}
		index++;
		// set the current player to a random player
		//currentPlayer = randomInt(numPlayers, 0);
		//currentPlayer = floor(Random() * currentG.numPlayers);
		//currentG.whoseTurn = currentPlayer;
		//currentPlayer = 0;

		//if (i % 7 == 0)
			//returnVal = endTurn(&currentG);		
		
		// set the hand, deck and discard count to random cards
		currentG.handCount[currentPlayer] = randomInt(12, 10);
		hcTotal += currentG.handCount[currentPlayer];
		currentG.deckCount[currentPlayer] = randomInt(12, 10);
		currentG.discardCount[currentPlayer] = randomInt(12, 10);

		// fill the hand, deck, and discard piles with random cards
		int p;
		for (p = 0; p < currentG.handCount[currentPlayer]; p++)
			currentG.hand[currentPlayer][p] = randomInt(26, 4);
			//currentG.hand[currentPlayer][p] = floor(Random() * 27);
		for (p = 0; p < currentG.deckCount[currentPlayer]; p++)
			currentG.deck[currentPlayer][p] = randomInt(26, 4);
			//currentG.deck[currentPlayer][p] = floor(Random() * 27);
		for (p = 0; p < currentG.discardCount[currentPlayer]; p++)
			currentG.discard[currentPlayer][p] = randomInt(26, 4);
			//currentG.discard[currentPlayer][p] = floor(Random() * 27);
		// set the first card to the appropriate smithy card
		currentG.hand[currentPlayer][0] = k[0];

		//for (p = 0; p < currentG.handCount[currentPlayer]; p++)
			//printf("%d ", currentG.hand[currentPlayer][p]);
		//printf("\n");

		// copy game state
		memcpy(&copyOfG, &currentG, sizeof(struct gameState));
		// play the card on the copied game state
		//printf("Before Playcard\n");
		//returnVal = playCard(0, 0, 0, 0, &copyOfG);
		returnVal = playCard(handP, choice1, choice2, choice3, &copyOfG);
		//printf("After Playcard\n");
		if (returnVal != 0)
		{
			errorArr[index] += 1;
			//printf("\n  Error Playing Card with playCard() function ... Please Run Again!\n");
		}
		index++;
		
		// play the card on the current game state using the internal smithy function
		//printf("Before internal call\n");
		returnVal = getInternalAdventurerEffect(currentPlayer, drawnT, z, cardD, &currentG);
		//printf("After internal call\n");
		if (returnVal != 0)
		{
			errorArr[index] += 1;
			//printf("\n  Error Playing Card with internal function ... Please Run Again!\n");
		}
		index++;

		if (copyOfG.handCount[currentPlayer] != currentG.handCount[currentPlayer])
		{
			errorArr[index] += 1;
		}
		index++;

		// test actions
		if (copyOfG.numActions != currentG.numActions)
			errorArr[index] += 1;
		index++;
		// test coins
		if(copyOfG.coins != currentG.coins)
			errorArr[index] += 1;
		index++;
		// test buys
		if(copyOfG.numBuys != currentG.numBuys)
			errorArr[index] += 1;
		index++;
		// test score
		if(scoreFor(currentPlayer, &copyOfG) != scoreFor(currentPlayer, &currentG))
			errorArr[index] += 1;
		index++;

		for (p = 0; p < currentG.handCount[currentPlayer]; p++)
		{
			if (copyOfG.hand[currentPlayer][p] != currentG.hand[currentPlayer][p])
			{
				//printf("%d, %d\n", copyOfG.hand[currentPlayer][p], currentG.hand[currentPlayer][p]);
				errorArr[index] += 1;
				hcError++;
			}
		}
		index++;

		//printf("Ending Test #%d\n\n", i + 1);
	}

	index = 0;
	
	printf("   Summary Information\n\n");
	double avg = (double)errorArr[index] / MAX;
	printf("     %d Errors Initializing Game\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;
	avg = (double)errorArr[index] / MAX;
	printf("     %d Errors Calling PlayCard() Function\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;
	avg = (double)errorArr[index] / MAX;
	printf("     %d Errors Calling Internal() Function\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;
	avg = (double)errorArr[index] / MAX;
	printf("     %d Errors with Number of Cards in Hand\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;
	avg = (double)errorArr[index] / MAX;
	printf("     %d Errors with Number of Actions Count\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;
	avg = (double)errorArr[index] / MAX;
	printf("     %d Errors with Number of Current Coins\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;
	avg = (double)errorArr[index] / MAX;
	printf("     %d Errors with Number of Current Buys\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;
	avg = (double)errorArr[index] / MAX;
	printf("     %d Errors with Current Scores for Current Player\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;
	avg = (double)errorArr[index] / MAX;
	printf("     %d Errors with Cards in Current Player Hand\n", errorArr[index]);
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);
	index++;

	printf("     %d Cards out of %d did not match in Players Hand\n", hcError, hcTotal);
	avg = (double) hcError / hcTotal;
	printf("     %0.2f Percent Error\n\n", (double)avg * 100);

	return 0;
}


int getInternalAdventurerEffect(int currentPlayer, int drawntreasure, int z, int cardDrawn, struct gameState *state)
{
	//check if it is the right phase
	if (state->phase != 0)
		return -1;
	//check if player has enough actions
	if ( state->numActions < 1 )
		return -1;
	
	int temphand[MAX_HAND];
	while(drawntreasure < 2)
	{
		if (state->deckCount[currentPlayer] < 1)
		{//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		{
			drawntreasure++;
		}
		else
		{
			temphand[z] = cardDrawn;
			state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
	}
	while(z - 1 >= 0)
	{
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z = z - 1;
	}
	return 0;
}

int randomInt(int maximum, int minimum)
{
	return (rand() % (maximum - minimum + 1) + minimum);
}

void printStr(int curr, int expect)
{
	if (curr == expect)
	{
		printf("Passed\tdominion function %d\tinternal function %d\n", curr, expect);
	}
	else
	{
		printf("Failed\tdominion function %d\tinternal function %d\n", curr, expect);
	}
}
