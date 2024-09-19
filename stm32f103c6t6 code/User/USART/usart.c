#include "sys.h"
#include "usart.h"	  


#pragma import(__use_no_semihosting)             
//标准库需要支持的函数
struct __FILE 
{
	int handle;
};

FILE __stdout;       
//定义_sys_exit()以避免工作在半主机状态
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数
//这个需要根据MCU和我们希望printf从哪个串口输出来确认 __WAIT_TODO__
int fputc(int ch, FILE *f)
{
	//注意：USART_FLAG_TXE是检查发送缓冲区是否为空，这个要在发送前检查，检查这个提议提高发送效率，但是在休眠的时候可能导致最后一个字符丢失
	//USART_FLAG_TC是检查发送完成标志，这个在发送后检查，这个不会出现睡眠丢失字符问题，但是效率低（发送过程中发送缓冲区已经为空了，可以接收下一个数据了，但是因为要等待发送完成，所以效率低）
	//不要两个一起用，一起用效率最低
	
	//循环等待直到发送缓冲区为空(TX Empty)此时可以发送数据到缓冲区
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {}
	USART_SendData(USART1, (uint8_t) ch);

  /* 循环等待直到发送结束*/
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}

	return ch;
}
void uart_init(u32 bound)//串口1  引脚为PB6-TX  PB7-RX
{//作为日志输出
	
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟  
    
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //tx脚推栏输出 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //rx浮空输入（数据传送的话必须用这个） 
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);  
		 
		 GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);//管脚映射
	
    //Usart1 NVIC 配置
		
   // NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
   // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级0
   // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;      //响应优先级0
  //  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //USART_IRQn通道使能
   // NVIC_Init(&NVIC_InitStructure); //初始化NVIC

    //USART1 配置
    USART_InitStructure.USART_BaudRate = bound;//波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//数据长度
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位1
    USART_InitStructure.USART_Parity = USART_Parity_No;//校验位无
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控制无
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //使能串口的接收和发送功能
    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE|USART_IT_IDLE, ENABLE);//配置了接收中断和总线空闲中断
    USART_Cmd(USART1, ENABLE);      //串口外设使能
	//	USART_ClearFlag(USART1,USART_FLAG_TC);    
}

void USART1_IRQHandler( void )
{ 
	
}