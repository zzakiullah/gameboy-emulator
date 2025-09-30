/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define PB_DPAD_UP_Pin GPIO_PIN_3
#define PB_DPAD_UP_GPIO_Port GPIOC
#define PB_DPAD_UP_EXTI_IRQn EXTI3_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define PB_SELECT_Pin GPIO_PIN_6
#define PB_SELECT_GPIO_Port GPIOA
#define PB_SELECT_EXTI_IRQn EXTI9_5_IRQn
#define PB_START_Pin GPIO_PIN_7
#define PB_START_GPIO_Port GPIOA
#define PB_START_EXTI_IRQn EXTI9_5_IRQn
#define PB_DPAD_DOWN_Pin GPIO_PIN_4
#define PB_DPAD_DOWN_GPIO_Port GPIOC
#define PB_DPAD_LEFT_Pin GPIO_PIN_5
#define PB_DPAD_LEFT_GPIO_Port GPIOC
#define PB_DPAD_LEFT_EXTI_IRQn EXTI9_5_IRQn
#define PB_DPAD_RIGHT_Pin GPIO_PIN_0
#define PB_DPAD_RIGHT_GPIO_Port GPIOB
#define PB_DPAD_RIGHT_EXTI_IRQn EXTI0_IRQn
#define PB_A_Pin GPIO_PIN_1
#define PB_A_GPIO_Port GPIOB
#define PB_A_EXTI_IRQn EXTI1_IRQn
#define PB_B_Pin GPIO_PIN_2
#define PB_B_GPIO_Port GPIOB
#define PB_B_EXTI_IRQn EXTI2_IRQn
#define ILI9341_D0_Pin GPIO_PIN_12
#define ILI9341_D0_GPIO_Port GPIOB
#define ILI9341_D1_Pin GPIO_PIN_13
#define ILI9341_D1_GPIO_Port GPIOB
#define ILI9341_D2_Pin GPIO_PIN_14
#define ILI9341_D2_GPIO_Port GPIOB
#define ILI9341_D3_Pin GPIO_PIN_15
#define ILI9341_D3_GPIO_Port GPIOB
#define ILI9341_D4_Pin GPIO_PIN_6
#define ILI9341_D4_GPIO_Port GPIOC
#define ILI9341_D5_Pin GPIO_PIN_7
#define ILI9341_D5_GPIO_Port GPIOC
#define ILI9341_D6_Pin GPIO_PIN_8
#define ILI9341_D6_GPIO_Port GPIOC
#define ILI9341_D7_Pin GPIO_PIN_9
#define ILI9341_D7_GPIO_Port GPIOC
#define ILI9341_RD_Pin GPIO_PIN_8
#define ILI9341_RD_GPIO_Port GPIOA
#define ILI9341_WR_Pin GPIO_PIN_9
#define ILI9341_WR_GPIO_Port GPIOA
#define ILI9341_CD_Pin GPIO_PIN_10
#define ILI9341_CD_GPIO_Port GPIOA
#define ILI9341_CS_Pin GPIO_PIN_11
#define ILI9341_CS_GPIO_Port GPIOA
#define ILI9341_RST_Pin GPIO_PIN_12
#define ILI9341_RST_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
