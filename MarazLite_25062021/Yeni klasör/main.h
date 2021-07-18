/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define yon_hata_kesme_pin_Pin GPIO_PIN_3
#define yon_hata_kesme_pin_GPIO_Port GPIOC
#define yon_hata_kesme_pin_EXTI_IRQn EXTI3_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define BLDC_pin_4_Pin GPIO_PIN_6
#define BLDC_pin_4_GPIO_Port GPIOA
#define BLDC_fren_pin_Pin GPIO_PIN_7
#define BLDC_fren_pin_GPIO_Port GPIOA
#define yon_potans_pin_Pin GPIO_PIN_4
#define yon_potans_pin_GPIO_Port GPIOC
#define yon_pin_6_Pin GPIO_PIN_12
#define yon_pin_6_GPIO_Port GPIOB
#define yon_hata_pin_Pin GPIO_PIN_13
#define yon_hata_pin_GPIO_Port GPIOB
#define yon_pin_b_Pin GPIO_PIN_14
#define yon_pin_b_GPIO_Port GPIOB
#define yon_pin_a_Pin GPIO_PIN_15
#define yon_pin_a_GPIO_Port GPIOB
#define yon_pwm_pin_Pin GPIO_PIN_6
#define yon_pwm_pin_GPIO_Port GPIOC
#define durum_led_2_Pin GPIO_PIN_8
#define durum_led_2_GPIO_Port GPIOC
#define durum_led_1_Pin GPIO_PIN_9
#define durum_led_1_GPIO_Port GPIOC
#define BLDC_pwm_pin_Pin GPIO_PIN_8
#define BLDC_pwm_pin_GPIO_Port GPIOA
#define BLDC_yon_pin_Pin GPIO_PIN_9
#define BLDC_yon_pin_GPIO_Port GPIOA
#define BLDC_hal_1_Pin GPIO_PIN_10
#define BLDC_hal_1_GPIO_Port GPIOA
#define BLDC_hal_2_Pin GPIO_PIN_11
#define BLDC_hal_2_GPIO_Port GPIOA
#define BLDC_hal_2_EXTI_IRQn EXTI15_10_IRQn
#define BLDC_hal_3_Pin GPIO_PIN_12
#define BLDC_hal_3_GPIO_Port GPIOA
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
