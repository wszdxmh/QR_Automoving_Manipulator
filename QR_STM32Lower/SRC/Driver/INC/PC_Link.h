/**
  ************************************
  * @file    PC_Link.h
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.09.27
  * @brief   机械手串口调试函数
	************************************
*/
#ifndef __PC_LINK_H
#define __PC_LINK_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "manipulator.h"
#include "delay.h"
#include "debug.h"
#include "usart.h"
#include "tim.h"
#include "sys.h"
#include "ZGH.h"

void Send_PC(uint8_t header, uint16_t date);
void USART1_IRQHandler(void);

#endif
