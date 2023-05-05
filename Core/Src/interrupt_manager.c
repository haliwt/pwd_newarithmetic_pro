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
    
    if(GPIO_Pin == KEY_Pin){


	    __HAL_GPIO_EXTI_CLEAR_IT(KEY_Pin);
	    if(run_t.lowPower_flag == 0){
		 	
				 SystemClock_Config();
			     HAL_ResumeTick();
			    run_t.inputDeepSleep_times =0;
			 	POWER_ON();
			
			run_t.lowPower_flag++;
			run_t.readI2C_data =1;//WT.EDIT 2022.09.26 jump the "if(run_t.touchkey_first_turn_on_led==1 && run_t.panel_lock ==0)"
			run_t.touchkey_first_turn_on_led =1;//WT.EDIT 2022.09.26
		    run_t.gTimer_8s=0;//WT.EDIT 2022.09.26
		   
	    }
	    else{
	    	POWER_ON();
	    	run_t.readI2C_data =1;//WT.EDIT 2022.09.26 jump the "if(run_t.touchkey_first_turn_on_led==1 && run_t.panel_lock ==0)"
			run_t.touchkey_first_turn_on_led =1;//WT.EDIT 2022.09.26
		    run_t.gTimer_8s=0;//WT.EDIT 2022.09.26

	    }

	}

   if(GPIO_Pin == SC12B_KEY_Pin){
   
      __HAL_GPIO_EXTI_CLEAR_IT(SC12B_KEY_Pin);//WT.EDIT 2022.09.09
      if(run_t.lowPower_flag <3){
	 	     SystemClock_Config();
			  HAL_ResumeTick();
			  run_t.inputDeepSleep_times =0;
			  POWER_ON();

          
	  
		 run_t.lowPower_flag++;
		 if(touchkey != run_t.touchkey_first && run_t.Confirm_newPassword ==0){//2022.10.19
		 	  touchkey = run_t.touchkey_first;
		      run_t.readI2C_data =0;//WT.EDIT 2022.09.26
			  run_t.gTimer_200ms=0;
			  run_t.gTimer_8s=0;//WT.EDIT 2022.10.08
		 }
      	}
      	else{
      		POWER_ON();


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
    
	run_t.gTimer_200ms ++;
    if(t0>99){ //10*100 =1000ms "1s"
       t0=0;
	   
	  run_t.gTimer_10s_start++;
	   
	   
	   run_t.gTimer_8s++;
	   run_t.gTimer_10s ++;
	   run_t.gTimer_ADC ++;
	  
	   if(run_t.gTimer_10s_start>9){ //10s
		 run_t.gTimer_10s_start=0;
		 run_t.gTimer_input_error_times_60s++;
	     run_t.inputDeepSleep_times++;
		
	    

	   }
	
    }  

	}
}


