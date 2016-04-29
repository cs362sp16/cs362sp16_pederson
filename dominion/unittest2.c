#include"myassert.h"
#include"dominion.h"

void scoreFor_test(){
   struct gameState *state = malloc(sizeof(struct gameState));
   state->numPlayers = 1;
   state->handCount[1] = 0;
   state->discardCount[1] = 0;
   state->deckCount[1] = 0;

   //assigning hand cards
   state->handCount[1] = 3;
   state->hand[1][1] = curse; //-1
   state->hand[1][2] = curse; //-1
   state->hand[1][3] = curse; //-1

   myassert(scoreFor(1, state) == -3, "scoreFor failed from hand cards\n");
   state->handCount[1] = 4;
   state->hand[1][4] = duchy; //3
   myassert(!scoreFor(1, state), "scoreFor failed from hand cards\n");

   //assigning discardCount
   state->discardCount[1] = 3;
   state->discard[1][1] = curse; //-1
   state->discard[1][2] = curse; //-1
   state->discard[1][3] = curse; //-1

   myassert(scoreFor(1, state) == -3, "scoreFor failed from discard pile\n");
   state->discardCount[1] = 4;
   state->discard[1][4] = duchy; //3
   myassert(!scoreFor(1, state), "scoreFor failed from discard pile\n");

   //assigning deckCount
   state->deckCount[1] = 3;
   state->deck[1][1] = curse; //-1
   state->deck[1][2] = curse; //-1
   state->deck[1][3] = curse; //-1

   myassert(scoreFor(1, state) == -3, "scoreFor failed from deck\n");
   state->deckCount[1] = 4;
   state->deck[1][4] = duchy; //3
   myassert(!scoreFor(1, state), "scoreFor failed from deck\n");
}

