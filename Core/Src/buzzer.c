#include "buzzer.h"
#include "gpio.h"
#include "run.h"
#include "delay.h"
#define CPU_FREQUENCY_MHZ 				24 // STM32时钟主频


static void Fail_Buzzer_Sound(void);
static void Buzzer_Two_KeySound(void);


/*****************************************************************
  *
  *Function Name: void BUZZER_KeySound(void)
  *Function: Key be pressed carry out sound
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void BUZZER_KeySound(void)
{
  //unsigned int m=300;//80
  unsigned int m=70;//100//80
	while(m--){

    HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
    //delay_us(600);
    delay_us(500);//460//__delay_us(300);;//__delay_us(800);//delayUS(300);
   
       

  }
}

static void Buzzer_Two_KeySound(void)
{
  //unsigned int m=300;//80
  unsigned int m=90;//100//80
	while(m--){

    HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
    //delay_us(600);
    delay_us(600);//460//__delay_us(300);;//__delay_us(800);//delayUS(300);
   
       

  }
}

/*****************************************************************
  *
  *Function Name: void BUZZER_KeySound(void)
  *Function: Key be pressed carry out sound
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void Buzzer_LongSound(void)
{
    unsigned int m=400;//400
	while(m--){

	   HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
	 //delay_us(600);//(600)__delay_us(300);//delayUS(600);
     delay_us(500);
     
    }
}
/*****************************************************************
  *
  *Function Name: void Buzzer_ShortSound(void)
  *Function: short sound
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void Buzzer_ShortSound(void)
{
    unsigned int m=50;//200
	

	 while(m--){

	   HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
	  delay_us(500);//460



	 }

}
/*****************************************************************
  *
  *Function Name: void Buzzer_ErrorSound(void)
  *Function: error sound
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void Buzzer_ErrorSound(void)
{
	unsigned int m=200;//70//80//200
  
	while(m--){

  	HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
  //delay_us(600);
     delay_us(500);  
 

  }


}

/*****************************************************************
  *
  *Function Name: void Buzzer_ErrorSound(void)
  *Function: high frequency 
  *Input Ref:NO
  *Return Ref:NO
  *
*****************************************************************/
void Buzzer_High_Sound(void)
{
     unsigned int m=50;//250
	
  
      while(m--){
          HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
          delay_us(600);//480
         
       }
}

void Buzzer_High_Sound_2(void)
{
     unsigned int m=70;//40;//100

      while(m--){
          HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
          delay_us(700);//__delay_us(500);//delayUS(99);
       }
}



/****************************************************************************
*
*Function Name:void Buzzer_Sound(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/


static void Fail_Buzzer_Sound(void)
{

	Buzzer_ErrorSound();//Buzzer_ShortSound();//Buzzer_ReSound();//fail sound has two sound //WT.EDIT 2022.09.13
    BUZZER_OFF();
	HAL_Delay(100);
	Buzzer_ErrorSound();//Buzzer_ShortSound();//Buzzer_ReSound();//fail sound has two sound 
	BUZZER_OFF();
    HAL_Delay(100);
	Buzzer_ErrorSound();
	BUZZER_OFF();
	//HAL_Delay(50);

}
/****************************************************************************
*
*Function Name:void Buzzer_Sound_Handler(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void Buzzer_Sound_Handler(void)
{

     static uint8_t sound_continuce;
    switch(run_t.buzzer_sound_tag){

	   case key_sound:
	   	    if(sound_continuce==0){
                sound_continuce++;
                BUZZER_KeySound();
              
                
            }
	        run_t.buzzer_sound_tag = buzzer_sound_null;

	  break;

	  case two_short_one_sound: //run_t.buzzer_two_short ==1
	 	   
            Buzzer_High_Sound();
	 	   	
	        run_t.buzzer_sound_tag = buzzer_sound_null;
       break;

	   case two_short_two_sound://run_t.buzzer_two_short ==2
        
	          Buzzer_Two_KeySound();//Buzzer_ShortSound(); //WT.EDIT 2022.09.13
			  HAL_Delay(200);
			  Buzzer_Two_KeySound();
          	
		 run_t.buzzer_sound_tag = buzzer_sound_null;
			

	  break;
	  

	  case high_sound://run_t.buzzer_highsound_flag==1

         Buzzer_High_Sound();
	     HAL_Delay(100);
		 Buzzer_High_Sound_2();
			
		 run_t.buzzer_sound_tag = buzzer_sound_null;
	 break;


     case  clear_eeprom_sound: //run_t.clearEeeprom_done == 1

	 
		Buzzer_LongSound(); //WT.EDIT 2022.10.05
			
	
  		run_t.buzzer_sound_tag = buzzer_sound_null;
     break;

	 case confirm_sound://run_t.buzzer_longsound_flag ==1
	 
  		Buzzer_LongSound();
	 	
		  run_t.buzzer_sound_tag = buzzer_sound_null;
     break;

	 case fail_sound://run_t.fail_sound_flag ==1)
      
	        Fail_Buzzer_Sound();
		   
     
		run_t.buzzer_sound_tag = buzzer_sound_null;
	 break;

	 case buzzer_sound_null:
       sound_continuce=0;
	 	   BUZZER_OFF() ;

	 break;


	}



}

