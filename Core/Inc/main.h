/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */





/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR_CCW_Pin GPIO_PIN_14
#define MOTOR_CCW_GPIO_Port GPIOC


#define MOTOR_CW_Pin GPIO_PIN_15
#define MOTOR_CW_GPIO_Port GPIOC

#define BAT_VOL_Pin 						GPIO_PIN_0
#define BAT_VOL_GPIO_Port 					GPIOA

#define LOW_LED_Pin 						GPIO_PIN_1
#define LOW_LED_GPIO_Port 					GPIOA

#define OK_LED_Pin             				 GPIO_PIN_2
#define OK_LED_GPIO_Port       				 GPIOA

#define ERR_LED_Pin            				 GPIO_PIN_3
#define ERR_LED_GPIO_Port     				 GPIOA

#define IIC_SCL_Pin GPIO_PIN_4
#define IIC_SCL_GPIO_Port GPIOA


#define KEY_Pin GPIO_PIN_5
#define KEY_GPIO_Port GPIOA
#define KEY_EXTI_IRQn EXTI4_15_IRQn


#define BEEP_Pin GPIO_PIN_6
#define BEEP_GPIO_Port GPIOA

#define CTRL2_Pin 					GPIO_PIN_7
#define CTRL2_GPIO_Port 			GPIOA

#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOB

#define SC12B_KEY_Pin GPIO_PIN_9
#define SC12B_KEY_GPIO_Port GPIOA
#define SC12B_KEY_EXTI_IRQn EXTI4_15_IRQn



#define IIC_SDA_Pin GPIO_PIN_10
#define IIC_SDA_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
void SystemClock_Config(void);


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
