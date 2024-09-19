#include "sys.h"
#include "usart.h"	  


#pragma import(__use_no_semihosting)             
//��׼����Ҫ֧�ֵĺ���
struct __FILE 
{
	int handle;
};

FILE __stdout;       
//����_sys_exit()�Ա��⹤���ڰ�����״̬
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����
//�����Ҫ����MCU������ϣ��printf���ĸ����������ȷ�� __WAIT_TODO__
int fputc(int ch, FILE *f)
{
	//ע�⣺USART_FLAG_TXE�Ǽ�鷢�ͻ������Ƿ�Ϊ�գ����Ҫ�ڷ���ǰ��飬������������߷���Ч�ʣ����������ߵ�ʱ����ܵ������һ���ַ���ʧ
	//USART_FLAG_TC�Ǽ�鷢����ɱ�־������ڷ��ͺ��飬����������˯�߶�ʧ�ַ����⣬����Ч�ʵͣ����͹����з��ͻ������Ѿ�Ϊ���ˣ����Խ�����һ�������ˣ�������ΪҪ�ȴ�������ɣ�����Ч�ʵͣ�
	//��Ҫ����һ���ã�һ����Ч�����
	
	//ѭ���ȴ�ֱ�����ͻ�����Ϊ��(TX Empty)��ʱ���Է������ݵ�������
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {}
	USART_SendData(USART1, (uint8_t) ch);

  /* ѭ���ȴ�ֱ�����ͽ���*/
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}

	return ch;
}
void uart_init(u32 bound)//����1  ����ΪPB6-TX  PB7-RX
{//��Ϊ��־���
	
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART1��GPIOAʱ��  
    
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //tx��������� 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //rx�������루���ݴ��͵Ļ������������ 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);  
		 
		 GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);//�ܽ�ӳ��
	
    //Usart1 NVIC ����
		
   // NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
   // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�0
   // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;      //��Ӧ���ȼ�0
  //  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //USART_IRQnͨ��ʹ��
   // NVIC_Init(&NVIC_InitStructure); //��ʼ��NVIC

    //USART1 ����
    USART_InitStructure.USART_BaudRate = bound;//������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//���ݳ���
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ1
    USART_InitStructure.USART_Parity = USART_Parity_No;//У��λ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ����������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //ʹ�ܴ��ڵĽ��պͷ��͹���
    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE|USART_IT_IDLE, ENABLE);//�����˽����жϺ����߿����ж�
    USART_Cmd(USART1, ENABLE);      //��������ʹ��
	//	USART_ClearFlag(USART1,USART_FLAG_TC);    
}

void USART1_IRQHandler( void )
{ 
	
}