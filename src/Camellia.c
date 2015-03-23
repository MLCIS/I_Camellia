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
    int Count = 0;
    int round_count =0 ;
    long data_len = JUDGE(data);
    for (;Count < data_len ; Count ++){
    }
    return b;
}

int
main(int argc,const char ** argv){
    
    Stream test_ = (Stream) new ( test_,16);
    LOG(test_,"... ok\n");
    printf("%d",3/2);
    return OK; 
}





