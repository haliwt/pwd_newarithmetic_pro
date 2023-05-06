#include "single_mode.h"
#include "run.h"
#include "led.h"
#include "touchkey.h"
#include "motor.h"
#include "buzzer.h"
#include "key.h"
#include "delay.h"



static void Save_To_EeepromNewPwd(void);
static void UnLock_Aand_SaveData_Handler(void);


/*******************************************************
 * 
 * Function Name: void Start_PowerOn_Handler(void)
 * Function: start power on handler
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
void Start_PowerOn_Handler(void)
{
    
	if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==0   && run_t.powerOn ==0){
	              run_t.powerOn++;
				  run_t.factory_test = 1;
			
				  run_t.gTimer_input_error_times_60s =0;
				 // run_t.buzzer_flag =1;
                  run_t.buzzer_sound_tag = key_sound;
				  POWER_ON();
				  run_t.backlight_label  = BACKLIGHT_FACTORY_LED;
	  
	  }
	 else{
	 	if(run_t.powerOn ==0){

			run_t.powerOn++;
			run_t.confirm_button_flag =0;
			//run_t.password_unlock =UNLOCK_MOTOR_RUN_90_ANGLE; // 4: power on is motor 1/4 angle
			run_t.motor_doing_flag = motor_null;
			run_t.gTimer_8s=0;
		
			run_t.lowPower_flag=0; //low power flag
		
			POWER_ON();
			BACKLIGHT_ON();
			BUZZER_KeySound();//WT.EDIT 2022.09.12
		           
		} 
	 }

}
/*******************************************************
 * 
 * Function Name: void Start_PowerOn_Handler(void)
 * Function: start power on handler
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
void CheckPassword_Lock_Handler(void)
{


	switch(run_t.confirm_button_flag){

	    case confirm_button_donot_pressed:
	    if(run_t.panel_lock==0 &&  run_t.factory_test ==0){
		   TouchKey_Handler();
	     }

       break;

	   case confirm_button_pressed:
	       run_t.confirm_button_flag=confirm_button_donot_pressed;
	       RunCommand_Unlock();
	    
	   break;

	   case confirm_button_unlock:
	   	
	     UnLock_Aand_SaveData_Handler();

	   break;
	}
	
}

/**************************************************************************
	*
	*Funtcion Name:static void UnLock_Aand_SaveData_Handler(void)
	*Function : to special action process 
	*Input Ref: NO
	*Return Ref:NO
	*
**************************************************************************/
static void UnLock_Aand_SaveData_Handler(void)
{
   
	switch(run_t.new_pwd_save_data_tag){


	case NEW_PWD_SAVE_DATA_TO_EEPROM: //SaveData to EEPROM //new password for the first input 
        run_t.confirm_button_flag=confirm_button_donot_pressed  ;
	    run_t.new_pwd_save_data_tag =UNLOCK_NULL;

	   Save_To_EeepromNewPwd();
    break;


    case UNLOCK_OVER_MAX_PWD_NUMBERS: // over times ten group numbers posswords 
		
		run_t.gTimer_8s=0;
		run_t.Confirm_newPassword =0; //to save new password of flag 
		run_t.inputNewPasswordTimes =0;
	    run_t.inputNewPassword_Enable =0; 
		
		
		run_t.confirm_button_flag =confirm_button_donot_pressed ;
		

		//run_t.fail_sound_flag=1; 
         run_t.buzzer_sound_tag = fail_sound;
	
		run_t.clear_inputNumbers_newpassword=0;

	
	

		//led control led
	
		run_t.backlight_label = BACKLIGHT_ERROR_BLINK;

		run_t.new_pwd_save_data_tag=UNLOCK_NULL;
		run_t.confirm_button_flag=confirm_button_donot_pressed  ;

    break;

	default :

	break;

    }


}
/*******************************************************
 * 
 * Function Name:void Save_To_EeepromNewPwd(void)
 * Function: start power on handler
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
static void Save_To_EeepromNewPwd(void)
{

	if(run_t.inputNewPassword_Enable ==1 && run_t.inputNewPasswordTimes ==2 ){//WT.EDIT .2022.09.28.if(run_t.adminiId==1){
		
		   SavePassword_To_EEPROM();
			
	 }
	run_t.gTimer_8s =0;
	run_t.inputDeepSleep_times =0;
	
	
}


