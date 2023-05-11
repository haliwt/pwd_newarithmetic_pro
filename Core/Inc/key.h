#ifndef __KEY_H_
#define __KEY_H_
#include "main.h"


//#define KEY_GPIO_PIN                 GPIO_PIN_5
//#define KEY_GPIO_PORT                GPIOA 
//
//
//#define TOUCH_KEY_GPIO_PIN             GPIO_PIN_9   
//#define TOUCH_KEY_GPIO                 GPIOA

#define		_KEY_ALL_OFF				  0X1F

//normal times be pressed key
#define		_KEY_TRG_1_WK_UP     			0x01  //WK_UP
#define		_KEY_TRG_2_KEY_1     			0x02  //??????--???
#define		_KEY_TRG_3_TIMER     			0x04   //????
#define		_KEY_TRG_4_FILTER     			0x08
// combination of buttons 
#define		_KEY_TRG_5_WINDTI   			0x11   //?????
#define		_KEY_TRG_6_WINDTI   			0x12   //?????
#define		_KEY_TRG_7_WINDTI   			0x14   //?????
#define		_KEY_TRG_8_WINDTI   			0x18   //?????

//long times be pressed
#define		_KEY_CONT_1_WK_UP     	     0x81    //??????--???
#define		_KEY_CONT_2_KEY_1    		 0x82    //??????--???
#define		_KEY_CONT_3_TIMER     	     0x84    //?????? ?????
#define		_KEY_CONT_4_FILTER     	     0x88    //??? --?????
#define		_KEY_CONT_5_WINDTI     		 0x89




#define		_KEY_CONT_1     	    0x81    //?????
#define		_KEY_CONT_2     		0x82
#define		_KEY_CONT_3     		0x84
#define		_KEY_CONT_4     	    0x88

#define		_KEY_COM_1    		    0x91
#define		_KEY_COM_2    		    0x92
#define		_KEY_COM_3    		    0x94
#define		_KEY_COM_4    		    0x98

typedef  struct  _state_
{
 unsigned char          read;
 unsigned char          buffer;
 unsigned char          value;
 unsigned char          off_time;
 unsigned long          on_time;

 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;

extern key_types key;

extern uint8_t virtualPwd[20];

extern void (*ReadDigital_Key_Numbers_Handler)(void);
extern void (*Input_NewPwd_Digtial_Handler)(uint16_t dat);


uint8_t Scan_Key(void);



void KeyFiles_Init(void);

void RunCheck_Mode(uint16_t dat);

void  SideKey_Fun(uint8_t keyvalue);
void TouchKey_Run_Handler(void (*touchkey_huandler)(void));
void ReadInput_KeyNumber_Handler(void(*read_digital_key_handler)(void));
void Input_NewPwd_Digital_Handler(void(*input_new_digital_handler)(uint16_t dat));

void TouchKey_Handler(void);



#endif 
