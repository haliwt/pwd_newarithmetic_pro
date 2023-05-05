#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "main.h"


#define MOTOR_CW_GPIO_PIN    		GPIO_PIN_14
#define MOTOR_CW_GPIO				GPIOC

#define MOTOR_CW_RUN()         HAL_GPIO_WritePin(MOTOR_CW_GPIO,MOTOR_CW_GPIO_PIN,GPIO_PIN_SET)//  (PORTAbits.RA4 =1)
#define MOTOR_CW_OFF()		   HAL_GPIO_WritePin(MOTOR_CW_GPIO,MOTOR_CW_GPIO_PIN,GPIO_PIN_RESET)// (PORTAbits.RA4 = 0)



#define MOTOR_CCW_GPIO_PIN        GPIO_PIN_15
#define MOTOR_CCW_GPIO            GPIOC

#define MOTOR_CCW_RUN()          HAL_GPIO_WritePin(MOTOR_CCW_GPIO,MOTOR_CCW_GPIO_PIN,GPIO_PIN_SET)//(PORTAbits.RA5 = 1)
#define MOTOR_CCW_OFF()          HAL_GPIO_WritePin(MOTOR_CCW_GPIO,MOTOR_CCW_GPIO_PIN,GPIO_PIN_RESET)//(PORTAbits.RA5 = 0)





void Motor_CCW_Run(void);
void Motor_CW_Run(void);
void Motor_Stop(void);









#endif 

