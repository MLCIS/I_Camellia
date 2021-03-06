#include "CIPHER.h"


size_t
JUDGE(Stream cons_arg){
    size_t length = strlen((const char *)cons_arg);
    return length;
}

Bool
eva(Uchar *  data){
    * data = (* data ) + 0x01;
    return OK;
}

Stream
n_DSR (Stream  data , Stream constant_para , int rank_n ){//size_t  (* judge )(Stream) ){
    int n = rank_n;//judge (constant_para);
    //printf("count : %d\n" , n );
    int COUNT_8 = 0;
    Bool if_mod_add = false;
    for (; COUNT_8 < n ; COUNT_8 ++){
        Bool if_first_1 = LEFT_SHIFT( data+ COUNT_8); // pass the index uchar * to  ( bool LEFT_SHIFT (uchar * ) );

        if (if_first_1 == true ){
            if (COUNT_8 == 0) {
                if_mod_add = true;
            }else{
                eva ( data + COUNT_8 -1 ); 
            }
        }
    }

    if (if_mod_add == true) {
        Bool err_if = MOD_ADD(data, constant_para);     
        if (err_if == false ) {
            LOG(String2Stream("Error"), "structure constant argument is not matched to data !\n");
        }
    }

    return data;
    
}   

Uchar
LEFT_SHIFT_CYCLE_BYTE(Uchar one){
    Uchar max = ( one  << 7 & 0xff ) >> 7;
    if (max  != 0x0){
    	return (one << 1 ) + max;	
    }

    return one << 1;

}

Stream
LEFT_SHIFT_CYCLE_STREAM(Stream data){
    int COUNT_8 = 0;
    int n = JUDGE(data);
    Bool if_mod_add = false;
    Bool if_first_1 = false;
    for (; COUNT_8 < n ; COUNT_8 ++){
        Bool if_first_1 = LEFT_SHIFT( data+ COUNT_8); // pass the index uchar * to  ( bool LEFT_SHIFT (uchar * ) );

        if (if_first_1 == true ){
            if (COUNT_8 == 0) {
                if_mod_add = true;
            }else{
                eva ( data + COUNT_8 -1 ); 
            }
        }
    }




    return data;
}


