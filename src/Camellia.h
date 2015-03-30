#include "basiclib.h"

#ifndef _CAMELLIA
#define _CAMELLIA 
Block*
M(Block *);

Bool
_single_Round(Block * key,Block * left,Block * right,lambda func);

#endif