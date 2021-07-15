
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
//��̬��������
//������
static TaskHandle_t AppTaskCreate_Handle = NULL;
static TaskHandle_t LED1_TASK_Handle = NULL;
static TaskHandle_t LED2_TASK_Handle = NULL;

//��������
static void AppTaskCreate(void);   //���ڴ�������
static void LED1_Task(void* pvParamerers);  //LED1_Task����ʵ��
static void LED2_Task(void* pvParamerers);  //LED2_Task����ʵ��


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
                      (const char* )"AppTaskCreate",   //��������
                      (uint16_t     )512,               //����ջ��С
                      (void*        )NULL,             //���ݸ��������Ĳ���
                      (UBaseType_t  )1,                //�������ȼ�
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
* @��������AppTaskCreate
* @����˵�������񴴽�����
* @��������
* @����ֵ����
*******************************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;
  
  taskENTER_CRITICAL();    //�����ٽ���
  
  xReturn = xTaskCreate((TaskFunction_t)LED1_Task,
                                      (const char* )"LED1_Task",   //��������
                                      (uint16_t     )128,               //����ջ��С
                                      (void*        )NULL,             //���ݸ��������Ĳ���
                                      (UBaseType_t  )2,                //�������ȼ�
                                      (TaskHandle_t*)&LED1_TASK_Handle);
  
  xReturn = xTaskCreate((TaskFunction_t)LED2_Task,
                                      (const char* )"LED2_Task",   //��������
                                      (uint16_t     )128,               //����ջ��С
                                      (void*        )NULL,             //���ݸ��������Ĳ���
                                      (UBaseType_t  )2,                //�������ȼ�
                                      (TaskHandle_t*)&LED2_TASK_Handle);    
    if(pdPASS == xReturn)
    
      vTaskDelete(AppTaskCreate_Handle);
    
   taskEXIT_CRITICAL();    //�˳��ٽ���
    
}
/*******************************************************************************
* @��������LED_Task
* @����˵����LED_Task��������
* @��������
* @����ֵ����
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
* @��������LED_Task
* @����˵����LED_Task��������
* @��������
* @����ֵ����
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

