#include "CIPHER.h"

int
main(){
	printf("function test :\n");
	uchar t = 0x0f;
	int n = strlen("hello");
	size_t n2 = strlen("hello");
	printf(" int : %d\n size_t : %d\n",n,n2);
	
	printf("LOG test :\n");
	LOG(&t,"testing ");
	stream test_data ;
	printf(" %s \n",test_data);
	test_data =  (stream) new ( (stream) test_data, 20);

	printf(" %s \nlen : %d \n",test_data, strlen(test_data) );

	for (; t != NULL ; ){
		LEFT_SHIFT(&t );
		printf(" uchar : %8lu \n",t);
	}	
	printf("hello world\n");
	printf("uchar :  %d \n",sizeof(uchar));
	
	printf("############# test ok ############################\n\t--------------------- load process -----------------------\n");
	stream test_data2  = (stream ) new ((stream) test_data2, 3);
	stream const_data = (stream ) new ((stream ) const_data ,3);
	* const_data =  0xaa;
	* (const_data +1 ) = 0xaa;
	* (const_data +2 ) = 0xaa;	
	int index = 0;
	for(;index < 24 ; index ++ ){
	    printf("\nindex : %d \n ",index);
	    test_data2 =  n_DSR(test_data2, const_data , &JUDGE );
	    LOG(test_data2,"Result ") ;
	}
	return OK;

}
