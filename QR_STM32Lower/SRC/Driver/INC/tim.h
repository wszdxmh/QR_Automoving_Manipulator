/**
  ************************************
  * @file    tim.h
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.05
  * @brief   ��ʱ������
	************************************
*/

#ifndef __TIM_H
#define __TIM_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "misc.h"
#include "led.h"

void TIM1_Init(uint16_t period, uint16_t prescaler);
void TIM_PWM_Init(uint16_t arr, uint16_t psc);

#endif
