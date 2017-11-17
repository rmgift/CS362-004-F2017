/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * Required Cards: SMITHY, and ADVENTURER
 * Selected Cards: BARON, MINE, and VILLAGE
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set DEBUG_TEST to 0 to remove printfs from output
#define DEBUG_TEST 1

int main() 
{
	int seed = 1000;
	int numPlayers = 2;	// two player game
	int index, count = 0;
	const int numTests = 6;

	int array[numTests];
	for (index = 0; index < numTests; index++)
		array[index] = 0;
	index = 0;
	// enumerated card options:
	// adventurer, council_room, feast, gardens, mine, remodel, smithy, village,
	// baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo,
	// outpost, salvager, sea_hag, treasure_map
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState currentG, copyOfG;
	int returnVal = 0;

	returnVal = initializeGame(numPlayers, k, seed, &currentG);
	if (returnVal > 0)
		printf("Error Initializing Game Struct, Please Run Again!\n");

	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                          numHandCards() TESTING                             |\n");
	printf("|                                                                             |\n");
	printf("|          int numHandCards(struct gameState *state)                          |\n");
	printf("|               return state->handCount[ whoseTurn(state) ];                  |\n");
	printf("|          int whoseTurn(struct gameState *state)                             |\n");
	printf("|               return state->whoseTurn;                                      |\n");
	printf("|_____________________________________________________________________________|\n\n");

	// numHandCards = returns number of cards in the current player's hand
	// within the function is also call's whoseTurn which we must examine

	printf("\n   Unit Test 3.%d: Verify Current Player is Same in Both Game States.\n", index + 1);
	// then copy struct over for comparison
	memcpy(&copyOfG, &currentG, sizeof(struct gameState));
	printf("   Created A Copy of Game State Before Calling Any Functions.\n");
	printf("    Copied: %d\tOriginal: %d\n", whoseTurn(&copyOfG), whoseTurn(&currentG));
	if (whoseTurn(&copyOfG) != whoseTurn(&currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Unit Test 3.%d: Verify Current Player Changed\n", index + 1);
	endTurn(&copyOfG);
	printf("   Called endTurn on Copied Version of Game State.\n");
	printf("    Copied: %d\tOriginal: %d\n", whoseTurn(&copyOfG), whoseTurn(&currentG));
	if (whoseTurn(&copyOfG) ==  whoseTurn(&currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Unit Test 3.%d: Verify Hand Count Changed\n", index + 1);
	drawCard(whoseTurn(&copyOfG), &copyOfG);
	printf("   Called drawCard on Copied Version of Game State.\n");
	printf("    Copied: %d\tOriginal: %d\n", numHandCards(&copyOfG), numHandCards(&currentG));
	if (numHandCards(&copyOfG) == numHandCards(&currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Unit Test 3.%d: Verify Hand Count Changed\n", index + 1);
	discardCard(0, whoseTurn(&copyOfG), &copyOfG, 0);
	discardCard(0, whoseTurn(&copyOfG), &copyOfG, 0);
	discardCard(0, whoseTurn(&copyOfG), &copyOfG, 0);
	printf("   Called discardCard 3 times on Copied Version of Game State.\n");
	printf("    Copied: %d\tOriginal: %d\n", numHandCards(&copyOfG), numHandCards(&currentG));
	if (numHandCards(&copyOfG) == numHandCards(&currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Unit Test 3.%d: Verify Current Player Changed\n", index + 1);
	endTurn(&copyOfG);
	printf("   Called endTurn on Copied Version of Game State, Back to Player 0.\n");
	printf("    Copied: %d\tOriginal: %d\n", whoseTurn(&copyOfG), whoseTurn(&currentG));
	if (whoseTurn(&copyOfG) !=  whoseTurn(&currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Unit Test 3.%d: Verify Hand Count Changed\n", index + 1);
	printf("   Player 0 Hand Count Should Remain Unchanged in Copied State\n");
	printf("    Copied: %d\tOriginal: %d\n", numHandCards(&copyOfG), numHandCards(&currentG));
	if (numHandCards(&copyOfG) != numHandCards(&currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;


	printf(" _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                      numHandCards() TESTING SUMMARY                         |\n");
	printf("|_____________________________________________________________________________|\n");
	printf("\n");
	for (index = 0; index < numTests; index++)
	{
		if (array[index] == 1)
			printf("    \t\tUnit Test 3.%d Failed.\n", index + 1);
		else
			printf("    Unit Test 3.%d Passed.\n", index + 1);
	}
	printf("\n    %d Out of %d Tests Passed\n", (numTests - count), numTests);

	printf(" _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                     numHandCards() TESTING COMPLETED                        |\n");
	printf("|_____________________________________________________________________________|\n\n");


	return 0;
}
