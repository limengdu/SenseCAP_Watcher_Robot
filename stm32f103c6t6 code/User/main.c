/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
	*
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "stdio.h"
#include "systick.h" 
#include "exti.h" 
#include "sys.h"
#include "usart.h"
#include "string.h"
#define KEY1 PBin(4)
#define KEY1_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY1_PORT			 GPIOB
#define KEY1_PORT_PIN  GPIO_Pin_4

void RCC_Config(void);
void send_data(char * uiData);
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	
	RCC_Config();
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(KEY1_PORT_CLK|KEY1_PORT_CLK,ENABLE);//使能PORTA,PORTC时钟

  GPIO_InitStructure.GPIO_Pin  = KEY1_PORT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
  GPIO_Init(KEY1_PORT, &GPIO_InitStructure);//初始化GPIO
	
	
	delay_init();
	uart_init(9600);//
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	
	
	//执行分组动作，动作需要在小程序上进行训练，0A是固定值，19代表执行ID为19编号的动作组，id值从小程序中按键管理里面获取
	//send_data("$0A19!");
	
	
	//控制单个舵机直接运行，格式：1A为固定写法，002表示舵机编号，三位数；030表示舵机旋转的角度值，三位数，取值范围从000-180内
	send_data("$1A002030!");//2号舵机执行30度
	delay_ms(200);//休息500毫秒
	send_data("$1A002050!");//2号舵机执行50度
	delay_ms(200);//休息500毫秒
	send_data("$1A002070!");//2号舵机执行70度
	/*
	while(1)
	{
		
    delay_ms(1000);//去抖动
	//	pwm_send_data("$0A29!");
  if(KEY1==0)
  {
    delay_ms(5);//去抖动
    if(KEY1==0)
		{//执行分组动作，动作需要在小程序上进行训练，0A是固定值，19代表执行ID为19编号的动作组，id值从小程序中按键管理里面获取
			//	send_data("$0A29!");
		}
  }
	
	}*/
	
	return (1);
}
/**发送串口数据*/
void send_data(char * Data)
{
  while(*Data!='\0')
  {
			delay_ms(1);
      while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//读取串口状态
      USART_SendData(USART1, *Data);
      Data++;
	}
	
}



void RCC_Config(void)
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);//使能外部时钟
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY)==RESET);
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);//配置hclk时钟
	RCC_PCLK2Config(RCC_HCLK_Div1);//
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
	RCC_PLLCmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
}

