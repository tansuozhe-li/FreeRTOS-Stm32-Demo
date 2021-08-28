#include "common.h"
#include "app_cfg.h"
#include "usart.h"
#include "gpio.h"
#include "sysclk.h"
#include "FreeRTOS.h"
#include "task.h"
#include "device_term.h"
#include "led_test.h"
#include "debug.h"

/*******************************************************************************
* @函数名：LED_Task
* @功能说明：LED_Task任务主体
* @参数：无
* @返回值：无
*******************************************************************************/
static void LED1_Task(void* parameter)
{
    while (1)
  {
    //HAL_GPIO_WritePin(GPIOG, LED1_Pin, GPIO_PIN_SET);
    drv_gpio_clrbit(GPIOG,LED1_Pin);
   vTaskDelay(100);
   //HAL_GPIO_WritePin(GPIOG, LED1_Pin, GPIO_PIN_RESET);
   drv_gpio_setbit(GPIOG,LED1_Pin);
   vTaskDelay(100);
  }
}

/*******************************************************************************
* @函数名：LED_Task
* @功能说明：LED_Task任务主体
* @参数：无
* @返回值：无
*******************************************************************************/
static void LED0_Task(void* parameter)
{
    while (1)
  {
    drv_gpio_clrbit(GPIOG,LED0_Pin);
    vTaskDelay(50);
    drv_gpio_setbit(GPIOG,LED0_Pin);
    vTaskDelay(50);
  }
}


TaskHandle_t LED1_TASK_Handle;
static void task_create_led1(void)
{
  BaseType_t xReturn = pdPASS;
  
  xReturn = xTaskCreate((TaskFunction_t)LED1_Task,
                       (const char* )"LED1_Task",   
                       (uint16_t     )128,           
                       (void*        )NULL,        
                       (UBaseType_t  )4,             
                       (TaskHandle_t*)&LED1_TASK_Handle);  

  if(xReturn == pdPASS)
    term_printf("\n LED1 TASK create success \n");
  else
    term_printf("\n LED1 TASK create failed \n");
}


TaskHandle_t LED0_TASK_Handle;
static void task_create_led0(void)
{
  BaseType_t xReturn = pdPASS;
  
  xReturn = xTaskCreate((TaskFunction_t)LED0_Task,
                       (const char* )"LED0_Task",   
                       (uint16_t     )128,           
                       (void*        )NULL,          
                       (UBaseType_t  )5,             
                       (TaskHandle_t*)&LED0_TASK_Handle); 
  
  if(xReturn == pdPASS)
    term_printf("\n LED0 TASK create success \n");
  else
    term_printf("\n LED0 TASK create failed \n");

}

void led_test()
{
  drv_gpio_openbit(GPIOG,LED0_Pin,OUTPUT,1);
  drv_gpio_openbit(GPIOG,LED1_Pin,OUTPUT,1);
  drv_gpio_openbit(GPIOG,LED2_Pin,OUTPUT,1);
  
  task_create_led0();
  task_create_led1();
}

