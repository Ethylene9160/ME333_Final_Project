/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

#define S0_L HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0)
#define S0_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1)

#define S1_L HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0)
#define S1_H HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1)

#define S2_L HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,0)
#define S2_H HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,1)

#define S3_L HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,0)
#define S3_H HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,1)

#define LED_OFF HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,0)
#define LED_ON  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,1)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

void TCS_Next(int s1, int s2);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

