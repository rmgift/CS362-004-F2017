CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#cardTests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	#gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	#gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	#gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	#gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

#unitTests: unittest1.c dominion.o rngs.o
	#gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	#gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	#gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	#gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

myUnitTests: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	#use gcov -b -f option for all branch probabilities
	echo "Results for running Assignment 3 Unit Tests:" > unittestresults.out

	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	#gcov -b -f dominion.c >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	#gcov -b -f dominion.c >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 2 >> unittestresults.out
	#gcov -b -f dominion.c >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 2 >> unittestresults.out
	#gcov -b -f dominion.c >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 2 >> unittestresults.out
	#gcov -b -f dominion.c >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	#gcov -b -f dominion.c >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	#gcov -b -f dominion.c >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	#gcov -b -f dominion.c >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out

	cat dominion.c.gcov >> unittestresults.out

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 myUnitTests

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
