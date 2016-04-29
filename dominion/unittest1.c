#include"myassert.h"
#include"dominion.h"
#include<string.h>
#include<stdlib.h>

void kingdomCards_test(){
   int *inputarray = malloc(10 * sizeof(int));
   int *resultarray = malloc(10 * sizeof(int));

   bzero(inputarray, strlen(inputarray));
   memcpy(resultarray, inputarray, strlen(resultarray));
   inputarray = kingdomCards(inputarray[0], inputarray[1], inputarray[2],
	 		      inputarray[3], inputarray[4], inputarray[5],
	 		      inputarray[6], inputarray[7], inputarray[8],
			      inputarray[9]);
   myassert(memcmp(inputarray, resultarray, strlen(resultarray)), "kingdomCards() had an error when inputed all zerors");

//   inputarray = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   for(int i = 0; i < 10; i++)
      inputarray[i] = i;
   memcpy(resultarray, inputarray, strlen(resultarray));
   inputarray = kingdomCards(inputarray[0], inputarray[1], inputarray[2],
      		              inputarray[3], inputarray[4], inputarray[5],
	 		      inputarray[6], inputarray[7], inputarray[8],
			      inputarray[9]);
   myassert(memcmp(inputarray, resultarray, strlen(resultarray)), "kingdomCards() had an error when inputed 0 through 9");


//   inputarray = {0 , 1, 2, 3, -1, -2, -3, -4, -5, -6};
   for(int i = 0; i < 4; i++)
      inputarray[i] = i;
   for(int i = 0; i < 6; i++)
      inputarray[i+4] = (-1) * i;

   memcpy(resultarray, inputarray, strlen(resultarray));
   inputarray = kingdomCards(inputarray[0], inputarray[1], inputarray[2],
			      inputarray[3], inputarray[4], inputarray[5],
	 		      inputarray[6], inputarray[7], inputarray[8],
			      inputarray[9]);
   myassert(memcmp(inputarray, resultarray, strlen(resultarray)), "kingdomCards() had an error when inputed -6 throuth 3 out of order");
}
