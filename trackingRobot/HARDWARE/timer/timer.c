#include "timer.h"
#include "sys.h"


//4个直流电机使能端PWM 初始化 TIM1_PWM 初始化
void TIM1_PWM_Init(u16 arr,u16 psc){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	TIM_OCInitTypeDef TIM_OCInitStructure;
//	NVIC_InitTypeDef NVIC_Initstructure;
	

//初始化GPIO   复用推挽  没有重映射
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//使能定时器1时钟
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设
	
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); //Timer3部分重映射 

	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init( GPIOE,&GPIO_InitStructure);//PE9
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOE,&GPIO_InitStructure);//PE11

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOE,&GPIO_InitStructure);//PE13

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOE,&GPIO_InitStructure);//PE14
	
//初始化timer1
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

//初始化 timer1 pwm
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	//???????????????????????????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	
//使能预装在寄存器
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);	
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_SetCounter(TIM1,0);
	
//
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);

	TIM_Cmd(TIM1,ENABLE);
}



//定时器3初始化
void TIM3_Time_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能TIM3的时钟


	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = TIM3_Reload_Num;//设置下一个更新事件后，装入自动重装载寄存器的值	
	TIM_TimeBaseStructure.TIM_Prescaler = TIM3_Frequency_Divide;//设置TIM3时钟预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;// 设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//根据参数初始化TIM3的计数方式
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//允许TIM3更新中断

	//TIM3的中断NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  			// TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  	// 抢占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  		// 子优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			// 使能TIM3_IRQn通道
	NVIC_Init(&NVIC_InitStructure);  							// 初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  									// 使能TIM3
}


extern u8 timerTimeUp[15];
void clearTimerFlag(void){
    u8 i;
    for(i = 0; i < 15; i++){
        timerTimeUp[i] = 0;
    }
}

