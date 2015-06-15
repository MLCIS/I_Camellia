#include "Camellia.h"


Block *
new_Camellia_block(Block * primary){
    int i,i2;
    CBlock * ca_Block = (CBlock *) malloc(sizeof(CBlock));
    ca_Block->id = primary->id;
    Block * left_block = init_Block_LEN(left_block,BLOCK_64_LEN);
    Block * right_block = init_Block_LEN(left_block,BLOCK_64_LEN);
    primary->left_block = left_block;
    primary->right_block = right_block;

    for (i=0;i<8;i++){
        primary->left_block->content[i] = primary->content[i];
        primary->right_block->content[i] = primary->content[i+8];
    }

    return primary;
}


Bool
F(Block * left,Block* key){
    //check len 
    if (left->block_byte_len != BLOCK_64_LEN   ) {
        return false;
    }

    Bool res = add_mod_Block(left,key);
    _s(left);
    return res;
}

/*
    single round :include F 

    argu: key, left 64 block right 64 block

*/
Bool
_single_Round(Block * key,Block * left,Block * right,lambda_2 func){
    Bool if_ok = false;
    Block * tmp_block = init_Block(tmp_block);
    copy_Block(tmp_block,right);

    if_ok = copy_Block(right,left);
    // Log_block(right);
    // Log_block(left);
    if (!if_ok){
        printf("error in copy_Block \n");
    }
    func(left,key);
    // F(left,key);
    if_ok += (add_mod_Block(left,tmp_block)    );
    if(if_ok == 2){
        return true;
    }
    if (!if_ok){
        printf("error in mod add \n");
    }
    return false;
}



Bool
FL(Block * left,Block * key){
    int i =0;
    Stream tmp_l32 = new (tmp_l32,BLOCK_64_LEN/2);
    Stream tmp_r32 = new (tmp_r32,BLOCK_64_LEN/2);
    Stream tmp_r32_new = new (tmp_r32,BLOCK_64_LEN/2);
    Stream tmp_l32_new = new (tmp_r32,BLOCK_64_LEN/2);
    
    // copy_stream(tmp_l32,left->content,BLOCK_64_LEN/2);
    int ii=0;
    for(;ii<BLOCK_64_LEN/2;ii++){
        tmp_l32[ii] = left->content[ii];
        tmp_r32[ii] = left->content[ii+4]; 
    }


    // for (i = 4 ;i < 8 ; i ++){
    //     tmp_r32[i-4] = left->content[i]; 
    // }
    copy_stream(tmp_l32_new,tmp_l32,BLOCK_64_LEN/2);

    for (i=0;i < BLOCK_64_LEN/2 ; i ++ ){
        tmp_l32[i] &= key->content[i]; 
    }
    LEFT_SHIFT_STREAM_32(tmp_l32);
    // printf("%s\t%s\n",tmp_l32,tmp_r32);
    MOD_ADD_4(tmp_l32,tmp_r32);
    // copy_stream(tmp_l32_new,tmp_l32);


    for (i=4;i < BLOCK_64_LEN ; i ++ ){
        tmp_r32[i-4] = tmp_l32[i-4] | key->content[i]; 
    }
    MOD_ADD_4(tmp_r32,tmp_l32_new);

    for (i= 0;i < BLOCK_64_LEN; i++){
        if (i < BLOCK_64_LEN/2){
            left->content[i]= tmp_r32[i];    
        }else{
            left->content[i]= tmp_l32[i-4];    
        }
        
    }
    return true;

}

Bool
FL_1(Block * left,Block *key){
    int i =0;
    Stream tmp_l32 = new (tmp_l32,BLOCK_64_LEN/2);
    Stream tmp_r32 = new (tmp_r32,BLOCK_64_LEN/2);
    Stream tmp_r32_new = new (tmp_r32,BLOCK_64_LEN/2);
    Stream tmp_l32_new = new (tmp_r32,BLOCK_64_LEN/2);
    
    // copy_stream(tmp_l32,left->content,BLOCK_64_LEN/2);
    // for (i = 4 ;i < 8 ; i ++){
    //     tmp_r32[i-4] = left->content[i]; 
    // }

    int ii=0;
    for(;ii<BLOCK_64_LEN/2;ii++){
        tmp_l32[ii] = left->content[ii];
        tmp_r32[ii] = left->content[ii+4]; 
    }

    copy_stream(tmp_r32_new,tmp_l32,BLOCK_64_LEN/2);

    for (i=0;i < BLOCK_64_LEN/2 ; i ++ ){
        tmp_r32[i] |= key->content[i]; 
    }
    
    MOD_ADD_4(tmp_r32,tmp_l32);
    // copy_stream(tmp_l32_new,tmp_l32);


    for (i=4;i < BLOCK_64_LEN ; i ++ ){
        tmp_l32[i-4] = tmp_r32[i-4] & key->content[i]; 
    }
    LEFT_SHIFT_STREAM_32(tmp_l32);

    MOD_ADD_4(tmp_l32,tmp_r32_new);

    for (i= 0;i < BLOCK_64_LEN; i++){
        if (i < BLOCK_64_LEN/2){
            left->content[i]= tmp_r32[i];    
        }else{
            left->content[i]= tmp_l32[i-4];    
        }
        
    }
    return true;

}


Bool
_s(Block * left ){
    Stream  tmp_a   =  new (tmp_a,BLOCK_64_LEN);
    int count = 0;
    copy_stream(tmp_a,left->content,BLOCK_64_LEN);
    // LOG(left->content,"tmp");
    left->content[0] = tmp_a[5] ^ tmp_a[2];
    left->content[1] = tmp_a[6] ^ tmp_a[1];
    left->content[2] = tmp_a[7] ^ tmp_a[5] ^ tmp_a[2];
    left->content[3] = tmp_a[7] ^ tmp_a[3];
    left->content[4] = tmp_a[6] ^ tmp_a[4];
    left->content[5] = tmp_a[5] ^ tmp_a[2];
    left->content[6] = tmp_a[7] ^ tmp_a[1];
    left->content[7] = tmp_a[6] ^ tmp_a[4];

    // LOG(left->content,"ok");
    for(;count < 8; count++){
        left->content[count] = S_BOX[left->content[count]];
    } 
    
    // LOG(left->content,"tmp");
    // int i=0;
    // for (;i < 8 ; i ++){
    //     printf("%x\t",left->content[i] );    
    // 
    return true;
}

Bool
_p(Block * left){
    Stream  tmp_a   =  new (tmp_a,BLOCK_64_LEN);
    int count = 0;
    copy_stream(tmp_a,left->content,BLOCK_64_LEN);
    
     left->content[0] = tmp_a[0]  ^ tmp_a[2] ^ tmp_a[3]  ^ tmp_a[5] ^ tmp_a[6] ^ tmp_a[7]  ;
     left->content[1] = tmp_a[0] ^ tmp_a[1]  ^ tmp_a[3] ^ tmp_a[4]  ^ tmp_a[6] ^ tmp_a[7] ;
     left->content[2] = tmp_a[0] ^ tmp_a[1] ^ tmp_a[2]  ^ tmp_a[4] ^ tmp_a[5]  ^ tmp_a[7] ;
     left->content[3] =  tmp_a[1] ^ tmp_a[2] ^ tmp_a[3] ^ tmp_a[4] ^ tmp_a[5] ^ tmp_a[6] ;
     left->content[4] = tmp_a[0] ^ tmp_a[1]  ^ tmp_a[5] ^ tmp_a[6] ^ tmp_a[7] ;
     left->content[5] =  tmp_a[1] ^ tmp_a[2]  ^ tmp_a[4]  ^ tmp_a[6] ^ tmp_a[7] ;
     left->content[6] =  tmp_a[2] ^ tmp_a[3] ^ tmp_a[4] ^ tmp_a[5] ^  tmp_a[7] ;
     left->content[7] = tmp_a[0]  ^ tmp_a[3] ^ tmp_a[4] ^ tmp_a[5] ^ tmp_a[6] ;

    
    return false;
}



Block * 
Key_A(Block * key){
    // Block * key_a = new_Camellia_block(key);
    Block * key_a =  init_Block(key_a);
    copy_Block(key_a,key);
    _s(key_a->left_block);
    _p(key_a->right_block);
    key->next = key_a;
    return key;
}

/*
*   argu: n is size to left
*   argu: l_or_r  l = 0  r = 1
*/
Bool
_key_g(int n,int l_or_a ,int L_or_R ,Block * key,Block * get_key){
    int type = l_or_a;
    int i =0;
    for(;i<n;i++){
        if (type == 1){
            if ( L_or_R  == 3){
                LEFT_SHEFT_BLOCK(key->next->right_block);
       
            }else{
                LEFT_SHEFT_BLOCK(key->next->left_block);        

            }
            
        }else if (type == 0){
            if (L_or_R  == 3){
                LEFT_SHEFT_BLOCK(key->right_block); 
                // printf("(r) ");
                // Log_Cammellia_block(key);    

            }else{
                LEFT_SHEFT_BLOCK(key->left_block);        
                // printf("(l) ");
                // Log_Cammellia_block(key);    


            }
        }
        
    }

    if (type == 1){
        if ( L_or_R  == 3){
            copy_stream (get_key->content , key->next->right_block->content,BLOCK_64_LEN);        
        }else{

            copy_stream( get_key->content , key->next->left_block->content,BLOCK_64_LEN);
        }
            
    }else if (type == 0){
        if (L_or_R  == 3){
            copy_stream (get_key->content ,key->right_block->content,BLOCK_64_LEN);   
        }else{
            copy_stream( get_key->content ,key->left_block->content,BLOCK_64_LEN);
        }
    }
    
    // printf("(key log)" );

    // Log_Cammellia_block(key);
    // Log_block(get_key);
    return true;
}


/* generate key1 ~ key18 kl1 = 19 
*  Describle : kl2 = 20 
*              kl3 = 21 
*              kl4 = 22 
*              kw1 23 
*              kw2 = 24 
*  Argu : key_number int  
*  Argu : primary key 
*/
Block *
key_gen(int n,Block * key){
    int l = 0;
    int a = 1;
    int L = 2;
    int R = 3;
    Block * new_key = init_Block(new_key);
    Block * tmp_key = init_Block_LEN(tmp_key,BLOCK_64_LEN);
    int i=0;
    // Block * new_key = init_Block_LEN(new_key,BLOCK_64_LEN);
    // CBlock * key;
    copy_Block(new_key,key);
    switch  (n){

        case 1:
            
            _key_g(0,a,L,new_key,tmp_key);
            
        break;
        case 2:
            _key_g(0,a,R,new_key,tmp_key);
        break;
        case 3:
            _key_g(15,l,L,new_key,tmp_key);
            // copy_Block(new_key,key->next)
            // key->next->LEFT;
        break;
        case 4:

            _key_g(15,l,R,new_key,tmp_key);

            // copy_Block(new_key,key->next)
            // key->next->LEFT;
        break;
        case 5:
            _key_g(15,1,L,new_key,tmp_key);
            
        break;
        case 6:
            _key_g(15,1,R,new_key,tmp_key);
            
        break;
        case 7:

            _key_g(45,0,L,new_key,tmp_key);
        break;
        case 8:
            _key_g(45,0,R,new_key,tmp_key);
        break;
        case 9:
            _key_g(45,1,L,new_key,tmp_key);
        break;
        case 10:
            _key_g(60,0,R,new_key,tmp_key);
        break;
        case 11:
            _key_g(60,1,L,new_key,tmp_key);
        break;
        case 12:
            _key_g(60,1,R,new_key,tmp_key);
        break;
        case 13:
            _key_g(94,0,L,new_key,tmp_key);
        break;
        case 14:
            _key_g(94,0,R,new_key,tmp_key);
        break;
        case 15:
            _key_g(94,1,L,new_key,tmp_key);
        break;
        case 16:
            _key_g(94,1,R,new_key,tmp_key);
        break;
        case 17:
            _key_g(111,0,L,new_key,tmp_key);
        break;
        case 18:
            _key_g(111,0,R,new_key,tmp_key);
        break;
        /*
        *  follow is kl kw
        */
        case 19:
            _key_g(30,1,L,new_key,tmp_key);
        break;
        case 20:
            _key_g(30,1,R,new_key,tmp_key);
        break;
        case 21:
            _key_g(77,0,L,new_key,tmp_key);
        break;
        case 22:
            _key_g(77,0,R,new_key,tmp_key);
        break;
        case 23:
            _key_g(111,1,L,new_key,tmp_key);
        break;
        case 24:
            _key_g(111,1,R,new_key,tmp_key);
        break;
        case 25:
            _key_g(0,l,L,new_key,tmp_key);
        break;
        case 26:
            _key_g(0,l,R,new_key,tmp_key);
        break;
    }

    return tmp_key; 

}

Bool
Log_Cammellia_block(Block * b){
    int i =0;
    if ( !b->left_block){
        printf("not a camellia block , use new_Camellia_block(Block *) before this\n");
        return false;
    }
    for (;i<8 ;i++){
        printf("[%x,",b->left_block->content[i]);
        printf("%x]",b->right_block->content[i]);
    }
    printf("\n");
    return 0;
}

Bool
Log_block(Block * b){
    int i =0;
    if ( !b->content){
        printf("not a camellia block , use new_Camellia_block(Block *) before this\n");
        return false;
    }
    for (;i<8 ;i++){
        printf("%x|",b->content[i]);
    }
    printf("\n");
    return true;
}
Bool
_change(Block * b){
    Block * tmp_b = init_Block_LEN(tmp_b,BLOCK_64_LEN);
    copy_Block(tmp_b,b);
    b->left_block = b->right_block;
    b->right_block = tmp_b->left_block;
    return true;
}
Block *
Camellia(Block * plaint_block ,Block * key_block ,Bool d_or_e ){
    // init plain_text
    // Stream plaint_stream = String2Stream(plaint_text);
    // Stream key_stream = String2Stream(key);
    
    // Block * test_b = new_block(plaint_stream);
    // Block * cblock = new_Camellia_block(test_b);


    // Block * key_block = new_block(key_stream);
    Block * cblock =  plaint_block;// new_Camellia_block(key_block);
    // Log_Cammellia_block(c_key_b); 
    Block * key_a = key_block; // Key_A(c_key_b);

    //

    int round_count = 0;
    Block * keyw1 = key_gen(25,key_a);
    Block * keyw2 = key_gen(26,key_a);
    if(d_or_e){
        keyw1 = key_gen(23,key_a);
        keyw2 = key_gen(24,key_a);
    }
    // Log_Cammellia_block(cblock);
    // Log_block(keyw1);
    // Log_block(keyw2);
    add_mod_Block(cblock->left_block,keyw1);
    add_mod_Block(cblock->right_block,keyw2);

    for(;round_count <6; round_count++){

        Block * key_n = key_gen(round_count+1,key_a);
        if (d_or_e){
            key_n = key_gen(18-round_count,key_a );  
        } 
        _single_Round(key_n,cblock->left_block,cblock->right_block,(lambda_2)F);
    }
/*   
    Block * key19;
    Block * key20;
    if(d_or_e){

        key19 = key_gen(21,key_a);
        key20 = key_gen(22,key_a);
        FL_1(cblock->right_block,key19);
        FL(cblock->left_block,key20);

    }else{
        key19 = key_gen(19,key_a);
        key20 = key_gen(20,key_a);
        FL(cblock->right_block,key19);
        FL_1(cblock->left_block,key20);
        
    }
*/
    
    for(;round_count <12; round_count++){
        Block * key_n = key_gen(round_count+1,key_a);
        if (d_or_e){
            key_n = key_gen(18-round_count,key_a );  
        } 
        _single_Round(key_n,cblock->left_block,cblock->right_block,(lambda_2)F);
    }
/*
    Block * key21 ;
    Block * key22 ;
    if(d_or_e){
        key21 = key_gen(19,key_a);
        key22 = key_gen(20,key_a);
        FL_1(cblock->right_block,key21);
        FL(cblock->left_block,key22);

    }else{
        key21 = key_gen(21,key_a);
        key22 = key_gen(22,key_a);

        FL(cblock->right_block,key21);
        FL_1(cblock->left_block,key22);
        
    }
*/        
    for(;round_count <18; round_count++){
        Block * key_n = key_gen(round_count+1,key_a);
        if (d_or_e){
            key_n = key_gen(18-round_count,key_a );  
        } 
        _single_Round(key_n,cblock->left_block,cblock->right_block,(lambda_2)F);
    }

    _change(cblock);


    Block * key23 = key_gen(23,key_a);
    Block * key24 = key_gen(24,key_a);

    if(d_or_e){
        key23 = key_gen(25,key_a);
        key24 = key_gen(26,key_a);
    }
    // Log_Cammellia_block(cblock);
    // Log_block(key23);
    // Log_block(key24);
    add_mod_Block(cblock->left_block,key23);
    add_mod_Block(cblock->right_block,key24);
    return cblock;

}
/*

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
    Log_Cammellia_block(cblock);
    _s(cblock->left_block);
    Log_Cammellia_block(cblock);
    _p(cblock->left_block);
    Log_Cammellia_block(cblock);
    LEFT_SHEFT_BLOCK (cblock->left_block);
    Log_Cammellia_block(cblock);

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
    
    // Log_block(key1);
    // F(cblock->left_block,key1);
    // printf("%d\n",cblock->left_block->block_byte_len);
    // printf("%d\n",key1->block_byte_len);
    Log_Cammellia_block(cblock);
    int round_count = 0;
    Bool d_or_e = false;
    Block * key_n ;
    for(;round_count <6; round_count++){

        key_n = key_gen(round_count+1,key_a);
        if (d_or_e){
            key_n = key_gen(6-round_count,key_a );  
        } 
        _single_Round(key_n,cblock->left_block,cblock->right_block,(lambda_2)F);
    }
    Log_Cammellia_block(cblock);
    d_or_e = true;
    for(round_count=0;round_count <6; round_count++){

        key_n = key_gen(round_count+1,key_a);
        if (d_or_e){
            key_n = key_gen(6-round_count,key_a );  
        } 
        _single_Round(key_n,cblock->right_block,cblock->left_block,(lambda_2)F);
    }
    Log_Cammellia_block(cblock);
    Block * key19 = key_gen(19,key_a);
    Block * key20 = key_gen(20,key_a);
    
    // Log_Cammellia_block(cblock);
    // FL(cblock->left_block,key19);
    // FL_1(cblock->right_block,key20);
    // Log_Cammellia_block(cblock);
    // FL(cblock->right_block,key19);
    // FL_1(cblock->left_block,key20);
    // Log_Cammellia_block(cblock);

    _change(cblock);
    
    printf("test cammellia : \n");
    Log_Cammellia_block(cblock);
    Block * cipher = Camellia(cblock,key_a,false);
    Log_Cammellia_block(cipher);
    // _change(cipher);
    Block * plain = Camellia(cipher,key_a,true);
    Log_Cammellia_block(plain);

    // Log_block(key1);
    // LEFT_SHIFT_STREAM(cblock->LEFT->content);
      // block_log(cblock->LEFT);
    return OK; 
}
*/
