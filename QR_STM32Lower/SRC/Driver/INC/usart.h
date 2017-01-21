/**
  ************************************
  * @file    usart.h
  * @author  çÑ»Ô
  * @version V3.5.0
  * @date    2015.08.02
  * @brief   ´®¿ÚÇý¶¯
	************************************
*/

#ifndef __USART_H
#define __USART_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"

void Usart_Init(uint32_t baudrate);

#endif
