/**
  ************************************
  * @file    0led.h
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.03
  * @brief   PB8
	************************************
*/

#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"

//OLED显示范围定义
#define X_WIDTH 128
#define Y_WIDTH 64

//OLED引脚定义
#define SCL  PBout(10)
#define SDA  PBout(11)
#define RST  PDout(9)
#define DC   PDout(8)

void LCD_Init(void);
void LCD_WriteByte(uint8_t data);
void LCD_WrCmd(uint8_t cmd);
void LCD_WrData(uint8_t data);
void LCD_Fill(uint8_t bmp_dat);
void LCD_Set_Pos(uint8_t x, uint8_t y);
void LCD_P6x8Num(uint8_t x, uint8_t y, uint16_t data);
void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
void SPI2_Init(void);
uint8_t SPI2_ReadWriteByte(uint8_t TxData);

#endif
