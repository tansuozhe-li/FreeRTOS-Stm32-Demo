/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */

#include "gpio.h"

//void MX_GPIO_Init(void)
//{
//
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOH_CLK_ENABLE();
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOG_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//  __HAL_RCC_GPIOF_CLK_ENABLE();
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
//
//  /*Configure GPIO pins : PGPin PGPin */
//  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED2_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
//
//  GPIO_InitStruct.Pin = KEY0_Pin | KEY1_Pin | KEY2_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOF,&GPIO_InitStruct);
// 
//}
/*******************************************************************************
函数名称：drv_gpio_openbit
函数功能：初始化GPIO
入口参数：port:指定的GPIO端口,如GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF
          pin :指定的GPIO端口的具体某一位GPIO_PIN_0-15
          mode:指定的GPIO端口的模式，INPUT=0,OUTPUT=1,
          data:输入：1-上拉电阻，0-下拉电阻，输出：1-高电平，0-低电平
出口参数：无
*******************************************************************************/
void drv_gpio_openbit(GPIO_TypeDef *port, u_int16_t pin, GPIO_MODED mode, u_int8_t data)
{
  
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(port == GPIOA)
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }else if(port == GPIOB){
    __HAL_RCC_GPIOB_CLK_ENABLE();
  }else if(port == GPIOC){
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }else if(port == GPIOD){
    __HAL_RCC_GPIOD_CLK_ENABLE();
  }else if(port == GPIOE){
    __HAL_RCC_GPIOE_CLK_ENABLE();
  }else if(port == GPIOF){
    __HAL_RCC_GPIOF_CLK_ENABLE();
  }else if(port == GPIOG){
    __HAL_RCC_GPIOG_CLK_ENABLE();
  }else if(port == GPIOH){
    __HAL_RCC_GPIOH_CLK_ENABLE();
  }else{
    __HAL_RCC_GPIOI_CLK_ENABLE();
  }
       
    GPIO_InitStruct.Pin = pin;
    
    if(mode == INPUT)
    {
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      if(data == 0)
      {
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;//下拉激活
      }else{
        GPIO_InitStruct.Pull = GPIO_PULLUP;//上拉激活
      }
    }
    
    if(mode == OUTPUT)
    {
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; //推挽输出
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      if(data == 0)
      {
         HAL_GPIO_WritePin(port,pin,GPIO_PIN_RESET);
       }else{
        HAL_GPIO_WritePin(port,pin,GPIO_PIN_SET);
       }
    }
    
    GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_LOW;
    
    HAL_GPIO_Init(port,&GPIO_InitStruct);
}




/*******************************************************************************
函数名称：drv_gpio_setbit
函数功能：设置指定端口的某一位为高电平
入口参数：port:指定的GPIO端口,如GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF
          pin :指定的GPIO端口的具体某一位GPIO_PIN_0-15
出口参数：无
*******************************************************************************/
void drv_gpio_setbit(GPIO_TypeDef *port,u_int16_t pin)
{
  
  HAL_GPIO_WritePin(port,pin,GPIO_PIN_SET);
  
}

/*******************************************************************************
函数名称：drv_gpio_clrbit
函数功能：设置指定端口的某一位为低电平
入口参数：port:指定的GPIO端口,如GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF
          pin :指定的GPIO端口的具体某一位GPIO_PIN_0-15
出口参数：无
*******************************************************************************/
void drv_gpio_clrbit(GPIO_TypeDef *port,u_int16_t pin)
{
  
  HAL_GPIO_WritePin(port,pin,GPIO_PIN_RESET);
  
}

/*******************************************************************************
函数名称：drv_gpio_getbit
函数功能：获取指定端口的某一位电平
入口参数：port:指定的GPIO端口,如GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF
          pin :指定的GPIO端口的具体某一位GPIO_PIN_0-15
出口参数：无
*******************************************************************************/
u_int32_t drv_gpio_getbit(GPIO_TypeDef *port,u_int16_t pin)
{
  u_int32_t bit_value =0;
  if(HAL_GPIO_ReadPin(port,pin))
  {
    bit_value = 1;
  }else{
    bit_value = 0;
  }
  return bit_value;
}

/*******************************************************************************
函数名称：drv_gpio_togglebit
函数功能：翻转指定端口的某一位电平
入口参数：port:指定的GPIO端口,如GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF
          pin :指定的GPIO端口的具体某一位GPIO_PIN_0-15
出口参数：无
*******************************************************************************/
void drv_gpio_togglebit(GPIO_TypeDef *port,u_int16_t pin)
{
  
  HAL_GPIO_TogglePin(port,pin);
  
}

/*******************************************************************************
函数名称：drv_gpio_togglebit
函数功能：翻转指定端口的某一位电平
入口参数：port:指定的GPIO端口,如GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF
          pin :指定的GPIO端口的具体某一位GPIO_PIN_0-15
出口参数：无
*******************************************************************************/
void drv_gpio_enableIRQ(GPIO_TypeDef *port,u_int16_t pin)
{
  
}




