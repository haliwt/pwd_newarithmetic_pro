#ifndef __RUN_H_
#define __RUN_H_
#include "main.h"

#define ADMINI     		0x00 //0X00
#define USER_1     		0X08
#define USER_2     		0X10
#define USER_3     		0X18
#define USER_4    	 	0X20  
#define USER_5     		0X28
#define USER_6    	 	0X30
#define USER_7    	 	0X38  
#define USER_8     		0X40
#define USER_9     		0x48
#define USER_10    	 	0x50
#define USER_11         0x58

#define ADMIN_SAVE_ADD         0x80  //administrator of be save 
#define USER_SAVE_ADD_1        0X81
#define USER_SAVE_ADD_2        0x82

//new FPC board
typedef enum 
{
   SPECIAL_1 =0x8000,KEY_1=0x100, KEY_2=0x80, KEY_3=0x40, KEY_4=0x20, KEY_5=0x10,
   KEY_6= 0x4000, KEY_7=0x2000, KEY_8=0x1000, KEY_9=0x800, KEY_0=0x400, SPECIAL_2=0x200

}TouchKey_Numbers;


typedef enum _unlock_state{

	UNLOCK_NULL,
	UNLOCK_FAIL,
	UNLOCK_SUCCESS,
	
}unlock_state_t;

typedef enum _new_password_save_t{

    NEW_PWD_SAVE_DATA_TO_EEPROM=0x01,
	UNLOCK_OVER_MAX_PWD_NUMBERS



}new_password_save_t;


typedef struct __RUN_T{
	//enum State state_;
    //unsigned char cmdCtr_;   //event order cunter

    unsigned char powerOn;
	uint8_t   getTouchkey;
	uint8_t   getSpecial_1_key;
	uint8_t   getSpecial_2_key;
	uint8_t   getNumbers_key;
	
	uint8_t   keyPressed_flag;

	
	uint8_t  clearEeeprom_count;
	uint8_t  backlight_label;
	
	
	
	uint8_t Confirm_newPassword;
	uint8_t inputNewPasswordTimes;

	uint8_t motor_return_homePosition;
    uint8_t error_times;
	uint8_t panel_lock;
	uint8_t lock_fail;
	uint8_t inputDeepSleep_times;
	uint8_t clearEeprom;
    
    uint8_t eepromAddress;
    uint8_t ADC_times;




    uint8_t inputNewPassword_Enable;
	
    uint8_t clear_inputNumbers_newpassword;
	uint8_t inputNewPwd_OK_led_blank_times;
	uint8_t motor_doing_flag;

    
    
	uint8_t BackLight;

	
	//buzzer sound
	

	uint8_t buzzer_sound_tag;

	//new password
    uint8_t new_pwd_save_data_tag;
	
	uint8_t input_digital_key_number_counter;
	uint8_t  confirm_button_flag;
	uint8_t  password_unlock;
	uint8_t       led_ok_flag;
	uint8_t 	  led_error_flag ;
	uint8_t       Led_battery_flag;
	
    

	uint8_t factory_test;
	uint8_t lowPower_flag;
	uint8_t oneself_copy_behavior;
  
	


	uint8_t clearEeeprom_done;
	
	uint8_t gTimer_8s;
	uint8_t  gTimer_ADC;
	
	uint8_t  gTimer_input_error_times_60s;
	

     uint8_t readEepromData;

	uint16_t motorRunCount;
	uint16_t   returnHomePosition_Count;

	uint32_t userId;
    
	
}RUN_T;


extern RUN_T run_t;
extern uint8_t pwd1[6];
extern uint8_t pwd2[6];
extern uint8_t Readpwd[6];




extern void (*RunChed_KeyMode)(uint16_t keydat);

void RunCommand_Unlock(void);


void SavePassword_To_EEPROM(void);

void CParserDispatch(void);


void RunCheck_KeyMode_Handler(void(*keymode_handler)(uint16_t keydat));

void ReadPassword_EEPROM_SaveData(void);

uint8_t  CompareValue(uint8_t *pt1,uint8_t *pt2);

unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number);

uint8_t OverNumbers_Password_Handler(void);

#endif 



