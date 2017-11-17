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


myRT1: randomtestcard1.c dominion.o rngs.o

	echo "Results for running Assignment 4 Random Testing 1:" > randomtestcard1.out

	echo "randomcardtest1.c:" >> randomtestcard1.out
	gcc -o rtc1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./rtc1 >> randomtestcard1.out
	gcov -f dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

myRT2: randomtestcard2.c dominion.o rngs.o

	echo "Results for running Assignment 4 Random Testing 2:" > randomtestcard2.out
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o rtc2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./rtc2 >> randomtestcard2.out
	gcov -f dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

myRT3: randomtestcard3.c dominion.o rngs.o

	echo "Results for running Assignment 4 Random Testing 3:" > randomtestcard3.out
	echo "randomtestcard3.c:" >> randomtestcard3.out
	gcc -o rtc3 -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	./rtc3 >> randomtestresults.out
	gcov -f dominion.c >> randomtestcard3.out
	cat dominion.c.gcov >> randomtestcard3.out

myRTA: randomtestcardadventurer.c dominion.o rngs.o

	echo "Results for running Assignment 4 Random Testing Adventurer:" > randomtestadventurer.out
	echo "randomtestcardadventurer.c:" >> randomtestadventurer.out
	gcc -o rtca -g randomtestcardadventurer.c dominion.o rngs.o $(CFLAGS)
	./rtca >> randomtestadventurer.out
	gcov -f dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out


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

randomTests: myRT1 myRT2 myRTA

myTests: myUnitTests randomTests

all: playdom player testDrawCard testBuyCard badTestDrawCard myUnitTests 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard badTestDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 rtc1 rtc2 rtc3 rtca
