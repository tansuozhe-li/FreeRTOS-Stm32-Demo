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

 
#include "stm32f4xx_hal.h"
#include "common.h"

typedef enum
{
  INPUT = 0,
  OUTPUT =1
}GPIO_MODED;  
 

void MX_GPIO_Init(void);

void drv_gpio_openbit(GPIO_TypeDef *port, u_int16_t pin, GPIO_MODED mode, u_int8_t data);
void drv_gpio_setbit(GPIO_TypeDef *port,u_int16_t pin);
void drv_gpio_clrbit(GPIO_TypeDef *port,u_int16_t pin);
u_int32_t drv_gpio_getbit(GPIO_TypeDef *port,u_int16_t pin);
void drv_gpio_togglebit(GPIO_TypeDef *port,u_int16_t pin);

#endif


