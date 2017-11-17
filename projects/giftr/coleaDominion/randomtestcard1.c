/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * Required Cards: ADVENTURER
 * Selected Cards: SMITHY and VILLAGE
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <time.h>
#include <math.h>

#define TEST_CARD "smithy"
#define MAX 1000
#define NUMTESTS 8

int randomInt(int, int);
int internalSmithyEffect(int, int, int, struct gameState*);
void printStr(int, int);

int main() 
{	
	srand(time(NULL));
	
	int errorArr[NUMTESTS];
	int index;
	for (index = 0; index < NUMTESTS; index++)
		errorArr[index] = 0;

	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                               %s TESTING                                |\n", TEST_CARD);
	printf("|_____________________________________________________________________________|\n\n");

	
	int i, j;
	struct gameState currentG, copyOfG;	// game structs used for comparison
	int returnVal = 0;	// local variable to make sure function calls works
	int seed;
	int numPlayers = 2, currentPlayer = 0;
	// enumerated card options:
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	for (i = 0; i < MAX; i++)
	{
		index = 0;
		// randomize seed and number of players for each iteration
		//seed = 1000;
		//seed = floor(Random() * seed);
		seed = rand(); // seed a random number
		numPlayers = randomInt(4, 2);
		//printf("Starting Test #%d\n", i + 1);
		returnVal = initializeGame(numPlayers, k, seed, &currentG);
		if (returnVal > 0)
		{
			errorArr[index] += 1;
			//printf("Error Initializing Game Struct, Please Run Again!\n");
		}
		index++;
		// set the current player to a random player
		currentPlayer = floor(Random() * currentG.numPlayers);
		currentG.whoseTurn = currentPlayer;
		// set the hand, deck and discard count to a random cards
		currentG.handCount[currentPlayer] = floor(Random() * 26);
		currentG.deckCount[currentPlayer] = floor(Random() * 26);
		currentG.discardCount[currentPlayer] = floor(Random() * 26);

		// fill the hand, deck, and discard piles with random cards
		int p;
		for (p = 0; p < currentG.handCount[currentPlayer]; p++)
			currentG.hand[currentPlayer][p] = floor(Random() * 26);
		for (p = 0; p < currentG.deckCount[currentPlayer]; p++)
			currentG.deck[currentPlayer][p] = floor(Random() * 26);
		for (p = 0; p < currentG.discardCount[currentPlayer]; p++)
			currentG.discard[currentPlayer][p] = floor(Random() * 26);
		
		// set the first card to the appropriate smithy card
		currentG.hand[currentPlayer][0] = k[6];

		memcpy(&copyOfG, &currentG, sizeof(struct gameState));
		
		// play the card on the copied game state
		returnVal = playCard(0, 0, 0, 0, &copyOfG);
		if (returnVal != 0)
		{
			errorArr[index] += 1;
			//printf("\n  Error Playing Card with playCard() function ... Please Run Again!\n");
		}
		index++;
		
		// play the card on the current game state using the internal smithy function
		returnVal = internalSmithyEffect(0, currentPlayer, 0, &currentG);
		if (returnVal != 0)
		{
			errorArr[index] += 1;
			//printf("\n  Error Playing Card with internal function ... Please Run Again!\n");
		}
		index++;
		
		// test handCount
		if (copyOfG.handCount[currentPlayer] != currentG.handCount[currentPlayer])
			errorArr[index] += 1;
		index++;
		// test actions
		if (copyOfG.numActions != currentG.numActions)
			errorArr[index] += 1;
		index++;
		// test coin 
		if(copyOfG.coins != currentG.coins)
			errorArr[index] += 1;
		index++;
		// test buys
		if(copyOfG.numBuys != currentG.numBuys)
			errorArr[index] += 1;
		index++;
		// test scores
		if(scoreFor(currentPlayer, &copyOfG) != scoreFor(currentPlayer, &currentG))
			errorArr[index] += 1;
		index++;

		// clear out the current structs for next iteration
		for (j = 0; j < sizeof(struct gameState); j++) 
		{
			((char*)&currentG)[j] = floor(Random() * 256);
			((char*)&copyOfG)[j] = floor(Random() * 256);
		}

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
	
	return 0;
}

int randomInt(int maximum, int minimum)
{
	return (rand() % (maximum - minimum + 1) + minimum);
}

int internalSmithyEffect(int i, int currentPlayer, int handPos, struct gameState *state)
{
	//check if it is the right phase
	if (state->phase != 0)
		return -1;
	//check if player has enough actions
	if ( state->numActions < 1 )
		return -1;
	
	for (i = 0; i < 3; i++)
		drawCard(currentPlayer, state);
	discardCard(handPos, currentPlayer, state, 0);

	// decrease number of actions
	state->numActions--;
	
	return 0;
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
