/****************************************Copyright (c)****************************************************
**                                      
**                                 心灵互动
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               exti.c
** Descriptions:            中断程序的调用
**
**--------------------------------------------------------------------------------------------------------
** Created by:              向祎
** Created date:            2021-10-30
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef __EXTI_H
#define __EXTI_H 

/* Includes ------------------------------------------------------------------*/	   
#include "stm32f10x.h"
#include <stdio.h>

/* Private function prototypes -----------------------------------------------*/
void EXTI_InitConfiguration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void  EXTI0_IRQHandler(void);

#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/






























