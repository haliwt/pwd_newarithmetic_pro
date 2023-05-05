#include "motor.h"
#include "run.h"
#include "single_mode.h"
#include "led.h"
#include "buzzer.h"

static void MotorStart_CW_Step(void);//Up 
static void MotorStart_CCW_Step(void);
uint8_t ccw_flag,cw_flag;

/**********************************************************
 *
 * Function Name: void Motor_CCW_Run(void) 
 * Function : Open lock 
 * Input Ref: NO
 * Return Ref:NO
 *
 *********************************************************/
void Motor_CCW_Run(void) 
{
    if(ccw_flag==0){
        ccw_flag++;
        cw_flag=0;
       MotorStart_CCW_Step();
    }
    MOTOR_CCW_RUN();
   // MOTOR_CW_OFF();	
	
}
/**********************************************************
 *
 * Function Name: void Motor_CW_Run(void)
 * Function : shut off  lock 
 * Input Ref: NO
 * Return Ref:NO
 *
 *********************************************************/
void Motor_CW_Run(void)
{

     if(cw_flag==0){
       cw_flag++;
       ccw_flag=0;
       MotorStart_CW_Step();
     }
	 MOTOR_CW_RUN();	
	// MOTOR_CCW_OFF();
	
}



void Motor_Stop(void)
{
    MOTOR_CW_OFF(); //brake
    MOTOR_CCW_OFF(); //brake
}
/**
 * @brief 
 * 
 */
 static void MotorStart_CW_Step(void)//Up 
{
	
       MOTOR_CCW_OFF();
        
    //    MOTOR_CW_RUN();	
	   // HAL_Delay(25);//__delay_ms(25);
	   // MOTOR_CW_OFF();
	   // HAL_Delay(25);//__delay_ms(25);
       MOTOR_CW_RUN();	
       HAL_Delay(10);//__delay_ms(50);
	  
   
}

 static void MotorStart_CCW_Step(void)
{
   
        
      	MOTOR_CW_OFF();	
	
	   // MOTOR_CCW_RUN();
	   // HAL_Delay(25);//__delay_ms(50);
	   //  MOTOR_CCW_OFF();
	   // HAL_Delay(25);//__delay_ms(50);
       MOTOR_CCW_RUN();
	   HAL_Delay(10);
        
   }

 

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

		switch(run_t.motor_doing_flag){

		case motor_foreward:
			run_t.gTimer_8s =0;//WT.EDIT.2022.10.06
			run_t.confirm_button_flag = confirm_button_donot_pressed;
			run_t.motorRunCount++;

			if(run_t.motor_return_homePosition==0 ){
				run_t.motor_return_homePosition= 1; 
				Buzzer_LongSound(); //WT.EDIT 2022.10.06
				Motor_CCW_Run();//open lock 
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

			if(run_t.motorRunCount>160 && run_t.motorRunCount <200){
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

			if(run_t.motorRunCount >199){
                run_t.motorRunCount=0;
				run_t.motor_doing_flag=motor_revesal;
				run_t.motor_returnRun_flag =1;
				led=0;
			}
          
		  break;

		  case motor_revesal:
             run_t.returnHomePosition_Count++;
			run_t.gTimer_8s =0;
		     run_t.inputDeepSleep_times =0;
			if(run_t.motorRunCount <200){
			    Motor_CW_Run();// Close
			    
			}
			
			if(run_t.returnHomePosition_Count > 199){
			    Motor_Stop();
				
				run_t.motor_return_homePosition=0;//WT.EDIT 2022.08.18
				run_t.motor_returnRun_flag =0;
				 run_t.motor_doing_flag=motor_null;
				run_t.oneself_copy_behavior=0;
                
                run_t.led_error_flag=0;
				run_t.led_ok_flag =0;
				//led control gpio
				run_t.gTimer_8s =10;//WT.EDIT 2022.10.06
				run_t.backlight_label =BACKLIGHT_AT_ONCE_OFF;
			}

		
		  break;

		  case motor_null:


		  break;
		  
		  default:

		  break;
	   }
}

