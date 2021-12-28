#include "usart.h"	  


//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 
//end


//舵机串口初始化
void UART3_Init(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
		USART_DeInit(USART3); 

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
		GPIO_Init(GPIOD, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
		GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
		USART_InitStructure.USART_BaudRate = 9600; 
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
		USART_InitStructure.USART_StopBits = USART_StopBits_1; 
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None; 
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART3, &USART_InitStructure); 
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
		
		USART_Cmd(USART3, ENABLE);
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

//视觉串口初始化
void UART4_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
		USART_DeInit(UART4);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
		GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
		USART_InitStructure.USART_BaudRate = 115200; 
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
		USART_InitStructure.USART_StopBits = USART_StopBits_1; 
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None; 
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(UART4, &USART_InitStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
		
		USART_Cmd(UART4, ENABLE);
		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
		
		
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
		USART_DeInit(UART5); 

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
		GPIO_Init(GPIOC, &GPIO_InitStructure); 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
		GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
		USART_InitStructure.USART_BaudRate = 115200; 
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
		USART_InitStructure.USART_StopBits = USART_StopBits_1; 
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None; 
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(UART5, &USART_InitStructure); 
		
		NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ; 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(&NVIC_InitStructure);
		
		USART_Cmd(UART5, ENABLE);
		USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
		
}



//gaoyan            ？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
/*
void UART5_Send_String(u8 *p,u8 cnt)
{
		 while(cnt>0)
		 {	 
		     USART_ClearFlag(USART1, USART_FLAG_TC);
		     USART_SendData(USART1,*p++);		
//         printf("%02x  ",*p++);			 
		     while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		     {
		   	     ;
		     }
				 cnt--;
		 }
}*/
