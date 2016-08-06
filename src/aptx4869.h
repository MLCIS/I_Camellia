//
//  Syn.h
//  
//
//  Created by dark.h on 6/15/15.
//
//

#ifndef ____Syn__
#define ____Syn__

#include <stdio.h>
#include "CIPHER.h"
#include "basiclib.h"
#include <time.h>

/*
 * parmeters areas
 */

void * ErCheck_malloc(unsigned int size);

static unsigned char S_BOX_X[256] ={
	112,130,44,236,179,39,192,229,228,133,87,53,234,12,174,65,35,239,107,147,69,25,165,33,237,14,79,78,29,101,146,189,134,184,175,143,124,235,31,206,62,48,220,95,94,197,11,26,166,225,57,202,213,71,93,61,217,1,90,214,81,86,108,77,139,13,154,102,251,204,176,45,116,18,43,32,240,177,132,153,223,76,203,194,52,126,118,5,109,183,169,49,209,23,4,215,20,88,58,97,222,27,17,28,50,15,156,22,83,24,242,34,254,68,207,178,195,181,122,145,36,8,232,168,96,252,105,80,170,208,160,125,161,137,98,151,84,91,30,149,224,255,100,210,16,196,0,72,163,247,117,219,138,3,230,218,9,63,221,148,135,92,131,2,205,74,144,51,115,103,246,243,157,127,191,226,82,155,216,38,200,55,198,59,129,50,111,75,19,190,99,46,233,121,167,140,159,110,188,142,41,245,249,182,47,253,180,89,120,152,6,106,231,70,113,186,212,37,171,66,136,162,141,250,114,7,185,85,248,238,172,10,54,73,42,104,60,56,241,164,64,40,211,123,187,201,67,193,21,227,173,244,119,199,128,158

};

unsigned char
S_search(char x , char y);

Stream
MulLFSRX(Stream  inbuf,Uchar firstElectment);

Stream 
Concatenater(Stream in ,Uchar ele);

Uchar
SwitchDSR(Stream  in, Stream con , int rank,Uchar ele);

int
StreamLog(Stream a,int size);

int 
initDSR();

int
init_BUF_PAD(char * in);

int
init_IN(Stream buf);

Uchar
bagAlgorithm( Stream in );

Uchar
boxMap(Uchar location,Uchar first, Uchar last);


/*
 *  init and use 
 *
 */

int
aptx4869_init(char * );

unsigned char
aptx4869_kg();

unsigned char *
aptx4869_en(unsigned char * in ,long len,double rank);

unsigned char *
aptx4869_de(unsigned char * in ,long len,double rank);

int
aptx4869_file(char * file,char * key ,int rank,int mode);
#endif /* defined(____Syn__) */
