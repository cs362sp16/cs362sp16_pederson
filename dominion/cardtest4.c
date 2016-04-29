#include"myassert.h"
#include"dominion.h"
#include<string.h>

void outpost_test(){
   struct gameState *state = malloc(sizeof(struct gameState)), *teststate = malloc(sizeof(struct gameState));
   state->numPlayers = 2;
   state->whoseTurn = 1;
   state->outpostPlayed = 0;
   state->deckCount[1] = 2;
   state->deck[1][0] = outpost;
   state->deck[1][1] = outpost;

   memcpy(teststate, state, sizeof(struct gameState));
   discardCard(1, 1, state, 0);
   cardEffect(outpost, 0, 0, 0, teststate, 1, 0);
   myassert(memcmp(state, teststate, sizeof(struct gameState)), "outpost failed on first attempt\n");
   
   memcpy(teststate, state, sizeof(struct gameState));
   discardCard(0, 1, state, 0);
   cardEffect(outpost, 0, 0, 0, teststate, 0, 0);
   myassert(memcmp(state, teststate, sizeof(struct gameState)), "outpost failed on second attempt\n");
}
   
