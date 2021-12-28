#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#define USART_REC_LEN  	200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
//	  	
//extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
//extern u16 USART_RX_STA;         		//接收状态标记	
////如果想串口中断接收，请不要注释以下宏定义
//void uart_init(u32 bound);
//#endif

//extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲
//extern u16 USART_RX_STA;         		//接收状态标记
//void USART_Send_Data(u8 data);
//void USART1_Init(u32 pclk2,u32 bound);
//void USART2_Init(u32 bound);//初始化
//uint8_t get_ok_or_not(void);
//uint16_t get_long(void);
//void USART2_Send_String(u8 *p,u8 cnt);
//void USART2_Send_Byte(uint16_t Data);
void UART3_Init(void);
void UART4_Init(void);

#endif


