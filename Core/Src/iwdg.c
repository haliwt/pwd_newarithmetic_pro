/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    iwdg.c
  * @brief   This file provides code for the configuration
  *          of the IWDG instances.
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
#include "iwdg.h"

/* USER CODE BEGIN 0 */
uint8_t iwdg_ajust_flag;
/* USER CODE END 0 */

IWDG_HandleTypeDef hiwdg;

/* IWDG init function */
/******************************************
	*
	*IWDG: times Tout = pre_vale /40 * reLoad_value 
	*      128/40 * 4095 = 13107.2ms = 13s
	*
	*
******************************************/
void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  IWDG_ENABLE_WRITE_ACCESS(&hiwdg);
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 4095;
  IS_IWDG_RELOAD(4095)  ;
  IS_IWDG_PRESCALER(IWDG_PRESCALER_256);
 
 
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    iwdg_ajust_flag=1;
	Error_Handler();
	
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/* USER CODE BEGIN 1 */
void IWDG_Feed(void)
{
     HAL_IWDG_Refresh(&hiwdg) ;
    
}
/* USER CODE END 1 */
