#include "Camellia.h"

/*
 * @private fucntions' head is '__'
 *
 */

Block *
__init_Block(){
    Block * b =    (Block *) new( b , 1 ); 
    b->end    =    false;
    b->start  =    true;
    b->next   =    NULL;   
    return b;
}


Block *
new_Block(Stream data){
    Block * b =  __init_Block();
    b->start = true;

    return b;
}

int
main(int argc,const char ** argv){
    
    Stream test_ = (Stream) new ( test_,16);
    LOG(test_,"... ok\n");
    return OK; 
}





