#include"myassert.h"
#include"dominion.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int impliment(struct gameState *, int);
int initialize(struct gameState *, int *, int *);
int check(struct gameState *, struct gameState *);

const int card = great_hall;

int main(int argc, char *argv[]){
   struct gameState *state1 = malloc(sizeof(struct gameState)), 
	            *state2 = malloc(sizeof(struct gameState));
   int testseed, loops = 10000, i, handpos, bonus = 0, choice1, choice2, choice3;
   char str[100];

   if(argc > 1)
      testseed = atoi(argv[1]);
   else
      testseed = time(NULL);
   srand(testseed);

   if (argc > 2)
      loops = atoi(argv[2]);

   printf("Testing great hall %d times...\n", loops);
   
   for(i = 0; i < loops; i++){
//      printf("test %d\n", i + 1);
      if(initialize(state1, &handpos, &testseed))
	 printf("failed to initialize game states\n");
      else{
	 memcpy(state2, state1, sizeof(struct gameState));
	 memset(str, '\0', sizeof(char) * 100);
	 sprintf(str, "Great hall card failed (number of players = %d, handpos = %d, original deck count = %d",state1->numPlayers, handpos, state1->deckCount[state1->whoseTurn]);
//	 myassert(impliment(state1), "testing implimentation failed\n");
	 impliment(state1, handpos);
	 cardEffect(card, 0, 0, 0, state2, handpos, &bonus);
	 sprintf(str, "%s error number %d)\n",str, check(state1, state2));
	 myassert(check(state1, state2), str);
      }
   }

   (numFails()) ? printf("%d of %d tests FAILED\n", numFails(), loops) : printf("Test SUCCESSFUL\n");

   return 0;
}

int impliment(struct gameState *state, int handPos){
   discardCard(handPos, state->whoseTurn, state, 0);
   drawCard(state->whoseTurn, state);
   state->numActions++;
   return 0;
}

int initialize(struct gameState *state, int *handpos, int *testseed){
   srand(*testseed);
   *testseed = rand();
   int i, j, tresure = 0;
   
   state->numPlayers = rand() % (MAX_PLAYERS - 2) + 2;
   state->whoseTurn = rand() % state->numPlayers + 1;

   i = state->whoseTurn;
      //setting up players hand
      state->handCount[i] = rand();
      for(j = 0; j < state->handCount[i]; j++)
	 state->hand[i][j] = rand() % treasure_map;

      //setting up players deck
      state->deckCount[i] = rand();
      for(j = 0; j < state->deckCount[i]; j++){
	 state->deck[i][j] = rand() % treasure_map;
	 if(state->deck[i][j] == copper || state->deck[i][j] == silver || state->deck[i][j] == gold)
	    tresure++;
      }

      //setting up players discard
      state->discardCount[i] = rand();
      for(j = 0; j < state->discardCount[i]; j++){
	 state->discard[i][j] = rand() % treasure_map;
	 if(state->discard[i][j] == copper || state->discard[i][j] == silver || state->discard[i][j] == gold)
	    tresure++;
      }

      //adding testing card to hand
      if(state->handCount[state->whoseTurn] < 1)
	 state->handCount[state->whoseTurn] = 1;
      *handpos = rand() % state->handCount[state->whoseTurn];
      state->hand[state->whoseTurn][*handpos] = card;

   return 0;
}

int check(struct gameState *state1, struct gameState *state2){
   int cardcount1, cardcount2;

   //checking whose turn 
   if(state1->whoseTurn != state2->whoseTurn)
      return 1;

   //checking total card count
   cardcount1 = state1->handCount[state1->whoseTurn] + state1->deckCount[state1->whoseTurn] + state1->discardCount[state1->whoseTurn];
   cardcount2 = state2->handCount[state2->whoseTurn] + state2->deckCount[state2->whoseTurn] + state2->discardCount[state2->whoseTurn];
   if(cardcount1 != cardcount2)
      return 2;

   //checking hand
   if(state1->handCount[state1->whoseTurn] != state2->handCount[state2->whoseTurn])
      return 3;

   return 0;
}
