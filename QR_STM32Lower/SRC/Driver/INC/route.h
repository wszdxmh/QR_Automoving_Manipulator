/**
  ************************************
  * @file    route.h
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.20
  * @brief   路线规划
	************************************
*/

#ifndef __ROUTE_H
#define __ROUTE_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "manipulator.h"
#include "ultrasonic.h"
#include "delay.h"
#include "debug.h"
#include "run.h"
#include "sys.h"

//变量宏定义
#define ULTRASONIC_THRESHOLD  130

void R_1(void);
void R_2(void);
void R_3(void);
void R_4(void);
void R_5(void);
void R_6(void);

#endif
