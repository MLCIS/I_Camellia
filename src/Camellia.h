#include "CIPHER.h"

#ifndef _CAMELLIA

  #define _CAMELLIA 		OK
  #define BLOCK_LEN 		16
  #define BLOCK_TYPE 		40

  typedef struct Block {
	int 				size;
	int 				  id;
	Bool 				 end;
	Bool 			       start;
	Bool 		 	      if_eva;
	struct Block*   		next;
	struct Block* 		      before;
  	Uchar 		  content[BLOCK_LEN];

  }Block;

int 
countBlockFromStream(Stream );

Block*
block_get(Block* ,int );

Block *
init_Block(Block * );

Block * 
new_Block(Block  *, Stream);

Block * 
add_Block(Block * old,Block * newblock);

size_t
each_Block (Block * ,lambda callBack  );

Bool
LEFT_SHEFT_BLOCK(Block *);

Bool
LEFT_SHEFT_BLOCK_CYCLE(Block *);
Stream
__extend_stream(Stream stream);

Block *
last(Block * );

Block *
first(Block *);


#endif
