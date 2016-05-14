CFLAGS = -fpic -coverage -lm -std=c99 -w
SEED = 100
LOOPS = 10000

.PHONY:

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

unittest_results: cardtest unittest myassert.o dominion.o unittestresults.c interface.o rngs.o
	gcc -o unittestresults -g unittestresults.c myassert.o dominion.o cardtest1.o cardtest2.o cardtest3.o cardtest4.o unittest1.o unittest2.o unittest3.o unittest4.o interface.o rngs.o $(CFLAGS)

cardtest: cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest.h
	gcc -O -g -c cardtest1.c cardtest2.c cardtest3.c cardtest3.c cardtest4.c $(CFLAGS)

unittest: unittest1.c unittest2.c unittest3.c unittest4.c unittest.h
	gcc -O -g -c unittest1.c unittest2.c unittest3.c unittest4.c $(CFLAGS)

myassert.o: myassert.c myassert.h
	gcc -O -c myassert.c

randomtest: randomtestadventurer randomtestcard1 randomtestcard2 .PHONY

randomtestadventurer: randomtestadventurer.c myassert.o dominion.o rngs.o .PHONY
	gcc -o randomtestadventurer randomtestadventurer.c myassert.o dominion.o rngs.o $(CFLAGS)
	randomtestadventurer $(SEED) $(LOOPS) > randomtestadventurer.out
	echo "" >> randomtestadventurer.out
	echo "---------------------------" >> randomtestadventurer.out
	echo "" >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out

randomtestcard1: myassert.o dominion.o rngs.o randomtestcard1.c .PHONY
	gcc -o randomtestcard1 randomtestcard1.c myassert.o dominion.o rngs.o $(CFLAGS)
	randomtestcard1 $(SEED) $(LOOPS) > randomtestcard1.out
	echo "" >> randomtestcard1.out
	echo "---------------------------" >> randomtestcard1.out
	echo "" >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out

randomtestcard2: myassert.o dominion.o rngs.o randomtestcard2.c .PHONY
	gcc -o randomtestcard2 randomtestcard2.c myassert.o dominion.o rngs.o $(CFLAGS)
	randomtestcard2 $(SEED) $(LOOPS) > randomtestcard2.out
	echo "" >> randomtestcard2.out
	echo "---------------------------" >> randomtestcard2.out
	echo "" >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out


all: playdom player unittest_results 

clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe randomtestadventurer randomtestcard1 randomtestcard2 *.gcov *.gcda *.gcno *.so *.a *.dSYM
