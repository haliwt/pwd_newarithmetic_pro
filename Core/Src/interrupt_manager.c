#include "interrupt_manager.h"
#include "run.h"
#include "key.h"
#include "led.h"

/*******************************************************************************
    *
    * Function Name: void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
    * Function : Interrupt function call back 
    * Input Ref: GPIO_Pin interrupt of GPIO of pin number
    * Return Ref: No
    *
*******************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   static  uint8_t touchkey=0xff;
    
   
   if(GPIO_Pin == SC12B_KEY_Pin){
       POWER_ON();
   
      if(run_t.lowPower_flag ==0){
	  	   
	 	     SystemClock_Config();
			  HAL_ResumeTick();
			  run_t.inputDeepSleep_times =0;
			  POWER_ON();

          
	  
		 run_t.lowPower_flag++;
	
      	}
      	else{
      		POWER_ON();


      	}
   }
   
   if(GPIO_Pin == KEY_Pin){
  
	   POWER_ON();
		// __HAL_GPIO_EXTI_CLEAR_IT(KEY_Pin);
		 if(run_t.lowPower_flag == 0){
				 
				  SystemClock_Config();
				  HAL_ResumeTick();
				 run_t.inputDeepSleep_times =0;
				 POWER_ON();
			 
			 run_t.lowPower_flag++;
		 
  
			 run_t.gTimer_8s=0;//WT.EDIT 2022.09.26
			
		 }
		 else{
			 POWER_ON();
		 
	 
			 run_t.gTimer_8s=0;//WT.EDIT 2022.09.26
  
		 }
  
	 }
   

	 
  }


/****************************************************************************
*
*Function Name:void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim)
*Function : half -> 16bit, TIM2 timing time is 10ms 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    static unsigned char t0;

	if(htim->Instance==TIM2){
  
    t0++;
    if(t0>99){ //10*100 =1000ms "1s"
		t0=0;
        run_t.gTimer_8s++;
        run_t.gTimer_ADC ++;
        run_t.gTimer_input_error_times_60s++;
		run_t.inputDeepSleep_times++;
		
	    
	
    }  

	}
}


