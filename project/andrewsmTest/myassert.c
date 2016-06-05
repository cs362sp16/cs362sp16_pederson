#ifndef _MYASSERT_
#define _MYASSERT_
#include<stdbool.h>
#include<stdio.h>

int _FAILS_ = 0;
int myassert(bool expression, char *string){
	if(expression){
		_FAILS_++;
		printf("Failure number %d: %s", _FAILS_, string);
		return 1;
	}
	return 0;
}

int numFails(){
   return _FAILS_;
}
#endif
