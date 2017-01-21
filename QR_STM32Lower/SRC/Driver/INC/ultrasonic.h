/**
  ************************************
  * @file    ultrasonic.h
  * @author  çÑ»Ô
  * @version V3.5.0
  * @date    2015.08.10
  * @brief   ³¬Éù²¨Çý¶¯º¯Êý
	************************************
*/
#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "delay.h"

void Ultrasonic_TIM5_Init(uint16_t arr, uint16_t psc);
uint16_t Ultrasonic_Value(uint16_t arr, uint16_t psc);
uint16_t Ultrasonic_Mean_Value(uint16_t arr, uint16_t psc);

#endif
