#ifndef __sysclk_H
#define __sysclk_H

#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"

#define SYSCLK 168    //œµÕ≥ ±÷”

void SystemClock_Config(void);
void delay_init(void);
void delay_ms(int nms);
void delay_us(int nus);

#endif


