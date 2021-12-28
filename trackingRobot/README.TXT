├─CORE
│  ├─core_cm3.c
│  ├─core_cm3.h
│  └─startup_stm32f10x_hd.s	//定义中断服务函数名等
├─HARDWARE
│  ├─init			//初始化函数调用
│  │  ├─init.h
│  │  └─init.c
│  ├─motor			//电机驱动函数
│  │  ├─motor.c
│  │  └─motor.h
│  ├─servo			//舵机控制板驱动函数
│  │  ├─servo.c
│  │  └─servo.h
│  ├─timer			//定时器初始化
│  │  ├─timer.c
│  │  └─timer.h
│  └─tracker			//寻迹传感器初始化
│  │  ├─tracker.c
│  │  └─tracker.h
├─OBJECTS
│  ├─output.axf
│  ├─output.build_log.htm
│  ├─output.hex			//编译器链接成的可烧录的可执行十六进制文件
│  ├─output.htm
│  ├─output.lnp
│  ├─output.sct
│  ├─*.crf
│  ├─*.d			//编译器产生的依赖文件
│  └─*.o			//编译器产生的可执行对象文件
├─STM32F10x_FWLib
│  ├─inc
│  │  ├─misc.h
│  │  ...
│  └─src
│  │  ├─misc.c
│  │  ...
├─SYSTEM
│  ├─delay
│  │  ├─delay.c			//延时函数
│  │  └─delay.h
│  ├─sys
│  │  ├─stm32f10x_it.c		//串口、定时器中断服务函数
│  │  ├─stm32f10x_it.h
│  │  ...
│  └─usart
│      ├─usart.c		//串口初始化
│      └─usart.h
└─USER
    ├─main.c			//主程序
	...

比赛场地模拟一个植物苗圃，每支参赛队伍的起始区域摆放有10个模拟盆栽植物，盆栽分为绿色和红色两种。
如图所示，颜色随机摆放。机器人须从规定的起点区出发，达到盆栽区域后识别它们，再将其根据颜色分类，正确地移动到存储区域。
注意：要保证盆栽的直立状态，结束后需要回到起始区域。
      Green      Red
   ┌───────────────────┐
   └───────────────────┘
   ┌─────────┬─────────┐
   │         │         │
   │         │         │
   │         │         │
 ┌─┴─────────┴─────────┘
┌┴┐ ┴─┴─┴─┴─┴─┴─┴─┴─┴─┴
└─┘
使用设备：STM32F103ZET6开发板、可编程机械臂（PWM舵机驱动，带STM32舵机控制板）、直流电机（带驱动板）×4、灰度寻迹传感器×4（三个车头寻迹，一个用以近道识别）、OpenMV摄像头模块、锂电池、DC-DC稳压模块等。
