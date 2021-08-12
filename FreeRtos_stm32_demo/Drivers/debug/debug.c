/**
  ******************************************************************************
  * @file    debug.c
  * @brief   
  *          
  * @anthor  liqingchang
  ******************************************************************************
  */

#include "debug.h"
#include "usart.h"

///打印字符串
void term_uart_wrstr(char *p_str)
{
  while((*p_str) != (char)0u){
    if(*p_str == 0x0A){
      uart_send_char(0x0D);
      uart_send_char(0x0A);
      p_str++;
    }else{
      uart_send_char(*p_str++);
    }
  }
}


///格式打印
void term_printf(char *format, ...)
{
  static char buffer[200+1];
  va_list vArgs;
  memset(buffer,'0',sizeof(buffer));
  
  va_start(vArgs, format);
  vsprintf((char *)buffer, (char const *)format, vArgs);
  va_end(vArgs);
  
  term_uart_wrstr((char *)buffer);
}