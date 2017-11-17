/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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

void switchEnumForStr(int, int, int);

int main() {
	int seed = 1000;
	int numPlayers = 2;	// two player game
	//int currentPlayer = 0;	// identifies current player that makes decision
	int index = 0;

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
	printf("|                              getCost() TESTING                              |\n");
	printf("|_____________________________________________________________________________|\n\n");

	// case curse:	return 0;
	switchEnumForStr(index, getCost(index), 0);
	index++;
	//case estate: return 2;
	switchEnumForStr(index, getCost(index), 2);
	index++;	
	//case duchy: return 5;
	switchEnumForStr(index, getCost(index), 5);
	index++;	
	//case province: return 8;
	switchEnumForStr(index, getCost(index), 8);
	index++;	
	//case copper: return 0;
	switchEnumForStr(index, getCost(index), 0);
	index++;	
	//case silver: return 3;
	switchEnumForStr(index, getCost(index), 3);
	index++;	
	//case gold: return 6;
	switchEnumForStr(index, getCost(index), 6);
	index++;	
	//case adventurer: return 6;
	switchEnumForStr(index, getCost(index), 6);
	index++;	
	//case council_room: return 5;
	switchEnumForStr(index, getCost(index), 5);
	index++;	
	//case feast: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	
	//case gardens: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	
	//case mine: return 5;
	switchEnumForStr(index, getCost(index), 5);
	index++;	
	//case remodel: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	
	//case smithy: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	
	//case village: return 3;
	switchEnumForStr(index, getCost(index), 3);
	index++;	
	//case baron: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	
	//case great_hall: return 3;
	switchEnumForStr(index, getCost(index), 3);
	index++;	
	//case minion: return 5;
	switchEnumForStr(index, getCost(index), 5);
	index++;	
	//case steward: return 3;
	switchEnumForStr(index, getCost(index), 3);
	index++;	
	//case tribute: return 5;
	switchEnumForStr(index, getCost(index), 5);
	index++;	
	//case ambassador: return 3;
	switchEnumForStr(index, getCost(index), 3);
	index++;	
	//case cutpurse: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	
	//case embargo: return 2;
	switchEnumForStr(index, getCost(index), 2);
	index++;	
	//case outpost: return 5;
	switchEnumForStr(index, getCost(index), 5);
	index++;	
	//case salvager: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	
	//case sea_hag: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	
	//case treasure_map: return 4;
	switchEnumForStr(index, getCost(index), 4);
	index++;	

	printf(" _____________________________________________________________________________\n");
	printf("|                                                                             |\n");
	printf("|                         getCost() TESTING COMPLETED                         |\n");
	printf("|_____________________________________________________________________________|\n\n");

	return 0;
}

void switchEnumForStr(int val, int curr, int expect)
{
	char* passString;
	if (curr == expect)
		passString = "Passed.";
	else if (curr != expect)
		passString = "Failed.";
		
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

