#include "kmp.h"
#include "run.h"




/**************************************************************************
	*
	*Function Name :unsigned char BF_Search(unsigned char *virtual,unsigned char *pattern)
	*Function : serach long string inside if has son sort string 
	*Input Ref:NO
	*Return Ref:NO
	*
**************************************************************************/
unsigned char BF_Search(uint8_t *virtual,uint8_t *pattern,uint8_t length)
{
   unsigned char m;//n;
	unsigned char i=0,j=0;
	while(i < run_t.input_digital_key_number_counter){

          if(virtual[i] == pattern[j]){ //virtual password equal real password
                 i++;
				 j++;
		         m++;
				 if(m == (length)) return 1;

		  }
		  else{
 			 m=0;
			 i++;
		     j=0;


		  }



	}

//	if(n ==5){
//         return 1;
//
//	}
//	else if(n==4){
//         return 1;
//
//	}
	return 0;
	 

}
