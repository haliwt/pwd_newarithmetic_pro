#ifndef __SINGLE_MODE_H_
#define   __SINGLE_MODE_H_
#include "main.h"

typedef enum{

   confirm_button_donot_pressed,
   confirm_button_pressed,
   confirm_button_unlock,
   confirm_button_clearn_eeprom,
   confirm_button_lock_panel

}confirm_button_stat;

void Start_PowerOn_Handler(void);
void CheckPassword_Lock_Handler(void);

void CheckTouchKey_Press_Handler(void);





#endif 

