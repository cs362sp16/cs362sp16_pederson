#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#include"dominion.h"
#include"myassert.h"
#include"unittest.h"
#include"cardtest.h"
#include"rngs.h"
#include"interface.h"

int main(){
   int fails = numFails(), testfails = 0, testresults = 100;

   int file;
   file = open("unittestresults.out", O_WRONLY | O_CREAT, 432);
   dup2(file, 1);
   

   printf("Starting test unit\n");

   /*******************
    * unittests
    * ****************/
   printf("Startng unittest1\nTesting kindomCards function\n");
   kingdomCards_test();
   result(&fails, &testfails);

   printf("Startng unittest2\nTesting scoreFor function\n");
   scoreFor_test();
   result(&fails, &testfails);

   printf("Startng unittest3\nTesting whoseTurn function\n");
   whoseTurn_test();
   result(&fails, &testfails);

   printf("Startng unittest4\nTesting getWinner function\n");
   getWinner_test();
   result(&fails, &testfails);
   /*****************/

   /*****************
    * cardtests
    * **************/
   printf("Startng cardtest1\nTesting embargo card\n");
   embargo_test();
   result(&fails, &testfails);

   printf("Startng cardtest2\nTesting steward card\n");
   steward_test();
   result(&fails, &testfails);

   printf("Startng cardtest3\nTesting cutpurse card\n");
   cutpurse_test();
   result(&fails, &testfails);

   printf("Startng cardtest4\nTesting outpost card\n");
   outpost_test();
   result(&fails, &testfails);

   /***************/

   printf("Tests unit complete\n");

   printf("\nTest code covereage = %d\%", testresults);

   return 0;
}
   
   
void result(int *fails, int *testfails){
   if(numFails() == *fails)
      printf("Test SUCCESSFUL\n");
   else{
      *fails = numFails();
      *testfails++;
      printf("Test FAILED\n");
   }
}
