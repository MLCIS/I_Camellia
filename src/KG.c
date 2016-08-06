#include "CIPHER.h"
#include "KG.h"

/*
 * this primary function is for check 
 * length of key , this must be 128 bits
 *
 */
Bool
_check(Stream originl_key){
    int i =0,max = 128;
    for (;originl_key++ || i <= 128;i++);
    if (i  == 128){
    	return true;
    }
    return false;
}

Stream
_new(int len){
    Stream tmp =  (Stream) malloc(sizeof(Uchar) * len +1 );
    return tmp;
}

/**
 * to separate one 8 bit  to  double 8 bit;
 */
Stream
_sep(Uchar one){
    Stream ret = _new(2);
    //printf("d : %x\n",one);
    Uchar l = one << 4 & 0xff ;
    Uchar r = one >> 4 & 0xff ;

    ret[0] = l;
    ret[1] = r;
    //printf("l : %x\nr: %x\n",l,r);
    return ret;
}

/*
 * Balance function 
 */
Uchar
_balance_byte(Stream in ,Uchar old ){
    int i ;
    Uchar temp;
//    printf("%x  %x ",in[0],in[1]);
    for (i = 0; i < 2;i++){
    	temp ^= in[i];
    }
    temp = temp % 256;
    if( temp == old) {
        temp = LEFT_SHIFT_CYCLE_BYTE(temp);
    } 
//    printf("temp : %x\n",temp);
    return KG_BALANCE_TABLE[temp];
}


/**
 * @RET Stream select two byte
 * @arg Stream from 8 byte
 */
Stream
select_2(Stream from_8_stream){
    Stream s = _new(2);
    s[0] = from_8_stream[0] << 1 ^ 0xaa;
    s[1] = from_8_stream[1] >> 1 ^ 0x55;
    return s;
}

Uchar
_jump_select(Uchar one ,Uchar old){
   Uchar ne_one = LEFT_SHIFT_CYCLE_BYTE(one);
   if ( 1 == ((old << 7 &0xff ) >> 7)){
   	ne_one  = LEFT_SHIFT_CYCLE_BYTE(ne_one);
   }
   return one ^ old;
}

Uchar
_compress(Stream s,Uchar old){
    int i = 0;
    Uchar res = 0x01;
    for (;i<16 ;i++){
//	printf(" %x/",s[i]);
    	res += s[i];
	res = res % 0xff;
        res += LEFT_SHIFT_CYCLE_BYTE(old);
//	printf("%x ",res);
    }
    res ^= old;
    return res;
}

int
_log(Stream s){
    int i=0;
    for(;i<16;i++){
    	printf("%x ",s[i]);
    }
    printf("\n\n");
    return 0;
}

Uchar
KG(Stream originl_key){
    int num =0 ;
    Uchar old_jump = 0xff;
    Uchar old_b = 0xa7;
    Uchar old_c = 0x01;
    Uchar new_d = 0x07;
//    printf("%x \t %x ",0xa3,LEFT_SHIFT_CYCLE_BYTE(0xa3));
    originl_key = n_DSR(originl_key,DSR_128_CONSTANT,16);

 //   _log(originl_key);
    
    for(num=0; num < 16; num+=1){

//	printf("\no :%x \n",originl_key[num]);
        
        new_d = originl_key[num];
		new_d = LEFT_SHIFT_CYCLE_BYTE(new_d);
	new_d ^= old_b;
	//if ((old_b << 7 & 0xff ) >> 7 == 1){
	//    printf("s \n");
	new_d = LEFT_SHIFT_CYCLE_BYTE(new_d);
	//}

	Stream s2 = _sep(new_d);
	s2 =  select_2(s2);
	Uchar res  = _balance_byte(s2,old_b);
	old_b = LEFT_SHIFT_CYCLE_BYTE(old_b) +old_b  % 256;
	Uchar jpt = _jump_select(res,old_jump);
	old_jump = LEFT_SHIFT_CYCLE_BYTE(old_jump + 0x01);	
//	printf("|%x",jpt); 
	*(originl_key+num) = jpt;
    }
    _log(originl_key);
    
    Uchar mem_element = ( old_c + old_b +old_jump ) % 0xf;
    Uchar one_char = _compress(originl_key,originl_key[mem_element]);
    old_c = one_char;

    return one_char;
}
