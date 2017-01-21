/**
  ************************************
  * @file    key.h
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.02
  * @brief   ��������(PD0 PD1 PD2 PD3)
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

#define KEY_0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)//��ȡ����0
#define KEY_1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)//��ȡ����1
#define KEY_2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//��ȡ����2 
#define KEY_3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)//��ȡ����3

void Key_Init(void);
void EXTIX_Init(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);

#endif
