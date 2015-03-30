#include "basiclib.h"
#include "extendlib.h"



Bool
_single_Round(Block * key,Block * left,Block * right,lambda_2 func){
    Bool if_ok = false;
    Block * tmp_block = init_Block(tmp_block);
    copy_Block(tmp_block,right);

    if_ok = copy_Block(right,left);

    func(left,key);
    
    if_ok += (add_mod_Block(left,right)    );
    if(if_ok == 2){
        return true;
    }

    return false;
}


int
main(int argc,const char ** argv){
    
    
    printf("循环测试 : >");

    String some ;
    some = (String) new (some,400);
    gets(some);
    Stream one = String2Stream(some); 
    
    Block * test_b = new_block(one);
    Block * bak_b = init_Block(bak_b);

    copy_Block(bak_b,test_b);
    block_log(test_b);
    printf("\adsd\n");
    block_log(bak_b);
   
    each_Block(test_b,(lambda) block_log);
    LEFT_SHEFT_BLOCK_CYCLE(test_b);
    each_Block(test_b,(lambda) block_log);
    printf("\n");
    printf("Mod + 测试\n");

    String test_string = "hello";
    Stream test_stream = String2Stream(test_string);
    Block * new_one  = new_block(test_stream);
    
    block_log(test_b);
    block_log(new_one);
    MOD_ADD(test_b->content,new_one->content);

    block_log(test_b);
    return OK; 
}
