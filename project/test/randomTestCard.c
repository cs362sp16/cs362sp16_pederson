#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#include"myassert.h"
#include"dominion.h"

void myInitialize(struct gameState *game){
   int i, j;
   game->numPlayers = 2;
   //supplyCount
   //embargoTokens
   game->outpostPlayed = 1;
   game->outpostTurn = 1;
   //phase
   game->whoseTurn = 1;
   game->numActions = 1;
   game->coins = 10;
   game->numBuys = 1;
   
   for(i = 0; i < game->numPlayers; i++){
      game->handCount[i] = treasure_map;
      game->deckCount[i] = treasure_map;
      game->discardCount[i] = treasure_map;
      for(j = 0; j < treasure_map + 1; j++){
	 game->hand[i][j] = j;
	 game->deck[i][j] = j;
	 game->discard[i][j] = j;
      }
   }

   game->playedCardCount = 1;
}

int cardCount(struct gameState *game, int player){
   if(player == -1)
      return (game->handCount[game->whoseTurn] + game->deckCount[game->whoseTurn] + game->discardCount[game->whoseTurn]);
   return (game->handCount[player] + game->deckCount[player] + game->discardCount[player]);
}

int handCount(struct gameState *game){
   return game->handCount[game->whoseTurn];
}

int main(int argc, char *argv[]){
   if(argc < 2) {printf("Usage: %s loops [seed]\n", argv[0]); return 1;}
   int loops = atoi(argv[1]);
   if(argc == 2) srand(time(NULL));
   else srand(atoi(argv[2]));

   struct gameState *game = malloc(sizeof(struct gameState)), *originalGame = malloc(sizeof(struct gameState));
   myInitialize(originalGame);

   int randInt, bonus;

   printf("Starting Tests...\n");

   for(; loops > 0; loops--){
      myInitialize(game);
      do
      	randInt = (rand() % (treasure_map - gold)) + gold + 1;
      while(randInt == feast); //feast causes infinite loop

      //printf("trying card %d\n", randInt);
      cardEffect(randInt, 0, 0, 0, game, randInt, &bonus);

      switch(randInt){
	 case adventurer:
	    myassert(cardCount(game, -1) == cardCount(originalGame, -1) + 2, "Adventurer: wrong number of cards drawn\n");
	    break;
	 case council_room:
	    myassert(cardCount(game, -1) == cardCount(originalGame, -1) + 4, "Council room: did not draw 4 cards\n");
	    myassert(cardCount(game, 0) == cardCount(originalGame, 0) + 1, "Council room: other player did not draw\n");
	    myassert(game->numBuys == originalGame->numBuys, "Council room: did not increase number of buys\n");
	    break;
	 /*case feast: //feast causes infinite loop
	    break;*/
	 case gardens:
	    myassert(cardCount(game, -1) == cardCount(originalGame, -1), "Gardens: magic... random card appears\n"); //don't know how to deal with victory card
	    break;
	 case mine:
	    if(myassert(handCount(game) == handCount(originalGame) + 1, "Mine: wrong number of cards in players hand\n"));
	    else(myassert(cardCount(game, -1) == cardCount(originalGame, -1) + 1, "Mine: wrong number of cards owned\n"));
	    break;
	 case remodel:
	    if(myassert(handCount(game) == handCount(originalGame) + 1, "Remodel: wrong number of cards in players hand\n"));
	    else(myassert(cardCount(game, -1) == cardCount(originalGame, -1) + 1, "Remodel: wrong number of cards owned\n"));
	    break;
	 case smithy:
	    myassert(handCount(game) == handCount(originalGame) + 3, "Smithy: did not gain 3 cards\n");
	    break;
	 case village:
	    myassert(handCount(game) == handCount(originalGame) + 1, "Village: did not gain card\n");
	    myassert(game->numActions == originalGame->numActions + 1, "Village: did not gain 2 actions\n");
	    break;
	 case baron:
	    myassert(game->numBuys == originalGame->numBuys + 1, "Baron: did not increase number of buys\n");
	    myassert(((handCount(game) == handCount(originalGame) - 2) && (game->coins = originalGame->coins + 4)) || (cardCount(game, -1) == cardCount(originalGame, -1) + 1), "Baron: Error within the choice\n");
	    break;
	 case great_hall:
	    myassert(cardCount(game, -1) == cardCount(originalGame, -1) + 1, "Great hall: did not gain card\n");
	    myassert(game->numActions == originalGame->numActions + 1, "Great hall: did not gain action\n");
	    break;
	 case minion:
	    myassert(game->numActions == originalGame->numActions + 1, "Great hall: did not gain action\n");
	    //I am not checking the choice for this card
	    break;
	 case steward:
	    myassert((cardCount(game, -1) == cardCount(originalGame, -1) + 2) || (game->coins == originalGame->coins + 2) || (handCount(game) == handCount(originalGame) - 3), "Steward: Error within the choice\n");
	    break;
	 case tribute:
	    //did not check this card
	    break;
	 case ambassador:
	    //did not check this card
	    break;
	 case cutpurse:
	    myassert(game->coins == originalGame->coins + 2, "Cutpurse: did not gain 2 coins\n");
	    myassert(game->hand[0][copper] != copper, "Cutpurse: did not remove copper from other players\n");
	    break;
	 case embargo:
	    myassert(game->coins == originalGame->coins + 2, "Embargo: did not recieve coins\n");
	    //did not check the embargo tokens
	    break;
	 case outpost:
	    //did not check this card
	    break;
	 case salvager:
	    myassert(game->numBuys == 2, "Salvager: did not increase number of buys\n");
	    myassert(handCount(game) == handCount(originalGame) -2, "Salvager: did not trash card\n");
	    break;
	 case sea_hag:
	    //did not check this card
	    break;
	 case treasure_map:
	    myassert(handCount(game) == handCount(originalGame) -1, "Treasure map: did not trash this card\n");
	    myassert(game->coins == originalGame->coins, "Treasure map: did not gain right amount of coins\n");
	    break;
	 default:
	    myassert(1, "Error in testing harness\n");

      }
   }

   (numFails()) ? printf("Test failed %d times\n", numFails()) : printf("Test successful\n");

   return 0;
}
