#include "buzzer.h"
#include "gpio.h"
#include "run.h"
#include "delay.h"
#define CPU_FREQUENCY_MHZ 24 // STM32时钟主频
static void Buzzer_RunSound(void);
static void  Buzzer_InputNewPassword_two_short(void);
static void Fail_Buzzer_Sound(void);

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
  unsigned int m=100;//80
	while(m--){

    HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
    //delay_us(600);
    delay_us(500);//460//__delay_us(300);;//__delay_us(800);//delayUS(300);
   
       

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
    unsigned int m=200;
	

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
	unsigned int m=200;//80
  
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
     unsigned int m=80;//250
	
  
      while(m--){
          HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
          delay_us(500);//480
         
       }
}

void Buzzer_High_Sound_2(void)
{
     unsigned int m=100;//

      while(m--){
          HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);//BEEP=!BEEP;
          delay_us(500);//__delay_us(500);//delayUS(99);
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
static void Buzzer_RunSound(void)
{

	 if(run_t.clearEeeprom_done == 1){
		  	run_t.clearEeeprom_done = 0;

			Buzzer_LongSound(); //WT.EDIT 2022.10.05
		}
  
  
  
   if(run_t.buzzer_longsound_flag ==1 && run_t.fail_sound_flag ==0){
		   run_t.buzzer_longsound_flag =0;
		   run_t.buzzer_flag =0;
		   Buzzer_LongSound();
		  
	      
	 }
    else{


	 if(run_t.fail_sound_flag ==1){
	 	  run_t.fail_sound_flag=0; //WT.EDIT 2022.10.06
		   Fail_Buzzer_Sound();
	       run_t.buzzer_flag=0;//WT.EDIT 2022.10.19
		}
		else if(run_t.buzzer_flag ==1){
			run_t.buzzer_flag =0;//WT.EDIT 2022.10.06
		    BUZZER_KeySound();
		}

     }	
}

static void Fail_Buzzer_Sound(void)
{

	Buzzer_ErrorSound();//Buzzer_ShortSound();//Buzzer_ReSound();//fail sound has two sound //WT.EDIT 2022.09.13
    BUZZER_OFF();
	HAL_Delay(50);
	Buzzer_ErrorSound();//Buzzer_ShortSound();//Buzzer_ReSound();//fail sound has two sound 
	BUZZER_OFF();
    HAL_Delay(50);
	Buzzer_ErrorSound();
	BUZZER_OFF();
	//HAL_Delay(50);

}
/****************************************************************************
*
*Function Name:void  Buzzer_InputNewPassword_two_short(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static void  Buzzer_InputNewPassword_two_short(void)
{

     if(run_t.fail_sound_flag==0){//WT.EDIT 2022.10.06
	 	
      if(run_t.buzzer_two_short ==1){
	  	  
          run_t.buzzer_two_short =0;
		   run_t.inputDeepSleep_times =0; //WT.EDIT 2022.10.26
		   run_t.gTimer_8s=0;
          Buzzer_High_Sound();
	      run_t.buzzer_flag =0;
		
		 }


      if(run_t.buzzer_two_short ==2){
          run_t.buzzer_two_short =0;
		        run_t.inputDeepSleep_times =0;//WT.EDIT 2022.10.26
                run_t.gTimer_8s=0;
                BUZZER_KeySound();//Buzzer_ShortSound(); //WT.EDIT 2022.09.13
				HAL_Delay(50);
				BUZZER_KeySound();
				run_t.buzzer_flag =0;
		
			

        }
	  
     }

	 if(run_t.buzzer_highsound_flag==1){
	     run_t.buzzer_highsound_flag=0;
          Buzzer_High_Sound();
          HAL_Delay(50);
	      Buzzer_High_Sound_2();
	 


	 }

}

void Buzzer_Sound_Handler(void)
{

     Buzzer_RunSound();

     Buzzer_InputNewPassword_two_short();



}

