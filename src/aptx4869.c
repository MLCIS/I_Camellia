//
//  Syn.c
//  
//
//  Created by dark.h on 6/15/15.
//
//

#include "aptx4869.h"


static unsigned char CHAR_7[8] ;
static unsigned char CHAR_11[12] ;
static unsigned char CHAR_13[14] ;
static unsigned char CHAR_17[18] ;
static unsigned char CHAR_19[20] ;
static unsigned char CHAR_23[24] ;
static unsigned char CHAR_29[30] ;
static unsigned char CHAR_31[32] ;

static unsigned char IN_7[8] ;
static unsigned char IN_11[12] ;
static unsigned char IN_13[14] ;
static unsigned char IN_17[18] ;
static unsigned char IN_19[20] ;
static unsigned char IN_23[24] ;
static unsigned char IN_29[30] ;
static unsigned char IN_31[32] ;

/*
 * @LAST_ELE is a memerry able par
 * @LAST_CON is a memery able par
 */
static unsigned char IN_BUF[151] ;
static unsigned char LAST_ELE = 0x01;
static unsigned char LAST_CON = 0x01;
static unsigned char LAST_BAG = 0x01;

unsigned char SS[151] = {
139,0,44,147,226,115,117,184,58,26,94,176,165,152,153,195,145,254,232,144,12,23,95,124,207,99,109,1,30,65,
204,193,213,72,218,175,171,89,110,141,94,98,31,244,86,166,12,168,182,26,218,36,83,154,164,237,123,189,52,1,
168,201,234,221,247,80,169,225,97,78,220,83,121,128,62,70,78,113,150,83,81,55,241,137,117,251,69,127,14,236,
236,10,38,155,193,32,181,155,35,74,130,64,201,85,167,0,109,131,237,58,185,234,130,87,167,153,26,168,211,47,
13,164,169,254,47,64,246,50,71,212,201,111,200,120,73,15,43,48,32,138,157,171,222,84,9,208,49,171,212,82
};

unsigned char WEIGHT_VECTOR[8] = {
	211, 223, 227, 229, 233, 239, 241, 251
};

unsigned char SS_CONT [151] = {
	10,223,15,65,163,11,229,9,105,156,198,84,101,185,167,212,40,76,70,228,200,117,20,71,23,127,28,155,101,166,
		187,134,134,193,47,252,216,65,19,161,113,11,2,247,28,150,44,107,44,16,205,190,40,151,156,140,102,0,146,110,
		107,10,221,212,35,54,115,160,235,243,130,96,116,156,239,132,154,167,208,158,106,169,33,205,35,166,67,164,69,185,
		250,171,150,71,79,134,44,139,224,2,25,5,243,85,212,249,139,174,107,168,66,57,47,102,33,43,129,66,74,32,
		129,3,39,103,195,119,238,124,242,154,188,38,92,176,122,91,75,3,141,57,60,15,211,44,233,149,164,51,157,130
};

int RANK_NUM[8] = { 7,11,13,17,19,23,29,31 };

int
initDSR(){
	Stream s = (Stream ) SS;
	Stream new_stream = n_DSR(SS,SS_CONT,150);
	/*
	for(int i3=0; i3 < 150; i3++){
		printf("%x ",new_stream[i3]);
		
	}
	*/


	int i ,l,i2,count,last;
	i = 0;
	l = i;
	last = 0;
	for (i2=0;i2 < 8; i2++){
		count = RANK_NUM[i2];
		//printf("\n[%d] ",count);

		l += count;
		for(;i<l;i++){
			if (count == 7){
				CHAR_7[i] = new_stream[i];
			}else if (count == 11){
				CHAR_11[i-last] = new_stream[i];
			}else if (count == 13){
				CHAR_13[i-last] = new_stream[i];
			}else if (count == 17){
				CHAR_17[i-last] = new_stream[i];
			}else if (count == 19){
				CHAR_19[i-last] = new_stream[i];
			}else if (count == 23){
				CHAR_23[i-last] = new_stream[i];
			}else if (count == 29){
				CHAR_29[i-last] = new_stream[i];
			}else{
				CHAR_31[i-last] = new_stream[i];
			}
			//printf(" --- %d ",i-last);
		}
		last += count;	
	}

	return 1;

}

int
init_BUF_PAD(char * in){
	int in_i = 0;
	if (strlen(in) > 150){
		for (;in_i < 150; in_i ++){
			IN_BUF[in_i] = in[in_i];
		}
		IN_BUF[150] = 0x00;

		return 1;
	}
	int len = strlen(in);	
	int ulen = len;
	int i = 0;
	for(;i< len;i++){
		IN_BUF[i] = in[i] ;
	}

	for(len = 0;len <  150; len++){
		IN_BUF[len] = len ^ in[len % ulen] ^ in[ulen-1];	
	}
	

	return 1;
	
}

int
init_IN(Stream  buf){
/*	if (strlen((char * )buf) < 150 ){
		return 0;
	}
*/

	int i ,l,i2,count,last;
	i = 0;
	l = i;
	last = 0;
	for (i2=0;i2 < 8; i2++){
		count = RANK_NUM[i2];
		//printf("\n[%d] ",count);

		l += count;
//		printf("i : %d , count : %d ,l : %d\n",i,count,l);
		for(;i<l;i++){
			if (count == 7){
				IN_7[i] = buf[i];
				//printf(" [%x] ",IN_7[i]);
			}else if (count == 11){
				IN_11[i-last] = buf[i];
			}else if (count == 13){
				IN_13[i-last] = buf[i];
			}else if (count == 17){
				IN_17[i-last] = buf[i];
			}else if (count == 19){
				IN_19[i-last] = buf[i];
			}else if (count == 23){
				IN_23[i-last] = buf[i];
			}else if (count == 29){
				IN_29[i-last] = buf[i];
			}else{
				IN_31[i-last] = buf[i];
			}
			//printf(" --- %d ",i-last);
		}
		last += count;	
	}
	return 1;
}

Uchar
SwitchDSR(Stream  in, Stream con , int rank,Uchar ele){
	Uchar out = 0x00;
	//StreamLog(in,rank);	
	if ( ele >128  ){
		n_DSR(in,con,rank);
		out = in[0];
		//printf("+ %x ",out);
		
		return  out;
	}else{
		LEFT_SHIFT_CYCLE_STREAM(in);
		out = in[0];
		//printf("* %x ",out);

		in[rank-1] = ele;
		return out ^ ele;
	
	}

}

Uchar 
bagAlgorithm(Stream in){
	int i =0;
	int max_weight = 0;
	for(;i<8;i++){
		max_weight += in[i] * WEIGHT_VECTOR[i];
	}
	return max_weight % 256;
}

Stream
MulLFSRX(Stream  inbuf,Uchar firstElectment){
	int i,i2 ,i3, i4;
	int count ;
	Stream concatenate = new( concatenate,8);
	unsigned char firEle = firstElectment;


	for (i=0; i  < 8; i++){
		count = RANK_NUM[i];
		if (count == 7){
			concatenate[i] = SwitchDSR(IN_7,CHAR_7,count,LAST_ELE);
			LAST_ELE = concatenate[i];
		}else if (count == 11 ){
			concatenate[i] = SwitchDSR(IN_11,CHAR_11,count,LAST_ELE);
			LAST_ELE = concatenate[i];
		}else if (count == 13 ){
			concatenate[i] = SwitchDSR(IN_13,CHAR_13,count,LAST_ELE);
			LAST_ELE = concatenate[i];
		}else if (count == 17 ){
			concatenate[i] = SwitchDSR(IN_17,CHAR_17,count,LAST_ELE);
			LAST_ELE = concatenate[i];
		}else if (count == 19 ){
			concatenate[i] = SwitchDSR(IN_19,CHAR_19,count,LAST_ELE);
			LAST_ELE = concatenate[i];
		}else if (count == 23 ){
			concatenate[i] = SwitchDSR(IN_23,CHAR_23,count,LAST_ELE);
			LAST_ELE = concatenate[i];
		}else if (count == 29 ){
			concatenate[i] = SwitchDSR(IN_29,CHAR_29,count,LAST_ELE);
			LAST_ELE = concatenate[i];
		}else  {
			concatenate[i] = SwitchDSR(IN_31,CHAR_31,count,LAST_ELE);
			LAST_ELE = concatenate[i];
		}
		//printf("\t ele :  %x \n",LAST_ELE);
		
	}

	return concatenate;
}

Stream 
Concatenater(Stream in ,Uchar ele){
	Stream tmp = new(tmp,8);
	int i =0 ;
	if (ele < 128){
		for(;i<8;i++){
			tmp[7-i] = in[i];
		}	
		return tmp;
	}
	free(tmp);
	return in;
}

int
StreamLog(Stream a,int size){
	int i =0;
	for(;i<size;i++){
		printf("%x ",a[i]);
	}
	printf("\n");
	return 0;
}

Uchar
boxMap(Uchar locaiton ,Uchar first , Uchar last ){
	Uchar l = locaiton >> 4 & 0xf;
	Uchar h = locaiton & 0xf;
	Uchar l2 ,h2;
	if (LAST_BAG <127 ){
		h2 = first >> 4 & 0xf;	
		l2 = first & 0xf;
	}
	h2 = last >> 4 & 0xf;
	l2 = last & 0xf;

	int x = h * 16 + l;
	int y = h2 * 16 + l2;

	Uchar o = S_BOX_X[x];
	
	Uchar o2 = S_BOX_X[y];
	
	LAST_BAG = o ^ o2;

	return o ^ o2 ;

}
int 
aptx4869_init(char * in){
	initDSR();
	init_BUF_PAD(in);
	init_IN(IN_BUF);
	return 1;
}

unsigned char
aptx4869(){

	Stream  concatenate = MulLFSRX(IN_BUF,LAST_ELE);
	concatenate = Concatenater(concatenate,LAST_CON);
	Uchar bag_weight = bagAlgorithm(concatenate);
	Uchar out = boxMap(bag_weight,concatenate[0],concatenate[7]);
	return out;
}

int 
main(int argc,char ** argv){

	printf("\n ------ load       ------ \n");
	initDSR();
	printf("\n ------ load ok    ------ \n");

	init_BUF_PAD(argv[1]);
	printf("\n ------ input pad ok ---- \n");
	init_IN(IN_BUF);
	printf("\n ---- init input  ok ---- \n");
	int i,i2,count ;
	
	StreamLog(IN_7,7);
	StreamLog(IN_11,11);
	StreamLog(IN_13,13);
	StreamLog(IN_17,17);
	StreamLog(IN_19,19);
	StreamLog(IN_23,23);
	StreamLog(IN_31,31);

	printf("\n ----- inited input ----- \n");

	StreamLog(IN_BUF,150);

	printf("\n ----- first step ------- \n");

	Stream  concatenate = MulLFSRX(IN_BUF,LAST_ELE);
	printf("\t concatenate : ");
	StreamLog(concatenate,8);

	printf("\n ----- sencond step  ---- \n");
	concatenate = Concatenater(concatenate,LAST_CON);
	printf(" coned : "); 
	StreamLog(concatenate,8);

	Uchar bag_weight = bagAlgorithm(concatenate);
	printf("\n weight : %x \n",bag_weight);

	printf("\n ----- last step -------- \n");
	Uchar out = boxMap(bag_weight,concatenate[0],concatenate[7]);
	printf(" kg : %x ",out);


	printf("\n in : %s \n",argv[1]);
	i2 =0;
	Uchar res = 0xff;
	aptx4869_init(argv[1]);
	for (;i2 < 2048 ; i2 ++){	
		res = aptx4869();
		printf("| %d ",res);
	}
	
	return 0;
}
