#include "run.h"
#include "eeprom.h"
#include "led.h"
#include "buzzer.h"
#include "motor.h"
#include "kmp.h"
#include "single_mode.h"
#include "key.h"

RUN_T run_t;

uint8_t compare_value;

uint8_t readFlag[1]={0};
uint8_t pwd1[6];
uint8_t pwd2[6];
uint8_t origin_pwd[6]={1,2,3,4,0,0};

uint8_t Readpwd[6];
uint32_t eevalue ;
__IO uint8_t readpwd_array_length;


void (*RunChed_KeyMode)(uint16_t keydat);
void (*ClearVirtual_Numbers)(void);

static void Read_Administrator_Password(void);
static void ClearVirtual_Aarray_Fun(void);


void Run_Init(void)
{
    Clear_VirtualArray_Numbers(ClearVirtual_Aarray_Fun);


}

/****************************************************************************
*
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
uint8_t CompareValue(uint8_t *pt1,uint8_t *pt2)
{
	unsigned char i ;
   for(i=0;i<6;i++){
		if(*(pt1+i) != *(pt2+i)){
			return 0;
		}
		
	}
	return 1;
   
}
/****************************************************************************
*
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void SavePassword_To_EEPROM(void)
{
   static uint8_t eeNumbers;
   static uint8_t initvalue =0x01;
   run_t.gTimer_8s=0;
  for(eeNumbers =0; eeNumbers< 11;eeNumbers++){// password is ten numbers
      
	  switch(eeNumbers){	  
		   case 0:
		
			  run_t.userId= ADMINI;
				
		   break;

		   case 1 :
		        run_t.userId = USER_1;
			break;
		  
		   case 2: 
				run_t.userId = USER_2; 
			break;
		   
		   case 3 :
		     run_t.userId = USER_3; 
				
			break;
		   
		   case 4: 
	           run_t.userId = USER_4; 
			break;

		   case 5 :
		       run_t.userId = USER_5;  
			break;
		   
		   case 6: 
		        run_t.userId = USER_6; 
			
		    break;
		   case 7 :
		
		        run_t.userId = USER_7; 
			
		    break;
		   
		   case 8: 
		
			  run_t.userId = USER_8; 
			break;
		   
		   case 9 :
	
			run_t.userId = USER_9; 
				
			break;


		   case 10:
		   	  	run_t.gTimer_8s=0;
				run_t.Confirm_newPassword =0; //to save new password of flag 
				
				run_t.new_pwd_save_data_tag = UNLOCK_NULL;
				run_t.confirm_button_flag=confirm_button_donot_pressed;
				run_t.inputNewPasswordTimes =0;
				

				//run_t.fail_sound_flag=1; //WT.EDIT 2022.10.06
				run_t.buzzer_sound_tag = fail_sound;
				//eeprom ref	
		 
		        run_t.inputNewPassword_Enable =0; //WT.EDIT 2022.09.28
				run_t.keyPressed_flag =0; //WT.EDIT 2023.02.13

				//led error control 
	
				run_t.backlight_label = BACKLIGHT_ERROR_BLINK;
				
			   return ;			
				
		   break;

		  }

        EEPROM_Read_Byte(run_t.userId,&run_t.readEepromData,1);
		HAL_Delay(5);
		if(run_t.readEepromData !=1){
	 
             compare_value =CompareValue(pwd1, pwd2);
			
			 if(compare_value ==1){ //be save data to eeprom flag 
		 	     
		         EEPROM_Write_Byte(run_t.userId ,&initvalue,1);
				 HAL_Delay(5);
				 EEPROM_Write_Byte(run_t.userId + 0x01,pwd1,6);
				 HAL_Delay(5);
			 
	           
				//clear data reference 
				run_t.Confirm_newPassword =0;
				run_t.inputNewPassword_Enable =0; 
			    run_t.inputNewPasswordTimes = 0;
				run_t.input_digital_key_number_counter =0 ;
				
			    run_t.buzzer_sound_tag = confirm_sound;
				run_t.clear_inputNumbers_newpassword=0;

				run_t.password_unlock=UNLOCK_NULL;
				run_t.new_pwd_save_data_tag = UNLOCK_NULL;
				run_t.confirm_button_flag=confirm_button_donot_pressed;
		      
		      
	             //led control
				run_t.gTimer_8s=10;
			
			
				run_t.backlight_label = BACKLIGHT_OK_BLINK;
				
				return ;
			
			

			 }
			 else{
			 	//error
				run_t.inputNewPasswordTimes =0;
				run_t.Confirm_newPassword =0; 
			    run_t.inputNewPassword_Enable =0; 
				run_t.input_digital_key_number_counter =0 ;

				run_t.password_unlock=UNLOCK_NULL;
				run_t.new_pwd_save_data_tag = UNLOCK_NULL;
				run_t.confirm_button_flag=confirm_button_donot_pressed;
                 
      
				//run_t.fail_sound_flag=1;
				run_t.buzzer_sound_tag = fail_sound;
				//run_t.buzzer_longsound_flag =0;
			
				run_t.inputDeepSleep_times =0;
		
				run_t.clear_inputNumbers_newpassword=0;

	
				run_t.gTimer_8s=3;//WT.EDIT 2023.02.11
			
				run_t.backlight_label = BACKLIGHT_ERROR_BLINK;
				return ;
			}
              
		}
		
    }
		
}



/****************************************************************************
*
*Function Name:void RunCheck_Mode(unsigned int dat)
*Function : Read from EEPROM data. 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void RunCommand_Unlock(void)
{

     uint8_t i;

      run_t.gTimer_8s=0;//WT.EDIT 2022.09.28
	 if(run_t.Confirm_newPassword == 1){
	 	
	 	Read_Administrator_Password();//WT.EDIT 2022.010.07
	 }
	 else
		ReadPassword_EEPROM_SaveData();
     
	
	  //if(Fail == 1){//open lock  is fail run_t.unloak_flag =
       switch(run_t.password_unlock){

	   case UNLOCK_FAIL: //1
	   
	    run_t.password_unlock=UNLOCK_NULL;
	    run_t.confirm_button_flag=confirm_button_donot_pressed;
		run_t.Confirm_newPassword=0;
		
        run_t.gTimer_8s=0;
		OK_LED_OFF();
		ERR_LED_ON();
		//led

		
		run_t.backlight_label = BACKLIGHT_ERROR_BLINK;
		//others ref
		run_t.oneself_copy_behavior =0;//WT.EDIT 2022.10.28
		run_t.clear_inputNumbers_newpassword=0; 
	
		//eeprom ref
		run_t.eepromAddress=0;
		//key
		run_t.keyPressed_flag=0;
        
		run_t.error_times ++ ; //input times 5 ,
		if(run_t.error_times > 4){
			
			run_t.gTimer_input_error_times_60s =0;
            run_t.panel_lock=1;
			run_t.gTimer_8s=0;//WT.EDIT 2022.09.28
			run_t.backlight_label= BACKLIGHT_ERROR_OVER_INPUT_TIMES;    
		}
		//new input pwd ref
        run_t.Confirm_newPassword =0;
	    run_t.inputNewPassword_Enable =0;
		run_t.buzzer_sound_tag = fail_sound;
		
	    for(i=0;i<6;i++){
	  	   pwd1[i]=0;
		   Readpwd[i]=0;
		   pwd2[i]=0;
		   virtualPwd[i]=0;
		   
		
		 }

	   ClearVirtual_Numbers();
	  break;

	  case UNLOCK_SUCCESS://2


	     switch(run_t.Confirm_newPassword){

		 case 1: //set input new password 
			ERR_LED_OFF();
			OK_LED_ON();
		   
			run_t.password_unlock=UNLOCK_NULL;
			run_t.confirm_button_flag=confirm_button_donot_pressed;
			
			run_t.inputNewPassword_Enable =1; //Input Administrator password is OK
			run_t.Confirm_newPassword=0;
			run_t.inputNewPasswordTimes=0;
			run_t.input_digital_key_number_counter =0;
			
			run_t.eepromAddress=0;
	
			

			//run_t.buzzer_highsound_flag =1; //WT.EDIT 2022.10.28
			run_t.buzzer_sound_tag = high_sound;
			run_t.inputDeepSleep_times =0;
			run_t.error_times=0;
		
			

		    run_t.keyPressed_flag=0; //WT.EDIT 2023.
		    //led control 
		    run_t.gTimer_8s = 0;
		
			run_t.backlight_label = BACKLIGHT_NEW_PASSWORD_LED;
			//buzzzer sound
			for(i=0;i<6;i++){
		  	   pwd1[i]=0;
			  // Readpwd[i]=0;
			  // pwd2[i]=0;
			  // virtualPwd[i]=0;
				
			}
			
		//ClearVirtual_Numbers();
		
		break;

		case 0:
		   switch(run_t.oneself_copy_behavior){
		   	case 1:
	             run_t.gTimer_8s=0;
                
		        ERR_LED_OFF();
		        OK_LED_ON();
		
	
			    run_t.backlight_label = BACKLIGHT_OK_BLINK;
				run_t.oneself_copy_behavior=0;
				run_t.password_unlock = UNLOCK_NULL;
				run_t.confirm_button_flag=confirm_button_donot_pressed;
				run_t.confirm_button_flag = 0;
				run_t.inputDeepSleep_times =0;
				  for(i=0;i<6;i++){
				  	   pwd1[i]=0;
					   Readpwd[i]=0;
					   pwd2[i]=0;
					   virtualPwd[i]=0;
				
				  	}
               run_t.keyPressed_flag=0; //WT.EDIT 2023.
               run_t.buzzer_sound_tag = confirm_sound;
			  ClearVirtual_Numbers();
		 
		   break;
		   
		   case 0:
        
               run_t.motor_doing_flag=1;
			   run_t.backlight_label = BACKLIGHT_OK_BLINK;
			   run_t.password_unlock=UNLOCK_NULL;
		       run_t.confirm_button_flag = confirm_button_donot_pressed;
			 
			   run_t.inputDeepSleep_times =0;
			   run_t.keyPressed_flag=0; //WT.EDIT 2023.
				   
		       for(i=0;i<6;i++){
			  	   pwd1[i]=0;
				   Readpwd[i]=0;
				   pwd2[i]=0;
			      virtualPwd[i]=0;
			  	}

			   ClearVirtual_Numbers();
			   
		   break;
		   }
		  break;
	    }
		
		break; 
		 
		 
	  }
		
}
/****************************************************************************
*
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static void Read_Administrator_Password(void)
{
     
	  static unsigned char value,lenth;
	  static uint32_t    ReadAddress; 
      uint8_t i;

	 for(run_t.eepromAddress =0; run_t.eepromAddress <3;run_t.eepromAddress++){ //2022.10.07 be changed ten password 
	  
	    switch(run_t.eepromAddress){
	
				 case 0:
					  ReadAddress = ADMINI;
				 break;
				 
				 case 1:
					 ReadAddress = USER_1;
				  
			   break;
	
			   case 2:
					 ReadAddress = USER_2;
			   break;

			   default:

			   break;
	
			  
	
		   }

      
	   if(run_t.eepromAddress <3){
	   	 
		    run_t.gTimer_8s =0;//
		    EEPROM_Read_Byte(ReadAddress,readFlag,1);
		    HAL_Delay(5);
		   if(readFlag[0] ==1){// has a been saved pwassword 

                    
					EEPROM_Read_Byte(ReadAddress+0x01,Readpwd,6);
					HAL_Delay(5);
					
                    lenth= sizeof(Readpwd)/(sizeof(Readpwd[0]));
                    if(run_t.input_digital_key_number_counter > (lenth-1)){
 
                        value = BF_Search(virtualPwd,Readpwd,lenth);
						run_t.clear_virtual_numbers =1;
					}
					else
					    value = CompareValue(Readpwd,pwd1);
					
					
					if(value==1)//if(strcmp(pwd1,pwd2)==0)
					{
						readFlag[0]=0;
						
						run_t.password_unlock=UNLOCK_SUCCESS;
						//run_t.confirm_button_flag=confirm_button_unlock;
						  run_t.gTimer_8s =0;//
						  run_t.keyPressed_flag=0; //WT.EDIT 2023.
						return ;

					}
					else{ // pass word compare is error 
					     run_t.gTimer_8s =0;
						 run_t.keyPressed_flag=1;
						
                        
                   	}
						
		   	}
          
		   
		   if(run_t.eepromAddress==2){ //don't has a empty space,default password is  "1,2,3,4" ,don't be write new  password

			        ReadAddress = ADMINI;
                    EEPROM_Read_Byte(ReadAddress,readFlag,1);
                    HAL_Delay(5);
                   if(readFlag[0] ==0){

				    
                     if(run_t.input_digital_key_number_counter > 4){//6 default is 4 nuber adminstrator "1,2,3,4"
 
                            value=0;
							    
                         //value = BF_Search(virtualPwd,origin_pwd);
					 }
                    else
					 value =CompareValue(origin_pwd, pwd1);

				   if(value==1){
									   
						run_t.password_unlock=UNLOCK_SUCCESS;
						//run_t.confirm_button_flag=confirm_button_unlock;
						run_t.gTimer_8s =0;//
						run_t.keyPressed_flag=0; //WT.EDIT 2023
					
						return ;

					}
					else{

					    // Fail = 1;
						 run_t.password_unlock = UNLOCK_FAIL;
						// run_t.confirm_button_flag=confirm_button_unlock;
						 run_t.gTimer_8s =0;//
						 run_t.keyPressed_flag=0; //WT.EDIT 2023.

						 return ;
						
					}
				 }
                
             }
			 
				 
		}
      }
	
	  run_t.password_unlock = UNLOCK_FAIL;
}
/****************************************************************************
*
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void ReadPassword_EEPROM_SaveData(void)
{
     
	  static unsigned char value;//readpwd_array_length;
	  static uint32_t    ReadAddress; 
	  

	 for(run_t.eepromAddress =0; run_t.eepromAddress <11;run_t.eepromAddress++){ //2022.10.07 be changed ten password 
	  

		switch(run_t.eepromAddress){
	
				 case 0:
					  ReadAddress = ADMINI;
				 break;
				 case 1:
					 ReadAddress = USER_1;
				  
			   break;
	
				 case 2:
					 ReadAddress = USER_2;
			   break;
	
			   case 3:
					 ReadAddress = USER_3;
			   break;
	
			   case 4:
					 ReadAddress = USER_4;
			   break;
	
			   case 5:
					ReadAddress = USER_5;
				break;
	
			   case 6:
					 ReadAddress = USER_6;
				break;
				
				case 7:
					ReadAddress = USER_7;
				  break;
	
				 case 8:
				 
				   ReadAddress = USER_8;
				 break;
	
				 case 9:
				 
					  ReadAddress = USER_9;
			   break;
	
				 case 10:
				   //Fail = 1;
				   run_t.password_unlock = UNLOCK_FAIL;
			
		
				   return ;
				break;
	
		   }

      
	   if(run_t.eepromAddress <10){
	   	   if(run_t.Confirm_newPassword == 1){ //set save new password flag bit by administrator open lock
                ReadAddress = ADMINI;
           }
		   
		    EEPROM_Read_Byte(ReadAddress,readFlag,1);
		    HAL_Delay(3);
		   if(readFlag[0] ==1){// has a been saved pwassword 

					EEPROM_Read_Byte(ReadAddress + 0X01,Readpwd,6);
					HAL_Delay(5);
					
                    run_t.readpwd_array_length = sizeof(Readpwd)/(sizeof(Readpwd[0]));
                    if(run_t.input_digital_key_number_counter > 6){ //WT.EDIT 2023.02.14 over four numbers is virtical  //
 
                        value = BF_Search(virtualPwd,Readpwd,run_t.readpwd_array_length);
						run_t.clear_virtual_numbers =1;
					}
					else
					    value = CompareValue(Readpwd,pwd1);
					
					
					if(value==1)//if(strcmp(pwd1,pwd2)==0)
					{
						
						
						run_t.password_unlock=UNLOCK_SUCCESS;
						//if(run_t.input_digital_key_number_counter > 6)run_t.clear_virtual_numbers =1;
						run_t.input_digital_key_number_counter=0;
					
				
						run_t.keyPressed_flag=0; //WT.EDIT 2023.
						return ;

					}
					else{
						
                     	if(run_t.Confirm_newPassword == 1){
						  // Fail = 1;
						   run_t.password_unlock = UNLOCK_FAIL;
						 //  if(run_t.input_digital_key_number_counter > 6)run_t.clear_virtual_numbers =1;
						   run_t.input_digital_key_number_counter=0;
					
						
						   run_t.keyPressed_flag=0; //WT.EDIT 2023.
						   return;
							
						}
						//n_t.eepromAddress++ ;	
					}

			}
			else{ //don't has a empty space,default password is  "1,2,3,4" ,don't be write new  password

			     if(ReadAddress == ADMINI){

				    
                     if(run_t.input_digital_key_number_counter > 4){
 
                            value=0;
							//run_t.clear_virtual_numbers =1;    
                         //value = BF_Search(virtualPwd,origin_pwd);
					 }
                    else
					 value =CompareValue(origin_pwd, pwd1);

				   if(value==1){
									   
						 run_t.password_unlock=UNLOCK_SUCCESS;
					
						 run_t.input_digital_key_number_counter=0;
				
						 run_t.keyPressed_flag=0; //WT.EDIT 2023.
					
						return ;

					}
					else{

					   //  Fail = 1;
						 run_t.password_unlock = UNLOCK_FAIL;
					     run_t.input_digital_key_number_counter=0;
						
					
						  run_t.keyPressed_flag=0; //WT.EDIT 2023.
						 return ;
						
					}
				 }
				 //n_t.eepromAddress++ ;	
				 
			}

		 
	   	}
	  
	 }
}

/****************************************************************************
*
*Function Name:unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number)
{
     unsigned char temp ;
	 switch(number){

      case KEY_1: 
            
	 	    temp = 1;

	  break; 

	  case KEY_2:

	       temp =2;

	  break;

	  case KEY_3:
	  	   temp =3;

	  break;

	  case KEY_4:
	  	   temp =4;
	  break;

	  case KEY_5:
	  	   temp = 5;

	  break;

	  case 	KEY_6:

	       temp =6;

	  break;

	  case KEY_7 :

	       temp =7;
	  break;

	  case KEY_8 :

	       temp =8;
	  break;

	  case KEY_9 :

	       temp =9;
	  break;

	  case KEY_0 :

	       temp =0;
	  break;


      default :
	  	 

	  break;



	 }

	return temp;

}

static void ClearVirtual_Aarray_Fun(void)
{
    uint8_t i;
    if(run_t.clear_virtual_numbers==1){
		 run_t.clear_virtual_numbers=0;
		 for(i=6;i<20;i++){
		   virtualPwd[i]=0;
					   
	   }

    }
	run_t.readpwd_array_length = 0;
	HAL_Delay(5);
	
}

void RunCheck_KeyMode_Handler(void(*keymode_handler)(uint16_t keydat))
{
      RunChed_KeyMode=keymode_handler; 

}

void Clear_VirtualArray_Numbers(void(*clear_virtual)(void))
{

		ClearVirtual_Numbers = clear_virtual;
}

/****************************************************************************
*
*Function Name:void OverNumbers_Password_Handler(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
uint8_t OverNumbers_Password_Handler(void)
{
     uint32_t    ReadAddress; 
     uint8_t   read_flag;

	ReadAddress = USER_9;
	EEPROM_Read_Byte(ReadAddress,readFlag,0x01);


	if(readFlag[0] ==1){ //over ten numbers password
		
		read_flag = 1;
	}
	else{
	   
	   read_flag = 0;
	}

	return read_flag;


}
