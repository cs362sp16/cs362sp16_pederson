#include"myassert.h"
#include"dominion.h"
#include<string.h>

void steward_test(){
   int temp = 0;
   struct gameState *state = malloc(sizeof(struct gameState)), *testState = malloc(sizeof(struct gameState));
   state->numPlayers = 2;
   state->whoseTurn = 1;
   state->coins = 10;
   state->deckCount[state->whoseTurn] = 3;
   state->deck[1][0] = curse;
   state->deck[1][1] = curse;
   state->deck[1][2] = curse;
   state->handCount[state->whoseTurn] = 3;
   state->deck[1][0] = curse;
   state->deck[1][1] = curse;
   state->deck[1][2] = curse;
   state->hand[state->whoseTurn][3] = steward;//setting known steward
   
   //testing coin choice
   memcpy(testState, state, sizeof(struct gameState));
   state->coins = state->coins + 2;
   discardCard(3, state->whoseTurn, state, 1);
   cardEffect(steward, 2, 0, 0, testState, 3, &temp);
   myassert(memcmp(testState, state, sizeof(struct gameState)), "Cardeffect failed implimenting steward and picking to add coins\n");


   //testing draw card choice
   state->hand[state->whoseTurn][3] = steward;//setting known steward
   memcpy(testState, state, sizeof(struct gameState));
   drawCard(state->whoseTurn, state);
   drawCard(state->whoseTurn, state);
   discardCard(3, state->whoseTurn, state, 1);
   cardEffect(steward, 1, 0, 0, testState, 3, &temp);
   myassert(memcmp(testState, state, sizeof(struct gameState)), "Cardeffect failed implimenting steward and picking to draw cards\n");

   //testing discarding choice
   state->hand[state->whoseTurn][3] = steward;//setting known steward
   memcpy(testState, state, sizeof(struct gameState));
   discardCard(0, state->whoseTurn, state, 1);
   discardCard(0, state->whoseTurn, state, 1);
   discardCard(3, state->whoseTurn, state, 1);
   cardEffect(steward, 0, 0, 0, testState, 3, &temp);
   myassert(memcmp(testState, state, sizeof(struct gameState)), "Cardeffect failed implimenting steward and picking to discard cards\n");
}
