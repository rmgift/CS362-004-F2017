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

int randomInt(int, int);
int internalSmithyEffect(int, int, int, struct gameState*);
void printStr(int, int);

int main() 
{	
	srand(time(NULL));
	
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
		int choice1 = 0, choice2 = 0, choice3 = 0;
		int tempK[20] = { adventurer, council_room, feast, gardens, mine, remodel, smithy,
				 village, baron, great_hall, minion, steward, tribute, ambassador,
				 cutpurse, embargo, outpost, salvager, sea_hag, treasure_map };
		int x, idx = 0, max = 19, tempC = 0;
		while (idx < 10)
		{
			tempC = randomInt(max, 0);
			if (tempC == max)
			{
				k[idx] = tempK[tempC];
			}
			else
			{
				k[idx] = tempK[tempC];
				x = tempK[max];
				tempK[max] = tempK[tempC];
				tempK[tempC] = x;
			}
			max--;
			idx++;
		}
		// randomize seed and number of players for each iteration
		//seed = 1000;
		//seed = floor(Random() * seed);
		//seed = rand(); // seed a random number
		seed = randomInt(2000, 1000);
		numPlayers = randomInt(4, 2);
		//printf("Starting Test #%d\n", i + 1);
		returnVal = initializeGame(numPlayers, k, seed, &currentG);
		// set the current player to a random player
		//currentPlayer = floor(Random() * currentG.numPlayers);
		//currentG.whoseTurn = currentPlayer;
		// set the hand, deck and discard count to a random cards
		currentG.handCount[currentPlayer] = randomInt(26, 5);
		currentG.deckCount[currentPlayer] = randomInt(26, 5);
		currentG.discardCount[currentPlayer] = randomInt(26, 5);
		// fill the hand, deck, and discard piles with random cards
		int p;
		for (p = 0; p < currentG.handCount[currentPlayer]; p++)
			currentG.hand[currentPlayer][p] = randomInt(26, 5);
		for (p = 0; p < currentG.deckCount[currentPlayer]; p++)
			currentG.deck[currentPlayer][p] = randomInt(26, 5);
		for (p = 0; p < currentG.discardCount[currentPlayer]; p++)
			currentG.discard[currentPlayer][p] = randomInt(26, 5);

		choice1 = randomInt(3, 1);
		if (choice1 == 3)
		{
			choice1 = 0;
			choice2 = 0;
			choice3 = 1;
		}
		else if (choice1 == 2)
		{
			choice1 = 0;
			choice2 = 1;
			choice3 = 0;
		}
		else
		{
			choice1 = 1;
			choice2 = 0;
			choice3 = 0;
		}

		if (currentG.hand[currentPlayer][0] == mine)
		{
			choice1 = randomInt(26, 0);
			choice2 = randomInt(26, 0);
			choice3 = randomInt(26, 0);
		}		

		memcpy(&copyOfG, &currentG, sizeof(struct gameState));
		// play the card on the copied game state
		for (j = 0; j < copyOfG.handCount[currentPlayer]; j++)
			playCard(0, choice1, choice2, choice3, &copyOfG);
		//returnVal = playCard(0, choice1, choice2, choice3, &copyOfG);

		// cover all getCost pieces
		for (j = 0; j < 27; j++)
		{
			returnVal = getCost(j);
		}

		copyOfG.coins += 50;
		copyOfG.numBuys += 20;
		buyCard(gold, &copyOfG);
		buyCard(silver, &copyOfG);
		buyCard(copper, &copyOfG);
		buyCard(province, &copyOfG);
		buyCard(duchy, &copyOfG);
		buyCard(estate, &copyOfG); 

		//if (i % 10000 == 0)
			//printf("%d <--------------------\n", i);
		//returnVal = isGameOver(&currentG);
		//returnVal = getWinners(players[numPlayers], &currentG);
		
		// clear out the current structs for next iteration
		for (j = 0; j < sizeof(struct gameState); j++) 
		{
			((char*)&currentG)[j] = floor(Random() * 256);
			((char*)&copyOfG)[j] = floor(Random() * 256);
		}

		//printf("Ending Test #%d\n\n", i + 1);
	}
	
	return 0;
}

int randomInt(int maximum, int minimum)
{
	return (rand() % (maximum - minimum + 1) + minimum);
}

