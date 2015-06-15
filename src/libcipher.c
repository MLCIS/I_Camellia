#include "CIPHER.h"

/*
 * Object oriented functions 
 * these functions is very important for using later
 */
void *
new (void * template , size_t len ){
    //printf("%d count : %d \n" , sizeof(template),len);
    template =  malloc ( sizeof(template) * len);
//    printf("\n%d  %ld \n",len,strlen(template));
    return memset(template,0xff ,  len) ;
}

Bool
del (void * template){
    free(template);
    return OK;
}

int
_i_char(Uchar * v){
    printf("%x ",*v);
    return OK;
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
LEFT_SHIFT_STREAM( Stream  data){
    size_t count = JUDGE(data);
    each(data,(lambda) _i_char ,count , UCHAR);
    each(data,(lambda) LEFT_SHIFT , count, UCHAR);
    each(data,(lambda) _i_char ,count , UCHAR);
    return count;
} 

Bool
LEFT_SHIFT_STREAM_32(Stream data){
    int i = 0;
    Bool if_eva =false;
    if (data[0] <<7 == 1){
        if_eva = true;
    } 
    for (;i < 4; i++){
        *(data+i) = (*(data+i) ) << 1; 
    }
    *(data+4) = (*(data+4)) + 0x01;

    return true;
}
    
Bool
MOD_ADD_4(Stream data,Stream const_arg){
    size_t data_len = JUDGE(data);
    size_t const_arg_len = JUDGE(const_arg);
    size_t now_point_count = 0;

    data_len = 4;

    Uchar * now_point = data;
//    LOG(*now_point,"before mod add ");
    // if (const_arg_len != data_len ){
    //     printf("\neror exit !  info : len :%d | %d \n",const_arg_len,data_len );

    //     return false;
    // }
    //printf("data len : %d\n",data_len);
    for (;now_point_count < data_len ; now_point_count ++ ){
        *( now_point + now_point_count) ^= *(const_arg + now_point_count);
    }
    return true;
}

Bool
MOD_ADD(Stream data, Stream const_arg){
    size_t data_len = JUDGE(data);
    size_t const_arg_len = JUDGE(const_arg);
    size_t now_point_count = 0;

    data_len = 8;

    Uchar * now_point = data;
//    LOG(*now_point,"before mod add ");
    // if (const_arg_len != data_len ){
    //     printf("\neror exit !  info : len :%d | %d \n",const_arg_len,data_len );

    //     return false;
    // }
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
    printf("\t\n");
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

Bool
copy_stream(Stream dst_data, Stream res_data,int len){
    int count ;
    for(count=0;count<len; count++){
        dst_data[count] = res_data[count];
    }
    if (count == len){
        return true;
    }
    printf("not same len  in copy_stream() info : (%d,%d)\n",count,len);
    return false;
}
