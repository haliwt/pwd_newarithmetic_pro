#include "key.h"
#include "main.h"
#include "gpio.h"
#include "run.h"
#include "led.h"
#include "buzzer.h"
#include "touchkey.h"
#include "single_mode.h"


key_types key;
uint8_t buzzertimes;
void (*TouchKey_Handler)(void);
__IO uint16_t  KeyValue;

uint32_t virtualPwd[20];

uint8_t read_key_value;
uint8_t key_up =1 ;


/*******************************************************************************
    *
    * Function Name: unsigned char  Scan_Key(void)
    * Function : state machine of key 
    * Input Ref: NO
    * Return Ref: key of value 
    *
*******************************************************************************/
uint8_t Scan_Key(void)
{
  unsigned char   reval = 0;
  key.read = _KEY_ALL_OFF; //0x1F 
   if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==0 )
	{
		key.read &= ~0x01; // 0x1f & 0xfe =  0x1E
		POWER_ON();
		BACKLIGHT_ON();
	}
	
	
	switch(key.state )
	{
		case start:
		{
			if(key.read != _KEY_ALL_OFF)
			{
				key.buffer   = key.read; //??:key.buffer = 0x1E  POWER KEY 
				key.state    = first;
				key.on_time  = 0;
				key.off_time = 0;
           		
                
			}
			break;
		}
		case first: //shot key times 
		{
			if(key.read == key.buffer) // adjust key be down 
			{
				if(++key.on_time> 100 && ++key.on_time < 500) //1000  0.5us -> short time key
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01, com = 0x0E ^ 0x1f = 0x11
					key.on_time = 0;
                    key.state   = second;
                    run_t.gTimer_8s=0;//WT.EDIT 2022.10.26
                 }
			}
			else
			{
				key.state   = start;
			}
			break;
		}
		case second: //long key times 
		{
			if(key.read == key.buffer) //again adjust key if be pressed down 
			{
				if(++key.on_time>1000)// 2000 = 7s long key be down
				{
					
					//key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					key.state   = finish;
					do{
                        buzzertimes++;
						run_t.gTimer_8s=0;//WT.EDIT 2022.10.26
						run_t.inputDeepSleep_times =0; //WT.EDIT 2022.10.26
                        BUZZER_KeySound();//Buzzer_ShortSound(); //WT.EDIT 2022.10.05
                        BUZZER_OFF(); 
                        HAL_Delay(400);
                       if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==1){
                         buzzertimes=0;
                         return 0;
                       }

                    }while(buzzertimes < 11);
                    if(buzzertimes > 9){
                        buzzertimes=0;
                        Buzzer_ShortSound();
                        BUZZER_OFF(); 
                        HAL_Delay(200);
                        Buzzer_ShortSound();
                        BUZZER_OFF(); 
                        run_t.gTimer_8s=0;//WT.EDIT 2022.10.26
                        run_t.eeprom_Reset_flag =1; //WT.EDIT 2022.10.26
                        run_t.inputDeepSleep_times =0; //WT.EDIT 2022.10.26
						run_t.backlight_label =BACKLIGHT_ON; //WT.EDIT 2022.10.26
                        while(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin) ==0);
                        key.value = key.value|0x80;
                    }

                   
			  }
			}
			else if(key.read == _KEY_ALL_OFF)  // loose hand 
			{
				if(++key.off_time>5) //30 don't holding key dithering
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
					
					key.state   = finish; // loose hand,shot time be pressed 
				}
			}
		   
			break;
		}
		case finish:
		{
			
			reval = key.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
			key.state   = end;
			run_t.gTimer_8s=0;//WT.EDIT 2022.10.26
         
			break;
		}
		case end:
		{
			if(key.read == _KEY_ALL_OFF)
			{
				if(++key.off_time>5)//50 //100
				{
					key.state   = start;
					run_t.gTimer_8s=0;//WT.EDIT 2022.10.26
                  
				}
			}
			break;
		}
		default:
		{
			key.state   = start;
            run_t.gTimer_8s=0;//WT.EDIT 2022.10.26
			break;
		}
	}
	return  reval;


}


/*******************************************************
 * 
 * Function Name: void  SideKey_Fun(uint8_t keyvalue)
 * Function: 
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
void  SideKey_Fun(uint8_t keyvalue)
{
     
	 if(keyvalue == 0x01){ //short times key that set up new passwords 
               
		run_t.Confirm_newPassword = 1; //set up new passwords of flag:1->enable ,0->disable
		run_t.inputDeepSleep_times =0;
		run_t.inputNewPassword_Enable =0;
		run_t.gTimer_8s=0;
		run_t.buzzer_flag =1;//WT.EDIT 2022.10.06
		run_t.backlight_label =BACKLIGHT_ON; //WT.EDIT .2022.10.06

       	run_t.inputNewPasswordTimes =0;
		run_t.password_unlock=0;//accomplish by save task//WT.EIDT 2022.09.12
		run_t.lock_fail =0;
		run_t.input_digital_key_number_counter =0;
		run_t.motor_return_homePosition=0;
        //WT.EDIT 2023.02.18
      
		run_t.touchkey_first_turn_on_led=0 ;
		run_t.panel_lock =0;
		run_t.gTimer_200ms=20;
        /********************************************/     
		
		
		POWER_ON();//WT.EDIT .2022.10.06
		BACKLIGHT_ON();   
		OK_LED_OFF();//WT.EDIT .2022.10.31
		ERR_LED_OFF();
		
	 
       }
	 
      if(keyvalue== 0x81){ //long times key that earse EEPROM password

        run_t.clearEeprom = 1;
		run_t.inputDeepSleep_times =0;
        run_t.gTimer_8s=0;
		
       }
}

/*******************************************************
 * 
 * Function Name:void TouchKey(void)
 * Function: start power on handler
 * INPUT Ref:NO
 * Return Ref:NO
 * 
********************************************************/
void TouchKey(void)
{
     static uint8_t key_init=0xff;
	 
	 if(I2C_Read_From_Device(SC12B_ADDR,0x08,SC_Data,2)==DONE){

	        read_key_value=Read_SC12B_KEY();
	       KeyValue =(uint16_t)(SC_Data[0]<<8) + SC_Data[1];
		 
	       while(key_up==1 &&  KeyValue !=0){
		   	    key_up=0;
		   		RunCheck_Mode(KeyValue); 

	       }
		   
	       if( KeyValue ==0){
		   	    key_up=1;
	            run_t.getSpecial_1_key++;
	            run_t.getSpecial_2_key++;
				run_t.getNumbers_key++;
	             

           }
	     
			  
	 
	 
	}
}

void TouchKey_Run_Handler(void (*touchkey_huandler)(void))
{

	TouchKey_Handler=touchkey_huandler;

}


/****************************************************************************
*
*Function Name:void RunCheck_Mode(unsigned int dat)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void RunCheck_Mode(uint16_t dat)
{
   unsigned char temp, i,read_numbers;
  
   static unsigned char k0=0xff,k1=0xff,k2=0xff,key,spec;
 

    switch(dat){

	  

	case SPECIAL_1 ://0x40: //CIN1->'*' clear data KEY 
		
      	if(k0 != run_t.getSpecial_1_key){
			k0 = run_t.getSpecial_1_key;

			run_t.getSpecial_2_key++;//n1++;
			run_t.getNumbers_key++;//n2++;
			run_t.keyPressed_flag =1; // has a input key be pressing 
			spec=1;
            //backlight
			run_t.backlight_label =BACKLIGHT_ON;
			//sound buzzer
			run_t.buzzer_flag =1;
            //panel lock ref 
			run_t.lock_fail=0;//WT.EDIT 2022.09.13
			run_t.gTimer_8s=0;  //LED turn on holde times

			POWER_ON();
            switch(run_t.inputNewPassword_Enable){

			  case 1:
				run_t.clear_inputNumbers_newpassword ++;
				run_t.gTimer_8s=0;
			    switch(run_t.clear_inputNumbers_newpassword){

				   case 2: 
					    //the second times cancel input new password action.

						run_t.clear_inputNumbers_newpassword=0;
						run_t.inputNewPassword_Enable=0; //cancel input input new password disable
						run_t.Confirm_newPassword=0;  //Clear set up input new password KEY
						run_t.inputNewPasswordTimes =0;

						run_t.buzzer_flag =1;
						run_t.stop_gTimer_8s =9;

						run_t.keyPressed_flag =0;
						run_t.input_newPassword_over_number = 0;
						//input key flag
						run_t.confirm_button_flag =0;
						run_t.input_digital_key_number_counter =0;

						run_t.password_unlock=UNLOCK_NULL;
						run_t.confirm_button_flag=confirm_button_unlock;

						run_t.lock_fail=0;
						run_t.led_ok_flag = ok_led_on;
						run_t.backlight_label =BACKLIGHT_OFF;

						/****************/
						OK_LED_OFF();
						ERR_LED_OFF();
					
						for(i=0;i<6;i++){
							pwd2[i]=0;
							pwd1[i]=0;
							return ; //WT.EDIT 2023.03.17
						}

					break;

					case 1:
					    //the first clear input digital key of data by input new password enable
						run_t.gTimer_8s=0;

						for(i=0;i<6;i++){
							pwd2[i]=0;
							pwd1[i]=0;
						}
						run_t.inputNewPasswordTimes =0; 
                    
					
						//other ref
						run_t.gTimer_8s=0;
						run_t.confirm_button_flag=confirm_button_unlock;
						//run_t.password_unlock=UNLOCK_SAVE_DATA_TO_EEPROM; //clear input numbers new passwords 
						run_t.new_pwd_save_data_tag= NEW_PWD_SAVE_DATA_TO_EEPROM;

						run_t.Confirm_newPassword=1;
						run_t.inputNewPwd_OK_led_blank_times=0;

				
				break;
			   }
       
		break;

		case 0:
	      for(i=0;i<6;i++){
		  	   pwd1[i]=0;
			   Readpwd[i]=0;
		
		  }
		
         break;
        }
			
	    ERR_LED_OFF();
		run_t.gTimer_8s=0;
		run_t.input_digital_key_number_counter =0 ;
		run_t.confirm_button_flag = 0;
		run_t.inputDeepSleep_times =0;
	
		    
	   }
	  
       break;

	

	 case SPECIAL_2://0x200: //CIN10 '#' ->confirm KEY
         if(k1 != run_t.getSpecial_2_key){
	         k1 = run_t.getSpecial_2_key;

             run_t.getSpecial_1_key++;//n1++
		     run_t.getNumbers_key++;//n2++;
		     run_t.keyPressed_flag =1;//has a input key be pressing 
		     spec=1;
			 
			run_t.backlight_label =BACKLIGHT_ON;
		   
         
			if(run_t.Confirm_newPassword ==0){
				run_t.buzzer_flag =1; 
				
            }
			else if(run_t.inputNewPasswordTimes ==0){
				run_t.buzzer_two_short = 1;
			}
			run_t.gTimer_8s=0;
			POWER_ON();

			

		    if(run_t.input_digital_key_number_counter ==0){
			
				run_t.confirm_button_flag = 0;
				run_t.gTimer_8s=0;
			}
		    else if(run_t.input_digital_key_number_counter < 4  && run_t.inputNewPassword_Enable ==0){//error input key times be msut greater than or equal to  4  
                OK_LED_OFF();
                ERR_LED_ON();
                run_t.input_digital_key_number_counter=0;
                run_t.confirm_button_flag = 0;
                run_t.error_times ++ ;
                run_t.lock_fail=1;
                run_t.fail_sound_flag=1;
				run_t.buzzer_flag =0;
                if(run_t.error_times > 4 ){ //OVER 5 error  times auto lock touchkey 60 s
	                run_t.gTimer_10s_start=0;//WT.EDIT 2022.09.20
	                run_t.gTimer_input_error_times_60s =0;
	                run_t.panel_lock=1;
					run_t.gTimer_8s=0;

                }

		   }
		   else{ //input key equal to 4 or bigger than  4
				if(run_t.inputNewPassword_Enable ==1){ //prepare input newpassword .WT.EDI 2022.10.13//if( run_t.Confirm_newPassword ==1){

			            run_t.inputNewPasswordTimes ++ ;  //recoder times
			             run_t.gTimer_8s=0;
						if(run_t.inputNewPasswordTimes ==1){
						 //Confirm Key "#"
						    run_t.buzzer_flag =0; 
							run_t.buzzer_two_short = 2;
                            
						}
					
						
						run_t.confirm_button_flag = 1; //run next step process
						run_t.input_digital_key_number_counter=0;
						run_t.inputDeepSleep_times =0;
						run_t.gTimer_8s=0;
						run_t.inputNewPwd_OK_led_blank_times=0;
						run_t.backlight_label =BACKLIGHT_OK_BLINK; //WT.EDIT .2023.03.27
					
						
			    }
				else if(run_t.motor_return_homePosition==0){ // return home position
						run_t.buzzer_flag =1; 
						run_t.confirm_button_flag = 1;
						run_t.inputNewPasswordTimes=0; 
					
						run_t.inputDeepSleep_times =0;
				}
				else if(run_t.motor_return_homePosition==1){ //motor runing ->repeat itself motor doing run

				        run_t.buzzer_flag =1; 
					   run_t.confirm_button_flag=1;
				       run_t.oneself_copy_behavior=1;
					   run_t.inputDeepSleep_times =0;
					   run_t.eepromAddress=0;

				 }
				 run_t.gTimer_8s=0;
			}
		   
		}
	 
      break;

	 
	case KEY_0:
		
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
		run_t.keyPressed_flag =1;
             
	break;

    case KEY_1 :

		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
	    run_t.inputNewPwd_OK_led_blank_times=0;
   	    run_t.keyPressed_flag =1;
	break;
			
    case KEY_2:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
  		run_t.keyPressed_flag =1;
	 
	break;
			
	case  KEY_3:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
		run_t.keyPressed_flag =1;
	
    break;
			
	case KEY_4:
			
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
		run_t.keyPressed_flag =1;
			
	break;
			
	case KEY_5:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;

		run_t.inputNewPwd_OK_led_blank_times=0;
		run_t.keyPressed_flag =1;
			
    break;
			
	case KEY_6:
		
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
		run_t.keyPressed_flag =1;
       
		
		
	break;
	case KEY_7:
		
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
		run_t.keyPressed_flag =1;

		
	break;
			
	case KEY_8:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
		run_t.keyPressed_flag =1;
	break;

	case KEY_9:
		key=1;
		spec=0;
		run_t.getNumbers_key++;
		run_t.inputDeepSleep_times =0;
		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
		run_t.keyPressed_flag =1;
	break;
		  

	}  

	if(k2 != run_t.getNumbers_key && key==1 && spec ==0){
				
		k2=run_t.getNumbers_key;
		key = 0;
		spec =1;
		run_t.getSpecial_1_key++;//n1++

		run_t.getSpecial_2_key++;//n1++;


		run_t.backlight_label =BACKLIGHT_ON;
	
		run_t.input_digital_key_number_counter ++ ;
		run_t.buzzer_flag =1;

		run_t.gTimer_8s=0;

		run_t.confirm_button_flag =0;
		POWER_ON();

		if(run_t.Confirm_newPassword ==1 && run_t.input_digital_key_number_counter >6){//WT.EDIT 2022.10.08

			
			run_t.gTimer_8s=0;
			run_t.fail_sound_flag =1;
			//led control 
			run_t.input_newPassword_over_number = 1;//run_t.lock_fail=1;
			run_t.backlight_label = BACKLIGHT_ERROR_BLINK;

		}
		else{
			temp = InputNumber_ToSpecialNumbers((TouchKey_Numbers) dat); //input Numbers
			//virtual password is 20bit
			if(run_t.input_digital_key_number_counter > 20) run_t.input_digital_key_number_counter =20;
			virtualPwd[run_t.input_digital_key_number_counter-1]=temp;
				
			if(run_t.input_digital_key_number_counter < 7){//run_t.inputNewPasswordTimes

				if(run_t.inputNewPasswordTimes ==0 && run_t.inputNewPassword_Enable ==1){//WT.EDIT 2022.10.14
					read_numbers = OverNumbers_Password_Handler();
					if(read_numbers==1){
						run_t.confirm_button_flag=confirm_button_unlock;
						//run_t.password_unlock=UNLOCK_OVER_MAX_PWD_NUMBERS; //over times ten group numbers password
                        run_t.new_pwd_save_data_tag= UNLOCK_OVER_MAX_PWD_NUMBERS;
					}
					else
					    pwd2[run_t.input_digital_key_number_counter-1]=temp; //the first input new password .
				}
				else  pwd1[run_t.input_digital_key_number_counter-1] =temp;

			}

		}

		run_t.gTimer_8s=0;
		run_t.inputNewPwd_OK_led_blank_times=0;
	}
}


