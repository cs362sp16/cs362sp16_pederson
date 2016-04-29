#include"myassert.h"
#include"dominion.h"
#include<string.h>

void cutpurse_test(){
   struct gameState *state = malloc(sizeof(struct gameState)), *teststate = malloc(sizeof(struct gameState));
   state->numPlayers = 3;
   state->whoseTurn = 1;
   state->handCount[0] = 1;
   state->hand[0][0] = cutpurse;
   state->handCount[1] = 3;
   for(int i = 0; i < state->handCount[1]; i++)
      state->hand[1][i] = i;//copper is not used
   state->handCount[2] = 3;
   for(int i = 0; i < state->handCount[2]; i++)
      state->hand[2][i] = copper;

   memcpy(teststate, state, sizeof(struct gameState));

   discardCard(0, 0, state, 0);

   //discarding other players copper
   discardCard(0, 2, state, 0);
   discardCard(1, 2, state, 0);

   //nothing is done for show card
   

   cardEffect(cutpurse, 0, 0, 0, teststate, 0, 0);
   myassert(memcmp(teststate, state, sizeof(struct gameState)), "cutpurse failed\n");
}

