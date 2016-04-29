CFLAGS = -fpic -coverage -lm -std=c99 -w

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

#test: cardtest unittest myassert.o dominion.o dominion_tester.c interface.o rngs.o
#	gcc -o dominion_tester -g dominion_tester.c myassert.o dominion.o cardtest1.o cardtest2.o cardtest3.o cardtest4.o unittest1.o unittest2.o unittest3.o unittest4.o interface.o rngs.o $(CFLAGS)

unittest_results: cardtest unittest myassert.o dominion.o unittestresults.c interface.o rngs.o
	gcc -o unittestresults -g unittestresults.c myassert.o dominion.o cardtest1.o cardtest2.o cardtest3.o cardtest4.o unittest1.o unittest2.o unittest3.o unittest4.o interface.o rngs.o $(CFLAGS)

cardtest: cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest.h
	gcc -O -g -c cardtest1.c cardtest2.c cardtest3.c cardtest3.c cardtest4.c $(CFLAGS)

unittest: unittest1.c unittest2.c unittest3.c unittest4.c unittest.h
	gcc -O -g -c unittest1.c unittest2.c unittest3.c unittest4.c $(CFLAGS)

myassert.o: myassert.c myassert.h
	gcc -O -c myassert.c

all: playdom player unittest_results 

clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM
