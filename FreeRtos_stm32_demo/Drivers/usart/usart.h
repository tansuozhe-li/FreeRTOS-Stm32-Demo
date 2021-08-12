/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#include "common.h"
#include "ring_queue.h"

#define usart1 USART1
#define uart5 UART5
typedef uint32_t device_handle;
extern device_handle g_uart_term_handle;
#define TERM_INDEX        5
#define TERM_PORT         UART5
#define TERMINAL_BAUD     115200
#define TERM_BUFF_SIZE    1500
static u_int8_t term_in_buff[TERM_BUFF_SIZE];

typedef struct _uart_device_info{
  u_int8_t init;   //该设备是否初始化准备接收数据标志
  u_int8_t index;  //uart设备索引，0,1,2,3
  RingQueue uart_ring_queue;  //用于维护设备的接收缓存的循环队列
}uart_device_info;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;


#define USART1_TX_Pin GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA
#define USART1_RX_Pin GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA
  
#define UART5_TX_Pin GPIO_PIN_12
#define UART5_TX_GPIO_Port GPIOC
#define UART5_RX_Pin GPIO_PIN_2
#define UART5_RX_GPIO_Port GPIOD





void uart_send_char(char ch);
void USART1_UART_Init();
void UART5_UART_Init();

void Error_Handler(void);


#endif /* __USART_H__ */

