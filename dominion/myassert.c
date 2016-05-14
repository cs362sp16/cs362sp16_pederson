#ifndef _MYASSERT_
#define _MYASSERT_
#include<stdbool.h>
#include<stdio.h>

int _FAILS_ = 0;
void myassert(bool expression, char *string){
	if(expression){
		_FAILS_++;
		printf("Failure number %d: %s", _FAILS_, string);
	}
}

int numFails(){
   return _FAILS_;
}
#endif
