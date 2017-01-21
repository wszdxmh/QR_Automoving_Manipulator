/**
  ************************************
  * @file    key.h
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.02
  * @brief   按键驱动(PD0 PD1 PD2 PD3)
	************************************
*/

#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "tim.h"
#include "sys.h"

#define KEY_0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)//读取按键0
#define KEY_1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)//读取按键1
#define KEY_2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//读取按键2 
#define KEY_3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)//读取按键3

void Key_Init(void);
void EXTIX_Init(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);

#endif
