#include "CIPHER.h"

#ifndef _IO
 #define _IO

typedef struct InS {
	Bool 		      if_first;
	Bool 		        if_end;
	Uchar 	content[BLOCK_128_LEN];
	struct InS * 		  next;
} Ins;


#define new_in()    	(InS * ) malloc ( sizeof(Ins) ); 


#endif
