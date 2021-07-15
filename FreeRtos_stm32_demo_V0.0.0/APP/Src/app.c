
/**
  ******************************************************************************
  * @file           : app.c
  * @brief          : Main program body
  * @anthor         : liqingchang
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "app_cfg.h"
#include "usart.h"
#include "gpio.h"
#include "sysclk.h"
#include "FreeRTOS.h"
#include "task.h"
//静态创建任务
//任务句柄
static TaskHandle_t AppTaskCreate_Handle = NULL;
static TaskHandle_t LED1_TASK_Handle = NULL;
static TaskHandle_t LED2_TASK_Handle = NULL;

//函数声明
static void AppTaskCreate(void);   //用于创建任务
static void LED1_Task(void* pvParamerers);  //LED1_Task任务实现
static void LED2_Task(void* pvParamerers);  //LED2_Task任务实现


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  USART1_UART_Init();
     
  BaseType_t xReturn = pdPASS;
     
  xReturn = xTaskCreate((TaskFunction_t)AppTaskCreate,
                      (const char* )"AppTaskCreate",   //任务名称
                      (uint16_t     )512,               //任务栈大小
                      (void*        )NULL,             //传递给任务函数的参数
                      (UBaseType_t  )1,                //任务优先级
                      (TaskHandle_t* )&AppTaskCreate_Handle);
  if(pdPASS == xReturn)
    vTaskStartScheduler();
//  else
//    return -1;
  
  while (1)
  {
  }
    
}
/*******************************************************************************
* @函数名：AppTaskCreate
* @功能说明：任务创建函数
* @参数：无
* @返回值：无
*******************************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;
  
  taskENTER_CRITICAL();    //进入临界区
  
  xReturn = xTaskCreate((TaskFunction_t)LED1_Task,
                                      (const char* )"LED1_Task",   //任务名称
                                      (uint16_t     )128,               //任务栈大小
                                      (void*        )NULL,             //传递给任务函数的参数
                                      (UBaseType_t  )2,                //任务优先级
                                      (TaskHandle_t*)&LED1_TASK_Handle);
  
  xReturn = xTaskCreate((TaskFunction_t)LED2_Task,
                                      (const char* )"LED2_Task",   //任务名称
                                      (uint16_t     )128,               //任务栈大小
                                      (void*        )NULL,             //传递给任务函数的参数
                                      (UBaseType_t  )2,                //任务优先级
                                      (TaskHandle_t*)&LED2_TASK_Handle);    
    if(pdPASS == xReturn)
    
      vTaskDelete(AppTaskCreate_Handle);
    
   taskEXIT_CRITICAL();    //退出临界区
    
}
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

    HAL_GPIO_WritePin(GPIOG, LED1_Pin, GPIO_PIN_SET);

   vTaskDelay(100);
   HAL_GPIO_WritePin(GPIOG, LED1_Pin, GPIO_PIN_RESET);
   vTaskDelay(100);
  }
}

/*******************************************************************************
* @函数名：LED_Task
* @功能说明：LED_Task任务主体
* @参数：无
* @返回值：无
*******************************************************************************/
static void LED2_Task(void* parameter)
{
    while (1)
  {
   
    HAL_GPIO_WritePin(GPIOG, LED0_Pin, GPIO_PIN_RESET);
    vTaskDelay(500);
 HAL_GPIO_WritePin(GPIOG, LED0_Pin, GPIO_PIN_SET);
    vTaskDelay(500);
  }
}

