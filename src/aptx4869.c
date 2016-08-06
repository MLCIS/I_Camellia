//
//  Syn.c
//  
//
//  Created by dark.h on 6/15/15.
//
//

#include "aptx4869.h"

#define EN_MODE 0
#define DE_MODE 1

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
static long long MEM[256] = {
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
} ;

unsigned char SS[151] = {
139,0,44,147,226,115,117,184,58,26,94,176,165,152,153,195,145,254,232,144,12,23,95,124,207,99,109,1,30,65,
204,193,213,72,218,175,171,89,110,141,94,98,31,244,86,166,12,168,182,26,218,36,83,154,164,237,123,189,52,1,
168,201,234,221,247,80,169,225,97,78,220,83,121,128,62,70,78,113,150,83,81,55,241,137,117,251,69,127,14,236,
236,10,38,155,193,32,181,155,35,74,130,64,201,85,167,0,109,131,237,58,185,234,130,87,167,153,26,168,211,47,
13,164,169,254,47,64,246,50,71,212,201,111,200,120,73,15,43,48,32,138,157,171,222,84,9,208,49,171,212,82
};

unsigned char SS_BAK[151] = {
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

void *
ErCheck_malloc(unsigned int size){
    void * ptr;
    ptr = malloc(size+1);
    if (ptr == NULL ){
    	fprintf(stderr,"Error : could not allocate head memmory.\n");
	exit(-1);
    }
    return ptr;
}

int
_fill(Stream des ,Stream source, int size){
	int i =0;
	for(;i < size ; i ++ ){
		des[i] = source[i];
	}
	return 0;
}

int
initDSR(){

	Stream s ,new_stream;
	_fill(SS_BAK,SS,150);

	memset(MEM,0,256);

	
	new_stream = n_DSR(SS_BAK,SS_CONT,150);


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
/*
	int len;
	for(len = 0;len <  150; len++){
		buf[len] = len  ;	
	}
*/	
	//memset(buf,0x0,150);

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
		int i =0;
		for(;i<rank;i++){
			in[i] = S_BOX_X[in[i]];
		}
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
	Stream concatenate = (Stream)ErCheck_malloc(8);
	concatenate[8] = NULL;
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
	Stream tmp = (Stream)ErCheck_malloc(8);
	tmp[9] = NULL;
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
		printf("%u ",a[i]);
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
	
//	LAST_BAG = o ^ o2;
	

	int res = o ^ o2  ;

//	res = (res + IN_BUF[res % 150] ) % 256;

	LAST_BAG = res ;


	MEM[res] ++;

//	res = (res + MEM[res]* 127 )%256 ;
	return res;
}


int 
aptx4869_init(char * in){

	LAST_ELE = 0x01;
	LAST_CON = 0x01;
	LAST_BAG = 0x01;
	initDSR();
	init_BUF_PAD(in);
	init_IN(IN_BUF);

	/*
	printf(" IN \n");
	StreamLog(IN_7,7);
	StreamLog(IN_11,11);
	StreamLog(IN_13,13);
	StreamLog(IN_17,17);
	StreamLog(IN_19,19);
	StreamLog(IN_23,23);
	StreamLog(IN_29,29);
	StreamLog(IN_31,31);
	printf(" Vector \n");
	printf("%x ",LAST_BAG);
	printf("%x ",LAST_CON);
	printf("%x ",LAST_ELE);

	printf("\n Char : \n");
	StreamLog(CHAR_7 ,7);
	StreamLog(CHAR_11,11);
	StreamLog(CHAR_13,13);
	StreamLog(CHAR_17,17);
	StreamLog(CHAR_19,19);
	StreamLog(CHAR_23,23);
	StreamLog(CHAR_29,29);
	StreamLog(CHAR_31,31);
	
	*/

	return 1;
}

unsigned char
aptx4869_kg(){

	Stream  concatenate = MulLFSRX(IN_BUF,LAST_ELE);
	concatenate = Concatenater(concatenate,LAST_CON);
	Uchar bag_weight = bagAlgorithm(concatenate);
	Uchar out = boxMap(bag_weight,concatenate[0],concatenate[7]);
	return out;
}

unsigned char * 
aptx4869_encrypt(unsigned char onechar,int rank){
	int scale = (int)rank;
	unsigned char * result = ErCheck_malloc(scale);

	int count = 0;

	srand(time(0));
	unsigned char key;
	int randnum ;
	randnum = rand() % scale;
	for(count=0; count < scale; count++){
		
		key = aptx4869_kg();
		if (count == randnum){
			result[randnum] = onechar ^ key;
		}else{
			result[count] = key;
		}
	}

	return result;

}

unsigned char
aptx4869_decrypt(unsigned char * in,int rank){
	int scale = (int)rank;
	int count = 0;
	int temp_i= -1;
	int temp_0;
	unsigned char keys[scale];
	for(;count < rank; count++){
		keys[count] = aptx4869_kg();
		if ( in[count] != keys[count]){
			temp_i = count;
		}
	}

	if (temp_i != -1 ){
		return in[temp_i] ^ keys[temp_i];
	}else{
		return 0x00;
	}
}

unsigned char * 
aptx4869_en(unsigned char * in ,long len ,double rank){
	int scale = (int) rank;
	long  count ;
	long randnum; 
	unsigned char * result =  ErCheck_malloc(len* scale);
	result[len* scale ] = NULL;
	unsigned char key ;
	long in_location  = 0 ;

	srand(time(0));
	int tmp_i;
	for(count = 0 ;count < len  ; count++){
       		randnum = rand() % scale;
		for (tmp_i = 0; tmp_i < scale;tmp_i++){
			key = aptx4869_kg();
	//		printf(" %x",key);
			if ( tmp_i  == randnum ){


			//	printf("count : %d r:%d %x^%x=%x \n",count * scale + tmp_i,randnum,key,in[in_location],in[in_location] ^ key ); 
				result[count * scale + tmp_i] = in[in_location] ^ key;
	//		printf("(f:%d %x-%x)",randnum,result[count],key);
				in_location ++;
			}else{
				result[count * scale + tmp_i] = key;
			}
		}

	}	

	return result;
	
	
	
	
}

unsigned char * 
aptx4869_de(unsigned char * buf ,long len,double rank){
	int scale = (int) rank;
	long  count ;
       	long rand = random() % scale;
	unsigned char * result =  ErCheck_malloc(len / scale);
	result[len/scale ] = NULL;
	unsigned char key[5] ;
	int flag = 0;
	int flag_sample;
	long in_location  = 0 ;
	int tmp_i ;
	for(count = 0 ;count < len /4 ; count++){
		tmp_i = 0;
		flag = -1;
		flag_sample = -1;
		for (tmp_i=0;tmp_i < scale; tmp_i ++ ){
			key[tmp_i] = aptx4869_kg();
	//		printf(" %x",key[tmp_i]); 
			if (buf[count*scale + tmp_i] != key[tmp_i] ){
				flag = tmp_i;		
			}
	//		if (buf[count * scale +tmp_i] == 0x0){
	//			flag_sample = tmp_i;
	//		}
		}
		if ( flag != -1 ){


			result[count] = buf[count*scale + flag] ^ key[flag];
			//printf("(f:%d %x=%x)",flag,buf[count * scale +flag],key[flag]);
		}else{
			result[count] = 0x00;//buf[count * scale + flag_sample ] ^ key[flag_sample];
			//printf("(%x=%x)",buf[count * scale +flag_sample],key[flag_sample]);
		}
	
	


		
	}	

	return result;
	

}

int 
aptx4869_file(char * file_name,char * key,int rank,int mode){
	FILE * fp = fopen(file_name,"rb");
	char * ToFile = ErCheck_malloc(100);
	strcpy(ToFile,file_name);
	if(mode == EN_MODE){
		strcat(ToFile,".cipher");
	}else{
		strcat(ToFile,".plaintext");
	}
	FILE * ToFp = fopen(ToFile,"wb");
	unsigned char * buf ;//=  ErCheck_malloc(rank);
	unsigned char buf_c;
	
	/* init kg 
	 *
	 */
	aptx4869_init(key);

	unsigned char * oneByte = ErCheck_malloc(1);
	if (mode == EN_MODE){
		while(fread(oneByte,1,1,fp) != 0 ){
			buf = aptx4869_encrypt(oneByte[0],rank);
			fwrite(buf,rank,1,ToFp);
			free(buf);
		}
	}else{
		buf = ErCheck_malloc( rank);
		while( fread(buf,1,rank,fp) != 0){
			buf_c = aptx4869_decrypt(buf,rank);
			//fwrite(buf_c,1,1,ToFp);
			fputc(buf_c,ToFp);
			
		}
		free(buf);
		
	}	

	fclose(fp);
	fclose(ToFp);

	return 1;

}

	
int 
main(int argc,char ** argv){
	/*
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

*/

	/*
	int i2;
	printf("\n in : %s \n",argv[1]);
	i2 =0;
	Uchar res = 0xff;
	aptx4869_init(argv[1]);
	for (;i2 <  atol(argv[2]) ; i2 ++){	
		res = aptx4869_kg();
		printf(" %d",res);
	}

	int ii = 0;
	for(; ii< 256;ii++){
		printf("%d : %-lld \n",ii,MEM[ii]);  
	}
	
	
*/
	
/*


	int l = strlen(argv[2]);
	aptx4869_init(argv[1]);
	unsigned char * s = aptx4869_en(argv[2],l,4);
	printf("\n");
	StreamLog(s,l* 4);
	printf("\n");
	aptx4869_init(argv[1]);
	printf("\n");
	printf("\n");
	char * real = aptx4869_de(s,l*4,4);
	printf("\n|%s|\n",real);

	
	*/

	int mode ;
	char * file = argv[1];
	char * key = argv[2];
	int rank = atoi(argv[3]);
	if (!strcmp(argv[4],"en")){
		mode = EN_MODE;
	}else if (! strcmp(argv[4] ,"de")){
		mode = DE_MODE;
	}else{
		fprintf(stderr,"mode must choose \"en\" or \"de\"\n");
		exit(-1);
	}

	aptx4869_file(file,key,rank,mode);

	/*
	unsigned char * all = ErCheck_malloc(2000);
	unsigned char * buf ;//= ErCheck_malloc(4);
	unsigned char one ; //= argv[1][i];
	aptx4869_init("dark");
	int i =0;
	for(;i < strlen(argv[1]) ; i++){
		one = argv[1][i];
		printf("en : %x \t \n",one); 	
	
		buf = aptx4869_encrypt(one,5);
		StreamLog(buf,5);
		strcat(all,buf);
	}
	aptx4869_init("dark");

	int cou = 0 ;
	int now = 0;
	for (i=0 ; i < strlen(argv[1]) ; i ++){
		buf = ErCheck_malloc(5);
		for(;cou < now + 5;cou ++){
			buf[cou - now]  = all[cou];
		}
		now += 5;
		StreamLog(buf,5);
		printf("\n de : ");
		one = aptx4869_decrypt(buf,5);
		printf(" %x \n",one);


	}
	*/
	return 0;
}

