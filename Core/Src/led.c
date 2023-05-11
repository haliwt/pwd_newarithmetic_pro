#include "led.h"
#include "run.h"
#include "gpio.h"
#include "buzzer.h"
#include "eeprom.h"
#include "adc.h"
#include "touchkey.h"
#include "iwdg.h"
#include "key.h"
#include "single_mode.h"

//#define DEBUG_FLAG    




uint8_t inputNewPwd_key_flag;


void Panel_LED_Off(void)
{

          BACKLIGHT_OFF();
		  OK_LED_OFF();
		  ERR_LED_OFF();
		 // BAT_LED_OFF();

}

/****************************************************************
*
*Function Name:void DisplayLed_Handler(void)
*Function : display back light and buzzer sound 
*Input Ref:
*Return Ref:
*
****************************************************************/
void ClearEEPROM_Data_Fun(void)
{
		//erase EEPRO data 
		  if(run_t.clearEeprom==1){
			run_t.clearEeprom = 0;
			run_t.gTimer_8s =0;

			ClearEEPRO_Data();
			run_t.gTimer_8s =0;
			
			run_t.clearEeeprom_done = 1;
			run_t.inputDeepSleep_times =0;//WT.EDIT 2022.10.26
			
			run_t.buzzer_sound_tag = confirm_sound;
		
			run_t. clearEeeprom_count=0;
			//back light led control
			
			run_t.backlight_label = BACKLIGHT_OK_BLINK; //WT.EDIT 2023.03.27
			run_t.confirm_button_flag=confirm_button_donot_pressed;
			run_t.Confirm_newPassword = 0;
			 
		  }
      

}

void Panel_Lock_Handler(void)
{
	ERR_LED_ON(); 
	 if(run_t.gTimer_input_error_times_60s > 59){
			   run_t.panel_lock =0;
			   run_t.error_times = 0;
		       ERR_LED_OFF(); 
		       run_t.confirm_button_flag=confirm_button_donot_pressed;
 
	}
         
}
/****************************************************************************
*
*Function Name:void BackLight_Fun(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void BackLight_Control_Handler(void)
{
    uint8_t i;
	static uint8_t err_counter,new_pwd_counter,confirm_ok_counter;
	static uint16_t err_cnt,ok_cnt,new_counter;
	//back light turn on or turn off function

	 

	  switch(run_t.backlight_label){
   
          case BACKLIGHT_ON:
             BACKLIGHT_ON();

		    	 new_counter = 0;
                 new_pwd_counter=0;
			     err_cnt = 0;
			    err_counter=0;
				
				ok_cnt	= 0;
				confirm_ok_counter=0; 
	
			if(run_t.gTimer_8s > 8){
                run_t.gTimer_8s=6;
				run_t.inputDeepSleep_times=0;
			    run_t.keyPressed_flag =0;
				run_t.backlight_label =BACKLIGHT_AT_ONCE_OFF;
				run_t.Confirm_newPassword=0;
			}
          break;

		  case BACKLIGHT_OFF: //0X00
		  
	        // BACKLIGHT_OFF();
			  new_counter = 0;
              new_pwd_counter=0;
			  err_cnt = 0;
			  err_counter=0;
			  ok_cnt	= 0;
			  confirm_ok_counter=0; 
			run_t.gTimer_total_backling_off=0;
		    if(run_t.gTimer_8s > 8){
	             run_t.keyPressed_flag =0;
				 run_t.inputDeepSleep_times=0;
				 run_t.backlight_label =BACKLIGHT_AT_ONCE_OFF;
			}

		
          break;

		 case BACKLIGHT_AT_ONCE_OFF://2
          if(run_t.keyPressed_flag ==1){
				BACKLIGHT_ON();
              
				run_t.gTimer_8s=0;
                run_t.backlight_label = BACKLIGHT_ON;
		  }
		  else{
			 if(run_t.gTimer_8s > 8){
			 	 new_counter = 0;
                 new_pwd_counter=0;
			     err_cnt = 0;
			    err_counter=0;
				
				ok_cnt	= 0;
				confirm_ok_counter=0; 
				Panel_LED_Off();
				run_t.gTimer_total_backling_off=0;
            	run_t.backlight_label =BACKLIGHT_INPUT_STOP_MODEL;
			 }
		   }
		break;

		case BACKLIGHT_OK_BLINK://3
         ok_cnt ++ ;
		 BACKLIGHT_ON();
		 ERR_LED_OFF();
		 if(ok_cnt  < 91 ){
	
			 OK_LED_OFF();
			  
		  }
		  else if(ok_cnt >89 && ok_cnt  < 182){//500.WT.EDIT 2022.10.31
			  OK_LED_ON();
		  }
	
		  if(ok_cnt >180){ //1000.WT.EDIT 2022.10.31
		  	ok_cnt  = 0;
			confirm_ok_counter++;
           
		   }
		  
		  if(confirm_ok_counter > 2){
			  ok_cnt  = 0;
			  confirm_ok_counter=0; 

			  new_counter = 0;
              new_pwd_counter=0;

			  new_counter = 0;
              new_pwd_counter=0;

			  run_t.gTimer_8s=10;

			run_t.backlight_label =BACKLIGHT_AT_ONCE_OFF;


		  }

		
		 break;

		case BACKLIGHT_ERROR_BLINK://4
		   err_cnt ++ ;
		    BACKLIGHT_ON();
		
		    OK_LED_OFF();
	
	  
		  if(err_cnt < 91 ){
	
			  ERR_LED_OFF();
			  
		  }
		  else if(err_cnt > 89 && err_cnt < 182){
			  ERR_LED_ON();
		  }
		  if(err_cnt>180){
		  	err_cnt = 0;
			err_counter++;
			
		  }
		  
		  if(err_counter > 2){
		  	err_cnt = 0;
			err_counter=0;
		    run_t.backlight_label =BACKLIGHT_OFF;
		 
		  }
	
		break;

		case BACKLIGHT_NEW_PASSWORD_LED: //5//new input Pwd
		   new_counter ++ ;
		   BACKLIGHT_ON();
		   ERR_LED_OFF();
		   if(new_counter < 115 ){
	
			  OK_LED_OFF();
			  
		  }
		  else if(new_counter>113 && new_counter < 231){//500.WT.EDIT 2022.10.31
			  OK_LED_ON();
		  }
	
		  if(new_counter>229){ //1000.WT.EDIT 2022.10.31
		  	new_counter = 0;
            new_pwd_counter++;
		  }
		  
		    
		    
		if(new_pwd_counter>9){

		    new_counter = 0;
            new_pwd_counter=0;
					
			run_t.inputNewPassword_Enable =0;
			run_t.backlight_label =BACKLIGHT_AT_ONCE_OFF;
					 
		}
                  
	   break;

		case BACKLIGHT_ERROR_OVER_INPUT_TIMES://6
			    run_t.keyPressed_flag =0;
		        BACKLIGHT_OFF();
				ERR_LED_OFF();
		        if(run_t.panel_lock==0){
                  run_t.backlight_label =BACKLIGHT_AT_ONCE_OFF;
		        }
		break;


		case BACKLIGHT_FACTORY_LED://7
		  BACKLIGHT_ON();
		  OK_LED_ON();
		  ERR_LED_ON();
		  BAT_LED_ON();
	
		if(run_t.gTimer_input_error_times_60s > 59){
			run_t.factory_test =0;
			run_t.gTimer_8s=10;
			  BACKLIGHT_OFF();
			  OK_LED_OFF();
			  ERR_LED_OFF();
			  BAT_LED_OFF();
	          run_t.backlight_label =BACKLIGHT_AT_ONCE_OFF;
		}
	
	    break;

		case BACKLIGHT_INPUT_STOP_MODEL: //8
		

            run_t.confirm_button_flag =0 ;
			run_t.powerOn =3;

			run_t.keyPressed_flag=0;
			run_t.password_unlock=0;
		    

			//clear new password flag
			run_t.inputNewPassword_Enable =0; //WT.EDIT 2022.09.28
			run_t.input_digital_key_number_counter =0;
			run_t.clear_inputNumbers_newpassword=0;
			
			//wake up touch key
		

	
			
			for(i=0;i<6;i++){ //WT.EDIT .2022.08.13
					*(pwd2 + i)=0;//pwd2[i]=0;
					*(Readpwd+i)=0;
					*(pwd1+i)=0;//pwd1[i]=0;

			}
			  POWER_OFF();
			  Panel_LED_Off();
			  HAL_ADC_Stop(&hadc);
		     

              if(run_t.inputDeepSleep_times > 19){  //wait 30s  
			   run_t.inputDeepSleep_times =0;

			   #ifdef DEBUG_FLAG

			       GPIO_Standby_Init();

			   #endif 
          		/*close tick timer low power Mode */
		
			    run_t.lowPower_flag=0;
              //  __HAL_IWDG_START(__HANDLE__)
				//HAL_SuspendTick();
				SysTick->CTRL = 0x00;//关闭定时器
                SysTick->VAL = 0x00;//清空val,清空定时器
				
				/* input low power mode "STOP"*/
				//__HAL_RCC_PWR_CLK_ENABLE();
		        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);//WFI ->wait for interrupt

                SystemClock_Config();//Low power of low frequency 8MHz
			   
		  }
		  break;
		}
		//ClearEEPROM_Data_Fun();
	    ADC_Detected_LowVoltage();
	    if(run_t.gTimer_total_backling_off > 180){
			run_t.gTimer_total_backling_off=0;
		  	Panel_LED_Off();

	     }
      
}

