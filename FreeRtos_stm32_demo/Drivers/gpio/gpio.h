/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif
  
#include "stm32f4xx_hal.h"
  
#define LED0_Pin        GPIO_PIN_13
#define LED0_GPIO_Port  GPIOG
#define LED1_Pin        GPIO_PIN_14
#define LED1_GPIO_Port  GPIOG
#define LED2_Pin        GPIO_PIN_15
#define LED2_GPIO_Port  GPIOG
  
#define KEY0_Pin        GPIO_PIN_6
#define KEY0_GPIO_Port  GPIOF
#define KEY1_Pin        GPIO_PIN_7
#define KEY1_GPIO_Port  GPIOF
#define KEY2_Pin        GPIO_PIN_8
#define KEY2_GPIO_Port  GPIOF


void MX_GPIO_Init(void);


#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

