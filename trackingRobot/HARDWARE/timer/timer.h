#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM3_Time_Init(void);
void clearTimerFlag(void);

//timer3
#define	TIM3_Frequency_Divide	71		// TIM3时钟预分频值
#define	TIM3_Reload_Num			999		// 自动重装载寄存器的值


/*
extern u8 over;
extern u8 over1;


void TIM6_Int_Init(u16 arr,u16 psc);
void TIM8_PWM_Init(u16 arr,u16 psc);
*/

#endif
