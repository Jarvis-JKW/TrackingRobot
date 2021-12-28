#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  

void delay_Init(u8 SYSCLK);
void delay_s(u8 ns);
void delay_ms(u16 nms);//no more than 1864
void delay_us(u32 nus);

#endif

