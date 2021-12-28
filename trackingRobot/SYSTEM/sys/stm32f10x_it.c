/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "timer.h"

 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}


//串口3服务中断程序
void USART3_IRQHandler(void){
	unsigned char Clear;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
		Clear=USART3->DR;
		Clear=Clear;
	}
}


extern u8 color;//1 = Red; 2 = Green
extern u8 VisionData[3];
//串口4服务中断程序, OpenMV使用
void UART4_IRQHandler(void)
{
	static u8 idx;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		VisionData[idx] = UART4->DR;
		idx++;
		if(idx > 1){
			idx = 0;
		}
		if(VisionData[0]=='R' || VisionData[1]=='R'){
			color = 'R';
		}else if(VisionData[0]=='G' || VisionData[1]=='G'){
			color = 'G';
		}else{
			color = 'N';
		}
	}
}


extern u16 timerClock;
extern u8 timerTimeUp[15], j;
//定时器3中断服务函数
void TIM3_IRQHandler(void){ 
 	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET )		// 判断是否为TIM3的更新中断
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  		// 清除TIM3更新中断标志
		timerClock++;
		if(timerClock >= 800)								// 1s
		{
			timerClock = 0;									// 定时器清零
			j++;
			if(timerTimeUp[14]==1){							// 判断定时数组是否溢出
				clearTimerFlag();
				j = 0;
			}else{
				timerTimeUp[j] = 1;
			}
		}
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
