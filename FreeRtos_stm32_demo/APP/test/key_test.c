#include "common.h"
#include "app_cfg.h"
#include "usart.h"
#include "gpio.h"
#include "sysclk.h"
#include "FreeRTOS.h"
#include "task.h"
#include "device_term.h"
#include "key_test.h"
#include "led_test.h"

 char BEEP = 0;
static void Key1_Task(void *parameter)
{
  while(1)
  {
//    if(BEEP == 1)
//      {
//        term_printf("\n 挂起LED任务 \n");
//          vTaskSuspend(LED0_TASK_Handle);
//       // vTaskSuspend(LED0_TASK_Handle);
//      }
////   else{
////             term_printf("\n 恢复LED任务 \n");
////     vTaskResume(LED0_TASK_Handle);
////     vTaskResume(LED1_TASK_Handle);
////     }
    
     vTaskDelay(100);
  }
}

TaskHandle_t KEY1_TASK_Handle;
//static TaskHandle_t KEY1_TASK_Handle;
static void task_create_key1(void)
{
  BaseType_t xReturn = pdPASS;
  
  xReturn = xTaskCreate((TaskFunction_t)Key1_Task,
                       (const char* )"Key1_Task",   
                       (uint16_t     )128,           
                       (void*        )NULL,          
                       (UBaseType_t  )6,             
                       (TaskHandle_t*)&KEY1_TASK_Handle); 
  
  if(xReturn == pdPASS)
    term_printf("\n KEY1 TASK create success \n");
  else
    term_printf("\n KEY1 TASK create failed \n");  
}

void EXTIX_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOF_CLK_ENABLE();               //开启GPIOF时钟
 	
	// 配置外部中断线 EXTI_Line6,7,8,9  
	GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9; 	 
	GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
	GPIO_Initure.Pull=GPIO_PULLUP;
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
 
	HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);       //外部中断5-9  刚好 PF6-9 在 EXTI9_5_IRQn里面   抢占优先级为2，子优先级为0
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);    
}

//外部中断线5-9服务程序
void EXTI9_5_IRQHandler(void)
{
  if(drv_gpio_getbit(KEY0_GPIO_Port,KEY0_Pin) == 0)
  {
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);		//调用中断处理公用函数		
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	    switch(GPIO_Pin)
    {
        case GPIO_PIN_6:
				     BEEP=1; //蜂鸣器响
             break;
				
    }
}
void key_test()
{
  drv_gpio_openbit(KEY0_GPIO_Port,KEY0_Pin,INPUT,1);
  drv_gpio_openbit(KEY1_GPIO_Port,KEY1_Pin,INPUT,1);
  drv_gpio_openbit(KEY2_GPIO_Port,KEY2_Pin,INPUT,1);

  EXTIX_Init();
  //task_create_key1();
}

