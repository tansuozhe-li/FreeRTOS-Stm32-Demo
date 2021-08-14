#ifndef _KEY_TEST_H_
#define _KEY_TEST_H_

#include "stm32f4xx_hal.h"
#include "common.h"
extern char BEEP;
#define KEY0_Pin        GPIO_PIN_6
#define KEY0_GPIO_Port  GPIOF
#define KEY1_Pin        GPIO_PIN_7
#define KEY1_GPIO_Port  GPIOF
#define KEY2_Pin        GPIO_PIN_8
#define KEY2_GPIO_Port  GPIOF

void key_test();


#endif