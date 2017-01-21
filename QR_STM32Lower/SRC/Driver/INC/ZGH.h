
#ifndef __ZGH_H_
#define __ZGH_H_

#include "stm32f10x.h"
#include "stm32_eval.h"
#include "led.h"
#include "tim.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "spi.h"
#include "stdio.h"
#include "PC_Link.h"
#include "math.h"
#include "string.h"

//变量宏定义
#define MANIPULATOR_DELAY_TIME  5
#define TURN_DELAY_TIME  2

//初始化状态
#define INIT_Waist   1500
#define INIT_Big_Arm  1540
#define INIT_Little_Arm   1600
#define INIT_Wrist   2280
#define INIT_Gripper   1250

//举高状态
#define HIGHT_Waist   1500
#define HIGHT_Big_Arm  1850
#define HIGHT_Little_Arm   1370
#define HIGHT_Wrist   2280
#define HIGHT_Gripper   1250

//位置1
#define Location_One_Waist   1100
#define Location_One_Big_Arm  1520
#define Location_One_Little_Arm   1620
#define Location_One_Wrist   2280
#define Location_One_Gripper   1250

//位置2
#define Location_Two_Waist   1260
#define Location_Two_Big_Arm  1520
#define Location_Two_Little_Arm   1620
#define Location_Two_Wrist   2280
#define Location_Two_Gripper   1250

//位置3
#define Location_Thr_Waist   1710
#define Location_Thr_Big_Arm  1520
#define Location_Thr_Little_Arm   1620
#define Location_Thr_Wrist   2280
#define Location_Thr_Gripper   1250

//位置4
#define Location_Fho_Waist   1960
#define Location_Fho_Big_Arm  1520
#define Location_Fho_Little_Arm   1620
#define Location_Fho_Wrist   2280
#define Location_Fho_Gripper   1250


extern struct MANIPULATOR_VALUE{
	uint16_t Waist;
	uint16_t Big_Arm;
	uint16_t Little_Arm;
	uint16_t Wrist;
	uint16_t Gripper;
}Manipulator_Value,Action_table;

//动作控制
void Test_Manipulator_Upper_Monitor(void);
void Manipulator_Init(void);
void Manipulator_ALL_Positive(struct MANIPULATOR_VALUE *manipulator);
void Manipulator_ALL_Reverse(struct MANIPULATOR_VALUE *manipulator);

//运动位置
void Manipulator_HIGHT_Start(char a[]);
void Manipulator_Init_Start(char a[]);
void Manipulator_Location_One_Start(void);
void Manipulator_Location_Two_Start(void);
void Manipulator_Location_Thr_Start(void);
void Manipulator_Location_Fho_Start(void);

//整套动作
void Hight_To_Location_To_Init(uint8_t num);
void QR_Control(void);

#endif
