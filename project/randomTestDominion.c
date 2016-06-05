#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#include"myassert.h"
#include"dominion.h"

enum phase{_buy, _action, _end};
const int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy},
	  display = 0;

int totalCards(struct gameState *game){
   return(game->handCount[game->whoseTurn] + game->deckCount[game->whoseTurn] + game->discardCount[game->whoseTurn]);
}


int main(int argc, char* argv[]){
   if(argc < 2){printf("Usage: %s loops [seed]\n", argv[0]); return 1;}
   int loops = atoi(argv[1]);
   if(argc == 2) srand(time(NULL));
   else srand(atoi(argv[2]));

   struct gameState g;
   struct gameState *game = &g;
   int numPlayers = 2, i, randNum, temp1, temp2;

   initializeGame(numPlayers, (int *)kCards, rand(), game);

   printf("Starting test...\n");

   i = 0;
   while(i < loops){
      randNum = rand() % (_end + 1);
      switch(randNum){
	 case(_buy):
	    if(display) printf("buying a card\n");
	    randNum = rand() % 10;
	    temp1 = game->supplyCount[randNum];
	    temp2 = totalCards(game);
	    if(buyCard(randNum, game)) break;
	    myassert(game->supplyCount[randNum] != temp1 - 1, "Buy Phase: Did not reduce supply Count\n");
	    myassert(totalCards(game) != temp2 + 1, "Buy Phase: Player did not gain card\n");
	    break;
	 case(_action):
	    if(display) printf("using a card\n");
	    temp1 = game->handCount[game->whoseTurn];
	    temp2 = playCard(rand() % game->handCount[game->whoseTurn], 0, 0, 0, game);
	    if(temp2 == -1) break;
	    myassert(game->handCount[game->whoseTurn] != temp1 - 1, "Action Phase: Played Card is still in players hand\n");
	    break;
	 case(_end):
	    if(display) printf("ending turn\n");
	    temp1 = game->whoseTurn;
	    temp1++;
	    if(temp1 > numPlayers - 1) temp1 = 0;
	    temp2 = endTurn(game);
	    if(temp2) break;
	    myassert(game->whoseTurn != temp1, "End Phase: Players turn did not end correctly\n");
	    break;
	 default:
	    myassert(1, "Error in test harness\n");
      }
      i++;
   }

   (numFails()) ? printf("Test failed %d times\n", numFails()) : printf("Test successful\n");

   return 0;
}
