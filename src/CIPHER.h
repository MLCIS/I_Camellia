#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#ifndef _CIPHER_MACRO
  
  #define _CIPHER_MACRO 	1
  #define 	OK 		0
  #define 	true 		1
  #define 	false   	0
  #define 	MIN_SIZE 	8
  #define 	BASE_JUDGE_BYTE 0x80
  #define 	BYTE_LOCK 	0xff

  typedef int Bool ;
  typedef unsigned char * Stream;
  typedef unsigned char Uchar;
  typedef char * String ;

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
MOD_ADD(Stream data, Stream const_arg);

Bool
LEFT_SHIFT (Uchar * );

Stream
n_DSR (Stream  data , Stream constant_para , size_t  (* judge )(Stream) ); 


#endif
