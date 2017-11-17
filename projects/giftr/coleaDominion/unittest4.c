/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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

//void switchEnumForStr(int, int, int);
void switchEnumForStr(int, int, int, char*, char*);

int main() 
{	
	int seed = 1000;
	int numPlayers = 2;	// two player game
	//int currentPlayer = 0;	// identifies current player that makes decision
	int index, count = 0;
	const int numTests = 10;

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
	printf("|                             gainCard() TESTING                              |\n");
	printf("|_____________________________________________________________________________|\n\n");	

	char* currStr = "Current:";
	char* expectStr = "Expected:";
	char* copyStr = "Copied:";
	char* ogStr = "Original:";
	// then copy struct over for comparison
	memcpy(&copyOfG, &currentG, sizeof(struct gameState));

	// first verify that all supply piles initialized appropriately
	printf("\n   Check the Initial Count of Kingdom, Treasure, and Victory Cards\n\n");

	int i;	
	for (i = 0; i < 10; i++)
	{
		switchEnumForStr(k[i], supplyCount(k[i], &copyOfG), supplyCount(k[i], &currentG), copyStr, ogStr);
	}
	printf("\n");
	for (i = 0; i < 7; i ++)
	{
		switchEnumForStr(i, supplyCount(i, &copyOfG), supplyCount(i, &currentG), copyStr, ogStr);
	}

	index++;
	printf("\n\n   Unit Test 4.%d Verify Current Player\t", index);
	printf("    %s %d\t%s %d\n", copyStr, whoseTurn(&copyOfG), ogStr, whoseTurn(&currentG));
	if (whoseTurn(&copyOfG) != whoseTurn(&currentG))
	{
		array[index] = 1;
		count++;
	}

	// Note: supplyPos is enum of choosen card
	// decrease number in supply pile
	// int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
	// returned value of -1 means supply pile is empty
	// 3 Flag Options

	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|           Testing gainCard with toFlag = 0, Place Cards in Discard          |\n");
	printf("|_____________________________________________________________________________|\n\n");	

	index++;
	printf("\n   Unit Test 4.%d Remove 1 Card From Each Stack & Compare To Original\n\n", index);
	// toFlag = 0 : add to discard
	returnVal = 0;
	for (i = 0; i < 27; i++)
	{
		returnVal = gainCard(i, &copyOfG, 0, whoseTurn(&copyOfG));
		if (returnVal == 0)
			switchEnumForStr(i, (supplyCount(i, &copyOfG)), (currentG.supplyCount[i] - 1), currStr, expectStr);
	}

	index++;
	printf("\n   Unit Test 4.%d Verify Discard Count\t", index);
	printf("    %s %d\t\t%s %d\n", copyStr, copyOfG.discardCount[whoseTurn(&copyOfG)], ogStr, currentG.discardCount[whoseTurn(&currentG)]);
	if (copyOfG.discardCount[whoseTurn(&copyOfG)] != (currentG.discardCount[whoseTurn(&currentG)] + 17))
	{
		array[index] = 1;
	}

	index++;
	printf("\n   Unit Test 4.%d Verify Score Change\t", index);
	printf("    %s %d\t\t%s %d\n", copyStr, scoreFor(whoseTurn(&copyOfG), &copyOfG), ogStr, scoreFor(whoseTurn(&currentG), &currentG));


	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|            Testing gainCard with toFlag = 1, Place Cards in Deck            |\n");
	printf("|_____________________________________________________________________________|\n\n");	
	// toFlag = 1 : add to deck
	index++;
	printf("\n   Unit Test 4.%d Remove 1 Card From Each Stack & Compare To Original\n\n", index);
	returnVal = 0;
	for (i = 0; i < 27; i++)
	{
		returnVal = gainCard(i, &copyOfG, 1, whoseTurn(&copyOfG));
		if (returnVal == 0)
			switchEnumForStr(i, (supplyCount(i, &copyOfG)), (currentG.supplyCount[i] - 2), currStr, expectStr);
	}
	index++;
	printf("\n   Unit Test 4.%d Verify Deck Count\t", index);
	printf("    %s %d\t\t%s %d\n", copyStr, copyOfG.deckCount[whoseTurn(&copyOfG)], ogStr, currentG.deckCount[whoseTurn(&currentG)]);
	if (copyOfG.deckCount[whoseTurn(&copyOfG)] != (currentG.deckCount[whoseTurn(&currentG)] + 17))
	{
		array[index] = 1;
	}
	index++;
	printf("\n   Unit Test 4.%d Verify Score Change\t", index);
	printf("    %s %d\t\t%s %d\n", copyStr, scoreFor(whoseTurn(&copyOfG), &copyOfG), ogStr, scoreFor(whoseTurn(&currentG), &currentG));


	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|            Testing gainCard with toFlag = 2, Place Cards in Hand            |\n");
	printf("|_____________________________________________________________________________|\n\n");	
	// toFlag = 2 : add to hand
	index++;
	printf("\n   Unit Test 4.%d Check the Discard Count of Copied Game to Original\n\n", index);
	returnVal = 0;
	for (i = 0; i < 27; i++)
	{
		returnVal = gainCard(i, &copyOfG, 2, whoseTurn(&copyOfG));
		if (returnVal == 0)
			switchEnumForStr(i, (supplyCount(i, &copyOfG)), (currentG.supplyCount[i] - 3), currStr, expectStr);
	}
	index++;
	printf("\n   Unit Test 4.%d Verify Hand Count\t", index);
	printf("    %s %d\t\t%s %d\n", copyStr, copyOfG.handCount[whoseTurn(&copyOfG)], ogStr, currentG.handCount[whoseTurn(&currentG)]);
	if (copyOfG.handCount[whoseTurn(&copyOfG)] != (currentG.handCount[whoseTurn(&currentG)] + 17))
	{
		array[index] = 1;
	}
	index++;
	printf("\n   Unit Test 4.%d Verify Score Change\t", index);
	printf("    %s %d\t\t%s %d\n", copyStr, scoreFor(whoseTurn(&copyOfG), &copyOfG), ogStr, scoreFor(whoseTurn(&currentG), &currentG));
	
	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                          gainCard() TESTING SUMMARY                         |\n");
	printf("|_____________________________________________________________________________|\n");
	printf("\n");
	for (index = 0; index < numTests; index++)
	{
		if (array[index] == 1)
			printf("    \t\t\tUnit Test 4.%d Failed.\n", index + 1);
		else
			printf("    Unit Test 4.%d Passed.\n", index + 1);
	}
	printf("\n    %d Out of %d Tests Passed\n", (numTests - count), numTests);

	printf(" _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                        gainCard() TESTING COMPLETED                         |\n");
	printf("|_____________________________________________________________________________|\n\n");


	return 0;
}


//void switchEnumForStr(int val, int curr, int expect)
void switchEnumForStr(int val, int curr, int expect, char* str1, char* str2)
{
	char* passString;
	if (curr == expect)
		passString = "Passed.";
	else if (curr == -1)
		passString = "Unused.";
	else
		passString = "Failed.";
		
	switch(val)
	{
		case 0:
			printf("    Curse %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 1:
			printf("    Estate %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 2:
			printf("    Duchy %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 3:
			printf("    Province %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 4:
			printf("    Copper %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 5:
			printf("    Silver %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 6:
			printf("    Gold %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 7:
			printf("    Adventurer %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 8:
			printf("    Council_Room %s\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 9:
			printf("    Feast %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;	
		case 10:
			printf("    Gardens %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 11:
			printf("    Mine %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 12:
			printf("    Remodel %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 13:
			printf("    Smithy %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 14:
			printf("    Village %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 15:
			printf("    Baron %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 16:
			printf("    Great_Hall %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 17:
			printf("    Minion %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 18:
			printf("    Steward %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 19:
			printf("    Tribute %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;	
		case 20:
			printf("    Ambassador %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 21:
			printf("    Cutpurse %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 22:
			printf("    Embargo %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 23:
			printf("    Outpost %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 24:
			printf("    Salvager %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 25:
			printf("    Sea_Hag %s\t\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
		case 26:
			printf("    Treasure_Map %s\t%s %d\t%s %d\n", passString, str1, curr, str2, expect);
			break;
	}
}
