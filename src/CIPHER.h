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

  typedef int Bool ;
  typedef unsigned char * Stream;
  typedef unsigned char Uchar;
  typedef unsigned int  Uint;
  typedef char * String ;
  typedef void * (*lambda )(void *) ;
  typedef void * (*lambdaRes) (void *, void *);

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
each_result(void * ,lambdaRes callback ,size_t end , size_t TYPE, void * result);

Bool
MOD_ADD(Stream data, Stream const_arg);

Bool
LEFT_SHIFT (Uchar *  );

Bool
LEFT_SHIFT_STREAM (Stream );


Stream
n_DSR (Stream  data , Stream constant_para , size_t  (* judge )(Stream) ); 

Stream
LEFT_SHIFT_CYCLE_STREAM (Stream data );

#endif
