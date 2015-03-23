#include "CIPHER.h"

void *
new (void * template , size_t len ){
    //printf("%d count : %d \n" , sizeof(template),len);
    template =  malloc ( sizeof(template) * len);
//    printf("\n%d  %ld \n",len,strlen(template));
    return memset(template,0xff ,  len) ;
}



Bool 
LEFT_SHIFT (Uchar * data){
    Bool if_first_is_1 = false;
    if_first_is_1 = ( BASE_JUDGE_BYTE & (* data) ) >> 7;
    * data  = (*data) << 1;
    * data  &=  BYTE_LOCK;
    return if_first_is_1;
}

Bool
MOD_ADD(Stream data, Stream const_arg){
    size_t data_len = JUDGE(data);
    size_t const_arg_len = JUDGE(const_arg);
    size_t now_point_count = 0;



    Uchar * now_point = data;
//    LOG(*now_point,"before mod add ");
    if (const_arg_len != data_len ){
	//printf("eror exit ! \n");
        return false;
    }
    //printf("data len : %d\n",data_len);
    for (;now_point_count < data_len ; now_point_count ++ ){
        *( now_point + now_point_count) ^= *(const_arg + now_point_count);
    }
    return true;
}


Bool
LOG(Uchar *  data ,char * str){
    for(;* data ; data ++){
    	printf("%x ",*data);
    }
    printf("\t|\t%s\n",str);
    return OK;
}

String
Stream2String (Stream argv){
    return (String) argv;
}

Stream
String2Stream (String argv){
    return (Stream ) argv;
}
