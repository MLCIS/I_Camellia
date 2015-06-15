#include "CIPHER.h"

#ifndef _BASICLIB

    #define _BASICLIB         OK
   typedef struct Block {
        int                             size;
        int                               id;
        Bool                             end;
        Bool                           start;
        Bool                          if_eva;
        struct Block*                   next;
        struct Block*                 before;
        Uchar         content[BLOCK_128_LEN];
        //extend block
        struct Block*             left_block;    
        struct Block*            right_block;    
        int                   block_byte_len;

    }Block;

int 
countBlockFromStream(Stream );

Block*
block_get(Block* ,int );

Block *
init_Block(Block * );

Block *
init_Block_LEN(Block * b,int LEN);

Bool
copy_Block(Block * des_block,Block * res_block);

Block * 
new_block( Stream);

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

Bool
add_mod_Block(Block * dst,Block * res);

int 
block_log(Block * block);

#endif
