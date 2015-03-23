#include "CIPHER.h"

#ifndef _CAMELLIA

  #define _CAMELLIA 		OK
  #define BLOCK_LEN 		16

  typedef struct block {
	Bool 		end;
	Bool 		start;
  	Uchar 		content[BLOCK_LEN];
	Uchar 	* 	next;
  }Block;


Block * 
new_Block(Stream);

#endif
