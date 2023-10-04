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
#include "stm32f0xx_hal.h"

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
#define LS1_Pin GPIO_PIN_13
#define LS1_GPIO_Port GPIOC
#define ChargeStatus_Pin GPIO_PIN_14
#define ChargeStatus_GPIO_Port GPIOC
#define DoneStatus_Pin GPIO_PIN_15
#define DoneStatus_GPIO_Port GPIOC
#define Det1_Pin GPIO_PIN_0
#define Det1_GPIO_Port GPIOF
#define LS2_Pin GPIO_PIN_1
#define LS2_GPIO_Port GPIOF
#define Det2_Pin GPIO_PIN_0
#define Det2_GPIO_Port GPIOC
#define LS3_Pin GPIO_PIN_1
#define LS3_GPIO_Port GPIOC
#define Det3_Pin GPIO_PIN_2
#define Det3_GPIO_Port GPIOC
#define LS4_Pin GPIO_PIN_3
#define LS4_GPIO_Port GPIOC
#define Det4_Pin GPIO_PIN_0
#define Det4_GPIO_Port GPIOA
#define LS5_Pin GPIO_PIN_1
#define LS5_GPIO_Port GPIOA
#define Det5_Pin GPIO_PIN_4
#define Det5_GPIO_Port GPIOF
#define LS6_Pin GPIO_PIN_5
#define LS6_GPIO_Port GPIOF
#define Det6_Pin GPIO_PIN_7
#define Det6_GPIO_Port GPIOA
#define ChargeEnable_Pin GPIO_PIN_4
#define ChargeEnable_GPIO_Port GPIOC
#define LS8_Pin GPIO_PIN_5
#define LS8_GPIO_Port GPIOC
#define Det8_Pin GPIO_PIN_0
#define Det8_GPIO_Port GPIOB
#define LS9_Pin GPIO_PIN_1
#define LS9_GPIO_Port GPIOB
#define Det9_Pin GPIO_PIN_2
#define Det9_GPIO_Port GPIOB
#define LS10_Pin GPIO_PIN_10
#define LS10_GPIO_Port GPIOB
#define Det10_Pin GPIO_PIN_11
#define Det10_GPIO_Port GPIOB
#define LS11_Pin GPIO_PIN_12
#define LS11_GPIO_Port GPIOB
#define Det11_Pin GPIO_PIN_13
#define Det11_GPIO_Port GPIOB
#define LS12_Pin GPIO_PIN_14
#define LS12_GPIO_Port GPIOB
#define Det12_Pin GPIO_PIN_15
#define Det12_GPIO_Port GPIOB
#define LS13_Pin GPIO_PIN_6
#define LS13_GPIO_Port GPIOC
#define Det13_Pin GPIO_PIN_7
#define Det13_GPIO_Port GPIOC
#define LS14_Pin GPIO_PIN_8
#define LS14_GPIO_Port GPIOC
#define Det14_Pin GPIO_PIN_9
#define Det14_GPIO_Port GPIOC
#define LS15_Pin GPIO_PIN_8
#define LS15_GPIO_Port GPIOA
#define Det15_Pin GPIO_PIN_11
#define Det15_GPIO_Port GPIOA
#define LS16_Pin GPIO_PIN_6
#define LS16_GPIO_Port GPIOF
#define Det16_Pin GPIO_PIN_7
#define Det16_GPIO_Port GPIOF
#define LS17_Pin GPIO_PIN_15
#define LS17_GPIO_Port GPIOA
#define Det17_Pin GPIO_PIN_10
#define Det17_GPIO_Port GPIOC
#define LS18_Pin GPIO_PIN_11
#define LS18_GPIO_Port GPIOC
#define Det18_Pin GPIO_PIN_12
#define Det18_GPIO_Port GPIOC
#define LS19_Pin GPIO_PIN_2
#define LS19_GPIO_Port GPIOD
#define Det19_Pin GPIO_PIN_3
#define Det19_GPIO_Port GPIOB
#define LS20_Pin GPIO_PIN_4
#define LS20_GPIO_Port GPIOB
#define Det20_Pin GPIO_PIN_5
#define Det20_GPIO_Port GPIOB
#define RC1_Pin GPIO_PIN_6
#define RC1_GPIO_Port GPIOB
#define RC1_EXTI_IRQn EXTI4_15_IRQn
#define RC2_Pin GPIO_PIN_7
#define RC2_GPIO_Port GPIOB
#define RC2_EXTI_IRQn EXTI4_15_IRQn
#define LS7_Pin GPIO_PIN_8
#define LS7_GPIO_Port GPIOB
#define Det7_Pin GPIO_PIN_9
#define Det7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
