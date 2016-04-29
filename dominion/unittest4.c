#include"myassert.h"
#include"dominion.h"

void getWinner_test(){
   struct gameState *state = malloc(sizeof(struct gameState));
   state->numPlayers = 2;
   state->whoseTurn = 1;
   int players[state->numPlayers], test[MAX_PLAYERS];
   int temp;

   //assigning cards
   state->discardCount[0] = 0;
   
   state->handCount[0] = 3;
   for(int i = 0; i < state->handCount[0]; i++)
   	state->hand[0][i] = curse;

   state->deckCount[0] = 0;

   state->discardCount[1] = 3;
   for (int i = 0;  i < state->discardCount[1]; i++)
     state->discard[1][i] = curse;

   state->handCount[1] = 0;
   state->deckCount[1] = 0;
   
   //totaling up points
   for(int i = 0; i < state->numPlayers; i++){
      players[i] = scoreFor(i, state);
      if(i > state->numPlayers)
	 players[i]++;
   }

   //finding max score
   temp = 0;
   for(int i = 0; i < state->numPlayers; i++)
      temp = fmax(temp, players[i]);

   //setting winers to 1 and losers to 0
   for(int i = 0; i < state->numPlayers; i++){
      if(players[i] == temp)
	 players[i] = 1;
      else 
	 players[i] = 0;
   }

   getWinners(test, state);
   myassert(memcmp(players, test, state->numPlayers), "getWinner test failed\n"); 
}

