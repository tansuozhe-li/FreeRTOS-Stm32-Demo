/**
  ******************************************************************************
  * @file    device_term.c
  * @brief   
  *          
  * @author   Lqc
  ******************************************************************************
  */
#include "device_term.h"
#include "common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
#include "led_test.h"
#include "key_test.h"
#include "app_cfg.h"

device_handle g_uart_term_handle;
//TaskHandle_t LED0_TASK_Handle;
/// 终端交互任务
///
/// @param  none
/// @return none
void task_term()
{
  while(1)
  {
   HAL_GPIO_WritePin(GPIOG, LED2_Pin, GPIO_PIN_SET);
   vTaskDelay(200);
   HAL_GPIO_WritePin(GPIOG, LED2_Pin, GPIO_PIN_RESET);
   vTaskDelay(200);
   
   if(BEEP== 1){
        term_printf("\n 挂起LED0任务 \n");
          //vTaskSuspend(LED0_TASK_Handle);
          BEEP =0;
   }   
  }
}
/// 创建终端交互任务
///
/// @param  none
/// @return none
TaskHandle_t TERM_TASK_Handle;
static void task_create_term(void)
{
  BaseType_t xReturn = pdPASS;
  
  xReturn = xTaskCreate((TaskFunction_t)task_term,
                       (const char* )"task_term",       
                       (uint16_t     )TASK_TERM_STK_SIZE,          
                       (void*        )NULL,             
                       (UBaseType_t  )TASK_TERM_PRIO,                
                       (TaskHandle_t*)&TERM_TASK_Handle);  
  if(xReturn == pdPASS)
    term_printf("\n终端交互任务创建成功\n");
  else
    term_printf("\n终端交互任务创建失败\n");
}

/// 终端交互模块初始化
///
/// 创建任务
/// @param  none
/// @return none
void init_term_module()
{
  //创建终端交互任务
  task_create_term();
}

