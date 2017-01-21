/**
  ************************************
  * @file    run.h
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.11
  * @brief   舵机控制函数
	************************************
*/

#ifndef __RUN_H
#define __RUN_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "debug.h"
#include "tim.h"
#include "sys.h"

//引脚定义
#define Run_L  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)
#define Run_Z  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define Run_R  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)
#define Run_Behind_L  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8)
#define Run_Behind_R  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)
#define Run_Front_L  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)
#define Run_Front_R  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)
#define Run_Under_L  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_10)
#define Run_Under_R  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11)

void ST188_Init(void);
void Run(uint16_t Left, uint16_t Right);
void Run_Stop(void);
void Run_Line_Slow(uint16_t count);
void Run_Line_Fast(uint16_t count);
void Back_Slow(uint16_t count);
void Turn_Right_180(void);
void Turn_Left_180(void);
void Tracking_Slow(void);
void Tracking_Slow_Distance(uint16_t a);
void Tracking_Slow_Double(void);
void Tracking_Slow_Double_Distance(uint16_t a);
void Tracking_Fast(void);
void Tracking_Fast_Distance(uint16_t a);
void Fast_To_Slow(void);
void Turn_Left_ACE(uint8_t num, char c[], uint16_t a, char b[], uint16_t d);
void Turn_Right_ACE(uint8_t num, char c[], uint16_t a, char b[], uint16_t d);
void Turn_Left_ACE_Angle(uint8_t num, char c[]);
void Turn_Left_ACE_Angle_Front(uint8_t num, char c[]);
void Turn_Left_ACE_Angle_Front_Delay(uint8_t num, char c[], uint16_t a, uint16_t b);
void Turn_Right_ACE_Angle(uint8_t num, char c[]);
void Turn_Right_ACE_Angle_Front(uint8_t num, char c[]);
void Turn_Right_ACE_Angle_Front_Delay(uint8_t num, char c[], uint16_t a, uint16_t b);
void Turn_Left_BD(uint8_t num, uint16_t count);
void Turn_Left_Delay(uint16_t a);
void Turn_Right_Delay(uint16_t a);
void Turn_Right_BD(uint8_t num, uint16_t count);
void Go_Cross(void);
void Go_Cross_Double(void);
void Go_Cross_Front(void);
void Start_Cross(void);
void Go_Start(void);

#endif
