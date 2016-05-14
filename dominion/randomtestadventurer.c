#include"myassert.h"
#include"dominion.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int impliment(struct gameState *);
int initialize(struct gameState *, int *, int *);
int check(struct gameState *, struct gameState *);

const int card = adventurer;

int main(int argc, char *argv[]){
   struct gameState *state1 = malloc(sizeof(struct gameState)), 
	            *state2 = malloc(sizeof(struct gameState));
   int testseed, loops = 10000, i, handpos, bonus = 0;
   char str[100];

   if(argc > 1)
      testseed = atoi(argv[1]);
   else
      testseed = time(NULL);
   if(testseed == 0){
      printf("Seed cannot be 0.\n");
      return 1;
   }
   PutSeed((long) testseed);

   if(argc > 2)
      loops = atoi(argv[2]);

   printf("Testing adventurer %d times...\n", loops);

   for(i = 0; i < loops; i++){
//      printf("test %d\n", i + 1);
      if(initialize(state1, &handpos, &testseed))
	 printf("failed to initialize game states\n");
      else{
	 memcpy(state2, state1, sizeof(struct gameState));
	 memset(str, '\0', sizeof(char) * 100);
	 sprintf(str, "Adventure card failed (number of players = %d, handpos = %d, original deck count = %d",state1->numPlayers, handpos, state1->deckCount[state1->whoseTurn]);
//	 myassert(impliment(state1), "testing implimentation failed\n");
	 impliment(state1);
	 cardEffect(card, 0, 0, 0, state2, handpos, &bonus);
	 sprintf(str, "%s error number %d)\n",str, check(state1, state2));
	 myassert(check(state1, state2), str);
      }
   }

   (numFails()) ? printf("%d of %d tests FAILED\n", numFails(), loops) : printf("Test SUCCESSFUL\n");
   return 0;
}

int impliment(struct gameState *state){
   int temphand[MAX_HAND], handpos = 0, tresure = 0, temp;

   while(tresure < 2){
//      printf("%d\t%d\n", state->deckCount[state->whoseTurn], state->discardCount[state->whoseTurn]);
      if(!state->deckCount[state->whoseTurn] && !state->discardCount[state->whoseTurn])
         return 1;

      //if deck is empty shuffles discard into deck
      if(!state->deckCount[state->whoseTurn]){
	 while(state->discardCount[state->whoseTurn] > 0){
	    state->deck[state->whoseTurn][state->deckCount[state->whoseTurn]] = state->discard[state->whoseTurn][state->discardCount[state->whoseTurn]]; //adds top of discard pile to top of deck
	    state->deckCount[state->whoseTurn]++;
	    state->discardCount[state->whoseTurn]--;
	 }
	 shuffle(state->whoseTurn, state);
      }

     state->deckCount[state->whoseTurn]--;
     temp = state->deck[state->whoseTurn][state->deckCount[state->whoseTurn]];
     if(temp == copper || temp == silver || temp == gold){
	state->hand[state->whoseTurn][state->handCount[state->whoseTurn]] = temp;
	state->handCount[state->whoseTurn]++;
	tresure++;
     }
     else{
	temphand[handpos] = temp;
	handpos++;
     }
   }
   //placing all non-tresure drawn cards into discard
   while(handpos > 0){
      state->discard[state->whoseTurn][state->discardCount[state->whoseTurn]] = temphand[handpos];
      state->discardCount[state->whoseTurn]++;
      handpos--;
   }

   return 0;
}

int initialize(struct gameState *state, int *handpos, int *testseed){
   srand(*testseed);
   *testseed = rand();
   int i, j, tresure = 0;
   
   state->numPlayers = rand() % (MAX_PLAYERS - 2) + 2;
   state->whoseTurn = rand() % state->numPlayers + 1;

   i = state->whoseTurn;
//   for(i = 0; i < state->numPlayers; i++){
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

      //checking treasure count
      while(tresure < 2){
	 if(rand() % 2){
	    if(state->deckCount[i] == 0)
	       state->deckCount[i]++;
	    state->deck[i][rand() % state->deckCount[i]] = rand() % 3 + copper; //note: silver and gold needs to imidiatly procede copper
	    tresure++;
	 }

	 else{
	    if(state->discardCount[i] == 0)
	       state->discardCount[i]++;
	    state->discard[i][rand() % state->discardCount[i]] = rand() % 3 + copper; //note: silver and gold needs to imidiatly procede copper
	    tresure++;
	 }
      }

//      printf("tresure count = %d\n", tresure);

      //adding testing card to hand
      if(state->handCount[state->whoseTurn] < 1)
	 state->handCount[state->whoseTurn] = 1;
      *handpos = rand() % state->handCount[state->whoseTurn];
      state->hand[state->whoseTurn][*handpos] = card;
//   }

   return 0;
}

int check(struct gameState *state1, struct gameState *state2){
   int cardcount1, cardcount2, tresure1, tresure2, i;

   //checking whose turn 
   if(state1->whoseTurn != state2->whoseTurn)
      return 1;

   //checking total card count
   cardcount1 = state1->handCount[state1->whoseTurn] + state1->deckCount[state1->whoseTurn] + state1->discardCount[state1->whoseTurn];
   cardcount2 = state2->handCount[state2->whoseTurn] + state2->deckCount[state2->whoseTurn] + state2->discardCount[state2->whoseTurn];
   if(cardcount1 != cardcount2)
      return 2;

   //checking hand count
   if(state1->handCount[state1->whoseTurn] != state2->handCount[state2->whoseTurn])
      return 3;

   //checking tresure count
   tresure1 = 0;
   tresure2 = 0;
   for(i = 0; i < state1->handCount[state1->whoseTurn]; i++)
      if(state1->hand[state1->whoseTurn][i] == copper || state1->hand[state1->whoseTurn][i] == silver || state1->hand[state1->whoseTurn][i] == gold)
	 tresure1++;
   for(i = 0; i < state2->handCount[state2->whoseTurn]; i++)
      if(state2->hand[state2->whoseTurn][i] == copper || state2->hand[state2->whoseTurn][i] == silver || state2->hand[state2->whoseTurn][i] == gold)
	 tresure2++;
   if(tresure1 != tresure2)
      return 4;

   return 0;
}
