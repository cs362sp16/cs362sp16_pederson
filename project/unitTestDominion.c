#include<stdlib.h>
#include<stdio.h>

#include"myassert.h"
#include"dominion.h"

const int kCards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

int cardCount(struct gameState *game){
   return (game->handCount[game->whoseTurn] + game->deckCount[game->whoseTurn] + game->discardCount[game->whoseTurn]);
}

int main(){
   struct gameState *game = malloc(sizeof(struct gameState));
   initializeGame(2, (int *)kCards, 10, game);
   int loops = 30, temp1, temp2;

   printf("Starting test...\n");
   while(isGameOver(game) && loops){
      loops--;
      temp1 = cardCount(game);
      temp2 = buyCard(5, game); //buying silver
      myassert(temp2 || temp1 < cardCount(game), "Bought card but never recieved card\n");
      temp1 = game->whoseTurn;
      temp2 = endTurn(game);
      myassert(temp2 || temp1 != game->whoseTurn, "Valid endTurn that did not change whose turn it is\n");
   }

   (numFails()) ? printf("Test failed %d times\n", numFails()) : printf("Test successful\n");
   return 0;
}
