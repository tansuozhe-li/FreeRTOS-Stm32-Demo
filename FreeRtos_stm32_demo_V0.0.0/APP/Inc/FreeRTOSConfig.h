/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f407xx.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

//断言
#if 0
#define vAssertCalled(char,int)  print("Error:%s,%d\r\n",char,int)
#defint configASSERT(x) if((x) == 0)  vAssertCalled(__FILE__,__LINE__)
#endif

/*******************************************************************************
                           FreeRTOS基础配置选项
*******************************************************************************/
/*
置1：抢占式调度器，置0：协作式调度器（时间片）协作式操作系统是任务主动释放CPU后
切换到下一个任务
*/
#define configUSE_PREEMPTION			    1
/*
1表示启用时间片调度（默认是启用的）
*/
#define configUSE_TIME_SLICING                      1
/*
选择下一个执行的任务：
通用方法：置0或者硬件不支持，C实现，效率较低，不限制最大优先级数据
特殊方法: 置1，汇编，效率较高，最大可用优先级32
*/
#define configUSE_PORT_OPTIMISED_TASK_SELECTION     1
/*
置1：启用低功耗 tickless模式，置0：保持系统节拍tick中断一直运行
*/
#define configUSE_TICKLESS_IDLE                     1
/*
写入实际的CPU内核时钟频率，也就是CPU指令执行频率
*/
#define configCPU_CLOCK_HZ			    ( SystemCoreClock )
/*
系统节拍中断的频率，即每秒中断的次数，每次产生中断，RTOS都会进行任务调度
*/
#define configTICK_RATE_HZ			    ( ( TickType_t ) 1000 )
/*
可使用的最大优先级
*/
#define configMAX_PRIORITIES			    ( 32 )
/*
空闲任务使用的栈大小
*/
#define configMINIMAL_STACK_SIZE		    ( ( unsigned short ) 128 )
/*
任务名的字符串长度
*/
#define configMAX_TASK_NAME_LEN			    ( 10 )
/*
系统节拍计数器变量数据类型，1表示16位，0表示32位，无符号整型
*/
#define configUSE_16_BIT_TICKS			    0
/*
空闲任务放弃CPU使用权，交给其他同优先级的用户任务，置1表示抢占式调度
*/
#define configIDLE_SHOULD_YIELD			    1
/*
启用消息队列，是FreeRTOS的IPC通信的一种
*/
#define configUSE_QUEUE_SETS                        1
/*
开启任务通知功能，默认开启。每个FreeRTOS任务具有一个32位的通知值，FreeRTOS任务通
知是直接向任务发送一个事件，并且接收任务的通知值是可以选择的，任务通过接收到的任
务通知值来解除任务的阻塞状态（假如因等待该任务通知而进入阻塞状态），相对于队列、
二进制信号量、计数信号量或事件组等IPC通信，使用任务通知更加灵活
*/
#define configUSE_TASK_NOTIFICATIONS                1
/*
使用互斥信号量
*/
#define configUSE_MUTEXES			    1
/*
使用递归互斥信号量
*/
#define configUSE_RECURSIVE_MUTEXES		    1
/*
使用计数信号量
*/
#define configUSE_COUNTING_SEMAPHORES	            1
/*
设置可以注册的信号量和消息队列个数
*/
#define configQUEUE_REGISTRY_SIZE		    8

#define configCHECK_FOR_STACK_OVERFLOW	            0
#define configUSE_APPLICATION_TASK_TAG	            0

/*******************************************************************************
                    FreeRTOS与内存申请有关配置选项
*******************************************************************************/
/*
支持动态内存分配申请
*/
#define configSUPPORT_DYNAMIC_ALLOCATION            1
/*
系统所有栈的大小
*/
#define configTOTAL_HEAP_SIZE			    ( ( size_t ) ( 75 * 1024 ) )

/*******************************************************************************
                    FreeRTOS与钩子函数有关的配置选项
*******************************************************************************/
#define configUSE_IDLE_HOOK			    0
#define configUSE_TICK_HOOK		            0
#define configUSE_MALLOC_FAILED_HOOK	            0

/*******************************************************************************
                    FreeRTOS与协程有关的配置选项（默认不启用）
*******************************************************************************/
#define configUSE_CO_ROUTINES 		            0
#define configMAX_CO_ROUTINE_PRIORITIES           ( 2 )

/*******************************************************************************
                 FreeRTOS与运行时间和任务状态收集有关的配置选项
*******************************************************************************/
/*
启用运行时间统计功能
*/
#define configGENERATE_RUN_TIME_STATS               0
/*
启用可视化跟踪调试
*/
#define configUSE_TRACE_FACILITY		    1
/*
与configUSE_TRACE_FACILITY同时为1时会编译一下3个函数
prvWriteNameToBuffer()
vTaskList()
vTaskGetRunTimeStats()
*/
#define configUSE_STATS_FORMATTING_FUNCTIONS        1

/*******************************************************************************
                 FreeRTOS与软件定时器有关的配置选项
*******************************************************************************/
/*
启用软件定时器 
*/
#define configUSE_TIMERS			    1
/*
软件定时器优先级 
*/
#define configTIMER_TASK_PRIORITY		  ( configMAX_PRIORITIES - 1 )
/*
软件定时器队列长度 
*/
#define configTIMER_QUEUE_LENGTH		    10
/*
软件定时器任务栈大小 
*/
#define configTIMER_TASK_STACK_DEPTH	        ( configMINIMAL_STACK_SIZE * 2 )

/*******************************************************************************
                 FreeRTOS可选函数配置选项
*******************************************************************************/
/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_xTaskGetSchedulerState               1
#define INCLUDE_vTaskPrioritySet		     1
#define INCLUDE_uxTaskPriorityGet		     1
#define INCLUDE_vTaskDelete			     1
#define INCLUDE_vTaskCleanUpResources	             1
#define INCLUDE_vTaskSuspend			     1
#define INCLUDE_vTaskDelayUntil			     1
#define INCLUDE_vTaskDelay			     1
#define INCLUDE_eTaskGetState                        1
#define INCLUDE_xTimerPendFunctionCall               1

/*******************************************************************************
                 FreeRTOS与中断有关的配置选项
*******************************************************************************/
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

