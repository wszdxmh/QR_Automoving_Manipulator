/**
  ************************************
  * @file    test.h
  * @author  Á—ª‘
  * @version V3.5.0
  * @date    2015.08.11
  * @brief   ≤‚ ‘∫Ø ˝
	************************************
*/

#ifndef __TEST_H
#define __TEST_H

#include "stm32f10x.h"
#include "stm32_eval.h"
#include "led.h"
#include "tim.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "spi.h"
#include "ultrasonic.h"
#include "run.h"
#include "debug.h"
#include "route.h"
#include "manipulator.h"
#include "stdio.h"
#include "PC_Link.h"
#include "math.h"
#include "ZGH.h"

void Test_Start_Cross(void);
void Test_Ultrasonic(void);
void Test_Manipulator_Upper_Monitor(void);
void Test_Manipulator(void);
void Test_Manipulator_Go_Cross(void);
void Test_Run_Turn(void);
void Rising_Filling(void);
void Test_R5_2(void);
void Run_BD(void);
void Text_R5_1(void);
void R2_3_test(void);
void R2_2_test(void);
void Test_Under(void);
void R2_1_Test(void);
void Test_Turn_Delay(void);
void Test_Run_1(void);
void Test_Run_C_B_C(void);

#endif
