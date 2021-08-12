/**
  ******************************************************************************
  * @file    device_term.c
  * @brief   
  *          
  * @author   Lqc
  ******************************************************************************
  */
#include "device_term.h"
#include "usart.h"
#include "common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"

device_handle g_uart_term_handle;

/// 终端交互任务
///
/// @param  none
/// @return none
void task_term()
{
  while(1)
  {
    u_int8_t c=0;
   HAL_GPIO_WritePin(GPIOG, LED2_Pin, GPIO_PIN_SET);
   vTaskDelay(900);
   HAL_GPIO_WritePin(GPIOG, LED2_Pin, GPIO_PIN_RESET);
   vTaskDelay(900);
   
   uart_get_char(&c);
   
   if(c != 0){
     HAL_GPIO_WritePin(GPIOG, LED2_Pin, GPIO_PIN_SET);
     term_printf("\n 接收的数据为：%s\n",c);
     term_printf("\n 接收的数据为：%d\n",c);
   }else{
     HAL_GPIO_WritePin(GPIOG, LED2_Pin, GPIO_PIN_RESET);
   }
   
     
   
  }
}
/// 创建终端交互任务
///
/// @param  none
/// @return none
static TaskHandle_t TERM_TASK_Handle = NULL;
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
   vTaskDelay(500);
   HAL_GPIO_WritePin(GPIOG, LED1_Pin, GPIO_PIN_RESET);
   vTaskDelay(500);
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
    vTaskDelay(100);
    HAL_GPIO_WritePin(GPIOG, LED0_Pin, GPIO_PIN_SET);
    vTaskDelay(100);
  }
}

static TaskHandle_t LED1_TASK_Handle = NULL;
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

static TaskHandle_t LED2_TASK_Handle = NULL;
static void task_create_led2(void)
{
  BaseType_t xReturn = pdPASS;
  
  xReturn = xTaskCreate((TaskFunction_t)LED2_Task,
                       (const char* )"LED2_Task",   
                       (uint16_t     )128,           
                       (void*        )NULL,          
                       (UBaseType_t  )5,             
                       (TaskHandle_t*)&LED2_TASK_Handle); 
  
  if(xReturn == pdPASS)
    term_printf("\n LED2 TASK create success \n");
  else
    term_printf("\n LED2 TASK create failed \n");

}
static void Key1_Task(void *parameter)
{
  while(1)
  {
    
  }
}

static TaskHandle KEY1_TASK_Handle = NULL;
static void task_create_key1(void)
{
  BaseType_t xReturn = pdPASS;
  
  xReturn = xTaskCreate((TaskFunction_t)Key1_Task,
                       (const char* )"Key1_Task",   
                       (uint16_t     )128,           
                       (void*        )NULL,          
                       (UBaseType_t  )5,             
                       (TaskHandle_t*)&KEY1_TASK_Handle); 
  
  if(xReturn == pdPASS)
    term_printf("\n KEY1 TASK create success \n");
  else
    term_printf("\n KEY1 TASK create failed \n");  
}




void led_test()
{
  task_create_led1();
  task_create_led2();
  task_create_key1();
}