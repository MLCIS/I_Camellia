#include "Camellia.h"

/*
 * @private fucntions' head is '__'
 *
 */

Stream
__extend_stream(Stream stream){
    int private_len = JUDGE(stream);

    Stream extended_stream = (Stream) new ( extended_stream ,countBlockFromStream(stream) * BLOCK_LEN);

    memmove(extended_stream,stream ,private_len);
    
    return extended_stream;
}

Block *
init_Block(Block * b){
    b = (Block * ) malloc(sizeof(Block)); 
    b->end    =    false;
    b->start  =    false;
    b->if_eva =    false;
    b->size   =    0;   
    b->next   =    NULL;   

    return b;
}

Block *
add_Block(Block * old, Block * new){
    old->next = new;
    new->size = old->size+1 ;
    return new;
}

int
countBlockFromStream(Stream stream ){

    return JUDGE(stream) / 16 +1  ; 
}

Block *
block_get(Block * block,int id){
    int _id = 0;
    for(;block->id < _id;block= block->next);
    return block; 
}

int 
i_char(Uchar * c){
    printf("%2x ",*c);
    *c -= 0x01;
    return OK;
}

Block *
new_Block(Block * old,Stream data){
    old = init_Block(old);
    data = __extend_stream(data);
    old->start = true;
    old->id =0;
    int Count = 0;
    int Round = 0;
    int round_count = 0  ;
    long data_len = JUDGE(data);
    int round_deviation = 0;
    Block * loadB = old;
    round_count = data_len / 16 ;    

    for (;Round < round_count ; Round ++){
    
        for (; Count < Round * 16 + 16; Count ++ ){
            round_deviation = Count - Round * 16;
            loadB->content[round_deviation] = data[Count];  
        }
        old->size += 1 ;        
        if( Round == round_count -1 ){
            loadB->end = true;
            
            return old;
        }else{
            Block * tempb = init_Block(tempb);
            tempb->before = loadB;
            loadB->next = tempb;
            loadB = loadB->next;
            loadB->id = loadB->before->id +1 ;

        }
    
    }
    
    return old;
}

size_t
each( void * Objects , lambda callBack ,size_t end ,size_t TYPE){
    int count = 0 ;
    Block * res;
    if (TYPE == BLOCK_TYPE){
        res = (Block * ) Objects;
    }
    
    for(; count < end  ;count++ ){
    
        if (TYPE == BLOCK_TYPE){
            callBack(res++);
        }else{
                callBack(Objects + TYPE * count );
        }
    }

    return count ;
}

size_t
each_result(void * Objects , lambdaRes callBack ,size_t end ,size_t TYPE , void * result){
    int count = 0;
    Block * res;
    if (TYPE == BLOCK_TYPE){
        res = (Block * ) Objects;
    }
    
    for(; count < end  ;count++ ){
    
    if (TYPE == BLOCK_TYPE){
        callBack(res++,result);
    }else{
            callBack(Objects + TYPE * count ,result);
    }
    }
    return count;

}

size_t
each_Block (Block * blocks , lambda callBack ){
    size_t all = blocks->size;
    for(;blocks-> end != true ;blocks = blocks->next ){
        callBack(blocks);
    
    }
    if (blocks->end == true){
        callBack(blocks);    
    }
    return all;
}

int 
block_log(Block * block){
    LOG(block->content, "ok");
     
    printf("size : %d| + :  %d ,id : %d",block->size,block->if_eva, block->id );
    printf("\n");
    return OK;
}

Bool
LEFT_SHEFT_BLOCK(Block * block){
    Uchar tmp = block->content[0];
    if ( (tmp >>7 )==1){
        block->if_eva = true;
    }

    LEFT_SHIFT_CYCLE_STREAM(block->content);
    return OK;
}
Bool
__eva_BLOCK(Block * block){
    if (block->next != NULL){
        block = block->next;
        
        if(block->if_eva == true){
            // printf("\n\n%d\n",block->id );
            block->before->content[15] += 0x1;
        }        
    }
    
    
    return true;
}

Block*
last(Block * block){
    for (;block->end != true; block= block->next);

    return block;

}

Block *
first(Block * block){
    for(;block->start != true; block= block->before);
    return block;
}

Bool
LEFT_SHEFT_BLOCK_CYCLE(Block * block){
    each_Block(block,(lambda) LEFT_SHEFT_BLOCK);
    each_Block(block,(lambda) __eva_BLOCK);


    block = last(block);

    if (first(block)->if_eva == true){
        last(block)->content[15] += 0x1;    
    }
    
    return true; 
}

int
main(int argc,const char ** argv){
    
    
    printf("循环测试 : >");

    String some ;
    some = (String) new (some,400);
    gets(some);
    Stream one = String2Stream(some); 
    
    Block * test_b = new_Block(test_b,one);
    
   
    each_Block(test_b,(lambda) block_log);
    LEFT_SHEFT_BLOCK_CYCLE(test_b);
    each_Block(test_b,(lambda) block_log);
    printf("\n");
    printf("Mod + 测试\n");

    String test_string = "hello";
    Stream test_stream = String2Stream(test_string);
    Block * new_one  = new_Block(new_one,test_stream);
    
    block_log(test_b);
    block_log(new_one);
    MOD_ADD(test_b->content,new_one->content);

    block_log(test_b);
    return OK; 
}
