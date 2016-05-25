#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

#include"myassert.h"
#include"dominion.h"
#include"interface.h"
#include"rngs.h"

#define BUFFER 200

const int TIMEOUT = 5, //seconds
      	  MAX_ACTIONS = 10;

int buys = 0, ends = 0, actions = 0;

enum Phase{action_, buy_, end_};

int totalCardCount(struct gameState *game, int player){
   return (numHandCards(game) + game->deckCount[player] + game->discardCount[player]);
}

int actionPhase(struct gameState *game, int randInt){
   int totalCards, card = handCard(randInt % game->handCount[game->whoseTurn], game);
   //printf("Played Card = %d\n", card);
   totalCards = fullDeckCount(game->whoseTurn, card, game);
   //printf("totalCards = %d\n", totalCards);
   return playCard(randInt % game->handCount[game->whoseTurn], 0, 0, 0, game);
}

int actionCheck(struct gameState *game, struct gameState *originalGame, int action){
   switch(action){
      case -1:
	 return ((totalCardCount(game, game->whoseTurn) == totalCardCount(originalGame, originalGame->whoseTurn)) ? 0 : 1);
      case 0:
	 return ((totalCardCount(game, game->whoseTurn) == totalCardCount(originalGame, originalGame->whoseTurn) - 1) ? 0 : 1);
   }
   return -1;
}

int buyPhase(struct gameState *game, int randInt){
   int playersCoins = countHandCoins(game->whoseTurn, game);
   int temp, availableCards[10] = {[0 ... 9] = -1};
   int cost[treasure_map + 1];
   //printf("playersCoins = %d\n", playersCoins);
   
   for(int i = 0; i <= treasure_map; i++){
      cost[i] = getCost(i);
      if(cost[i] > playersCoins) cost[i] = -1;
   }

   temp = 0;
   for(int i = 0; i < 10; i++){
      if(game->supplyCount[i] <= 0);
      else if(getCardCost(i) > playersCoins){
	 availableCards[i] = 0;
	 temp = 1;
      }
      else{
	 availableCards[i] = 1;
	 temp = 1;
      }
   }

      if(!temp) //No available cards
	 return -1;

      srand(randInt);
      /*printf("AvailableCards:");
      for(int i = 0; i < 10; i++)
	 printf(" %d", availableCards[i]);
      printf("\n");*/

      while(1){
	 temp = rand() % 10;
	 if(availableCards[temp] == 0){
	    buyCard(temp, game);
	    //printf("not enough coins\n");
	    return 1;
	 }
	 if(availableCards[temp] == 1){
	    buyCard(temp, game);
	    //printf("bought card from stack %d\n", temp);
	    return 0;
	 }
      }
   return -1;
}

int buyCheck(struct gameState *game, struct gameState *originalGame, int action){
   switch(action){
      case -1:
	 return ((totalCardCount(game, game->whoseTurn) == totalCardCount(originalGame, game->whoseTurn)) ? 0 : 1);
      case 0:
	 return ((totalCardCount(game, game->whoseTurn) == totalCardCount(originalGame, game->whoseTurn) + 1) ? 0 : 1);
      case 1:
	 return ((totalCardCount(game, game->whoseTurn) == totalCardCount(originalGame, game->whoseTurn)) ? 0 : 1);
   }
   return -1;
}

void endPhase(struct gameState *game, int randInt){
   endTurn(game);
}

int endCheck(struct gameState *game, struct gameState *originalGame){
   int player = originalGame->whoseTurn;
   player++;
   if(player >= originalGame->numPlayers)
      player = 0;
   return ((game->whoseTurn == player) ? 0 : 1);
}

int myIsGameOver(struct gameState *game){
   int k = 0;
   for(int i = 0; i < 10; i++)
      if(game->supplyCount[i] <= 0) k++;
   return ((k < 3) ? 0 : 1);
}

int scoreCheck(struct gameState *game, struct gameState *originalGame){
   int players[game->numPlayers], change = 0;
   if(getWinners(players, game)) return 1;
   for(int i = 0; i < game->numPlayers; i++){
      if(scoreFor(i, game) != scoreFor(i, originalGame)){
	 if(change > game->numPlayers) return 1;
	 change++;
      }
   }
   return 0;
}

void play(struct gameState *game, int seed){
   clock_t timer = clock();
   int temp;
   struct gameState *tempGame = malloc(sizeof(struct gameState));
   char str[BUFFER];

   while(!myIsGameOver(game) && !isGameOver(game) && (clock() - timer) / CLOCKS_PER_SEC < TIMEOUT){
      memcpy(tempGame, game, sizeof(struct gameState));
      switch(rand() % 6){
      case(action_):
//      defualt:
	 //printf("Testing action on player %d\n", game->whoseTurn);
	 temp = actionPhase(game, rand());
	 sprintf(str, "Failure in action phase with player %d\n", game->whoseTurn);
	 myassert(actionCheck(game, tempGame, temp), str);
	 actions++;
	 break;
      case(buy_):
	 //printf("Testing buying on player %d\n", game->whoseTurn);
	 temp = buyPhase(game, rand());
	 sprintf(str, "Failure in buy phase with player %d\n", game->whoseTurn);
	 myassert(buyCheck(game, tempGame, temp), str);
	 buys++;
	 break;
      case(end_):
	 //printf("Ending %d players turn\n", game->whoseTurn);
	 sprintf(str, "Failure in clean up phase with player %d\n", game->whoseTurn);
	 endPhase(game, rand());
	 myassert(endCheck(game, tempGame), str);
	 ends++;
	 }

      sprintf(str, "Failure accured in checking players scores\n");
      myassert(scoreCheck(game, tempGame), str);
   }
   if((clock() - timer) / CLOCKS_PER_SEC > TIMEOUT)
      printf("Timeout reached\n");
}

void myKingdomCards(int *cards, int randInt){
   srand(randInt);
   int duplicate;

   for(int i = 0; i < 10;){
      cards[i] = (rand() % (treasure_map + 1 - gold) + gold);
      duplicate = 0;
      for(int j = 0; j < i; j++)
	 if(cards[i] == cards[j]) duplicate++;
      if(!duplicate) {i++; printf("no dup\n");}
   }
}

int main(int argc, char *argv[]){
   //int kCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   int *kCards, tempCards[10];
   struct gameState g;
   struct gameState *game = &g;

   if(argc < 2){
      printf("Usage: %s [seed]\n", argv[0]);
      return 1;
   }

   if(atoi(argv[1]) < 0){
      srand(time(NULL));
   }
   else
      srand(atoi(argv[1]));

   selectKingdomCards(rand(), tempCards);
   kCards = kingdomCards(tempCards[0], tempCards[1], tempCards[2], tempCards[3], tempCards[4], tempCards[5], tempCards[6], tempCards[7], tempCards[8], tempCards[9]);

   /*printf("Kcards:");
   for(int i = 0; i < 10; i++)
      printf(" %d",kCards[i]);
   printf("\n");*/

   initializeGame((rand() % 3) + 2, kCards, atoi(argv[1]), game);
   
   printf("Supply count:");
   for(int i = 0; i < 10; i++)
      printf(" %d", game->supplyCount[i]);
   printf("\n");

   printf("Starting tests...\n");
   play(game, atoi(argv[1]));
   /*for(int i = 0; i < 10; i++){
      //selectKingdomCards(rand(), kCards);
      myKingdomCards(kCards, rand());
      initializeGame((rand() % 3) + 2, kCards, rand(), game);
      play(game, rand());
   }*/


   printf("Supply count:");
   for(int i = 0; i < 10; i++)
      printf(" %d", game->supplyCount[i]);
   printf("\n");

   printf("\nTests attempted:\n\t%d\tplayed cards\n\t%d\tbuys\n\t%d\tplayers turns\n", actions, buys, ends);
   (numFails()) ? printf("Test FAILED %d times\n", numFails()) : printf("Test is SUCCESSFUL\n");

   return 0;
}
