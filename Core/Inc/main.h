/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
void SystemClock_Config(void);
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
#define SW_Pin GPIO_PIN_0
#define SW_GPIO_Port GPIOC
#define SW_EXTI_IRQn EXTI0_IRQn
#define A_Pin GPIO_PIN_1
#define A_GPIO_Port GPIOC
#define B_Pin GPIO_PIN_2
#define B_GPIO_Port GPIOC
#define B_EXTI_IRQn EXTI2_IRQn
#define key_Pin GPIO_PIN_3
#define key_GPIO_Port GPIOC
#define key_EXTI_IRQn EXTI3_IRQn
#define Vout_Pin GPIO_PIN_1
#define Vout_GPIO_Port GPIOA
#define NTC_Pin GPIO_PIN_2
#define NTC_GPIO_Port GPIOA
#define T12_Pin GPIO_PIN_6
#define T12_GPIO_Port GPIOA
#define T12_CTRL_Pin GPIO_PIN_9
#define T12_CTRL_GPIO_Port GPIOE
#define EN_Pin GPIO_PIN_14
#define EN_GPIO_Port GPIOE
#define STATE_Pin GPIO_PIN_15
#define STATE_GPIO_Port GPIOE
#define Bluetooth_TX_Pin GPIO_PIN_10
#define Bluetooth_TX_GPIO_Port GPIOB
#define Bluetooth_RX_Pin GPIO_PIN_11
#define Bluetooth_RX_GPIO_Port GPIOB
#define LCD_SCL_Pin GPIO_PIN_13
#define LCD_SCL_GPIO_Port GPIOB
#define LCD_SDA_Pin GPIO_PIN_15
#define LCD_SDA_GPIO_Port GPIOB
#define LCD_RES_Pin GPIO_PIN_9
#define LCD_RES_GPIO_Port GPIOD
#define LCD_DC_Pin GPIO_PIN_11
#define LCD_DC_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_13
#define LCD_CS_GPIO_Port GPIOD
#define LCD_BL_Pin GPIO_PIN_15
#define LCD_BL_GPIO_Port GPIOD
#define Red_Pin GPIO_PIN_6
#define Red_GPIO_Port GPIOC
#define Green_Pin GPIO_PIN_7
#define Green_GPIO_Port GPIOC
#define TXD_Pin GPIO_PIN_9
#define TXD_GPIO_Port GPIOA
#define RXD_Pin GPIO_PIN_10
#define RXD_GPIO_Port GPIOA
#define led_Pin GPIO_PIN_9
#define led_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
