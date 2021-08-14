/**
  ******************************************************************************
  * @file           : app.c
  * @brief          : Main program body
  * @anthor         : liqingchang
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h" 
#include "app_cfg.h" 
#include "usart.h"
#include "gpio.h"
#include "sysclk.h"
#include "device_term.h"
#include "common.h"  
   
    

/// @name  AppTaskCreate
/// @brief 创建任务
/// @param none
/// @return none

TaskHandle_t AppTaskCreate_Handle;
static void AppTaskCreate(void)
{

  UART5_UART_Init();
  
  term_printf("\n\r\n\r............欢迎来到FreeRTOS操作系统.........\n\r\n\r");
  term_printf("....................STM32F407................\n\r\n\r");
  
  taskENTER_CRITICAL();    //进入临界区  
  init_term_module();//终端交互模块初始化 
  led_test();//led测试
  key_test();//key测试

  while(1)
  {
    vTaskDelete(AppTaskCreate_Handle); //删除起始任务
    taskEXIT_CRITICAL();    //退出临界区
  }
}


/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  HAL_Init();
  SystemClock_Config();

     
  BaseType_t xReturn = pdPASS;
     
  xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
                      (const char* )"AppTaskCreate",                 //任务名称
                      (uint16_t     )TASK_CREATE_STK_SIZE,            //任务栈大小
                      (void*        )NULL,                           //传递给任务函数的参数
                      (UBaseType_t  )TASK_CREATE_PRIO,               //任务优先级
                      (TaskHandle_t* )&AppTaskCreate_Handle);
  if(pdPASS == xReturn)
    vTaskStartScheduler();
  else
    return -1;
  
  while (1);  
}


