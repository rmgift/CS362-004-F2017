/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
#define TEST_CARD "baron"

void switchEnumForStr(int, int, int, char*, char*);

int main() 
{
	int seed = 1000;
	int numPlayers = 2;
	int currentPlayer = 0;
	int index, bonus = 0, count = 0;
	const int numTests = 18;
	int array[numTests];
	for (index = 0; index < numTests; index++)
		array[index] = 0;
	index = 0;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState currentG, copyOfG, copyOption2;
	int returnVal = 0;

	char* currStr = "Current:";
	char* expectStr = "Expected:";

	returnVal = initializeGame(numPlayers, k, seed, &currentG);
	if (returnVal > 0)
		printf("Error Initializing Game Struct, Please Run Again!\n");
	
	currentG.hand[currentPlayer][0] = k[8];
	currentG.hand[currentPlayer][1] = estate;
	memcpy(&copyOfG, &currentG, sizeof(struct gameState));
	memcpy(&copyOption2, &currentG, sizeof(struct gameState));

	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                               %s TESTING                                 |\n", TEST_CARD);
	printf("|                                                                             |\n");
	printf("|               FIRST ROUND OF TESTS: DISCARD ESTATE FOR 4 COINS              |\n");
	printf("|_____________________________________________________________________________|\n");

	// first round will test discarding an estate card
	returnVal = cardEffect(adventurer, 1, 0, 0, &copyOfG, 0, &bonus);
	if (returnVal != 0)
		printf("\n  Error Playing Card ... Please Run Again!\n");

	// BARON BUSINESS REQUIREMENTS
	// automatically get +1 buy
	// then you can either discard an estate card in your hand and gain 4 coins
	// or you can gain an estate card

	printf("\n   Test 1.%d: Verify %s was Played\n", index + 1, TEST_CARD);
	printf("    Current Played: %d\t\tExpected Played: %d\n", copyOfG.playedCards[copyOfG.playedCardCount - 1], k[8]);
	if (copyOfG.playedCards[copyOfG.playedCardCount - 1] != k[8])
	{
		array[index] = 1;
		count++;
	}
	index++;

	// First check whether or not +1 buy was added
	printf("\n   Test 4.%d: Verify Player Buys Count\n", index + 1);
	printf("    Current Buys: %d\t\tExpected Buys: %d\n", copyOfG.numBuys, currentG.numBuys + 1);
	if (copyOfG.numBuys != currentG.numBuys + 1)
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Player Coin Count\n", index + 1);
	printf("    Current Coins: %d\t\tExpected Coins: %d\n", copyOfG.coins, (currentG.coins + 4));
	if (copyOfG.coins != (currentG.coins + 4))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Current Hand Count\n", index + 1);
	printf("    Current Hand Count: %d\tExpected Hand Count: %d\n", copyOfG.handCount[currentPlayer], (currentG.handCount[currentPlayer] - 1));
	if (copyOfG.handCount[currentPlayer] != (currentG.handCount[currentPlayer] - 1))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Player Number of Actions\n", index + 1);
	printf("    Current Actions: %d\t\tExpected Actions: %d\n", copyOfG.numActions, (currentG.numActions - 1));
	if (copyOfG.numActions != (currentG.numActions - 1))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Current Player Score\n", index + 1);
	printf("    Current Score: %d\t\tExpected Score: %d\n", scoreFor(0, &copyOfG), scoreFor(0, &currentG));
	if (scoreFor(0, &copyOfG) != scoreFor(0, &currentG))
	{
		printf("    Current Discard: %d\t\tExpected Discard: %d\n", copyOfG.discardCount[currentPlayer], currentG.discardCount[currentPlayer]);
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Other Player Score\n", index + 1);
	printf("    Current Score: %d\t\tExpected Score: %d\n", scoreFor(1, &copyOfG), scoreFor(1, &currentG));
	if (scoreFor(1, &copyOfG) != scoreFor(1, &currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;
	
	printf("\n   Test 4.%d: Verify Treasure and Victory Card Supply Unchanged\n", index + 1);
	int p;
	for (p = 0; p < 7; p++)
	{
		if (copyOfG.supplyCount[p] != currentG.supplyCount[p])
			array[index] = 1;
		switchEnumForStr(p, copyOfG.supplyCount[p], currentG.supplyCount[p], currStr, expectStr);
	}
	index++;

	printf("\n   Test 4.%d: Verify Kingdom Card Supply Unchanged\n", index + 1);
	for (p = 0; p < 10; p++)
	{
		if (supplyCount(k[p], &copyOfG) != supplyCount(k[p], &currentG))
			array[index] = 1;
		switchEnumForStr(k[p], supplyCount(k[p], &copyOfG), supplyCount(k[p], &currentG), currStr, expectStr);
	}
	index++;

	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                               %s TESTING                                 |\n", TEST_CARD);
	printf("|                                                                             |\n");
	printf("|             SECOND ROUND OF TESTS: GAIN ESTATE CARD BUT NO COINS            |\n");
	printf("|_____________________________________________________________________________|\n");
	
	// second round of tests will choose to gain an estate card and place it in the discard
	returnVal = cardEffect(adventurer, 0, 0, 0, &copyOption2, 0, &bonus);
	//returnVal = cardEffect(k[8], 0, 0, 0, &copyOption2, 0, &bo);
	if (returnVal != 0)
		printf("\n  Error Playing Card ... Please Run Again!\n");

	printf("\n   Test 1.%d: Verify %s was Played\n", index + 1, TEST_CARD);
	printf("    Current Played: %d\t\tExpected Played: %d\n", copyOption2.playedCards[copyOption2.playedCardCount - 1], k[8]);
	if (copyOption2.playedCards[copyOption2.playedCardCount - 1] != k[8])
	{
		array[index] = 1;
		count++;
	}
	index++;

	// First check whether or not +1 buy was added
	printf("\n   Test 4.%d: Verify Player Buys Count\n", index + 1);
	printf("    Current Buys: %d\t\tExpected Buys: %d\n", copyOption2.numBuys, currentG.numBuys + 1);
	if (copyOption2.numBuys != currentG.numBuys + 1)
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Player Coin Count\n", index + 1);
	printf("    Current Coins: %d\t\tExpected Coins: %d\n", copyOption2.coins, currentG.coins);
	if (copyOption2.coins != currentG.coins)
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Current Hand Count\n", index + 1);
	printf("    Current Hand Count: %d\tExpected Hand Count: %d\n", copyOption2.handCount[currentPlayer], (currentG.handCount[currentPlayer] - 1));
	if (copyOption2.handCount[currentPlayer] != (currentG.handCount[currentPlayer] - 1))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Player Number of Actions\n", index + 1);
	printf("    Current Actions: %d\t\tExpected Actions: %d\n", copyOption2.numActions, (currentG.numActions - 1));
	if (copyOption2.numActions != (currentG.numActions - 1))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Current Player Score\n", index + 1);
	printf("    Current Score: %d\t\tExpected Score: %d\n", scoreFor(0, &copyOption2), (scoreFor(0, &currentG) + 1));
	if (scoreFor(0, &copyOption2) != (scoreFor(0, &currentG) + 1))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 4.%d: Verify Other Player Score\n", index + 1);
	printf("    Current Score: %d\t\tExpected Score: %d\n", scoreFor(1, &copyOption2), scoreFor(1, &currentG));
	if (scoreFor(1, &copyOption2) != scoreFor(1, &currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;
	
	printf("\n   Test 4.%d: Verify Treasure and Victory Card Supply Unchanged\n", index + 1);
	for (p = 0; p < 7; p++)
	{
		if (copyOption2.supplyCount[p] != currentG.supplyCount[p])
			array[index] = 1;
		switchEnumForStr(p, copyOption2.supplyCount[p], currentG.supplyCount[p], currStr, expectStr);
	}
	index++;

	printf("\n   Test 4.%d: Verify Kingdom Card Supply Unchanged\n", index + 1);
	for (p = 0; p < 10; p++)
	{
		if (supplyCount(k[p], &copyOption2) != supplyCount(k[p], &currentG))
			array[index] = 1;
		switchEnumForStr(k[p], supplyCount(k[p], &copyOption2), supplyCount(k[p], &currentG), currStr, expectStr);
	}
	index++;


	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                           %s TESTING SUMMARY                             |\n", TEST_CARD);
	printf("|_____________________________________________________________________________|\n");
	printf("\n");
	for (index = 0; index < numTests; index++)
	{
		if (array[index] == 1)
			printf("    \t\t\tTest 4.%d Failed.\n", index + 1);
		else
			printf("    Test 4.%d Passed.\n", index + 1);
	}
	printf("\n    %d Out of %d Tests Passed\n", (numTests - count), numTests);

	printf(" _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                         %s TESTING COMPLETED                             |\n", TEST_CARD);
	printf("|_____________________________________________________________________________|\n\n");

	return 0;
}


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
