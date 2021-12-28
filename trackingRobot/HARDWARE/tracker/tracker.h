#ifndef __TRACKER_H
#define __TRACKER_H

#include "sys.h"

void Track_Sensor_Init(void);

/*传感器被遮挡为1，同时对应侧LED熄灭*/
#define shortcutTracker GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5)	//PG5
#define middleTracker 	GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_9)	//PG9
#define leftTracker			GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10)//PG10
#define rightTracker 		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11)//PG11

#endif

