#ifndef    __LED_H_
#define    __LED_H_
#include "main.h"
#include "gpio.h"




#define  POWER_ON()         HAL_GPIO_WritePin(CTRL2_GPIO_Port,CTRL2_Pin,GPIO_PIN_SET)        // (PORTCbits.RC0= 1)
#define  POWER_OFF()        HAL_GPIO_WritePin(CTRL2_GPIO_Port ,CTRL2_Pin,GPIO_PIN_RESET)  ///  (PORTCbits.RC0 =0)



#define  BACKLIGHT_ON()       HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)//  (PORTCbits.RC3 = 1)
#define  BACKLIGHT_OFF()      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)//  (PORTCbits.RC3 = 0)




#define  BAT_LED_ON()          HAL_GPIO_WritePin(LOW_LED_GPIO_Port,LOW_LED_Pin,GPIO_PIN_RESET)//  (PORTCbits.RC4 = 0)
#define  BAT_LED_OFF()         HAL_GPIO_WritePin(LOW_LED_GPIO_Port,LOW_LED_Pin,GPIO_PIN_SET) //  (PORTCbits.RC4 =1 )



#define  OK_LED_ON()           HAL_GPIO_WritePin(OK_LED_GPIO_Port,OK_LED_Pin ,GPIO_PIN_RESET) //(PORTAbits.RA1 = 0)
#define  OK_LED_OFF()          HAL_GPIO_WritePin(OK_LED_GPIO_Port,OK_LED_Pin ,GPIO_PIN_SET)///   (PORTAbits.RA1 = 1)



#define  ERR_LED_ON()          HAL_GPIO_WritePin(ERR_LED_GPIO_Port,ERR_LED_Pin ,GPIO_PIN_RESET)//  (PORTAbits.RA0 =0)
#define  ERR_LED_OFF()         HAL_GPIO_WritePin(ERR_LED_GPIO_Port,ERR_LED_Pin ,GPIO_PIN_SET)   //  (PORTAbits.RA0 =1)
//#define KEY1_RA2_GetValue()        //   PORTAbits.RA2

typedef enum _backlight{
   
    BACKLIGHT_OFF,
    BACKLIGHT_ON,
    BACKLIGHT_AT_ONCE_OFF,
    BACKLIGHT_OK_BLINK,
    BACKLIGHT_ERROR_BLINK,
    BACKLIGHT_NEW_PASSWORD_LED,
    BACKLIGHT_ERROR_OVER_INPUT_TIMES,
    BACKLIGHT_FACTORY_LED,
    BACKLIGHT_INPUT_STOP_MODEL,
    BACKLIGHT_NULL


}backlight_enum_t;

typedef enum _led_ok_state_t {
    ok_led_off,
    ok_led_on

}led_ok_state_t;

typedef enum _led_error_state_t {
    error_led_off,
    error_led_on

}led_error_state_t;

typedef enum _led_battery_state_t {
     battery_led_off,
     battery_led_on
}led_battery_state_t;







void Panel_LED_Off(void);
void Fail_Buzzer_Sound(void);
void BackLight_Control_Handler(void);
void ClearEEPROM_Data_Fun(void);
void Panel_Lock_Handler(void);


#endif 
