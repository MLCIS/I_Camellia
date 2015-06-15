#include "Camellia.h"
#include "KG.h"

int
_Log(Stream s){
    int i =0 ;
    for (;i<16;i++){
    	printf("%x ",s[i]);
    }
    printf("\n");
    return 0;
}

int
main(int argc,const char ** argv){
    
    
    printf("循环测试 : >");

    String some ;
    some = (String) new (some,400);
    gets(some);
    Stream one = String2Stream(some); 
    
    Block * test_b = new_block(one);
    // char * a = new(a,20);
    // printf("%d\n",strlen(a) );
    // a =  (char *)malloc ( sizeof(char) * 20);
    // int te=0;
    // for(;a != ; a++){
        // te+=1;
    // }
    // if(0==NULL){
        // printf("ok\n");
    // }
    // printf("%d\n",NULL );

    // printf("%x\n",test_b->content[15] );
    // LEFT_SHEFT_BLOCK(test_b);
    // Block * bak_b = init_Block(bak_b);

    // copy_Block(bak_b,test_b);
    // block_log(test_b);
    // printf("\adsd\n");
    // block_log(bak_b);
   
    // each_Block(test_b,(lambda) block_log);
    // LEFT_SHEFT_BLOCK_CYCLE(test_b);
    // each_Block(test_b,(lambda) block_log);
    // printf("\n");
    // printf("Mod + 测试\n");

    // String test_string = "hello";
    // Stream test_stream = String2Stream(test_string);
    // Block * new_one  = new_block(test_stream);
    
    // block_log(test_b);
    // block_log(new_one);
    // MOD_ADD(test_b->content,new_one->content);

    // block_log(test_b);
    Block * cblock = new_Camellia_block(test_b);
    // block_log(cblock->LEFT);

    String key = (String) new (key,400);
    fflush(stdin);
    printf("key > :");
    gets(key);
    printf("%s\n",key);
    Stream key_one = String2Stream(key); 

    Block * key_block = new_block(key_one);


    Block * c_key_b = new_Camellia_block(key_block);
    // Log_Cammellia_block(c_key_b); 
    Block * key_a = Key_A(c_key_b);
    // Log_Cammellia_block(key_a);
    // Log_Cammellia_block(key_a->next);
    printf("single round test\n");
    Block * key1 = key_gen(1,key_a);
    Block * key2 = key_gen(2,key_a);
    Block * key3 = key_gen(3,key_a);
    Block * key4 = key_gen(4,key_a);
    
    Log_block(cblock);
    // F(cblock->left_block,key1);
    // printf("%d\n",cblock->left_block->block_byte_len);
    // printf("%d\n",key1->block_byte_len);
    Log_Cammellia_block(cblock);
    int round_count = 0;
    Bool d_or_e = false;
    printf("test cammellia : \n");
    Log_Cammellia_block(cblock);
    Block * cipher = Camellia(cblock,key_a,false);
    printf("test cammellia 2 : \n");
    Log_Cammellia_block(cipher);
    // _change(cipher);
    Block * plain = Camellia(cipher,key_a,true);
    Log_Cammellia_block(plain);

    // Log_block(key1);
    // LEFT_SHIFT_STREAM(cblock->LEFT->content);
      // block_log(cblock->LEFT);
    printf("KG : test \n");
    Stream ss = (Stream) new (ss,100);
    gets(ss);
    printf("ss : %s\n",ss);
//ss = nDSR(ss,DSR_128_CONSTANT,16);
  //  _Log(ss);
    //Stream new_s = select_2(ss) ;
    //printf("new : %s\n",new_s);
    int i =0;
    Uchar res; 
    for(;i<16; i++){
    	res = KG(ss);
	printf("output : %x \n",res);
	_Log(ss);
    }
    return OK; 
}
