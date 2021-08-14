#ifndef _LED_TEST_H_
#define _LED_TEST_H_

#include "stm32f4xx_hal.h"
#include "common.h"
#include "app_cfg.h"
#include "usart.h"
#include "gpio.h"
#include "sysclk.h"
#include "FreeRTOS.h"
#include "task.h"
#include "device_term.h"
#include "led_test.h"

#define LED0_Pin        GPIO_PIN_13
#define LED0_GPIO_Port  GPIOG
#define LED1_Pin        GPIO_PIN_14
#define LED1_GPIO_Port  GPIOG
#define LED2_Pin        GPIO_PIN_15
#define LED2_GPIO_Port  GPIOG


void led_test();

#endif