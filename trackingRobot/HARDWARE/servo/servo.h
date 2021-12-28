#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"
/*
void StepperInit(void);
void MoveStepper(u8 stepper, u8 dir, u16 pulse);
void MoveStepperST(u8 dir0, u16 pulse0,u8 dir1, u16 pulse1);
*/
//void set_uart(void);

void pick(u8 option);//0-11
void stopActionGroup(void);

#endif
