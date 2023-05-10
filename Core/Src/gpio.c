/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
//#define DEBUG  1
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MOTOR_CCW_Pin|MOTOR_CW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */

  HAL_GPIO_WritePin(GPIOA, LOW_LED_Pin|OK_LED_Pin|ERR_LED_Pin, GPIO_PIN_SET);


  HAL_GPIO_WritePin(GPIOA, IIC_SCL_Pin|BEEP_Pin|CTRL2_Pin|IIC_SDA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);


  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = MOTOR_CCW_Pin|MOTOR_CW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = LOW_LED_Pin|OK_LED_Pin|ERR_LED_Pin|CTRL2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;//GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = IIC_SCL_Pin|BEEP_Pin|IIC_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;//GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = SC12B_KEY_Pin;   //Touchkey
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; //GPIO_MODE_IT_RISING_FALLING ;//GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = KEY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING ; //WT.EDIT 2022.08.20
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
   HAL_NVIC_SetPriority(EXTI0_1_IRQn,0,0);
   HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
  
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);



}

/* USER CODE BEGIN 2 */

//WT.EDIT 2022.12.13 EDIT 
void GPIO_Standby_Init(void)
{

 GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

 /*Configure GPIO pins : PA5 PA6 PA7 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG ;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


   /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = LOW_LED_Pin|OK_LED_Pin|ERR_LED_Pin|CTRL2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG ;//GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = IIC_SCL_Pin|BEEP_Pin|IIC_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG ;//GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = MOTOR_CCW_Pin|MOTOR_CW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG ;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  
	/*Configure GPIO pin : PtPin */
	 GPIO_InitStruct.Pin = LED1_Pin;
	 GPIO_InitStruct.Mode =GPIO_MODE_ANALOG ;
	 GPIO_InitStruct.Pull = GPIO_PULLDOWN;//GPIO_NOPULL;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	 HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE END 2 */
