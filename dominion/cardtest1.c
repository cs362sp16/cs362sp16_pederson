#include"myassert.h"
#include"dominion.h"
#include<string.h>

void embargo_test(){
   int choice = 1;
   struct gameState *state = malloc(sizeof(struct gameState)), *testState = malloc(sizeof(struct gameState));
   state->coins = 10;
   state->supplyCount[choice] = 0;
   state->embargoTokens[choice] = 10;
   state->numPlayers = 2;
   state->handCount[1] = 3;
   state->hand[1][0] = 1;
   state->hand[1][1] = embargo;
   state->hand[1][2] = 0;
   state->discardCount[1] = 0;

   memcpy(testState, state, sizeof(struct gameState));

   state->coins = state->coins + 2;
   state->embargoTokens[choice]++;
   discardCard(1, 1, state, 1);

   Embargo(testState, 1, 1, choice);
   myassert(memcmp(state, testState, sizeof(struct gameState)), "Embargo failed\n");
}  
