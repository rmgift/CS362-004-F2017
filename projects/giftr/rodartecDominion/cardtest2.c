/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
#define TEST_CARD "adventurer"

void switchEnumForStr(int, int, int, char*, char*);

int main() 
{
	int seed = 1000;
	int numPlayers = 2;
	int currentPlayer = 0;
	int index, bonus = 0, count = 0;
	const int numTests = 10;
	int array[numTests];
	for (index = 0; index < numTests; index++)
		array[index] = 0;
	index = 0;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState currentG, copyOfG;
	int returnVal = 0;

	returnVal = initializeGame(numPlayers, k, seed, &currentG);
	if (returnVal > 0)
		printf("Error Initializing Game Struct, Please Run Again!\n");
	
	currentG.hand[currentPlayer][0] = adventurer;
	currentG.hand[currentPlayer][1] = gold;
	currentG.hand[currentPlayer][2] = silver;
	currentG.hand[currentPlayer][3] = gold;
	currentG.hand[currentPlayer][4] = gold;
	currentG.hand[currentPlayer][5] = gold;
	currentG.hand[currentPlayer][6] = silver;
	currentG.hand[currentPlayer][7] = gold;
	currentG.hand[currentPlayer][8] = gold;
	currentG.hand[currentPlayer][9] = silver;

	memcpy(&copyOfG, &currentG, sizeof(struct gameState));
	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                            %s TESTING                               |\n", TEST_CARD);
	printf("|_____________________________________________________________________________|\n");

	returnVal = cardEffect(adventurer, 0, 0, 0, &copyOfG, 0, &bonus);
	if (returnVal != 0)
		printf("\n  Error Playing Card ... Please Run Again!\n");

	// ADVENTURER BUSINESS REQUIREMENTS
	// gain cards from deck until we've put two more teasure cards in our hand
	// all other cards drawn will be discarded
	// if deck runs out before gaining two treasures, shuffle discard and make it the deck
	
	printf("\n   Test 2.%d: Verify Current Hand Count\n", index + 1);
	printf("    Current Hand Count: %d\tExpected Hand Count: %d\n", copyOfG.handCount[currentPlayer], (currentG.handCount[currentPlayer] + 2 - 1));
	if (copyOfG.handCount[currentPlayer] != (currentG.handCount[currentPlayer] + 2 - 1))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 2.%d: Verify %s Played\n", index + 1, TEST_CARD);
	printf("    Current Played: %d\t\tExpected Played: %d\n", copyOfG.playedCards[copyOfG.playedCardCount - 1], k[0]);
	if (copyOfG.playedCards[copyOfG.playedCardCount - 1] != k[0])
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 2.%d: Verify Correct Cards were Added and Discarded\n", index + 1);
	int cardsHand = numHandCards(&currentG);
	int cardsDeck = currentG.deckCount[currentPlayer];
	int cardsDisc = currentG.discardCount[currentPlayer];
	printf("    cards in Hand %d, cards on Deck %d, cards in discard %d\n", cardsHand, cardsDeck, cardsDisc);
	if (cardsDisc == 0)
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 2.%d: Verify Player Number of Actions\n", index + 1);
	printf("    Current Actions: %d\t\tExpected Actions: %d\n", copyOfG.numActions, (currentG.numActions - 1));
	if (copyOfG.numActions != (currentG.numActions - 1))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 2.%d: Verify Player Coin Count\n", index + 1);
	printf("    Current Coins: %d\t\tExpected Coins: %d\n", copyOfG.coins, currentG.coins);
	if (copyOfG.coins != currentG.coins)
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 2.%d: Verify Player Buys Count\n", index + 1);
	printf("    Current Buys: %d\t\tExpected Buys: %d\n", copyOfG.numBuys, currentG.numBuys);
	if (copyOfG.numBuys != currentG.numBuys)
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 2.%d: Verify Current Player Score\n", index + 1);
	printf("    Current Score: %d\t\tExpected Score: %d\n", scoreFor(0, &copyOfG), scoreFor(0, &currentG));
	if (scoreFor(0, &copyOfG) != scoreFor(0, &currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;

	printf("\n   Test 2.%d: Verify Other Player Score\n", index + 1);
	printf("    Current Score: %d\t\tExpected Score: %d\n", scoreFor(1, &copyOfG), scoreFor(1, &currentG));
	if (scoreFor(1, &copyOfG) != scoreFor(1, &currentG))
	{
		array[index] = 1;
		count++;
	}
	index++;

	char* currStr = "Current:";
	char* expectStr = "Expected:";
	// first 7 ENUM CARD are curse, estate, duchy, province, copper, silver, gold
	printf("\n   Test 2.%d: Verify Treasure and Victory Card Supply Unchanged\n", index + 1);
	int p;
	for (p = 0; p < 7; p++)
	{
		if (copyOfG.supplyCount[p] != currentG.supplyCount[p])
			array[index] = 1;
		switchEnumForStr(p, copyOfG.supplyCount[p], currentG.supplyCount[p], currStr, expectStr);
	}
	index++;

	printf("\n   Test 2.%d: Verify Kingdom Card Supply Unchanged\n", index + 1);
	for (p = 0; p < 10; p++)
	{
		if (supplyCount(k[p], &copyOfG) != supplyCount(k[p], &currentG))
			array[index] = 1;
		switchEnumForStr(k[p], supplyCount(k[p], &copyOfG), supplyCount(k[p], &currentG), currStr, expectStr);
	}
	index++;

	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                        %s TESTING SUMMARY                           |\n", TEST_CARD);
	printf("|_____________________________________________________________________________|\n");
	printf("\n");
	for (index = 0; index < numTests; index++)
	{
		if (array[index] == 1)
			printf("    \t\t\tTest 2.%d Failed.\n", index + 1);
		else
			printf("    Test 2.%d Passed.\n", index + 1);
	}
	printf("\n    %d Out of %d Tests Passed\n", (numTests - count), numTests);

	printf(" _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                       %s TESTING COMPLETED                          |\n", TEST_CARD);
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
