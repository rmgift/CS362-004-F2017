/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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

void switchEnumForStr(int, int, int, int);

int main() 
{
	int seed = 1000;
	int numPlayers = 2;	// two player game

	// enumerated card options:
	// adventurer, council_room, feast, gardens, mine, remodel, smithy, village,
	// baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo,
	// outpost, salvager, sea_hag, treasure_map

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState currentG;
	int returnVal = 0;
	returnVal = initializeGame(numPlayers, k, seed, &currentG);
	if (returnVal > 0)
		printf("Error Initializing Game Struct, Please Run Again!\n");	

	printf("\n _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                            supplyCount() TESTING                            |\n");
	printf("|_____________________________________________________________________________|\n\n");
	
	int tempSupply = 0;
	int i, sFlag = 0;
	for (i = 0; i < 27; i++)
	{
		//tempSupply = currentG.supplyCount[i];
		tempSupply = supplyCount(i, &currentG);
		// if curse card check and print
		if (i == 0 && tempSupply == 10) {
			sFlag = 0;
			switchEnumForStr(i, sFlag, tempSupply, 10);
		}
		else if (i == 0 && tempSupply != 10) {
			sFlag = 1;
			switchEnumForStr(i, sFlag, tempSupply, 10);
		}
		// estate, duchy, provice = 8
		else if ((i > 0 && i < 4) && tempSupply == 8) {
			sFlag = 0;
			switchEnumForStr(i, sFlag, tempSupply, 8);
		}
		else if ((i > 0 && i < 4) && tempSupply != 8) {
			sFlag = 1;
			switchEnumForStr(i, sFlag, tempSupply, 8);
		}
		// copper = 60 - 7 * number players
		else if (i == 4 && tempSupply == (60 - (7 * numPlayers))) {
			sFlag = 0;
			switchEnumForStr(i, sFlag, tempSupply, (60 - (7 * numPlayers)));
		}
		else if (i == 4 && tempSupply != (60 - (7 * numPlayers))) {
			sFlag = 1;
			switchEnumForStr(i, sFlag, tempSupply, (60 - (7 * numPlayers)));
		}
		// silver = 40
		else if (i == 5 && tempSupply == 40) {
			sFlag = 0;
			switchEnumForStr(i, sFlag, tempSupply, 40);
		}
		else if (i == 5 && tempSupply != 40) {
			sFlag = 1;
			switchEnumForStr(i, sFlag, tempSupply, 40);
		}
		// gold = 30
		else if (i == 6 && tempSupply == 30) {
			sFlag = 0;
			switchEnumForStr(i, sFlag, tempSupply, 30);
		}
		else if (i == 6 && tempSupply != 30) {
			sFlag = 1;
			switchEnumForStr(i, sFlag, tempSupply, 30);
		}
		// all others = 10 if in play
		else if (i > 6 && tempSupply == 10) {
			sFlag = 0;
			switchEnumForStr(i, sFlag, tempSupply, 10);
		}
		else if (i > 6 && tempSupply == -1) {
			sFlag = 2;
			switchEnumForStr(i, sFlag, tempSupply, -1);
		}
	}

	printf(" _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                       supplyCount() TESTING COMPLETED                       |\n");
	printf("|_____________________________________________________________________________|\n\n");
	
	return 0;
}

void switchEnumForStr(int val, int pfna, int curr, int expect)
{
	char* passString;
	if (pfna == 0)
		passString = "Passed.";
	else if (pfna == 1)
		passString = "Failed.";
	else if (pfna == 2)
		passString = "Unused.";
		
	switch(val)
	{
		case 0:
			printf("    Curse %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 1:
			printf("    Estate %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 2:
			printf("    Duchy %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 3:
			printf("    Province %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 4:
			printf("    Copper %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 5:
			printf("    Silver %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 6:
			printf("    Gold %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 7:
			printf("    Adventurer %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 8:
			printf("    Council_Room %s\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 9:
			printf("    Feast %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;	
		case 10:
			printf("    Gardens %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 11:
			printf("    Mine %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 12:
			printf("    Remodel %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 13:
			printf("    Smithy %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 14:
			printf("    Village %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 15:
			printf("    Baron %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 16:
			printf("    Great_Hall %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 17:
			printf("    Minion %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 18:
			printf("    Steward %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 19:
			printf("    Tribute %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;	
		case 20:
			printf("    Ambassador %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 21:
			printf("    Cutpurse %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 22:
			printf("    Embargo %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 23:
			printf("    Outpost %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 24:
			printf("    Salvager %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 25:
			printf("    Sea_Hag %s\t\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
		case 26:
			printf("    Treasure_Map %s\tCurrent: %d\tExpected:%d\n", passString, curr, expect);
			break;
	}
}
