#include "funpointer.h"
#include "single_mode.h"
#include "run.h"
#include "led.h"
#include "eeprom.h"
#include "kmp.h"
#include "buzzer.h"
#include "touchkey.h"
#include "motor.h"


/****************************************************************************
*
*Function Name:void RunMotor_Definite_Handler(void) 
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void RunMotor_Definite_Handler(void) //definite motor
{

        static uint8_t led=0;

		if(run_t.motor_doing_flag==1){//open lock doing

		        run_t.gTimer_8s =0;//WT.EDIT.2022.10.06
                run_t.confirm_button_flag = confirm_button_donot_pressed;
			    run_t.motorRunCount++;
		
				if(run_t.motor_return_homePosition==0 ){
				 	run_t.motor_return_homePosition= 1; 
				    Buzzer_LongSound(); //WT.EDIT 2022.10.06
				    Motor_CCW_Run();//open passwordlock 
					  run_t.led_ok_flag=1;
					 run_t.led_error_flag =0;
				     run_t.buzzer_flag=0;
					 run_t.lock_fail=0;
					 ERR_LED_OFF();
				     OK_LED_ON();
					
			
						 run_t.eepromAddress=0;
						 
						
						 run_t.error_times=0;
						
						 run_t.gTimer_8s =0;//WT.EDIT.2022.10.06

						 run_t.returnHomePosition_Count=0;
						 run_t.password_unlock=0;
				 }
			     
				 if(run_t.motorRunCount>1600 && run_t.motorRunCount <2101){
					 Motor_Stop();
					 if(led==0){
					 	led++;
				         run_t.led_ok_flag =0;
					     run_t.led_error_flag=0;
					     run_t.backlight_label =BACKLIGHT_ON;
					   
					 }
					  run_t.inputDeepSleep_times =0;
				      run_t.gTimer_8s =0;//WT.EDIT.2022.10.06
					}
				 
                  if(run_t.motorRunCount >2099){
				      run_t.motor_doing_flag=0;
				      run_t.motor_returnRun_flag =1;
				      led=0;
                  }
          

          }
		
         /*--------motor return run back home position--------*/
		  if(run_t.motor_returnRun_flag ==1){
		
			run_t.returnHomePosition_Count++;
			run_t.gTimer_8s =0;
		     run_t.inputDeepSleep_times =0;
			if(run_t.motorRunCount >1499){
			    Motor_CW_Run();// Close
			    run_t.motorRunCount =0;
			}
			
			if(run_t.returnHomePosition_Count > 1613){
			    Motor_Stop();
				
				run_t.motor_return_homePosition=0;//WT.EDIT 2022.08.18
				run_t.motor_returnRun_flag =0;
				run_t.oneself_copy_behavior=0;
                
                run_t.led_error_flag=0;
				run_t.led_ok_flag =0;
				//led control gpio
				run_t.gTimer_8s =10;//WT.EDIT 2022.10.06
				run_t.backlight_label =BACKLIGHT_AT_ONCE_OFF;
			}

		  }
}
