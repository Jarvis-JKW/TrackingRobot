#include "init.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "motor.h"
#include "tracker.h"
#include "servo.h"

void init_all(void){
	Stm32_Clock_Init(9);		//系统时钟设置
	delay_Init(72);					//延时初始化
	UART3_Init();						//舵机控制板串口初始化
	UART4_Init();						//视觉串口初始化
	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	Motor_IO_Init();				//电机正反转控制信号口
	Track_Sensor_Init();		//寻迹传感器初始化
	TIM1_PWM_Init(10000,1);	//电机PWM控制口
	TIM_SetCompare1(TIM1,0);
	TIM_SetCompare2(TIM1,0);
	TIM_SetCompare3(TIM1,0);
	TIM_SetCompare4(TIM1,0);
	TIM3_Time_Init();				//定时器3初始化
}







