#include "motor.h"
#include "delay.h"
#include "tracker.h"
#include "timer.h"

extern u8 i,j,timerTimeUp;
extern u16 timerClock;


//4个电机转向接口初始化  PE0,1,2,3,4,8,6,7
void Motor_IO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//使能GPIO外设
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStructure);		
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}



/*行走函数，正值为前进, 负值为后退*/
void walk(int speedL, int speedR){
	if(speedL > 0){
		motorLeftForward_IN1 = 0;//左前轮后退
		motorLeftForward_IN2 = 1;//左前轮前进
		motorLeftRear_IN1 = 0;//左后轮后退
		motorLeftRear_IN2 = 1;//左后轮前进
	}else{
		motorLeftForward_IN1 = 1;
		motorLeftForward_IN2 = 0;
		motorLeftRear_IN1 = 1;
		motorLeftRear_IN2 = 0;
		speedL = -speedL;
	}
	if(speedR > 0){
		motorRightForward_IN1 = 0;//右前轮后退
		motorRightForward_IN2 = 1;//右前轮前进
		motorRightRear_IN1 = 0;//右后轮后退
		motorRightRear_IN2 = 1;//右后轮前进
	}else{
		motorRightForward_IN1 = 1;
		motorRightForward_IN2 = 0;
		motorRightRear_IN1 = 1;
		motorRightRear_IN2 = 0;
		speedR = -speedR;
	}
	TIM_SetCompare1(TIM1,speedR*100);//右前
	TIM_SetCompare2(TIM1,speedL*100);//左后
	TIM_SetCompare3(TIM1,speedL*100);//左前
	TIM_SetCompare4(TIM1,speedR*100);//右后
	//delay_ms(100);
}

void turn(unsigned char toRight){

	int speedL = 70, speedR = 70;
	//increase diff between left & right
	if(toRight==1){
		do{
			speedR -= 10;
			walk(speedL, speedR);
			delay_ms(100);
		}while(speedR > -speedL);
	}else{
		do{
			speedL -= 10;
			walk(speedL, speedR);
			delay_ms(100);
		}while(speedL > -speedR);
	}
	delay_ms(400);//rotate
	
	//decrease diff between left & right
	while(speedL + speedR < 140 && middleTracker == 1){

		if(speedL < 70){
			speedL += 5;
		}else if(speedR < 70){
			speedR += 5;
		}else break;
		walk(speedL, speedR);
		delay_ms(150);
	}
	i++;
	timerClock = 0;//开始定时
	clearTimerFlag();
	j = 1;
}


