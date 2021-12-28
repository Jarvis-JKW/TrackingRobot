#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

void Motor_IO_Init(void);

/*DC motor
	3	1
	2	4*/
#define motorRightForward_IN1 PEout(0)
#define motorRightForward_IN2 PEout(1)
#define motorLeftRear_IN1 PEout(2)
#define motorLeftRear_IN2 PEout(3)
#define motorLeftForward_IN1 PEout(4)
#define motorLeftForward_IN2 PEout(8)
#define motorRightRear_IN1 PEout(6)
#define motorRightRear_IN2 PEout(7)


void walk(int speedL, int speedR);//必须为整型，否则会出错
void turn(unsigned char toRight);



#endif
