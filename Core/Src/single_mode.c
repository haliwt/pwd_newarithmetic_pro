#include "single_mode.h"
#include "run.h"
#include "led.h"
#include "touchkey.h"
#include "motor.h"
#include "buzzer.h"
#include "key.h"
#include "delay.h"



static void Save_To_EeepromNewPwd(void);
static void UnLock_And_SaveData_Handler(void);
static void Over_Input_MaxDigital_Fun(void);

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
				
                  run_t.buzzer_sound_tag = key_sound;
				  POWER_ON();
				   run_t.confirm_button_flag =confirm_button_donot_pressed;
				  run_t.backlight_label  = BACKLIGHT_FACTORY_LED;
	  
	  }
	 else{
	 	if(run_t.powerOn ==0){

			run_t.powerOn++;
			run_t.confirm_button_flag =confirm_button_donot_pressed;
			run_t.gTimer_8s=0;
		
			POWER_ON();
			BACKLIGHT_ON();
			OK_LED_OFF();
			ERR_LED_OFF();
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
	     if(run_t.factory_test == 0)
		    TouchKey_Handler();//TouchKey_Handler();
	   

       break;

	   case confirm_button_pressed_unlock:
	       RunCommand_Unlock();
	    
	   break;

	   case confirm_button_save_new_password:
	   	
	      Save_To_EeepromNewPwd();//UnLock_And_SaveData_Handler();

	   break;
       
       case confirm_button_clearn_eeprom:
	   	  ClearEEPROM_Data_Fun();
       
       break;
       
      case confirm_button_over_numbers:
			 Over_Input_MaxDigital_Fun();
	   break;
       
       case confirm_button_error_times:
           run_t.gTimer_input_error_times_60s =0;
           run_t.panel_lock=1;
           run_t.gTimer_8s=0;
           run_t.backlight_label= BACKLIGHT_ERROR_OVER_INPUT_TIMES; 
           run_t.confirm_button_flag=confirm_button_lock_panel;
       
       break;

	   case confirm_button_lock_panel:
          Panel_Lock_Handler();
       break;

	  
	}
	
}

/**************************************************************************
	*
	*Funtcion Name:static void Over_Input_MaxDigital_Fun(void)
	*Function : to special action process 
	*Input Ref: NO
	*Return Ref:NO
	*
**************************************************************************/
static void Over_Input_MaxDigital_Fun(void)
{
		run_t.gTimer_8s=0;
		
		run_t.Confirm_newPassword =0; //to save new password of flag 
		run_t.inputNewPasswordTimes =0;
	    run_t.inputNewPassword_Enable =0; 
		run_t.buzzer_sound_tag = fail_sound;
	
		run_t.clear_inputNumbers_newpassword=0;

	    run_t.backlight_label = BACKLIGHT_ERROR_BLINK;
		run_t.confirm_button_flag=confirm_button_donot_pressed  ;




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


