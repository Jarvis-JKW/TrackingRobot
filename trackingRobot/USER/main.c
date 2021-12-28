#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "sys.h"
#include "motor.h"
#include "init.h"
#include "tracker.h"
#include "servo.h"
#include "timer.h"
#define TARGET 10


u8 i = 0;//num of corners
u8 redFlag = 0, greenFlag = 0, workFlag = 0, shortcutFlag=0;
u8 VisionData[2], color;
u16 timerClock;
u8  timerTimeUp[15] = {0}, j = 1;


int main(){

	init_all();
	pick(0);
	walk(70,70);
	delay_ms(1500);
	
	while(i <= (TARGET * 4 + 2)){
		if(leftTracker==1 && middleTracker==1 && rightTracker==1){//corner
shortcut:
			if(i==0){
				turn(1);
			}else if(i == (TARGET * 4 + 1)){
				turn(0);
				break;
			}else{
				turn(i/4/TARGET);
			}

		}else if(leftTracker==1 && middleTracker==0 && rightTracker==1){//center
			if(i%4==3 && workFlag!=0){
				walk(70, 70);
			}else{
				walk(90, 90);
			}
			while(leftTracker==1 && middleTracker==0 && rightTracker==1){

			//未工作且在检测区
loop:		if(workFlag==0 && (i%4==1)){
				shortcutFlag=0;
				if(color != 'N' && i != TARGET*4+1){
					switch(color){
						case 'R': redFlag++;  workFlag=1;break;
						case 'G': greenFlag++;workFlag=2;break;
					}
					walk(0, 0);
					pick(1);
					delay_s(5);
					stopActionGroup();
					break;
				}
				//工作中且在放置区
			}else if((workFlag!=0) && (i%4==3)){
				if((timerTimeUp[1+redFlag]==1 && workFlag==1) ||
				(timerTimeUp[8+greenFlag]==1 && workFlag==2 && shortcutFlag==0) ||
				(timerTimeUp[1+greenFlag]==1 && workFlag==2 && shortcutFlag==2)){//放下

					walk(0,0);
					pick(2);
					delay_s(5);
					stopActionGroup();

					workFlag = 0;
					break;
				}else continue;
				
			//未工作但已驶出检测区
			}else if(workFlag==0 && (i%4==2)){
				i--;

			//工作中或工作完成且可抄近道
			}else if((workFlag==2 && (i%4==1) && shortcutTracker==0)
				 ||  (workFlag==0 && (i%4==3) && shortcutTracker==0 && i>29)){
				shortcutFlag=1;
					goto shortcut;
				}
			}

		}else if(leftTracker==0 && middleTracker==0 && rightTracker==1){//right-center
			walk(60,70);
			while(leftTracker==0 && middleTracker==0 && rightTracker==1){
				goto loop;
			}
			
		}else if(leftTracker==1 && middleTracker==0 && rightTracker==0){//left-center
			walk(70,60);
			while(leftTracker==1 && middleTracker==0 && rightTracker==0){
				goto loop;
			}

		}else if(leftTracker==0 && middleTracker==1 && rightTracker==1){//too right
			walk(30,70);
			while(leftTracker==0 && middleTracker==1 && rightTracker==1);
			
		}else if(leftTracker==1 && middleTracker==1 && rightTracker==0){//too left
			walk(70,30);
			while(leftTracker==1 && middleTracker==1 && rightTracker==0);
			
		}else if(leftTracker==0 && middleTracker==0 && rightTracker==0){//T crossing
			walk(70,70);
			if(shortcutFlag==1){
				shortcutFlag = 2;
			}
			while(leftTracker==0 && middleTracker==0 && rightTracker==0);
		}
	}
	walk(10, 70);
	delay_ms(1300);
	walk(70, 70);
	delay_ms(1300);
	walk(0, 0);
}


