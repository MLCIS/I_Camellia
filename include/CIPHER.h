#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>

#ifndef _CIPHER_MACRO
  
  #define _CIPHER_MACRO 	1
  #define 	OK 		0
  #define 	true 		1
  #define 	false   	0
  #define 	MIN_SIZE 	8
  #define 	BASE_JUDGE_BYTE 0x80
  #define 	BYTE_LOCK 	0xff
  #define 	INT 		4
  #define 	UCHAR 		1
  #define 	CHAR 		1
  #define BLOCK_64_LEN      8
  #define BLOCK_128_LEN     16
  #define BLOCK_TYPE        40    

  typedef int Bool ;
  typedef unsigned char * Stream;
  typedef unsigned char Uchar;
  typedef unsigned int  Uint;
  typedef char * String ;
  typedef void * (*lambda )(void *) ;
  typedef void * (*lambda_2) (void *, void *);

 /*
  * func declare  area
  */




String 
Stream2String( Stream );

Stream
String2Stream( String);

Bool 
LOG( Uchar * ,char * );

size_t
JUDGE (Stream);

void *
new (void * , size_t len );

Bool
del (void *);

size_t
each(void * ,lambda callback ,size_t end , size_t TYPE); 

size_t
each_result(void * ,lambda_2 callback ,size_t end , size_t TYPE, void * result);

Bool
MOD_ADD(Stream data, Stream const_arg);

Bool
MOD_ADD_4(Stream data,Stream const_arg);

Uchar
LEFT_SHIFT_CYCLE_BYTE(Uchar );

Bool
LEFT_SHIFT (Uchar *  );

Bool
LEFT_SHIFT_STREAM (Stream );

Bool
LEFT_SHIFT_STREAM_32(Stream data);

Stream
n_DSR (Stream  data , Stream constant_para , int rank_n);//size_t  (* judge )(Stream) ); 

Stream
LEFT_SHIFT_CYCLE_STREAM (Stream data );

Bool
copy_stream(Stream dst_data, Stream res_data,int len);

#endif
