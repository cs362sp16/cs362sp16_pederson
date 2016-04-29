#ifndef _MYASSERT_
#define _MYASSERT_
#include<stdbool.h>
#include<stdio.h>

int _FAILS = 0;
int myassert(bool expression, char *string){
	if(expression){
		_FAILS++;
		printf("Failure number %d: %s", _FAILS, string);
	}
}

int numFails(){
   return _FAILS;
}
#endif
