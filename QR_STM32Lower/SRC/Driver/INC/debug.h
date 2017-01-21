/**
  ************************************
  * @file    debug.h
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.11
  * @brief   调试参数函数
	************************************
*/

#ifndef __DEBUG_H
#define __DEBUG_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "tim.h"
#include "sys.h"
#include "run.h"

void Run_Slow(void);
void Run_Fast(void);
void Run_Back(void);
void Clockwise(void);
void AntiClockwise(void);

#endif
