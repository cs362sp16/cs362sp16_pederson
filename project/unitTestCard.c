#include<stdlib.h>
#include<stdio.h>

#include"myassert.h"
#include"dominion.h"

void initGame(struct gameState *game){
   game->numPlayers = 2;
   game->whoseTurn = 1;
   game->handCount[1] = 1;
   game->hand[1][0] = smithy;
   game->discardCount[1] = 10;
   game->deckCount[1] = 10;
}

int main(){
   struct gameState *game = malloc(sizeof(struct gameState));

   initGame(game);

   printf("Starting test..\n");

   cardEffect(smithy, 0, 0, 0, game, 0, NULL);

   myassert(game->handCount[1] == 3, "Wrong number of cards in hand\n");
   myassert(game->discardCount[1] == 11, "Wrong number of cards in discard\n");
   myassert(game->deckCount[1] == 7, "Wrong number of cards in deck\n");

   (numFails()) ? printf("Test failed\n") : printf("Test successful\n");
   
   return 0;
}
