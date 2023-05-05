#include "run.h"
#include "eeprom.h"
#include "led.h"
#include "buzzer.h"
#include "motor.h"
#include "kmp.h"
#include "single_mode.h"
#include "funpointer.h"
#include "key.h"

RUN_T run_t;

uint8_t compare_value;

uint8_t readFlag[1]={0};
uint8_t pwd1[6];
uint8_t pwd2[6];
uint8_t origin_pwd[6]={1,2,3,4,0,0};

uint8_t Readpwd[6];
uint32_t eevalue ;

void (*RunChed_KeyMode)(uint16_t keydat);
static void Read_Administrator_Password(void);

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
  for(eeNumbers =0; eeNumbers< 11;eeNumbers++){// password is ten numbers
        run_t.gTimer_8s=0;
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
				
				//key ref
				
				//buzzer ref
				run_t.buzzer_flag =0;//WT.EDIT 2022.10.06	
				run_t.fail_sound_flag=1; //WT.EDIT 2022.10.06
				//eeprom ref	
		        run_t.saveEEPROM_fail_flag =1; //WT.EDIT 2022.10.06	
		        run_t.clear_inputNumbers_newpassword=0;//WT.EDIT 2022.10.14
		      
		     
		        run_t.inputNewPassword_Enable =0; //WT.EDIT 2022.09.28
				run_t.keyPressed_flag =0; //WT.EDIT 2023.02.13

				//led error control 
				run_t.lock_fail =1;
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
			 
	           

	    		run_t.inputNewPasswordTimes =0;
				run_t.lock_fail =0;
				
		
			    //clear data reference 
				run_t.Confirm_newPassword =0;//WT.EIDT 2022.09.12
				run_t.buzzer_flag =0; //WT.EDIT 2022.10.05
				run_t.buzzer_longsound_flag =1;//WT.EDIT 2022.10.28
			
				run_t.clear_inputNumbers_newpassword=0;
		        run_t.inputNewPassword_Enable =0; 
		        run_t.inputNewPasswordTimes = 0;
	      

				//led control
				run_t.gTimer_8s=10;
				run_t.led_ok_flag = ok_led_on;
				//backlight ctl
				OK_LED_ON(); //WT.EDIT 2022.10.28
				ERR_LED_OFF();
				BACKLIGHT_OFF();
				run_t.backlight_label = BACKLIGHT_OK_BLINK;
				
				return ;
			
			

			 }
			 else{
			 	//error
				run_t.inputNewPasswordTimes =0;
				run_t.Confirm_newPassword =0; 
			    run_t.inputNewPassword_Enable =0; 

				run_t.password_unlock=UNLOCK_NULL;
				run_t.new_pwd_save_data_tag = UNLOCK_NULL;
				run_t.confirm_button_flag=confirm_button_donot_pressed;
                 
         
	      

				//clear has been set up reference
				
				run_t.motor_return_homePosition=0;
				run_t.buzzer_flag =0;
				run_t.fail_sound_flag=1; 
				run_t.buzzer_longsound_flag =0;
				run_t.saveEEPROM_fail_flag =1; 
				run_t.inputDeepSleep_times =0;
				run_t.buzzer_two_short = 0;
				run_t.clear_inputNumbers_newpassword=0;

				
				
				OK_LED_OFF(); //WT.EDIT 2022.10.28
				ERR_LED_ON();
				
				//led control led
				run_t.gTimer_8s=3;//WT.EDIT 2023.02.11
				run_t.lock_fail =1;   //input new password is error
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


	 if(run_t.Confirm_newPassword == 1){
	 	run_t.gTimer_8s=0;//WT.EDIT 2022.09.28
	 	Read_Administrator_Password();//WT.EDIT 2022.010.07
	 }
	 else
		ReadPassword_EEPROM_SaveData();
     
	
	  //if(Fail == 1){//open lock  is fail run_t.unloak_flag =
       switch(run_t.password_unlock){

	   case UNLOCK_FAIL: //1
	   
	    run_t.password_unlock=UNLOCK_NULL;
	    run_t.confirm_button_flag=confirm_button_donot_pressed;
        run_t.gTimer_8s=0;
		OK_LED_OFF();
		ERR_LED_ON();
		//led
	    run_t.led_ok_flag=0;
		run_t.led_error_flag =1;
		run_t.backlight_label = BACKLIGHT_ERROR_BLINK;
		//others ref
		run_t.oneself_copy_behavior =0;//WT.EDIT 2022.10.28
		run_t.clear_inputNumbers_newpassword=0; 
		run_t.lock_fail=1;
		//eeprom ref
		run_t.eepromAddress=0;
		//key
		run_t.keyPressed_flag=0;
        
		run_t.error_times ++ ; //input times 5 ,
		if(run_t.error_times > 4){
			run_t.gTimer_10s_start=0;
			run_t.gTimer_input_error_times_60s =0;
            run_t.panel_lock=1;
			run_t.gTimer_8s=0;//WT.EDIT 2022.09.28
			    
		}
		//new input pwd ref
        run_t.Confirm_newPassword =0;
	    run_t.inputNewPassword_Enable =0;
		//buzzer sound 
	    run_t.fail_sound_flag=1;
		run_t.buzzer_flag =0; //WT.EDIT 2022.10.19
		run_t.buzzer_two_short=0;//WT.EDIT 2022.10.19
		
	    for(i=0;i<6;i++){
	  	   pwd1[i]=0;
		   Readpwd[i]=0;
		   pwd2[i]=0;
		
		 }

	
	  break;

	  case UNLOCK_SUCCESS://2


	     switch(run_t.Confirm_newPassword){

		 case 1: //set input new password 
			ERR_LED_OFF();
			OK_LED_ON();
		    run_t.new_pwd_save_data_tag= NEW_PWD_SAVE_DATA_TO_EEPROM; //motor don't need run to moved 
			run_t.confirm_button_flag=confirm_button_unlock;
			run_t.password_unlock=UNLOCK_NULL;
			
			run_t.inputNewPassword_Enable =1; //Input Administrator password is OK
			
			
			run_t.motor_return_homePosition= 0;
			run_t.eepromAddress=0;
			run_t.confirm_button_flag = 0;
			
			run_t.buzzer_flag =0; 
			run_t.buzzer_highsound_flag =1; //WT.EDIT 2022.10.28
			run_t.inputDeepSleep_times =0;
			run_t.error_times=0;
			run_t.lock_fail=0;
			
			run_t.inputNewPwd_OK_led_blank_times=0;
		    run_t.keyPressed_flag=0; //WT.EDIT 2023.
		    //led control 
		    run_t.gTimer_8s = 7;
		    run_t.led_ok_flag = ok_led_on;
			run_t.backlight_label = BACKLIGHT_AT_ONCE_OFF;
		    
		
		
		break;

		case 0:
		 
	       if(run_t.oneself_copy_behavior ==1){//WT.EDIT 2022.10.28
	       	    run_t.gTimer_8s=0;
                Buzzer_LongSound(); //WT.EDIT 2022.10.06
		        ERR_LED_OFF();
		        OK_LED_ON();
				run_t.led_ok_flag =1;
				run_t.led_error_flag=0;
				run_t.buzzer_flag=0;
				run_t.oneself_copy_behavior=0;
				run_t.password_unlock = UNLOCK_NULL;
				run_t.confirm_button_flag=confirm_button_donot_pressed;
				run_t.confirm_button_flag = 0;
				run_t.inputDeepSleep_times =0;
				  for(i=0;i<6;i++){
				  	   pwd1[i]=0;
					   Readpwd[i]=0;
					   pwd2[i]=0;
				
				  	}
               run_t.keyPressed_flag=0; //WT.EDIT 2023.
		   }
           else{
               run_t.motor_doing_flag=1;
			   run_t.password_unlock=UNLOCK_NULL;
		       run_t.confirm_button_flag = confirm_button_donot_pressed;
			 
			   run_t.inputDeepSleep_times =0;
			   run_t.keyPressed_flag=0; //WT.EDIT 2023.
				   
		       for(i=0;i<6;i++){
			  	   pwd1[i]=0;
				   Readpwd[i]=0;
				   pwd2[i]=0;
			
			  	}

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
     
	  static unsigned char value;
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
					

                    if(run_t.input_digital_key_number_counter > 6){
 
                        value = BF_Search(virtualPwd,Readpwd);
					}
					else
					    value = CompareValue(Readpwd,pwd1);
					
					
					if(value==1)//if(strcmp(pwd1,pwd2)==0)
					{
						readFlag[0]=0;
						
						run_t.password_unlock=UNLOCK_SUCCESS;
						run_t.confirm_button_flag=confirm_button_unlock;
						  run_t.gTimer_8s =0;//
						  run_t.keyPressed_flag=0; //WT.EDIT 2023.
						  for(i=0;i<6;i++){
	                        pwd1[i]=0;
	                        pwd2[i]=0;
	                        Readpwd[i]=0;

                      		}
                       
						return ;

					}
					else{ // pass word compare is error 
						  
                     	//run_t.inputNewPassword_Enable =1; //Input Administrator password is OK
						run_t.confirm_button_flag = confirm_button_donot_pressed;
                      if(run_t.eepromAddress==2){
                        // Fail = 1;
						 run_t.password_unlock = UNLOCK_FAIL;
						run_t.confirm_button_flag = confirm_button_unlock;
						 run_t.gTimer_8s =0;//
						 run_t.keyPressed_flag=0; //WT.EDIT 2023.
						 for(i=0;i<6;i++){
	                        pwd1[i]=0;
	                        pwd2[i]=0;
	                        Readpwd[i]=0;

                         }
						 
						 return ;
                        
                   }
						
					}

			}
            else{
		   
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
						run_t.confirm_button_flag=confirm_button_unlock;
						run_t.gTimer_8s =0;//
						run_t.keyPressed_flag=0; //WT.EDIT 2023.
						  for(i=0;i<6;i++){
                        pwd1[i]=0;
                        pwd2[i]=0;
                        Readpwd[i]=0;

                      }
					
						return ;

					}
					else{

					    // Fail = 1;
						 run_t.password_unlock = UNLOCK_FAIL;
						 run_t.confirm_button_flag=confirm_button_unlock;
						 run_t.gTimer_8s =0;//
						 run_t.keyPressed_flag=0; //WT.EDIT 2023.
						
						   for(i=0;i<6;i++){
                        pwd1[i]=0;
                        pwd2[i]=0;
                        Readpwd[i]=0;

                      }
						 return ;
						
					}
				 }
                 else{
                        // Fail = 1;
						 run_t.password_unlock = UNLOCK_FAIL;
						 run_t.confirm_button_flag=confirm_button_unlock;
						 run_t.gTimer_8s =0;//
						 run_t.keyPressed_flag=0; //WT.EDIT 2023.
						   for(i=0;i<6;i++){
                        pwd1[i]=0;
                        pwd2[i]=0;
                        Readpwd[i]=0;

                      }
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
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void ReadPassword_EEPROM_SaveData(void)
{
     
	  static unsigned char value;
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
				   run_t.confirm_button_flag = confirm_button_unlock;
				   run_t.led_ok_flag =0;
				   run_t.led_error_flag=1;
				   return ;
				break;
	
		   }

      
	   if(run_t.eepromAddress <10){
	   	   if(run_t.Confirm_newPassword == 1){ //set save new password flag bit by administrator open lock
                ReadAddress = ADMINI;
           }
		   
		    EEPROM_Read_Byte(ReadAddress,readFlag,1);
		  //  HAL_Delay(5);
		   if(readFlag[0] ==1){// has a been saved pwassword 

					EEPROM_Read_Byte(ReadAddress + 0X01,Readpwd,6);
				//	HAL_Delay(5);
					

                    if(run_t.input_digital_key_number_counter > 4){ //WT.EDIT 2023.02.14 over four numbers is virtical  //
 
                        value = BF_Search(virtualPwd,Readpwd);
					}
					else
					    value = CompareValue(Readpwd,pwd1);
					
					
					if(value==1)//if(strcmp(pwd1,pwd2)==0)
					{
						readFlag[0]=0;
						
						 run_t.password_unlock=UNLOCK_SUCCESS;
						 run_t.confirm_button_flag = confirm_button_unlock;
						run_t.led_ok_flag =1;
						run_t.led_error_flag=0;
						run_t.keyPressed_flag=0; //WT.EDIT 2023.
						return ;

					}
					else{
						if(run_t.Confirm_newPassword ==1){
                     		readFlag[0]=0;
						  // Fail = 1;
						   run_t.password_unlock = UNLOCK_FAIL;
						   run_t.confirm_button_flag = confirm_button_unlock;
						   run_t.led_ok_flag =0;
						   run_t.led_error_flag=1;
						   run_t.keyPressed_flag=0; //WT.EDIT 2023.
							return ;
						}
						//n_t.eepromAddress++ ;	
					}

			}
			else{ //don't has a empty space,default password is  "1,2,3,4" ,don't be write new  password

			     if(ReadAddress == ADMINI){

				    
                     if(run_t.input_digital_key_number_counter > 4){
 
                            value=0;
							    
                         //value = BF_Search(virtualPwd,origin_pwd);
					 }
                    else
					 value =CompareValue(origin_pwd, pwd1);

				   if(value==1){
									   
						 run_t.password_unlock=UNLOCK_SUCCESS;
						  run_t.confirm_button_flag = confirm_button_unlock;
						 run_t.led_ok_flag =1;
						 run_t.led_error_flag=0;
						 run_t.keyPressed_flag=0; //WT.EDIT 2023.
					
						return ;

					}
					else{

					   //  Fail = 1;
						 run_t.password_unlock = UNLOCK_FAIL;
					     run_t.confirm_button_flag = confirm_button_unlock;
						  run_t.led_ok_flag =0;
						  run_t.led_error_flag=1;
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

void RunCheck_KeyMode_Handler(void(*keymode_handler)(uint16_t keydat))
{
      RunChed_KeyMode=keymode_handler; 

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
