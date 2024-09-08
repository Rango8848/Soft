/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define IN1_1_Pin GPIO_PIN_4
#define IN1_1_GPIO_Port GPIOA
#define IN1_2_Pin GPIO_PIN_5
#define IN1_2_GPIO_Port GPIOA
#define PumpMin1_Pin GPIO_PIN_6
#define PumpMin1_GPIO_Port GPIOA
#define PumpMin2_Pin GPIO_PIN_7
#define PumpMin2_GPIO_Port GPIOA
#define IN1_3_Pin GPIO_PIN_0
#define IN1_3_GPIO_Port GPIOB
#define IN1_4_Pin GPIO_PIN_1
#define IN1_4_GPIO_Port GPIOB
#define PumpMax1_Pin GPIO_PIN_13
#define PumpMax1_GPIO_Port GPIOB
#define IN2_1_Pin GPIO_PIN_14
#define IN2_1_GPIO_Port GPIOB
#define IN2_2_Pin GPIO_PIN_15
#define IN2_2_GPIO_Port GPIOB
#define PumpMax2_Pin GPIO_PIN_3
#define PumpMax2_GPIO_Port GPIOB
#define PumpMax3_Pin GPIO_PIN_4
#define PumpMax3_GPIO_Port GPIOB
#define IN3_3_Pin GPIO_PIN_5
#define IN3_3_GPIO_Port GPIOB
#define IN3_4_Pin GPIO_PIN_6
#define IN3_4_GPIO_Port GPIOB
#define IN3_1_Pin GPIO_PIN_8
#define IN3_1_GPIO_Port GPIOB
#define IN3_2_Pin GPIO_PIN_9
#define IN3_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
