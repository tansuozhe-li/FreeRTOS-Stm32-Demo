/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  */

#include "usart.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;

//串口发送一个字符
void uart_send_char(char ch)
{
  while((UART5->SR & 0x40) == 0);  //0-传送未完成，1-传送已完成
         UART5->DR = ch;
}

//串口接收一个字符
void uart_get_char(char *ch)
{
  while((UART5->SR & 0x20) == 0);  //0-未接收到数据，1-接收到数据
         *ch = UART5->DR;
}

//串口1初始化
void USART1_UART_Init()
{
  huart1.Instance = usart1;   
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

//串口5初始化
void UART5_UART_Init()
{
  huart5.Instance = uart5; //串口基地址      
  huart5.Init.BaudRate = 9600;  //设置串口波特率
  huart5.Init.WordLength = UART_WORDLENGTH_8B;  //设置传输位数 8
  huart5.Init.StopBits = UART_STOPBITS_1;  //传输停止位 1
  huart5.Init.Parity = UART_PARITY_NONE;  //奇偶校验
  huart5.Init.Mode = UART_MODE_TX_RX;    //启用接收发送模式
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;  //禁用硬件流控制模式
  huart5.Init.OverSampling = UART_OVERSAMPLING_16; //禁用过采样
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
}

//初始化底层硬件
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==usart1)
  {
    __HAL_RCC_USART1_CLK_ENABLE();  

    __HAL_RCC_GPIOA_CLK_ENABLE();
    //PA9->Tx引脚（复用推挽输出模式）
    GPIO_InitStruct.Pin = USART1_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    //PA10->Rx引脚（复用上拉输入模式）
    GPIO_InitStruct.Pin = USART1_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

  }
    if(uartHandle->Instance==uart5)
  {
    __HAL_RCC_UART5_CLK_ENABLE();   //启用时钟
    
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
//    GPIO_InitStruct.Pin = UART5_TX_Pin|UART5_RX_Pin;  //串口引脚
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;   //模式
//    GPIO_InitStruct.Pull = GPIO_NOPULL;   //无上拉或下拉激活
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
        //PA9->Tx引脚（复用推挽输出模式）
    GPIO_InitStruct.Pin = UART5_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    //PA10->Rx引脚（复用上拉输入模式）
    GPIO_InitStruct.Pin = UART5_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART5_IRQn);

  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
    __HAL_RCC_USART1_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOA, USART1_TX_Pin|USART1_RX_Pin);

    HAL_NVIC_DisableIRQ(USART1_IRQn);
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }

}
