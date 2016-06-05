CFLAGS = -fpic -coverage -lm -std=c99 -Wall
LOOPS = 1000
SEED = 10
OUTPUT = results.out

tests: .PHONY myassert.o dominion.o rngs.o
	gcc -o randomTestDominion randomTestDominion.c dominion.o rngs.o myassert.o $(CFLAGS)
	gcc -o randomTestCard randomTestCard.c dominion.o rngs.o myassert.o $(CFLAGS)
	gcc -o unitTestCard unitTestCard.c dominion.o rngs.o myassert.o $(CFLAGS)
	gcc -o unitTestDominion unitTestDominion.c dominion.o rngs.o myassert.o $(CFLAGS)
	echo "randomTestDominion" > $(OUTPUT)
	randomTestDominion $(LOOPS) $(SEED) >> $(OUTPUT)
	echo >> $(OUTPUT)
	echo "randomTestCard" >> $(OUTPUT)
	randomTestCard $(LOOPS) $(SEED) >> $(OUTPUT)
	echo >> $(OUTPUT)
	echo "unitTestDominion" >> $(OUTPUT)
	unitTestDominion >> $(OUTPUT)
	echo >> $(OUTPUT)
	echo "unitTestCard" >> $(OUTPUT)
	unitTestCard >> $(OUTPUT)

.PHONY:

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

myassert.o: myassert.c myassert.h
	gcc -O -c myassert.c

clean:
	rm -rf *.o *.gcov *.gcda *.gcno randomTestDominion randomTestCard unitTestCard unitTestDominion $(OUTPUT)
