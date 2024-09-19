/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	
	RCC_Config();
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(KEY1_PORT_CLK|KEY1_PORT_CLK,ENABLE);//ʹ��PORTA,PORTCʱ��

  GPIO_InitStructure.GPIO_Pin  = KEY1_PORT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
  GPIO_Init(KEY1_PORT, &GPIO_InitStructure);//��ʼ��GPIO
	
	
	delay_init();
	uart_init(9600);//
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	
	//ִ�з��鶯����������Ҫ��С�����Ͻ���ѵ����0A�ǹ̶�ֵ��19����ִ��IDΪ19��ŵĶ����飬idֵ��С�����а������������ȡ
	//send_data("$0A19!");
	
	
	//���Ƶ������ֱ�����У���ʽ��1AΪ�̶�д����002��ʾ�����ţ���λ����030��ʾ�����ת�ĽǶ�ֵ����λ����ȡֵ��Χ��000-180��
	send_data("$1A002030!");//2�Ŷ��ִ��30��
	delay_ms(200);//��Ϣ500����
	send_data("$1A002050!");//2�Ŷ��ִ��50��
	delay_ms(200);//��Ϣ500����
	send_data("$1A002070!");//2�Ŷ��ִ��70��
	/*
	while(1)
	{
		
    delay_ms(1000);//ȥ����
	//	pwm_send_data("$0A29!");
  if(KEY1==0)
  {
    delay_ms(5);//ȥ����
    if(KEY1==0)
		{//ִ�з��鶯����������Ҫ��С�����Ͻ���ѵ����0A�ǹ̶�ֵ��19����ִ��IDΪ19��ŵĶ����飬idֵ��С�����а������������ȡ
			//	send_data("$0A29!");
		}
  }
	
	}*/
	
	return (1);
}
/**���ʹ�������*/
void send_data(char * Data)
{
  while(*Data!='\0')
  {
			delay_ms(1);
      while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//��ȡ����״̬
      USART_SendData(USART1, *Data);
      Data++;
	}
	
}



void RCC_Config(void)
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);//ʹ���ⲿʱ��
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY)==RESET);
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);//����hclkʱ��
	RCC_PCLK2Config(RCC_HCLK_Div1);//
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
	RCC_PLLCmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
}

