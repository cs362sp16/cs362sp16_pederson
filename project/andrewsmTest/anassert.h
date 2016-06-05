#ifndef anassert
#include "stdio.h"
#include "dominion.h"

#define anassert(condition) \
{ \
	if(!(condition)) \
	{ \
		fprintf(stderr, "Assertion %s failed at &s inside %s\n",\
		(#condition),__FUNCTION__,__FILE__); \
	} \
}
#endif
