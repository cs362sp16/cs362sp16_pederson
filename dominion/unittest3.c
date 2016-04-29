#include<string.h>
#include"dominion.h"
#include"myassert.h"

void whoseTurn_test(){
   struct gameState *state = malloc(sizeof(struct gameState));
   char str[100];

   state->whoseTurn = 1;
   myassert(whoseTurn(state) != 1, "whoseTurn failed on turn 1\n");

   state->whoseTurn = 0;
   myassert(whoseTurn(state) != 0, "whoseTurn failed on turn 0\n");
}
