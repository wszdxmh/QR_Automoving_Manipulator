/**
  ************************************
  * @file    manipulator.h
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.22
  * @brief   机械手控制函数
	************************************
*/

#ifndef __MANIPULATOR_H
#define __MANIPULATOR_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "debug.h"
#include "tim.h"
#include "sys.h"
#include "run.h"
#include "PC_Link.h"

////变量宏定义
//#define MANIPULATOR_DELAY_TIME  5
//#define TURN_DELAY_TIME  5

//引脚宏定义
#define Put_Left_Out  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)
#define Put_Left_Mid  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)
#define Put_Right_Mid  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)
#define Put_Right_Out  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)

//
//变量宏定义
//
//循迹姿态    9.28调试完成
#define Tracking_Positioning_Left   1858
#define Tracking_Positioning_Right  1493
#define Tracking_Lift   1040
#define Tracking_Flat   640
#define Tracking_Clip   1650
//举高   9.28调试完成
#define Highest_Positioning_Left   2440
#define Highest_Positioning_Right  894
#define Highest_Lift   2170
#define Highest_Flat   1120
//抓最上面的物块    9.28调试完成
#define Catch_On_Positioning_Left   2174
#define Catch_On_Positioning_Right  1167
#define Catch_On_Lift   1290
#define Catch_On_Flat   1240
//抓中间的物块    9.28调试完成
#define Catch_In_Positioning_Left   2024
#define Catch_In_Positioning_Right  1322
#define Catch_In_Lift   1220
#define Catch_In_Flat   1000
//抓底下的物块    9.28调试完成
#define Catch_Under_Positioning_Left   1500
#define Catch_Under_Positioning_Right  1540
#define Catch_Under_Lift   1600
#define Catch_Under_Flat   2280
#define Catch_Under_Clip   1250
//放底下特殊姿态
#define Put_Special_Positioning_Left  1764
#define Put_Special_Positioning_Right 1589
#define Put_Special_Lift  1300
#define Put_Special_Flat  730

//过渡姿态   9.28调试完成
//抓上面过渡姿态
#define Transition_On_Positioning_Left   2455
#define Transition_On_Positioning_Right  878
#define Transition_On_Lift   1050
#define Transition_On_Flat   1250
//抓中间过渡姿态
#define Transition_In_Positioning_Left   2316
#define Transition_In_Positioning_Right  1021
#define Transition_In_Lift   960
#define Transition_In_Flat   960
//抓下面过渡姿态
#define Transition_Under_Positioning_Left   1959
#define Transition_Under_Positioning_Right  1389
#define Transition_Under_Lift   1000
#define Transition_Under_Flat   580

//抓放物块
#define Put  1480
#define Catch  1820

//仰角用于Run_Manipulator()函数
//上仰角
#define Put_On_Positioning_Left 2363
#define Put_On_Positioning_Right 973
//中仰角
#define Put_In_Positioning_Left 2187
#define Put_In_Positioning_Right 1154
//下仰角
#define Put_Under_Positioning_Left 1968
#define Put_Under_Positioning_Right 1379
//循迹仰角
#define Put_Tracking_Positioning_Left 2038
#define Put_Tracking_Positioning_Right 1307

uint16_t Abs_16(uint16_t a, uint16_t b);
uint16_t Cmp_Fh_16(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
uint16_t Cmp_Th_16(uint16_t a, uint16_t b, uint16_t c);
uint16_t Cmp_Tw_16(uint16_t a, uint16_t b);
uint16_t Return_All(char a[]);
void Lift_Flat(uint16_t lift, uint16_t flat);
void Positioning_Lift(uint16_t left, uint16_t right, uint16_t lift, uint16_t delay_time);
void Flat_Move(uint16_t flat);
void Positioning(uint16_t left, uint16_t right, uint16_t delay_time);
void Catch_Put(uint16_t clip);
void Attitude_Tracking(void);
void Attitude_Highest(void);
void Attitude_Catch_On(void);
void Attitude_Catch_In(void);
void Attitude_Catch_Under(void);
void Transition(void);
void Put_BCD(uint16_t a);
void Put_A(uint16_t a);
void Put_E(uint16_t a);
void Put_Catch(char a[], char b[]);
void All_Move(char a[], uint16_t b);
void Run_Manipulator(uint8_t num, char c[], char a[], char b[]);

#endif
