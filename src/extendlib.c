#include "extendlib.h"


Bool
F(Block * left,Block* key){
    //check len 
    if (left->block_byte_len != BLOCK_64_LEN   ) {
        return false;
    }
    
}