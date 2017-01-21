/**
  ************************************
  * @file    oled.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.03
	************************************
  * @brief   OLED驱动
	*
	************************************
*/

#include "oled.h"
#include "oled_library.h"

/**
  **********************************
  * @brief  SPI写数据
  * @param  data
  * @retval None
  **********************************
*/
void LCD_WriteByte(uint8_t data)
{
	for(uint8_t i=8; i>0; i--)
	{
		if(data&0x80)
			SDA = 1;//SDA=1
		else
			SDA = 0;//SDA=0
		SCL = 1;//SCL=1
		SCL = 0;//SCL=0
		data<<=1;
	}
}

/**
  **********************************
  * @brief  OLED写命令
  * @param  cmd
  * @retval None
  **********************************
*/
void LCD_WrCmd(uint8_t cmd)
{
	//SCL = 0;//SCL=0
	//DC = 0;//写命令,DC=0
	//LCD_WriteByte(cmd);
	GPIO_ResetBits(GPIOD, GPIO_Pin_8);
	SPI2_ReadWriteByte(cmd);
}

/**
  **********************************
  * @brief  OLED写数据
  * @param  data
  * @retval None
  **********************************
*/
void LCD_WrData(uint8_t data)
{
	//SCL = 0;//SCL=0
	//DC = 1;//写命令,DC=1
	//LCD_WriteByte(data);
	GPIO_SetBits(GPIOD, GPIO_Pin_8);
	SPI2_ReadWriteByte(data);
}

/**
  **********************************
  * @brief  OLED设置坐标
  * @param  x：0~128  y:0~7
  * @retval None
  **********************************
*/
void LCD_Set_Pos(uint8_t x, uint8_t y)
{
	LCD_WrCmd(0xb0+y);
	LCD_WrCmd(((x&0xf0)>>4)|0x10);
	LCD_WrCmd((x&0x0f)|0x01); 	
}

/**
  **********************************
  * @brief  OLED清屏
  * @param  bmp_dat: 写0x00达到清屏
  * @retval None
  **********************************
*/
void LCD_Fill(uint8_t bmp_dat)
{
	uint8_t x,y;
	LCD_Set_Pos(0,0);
	for(y=0; y<8; y++)
	{
		LCD_Set_Pos(0,y);
		for(x=0; x<128;x++)
			LCD_WrData(0x00);
	}
}

/**
  **********************************
  * @brief  初始化OLED引脚
  * @param  None
  * @retval 
  **********************************
*/
void LCD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure1;//定义结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOD外部时钟使能，特别重要！！！

	//初始化
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;//设置IO口
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;//设置为普通推挽输出
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;//频率50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure1);//初始化


	//初始化OLED
	RST = 0;//RST拉低
	delay_ms(1);
	RST = 1;//RST拉高
	delay_ms(1);
	
	//写入初始化命令
	LCD_WrCmd(0xae);//--turn off oled panel
	LCD_WrCmd(0x00);//---set low column address
	LCD_WrCmd(0x10);//---set high column address
	LCD_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	LCD_WrCmd(0x81);//--set contrast control register
	LCD_WrCmd(0xcf); // Set SEG Output Current Brightness
	LCD_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0???? 0xa1??
	LCD_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	LCD_WrCmd(0xa6);//--set normal display
	LCD_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	LCD_WrCmd(0x3f);//--1/64 duty
	LCD_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	LCD_WrCmd(0x00);//-not offset
	LCD_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	LCD_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	LCD_WrCmd(0xd9);//--set pre-charge period
	LCD_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	LCD_WrCmd(0xda);//--set com pins hardware configuration
	LCD_WrCmd(0x12);
	LCD_WrCmd(0xdb);//--set vcomh
	LCD_WrCmd(0x40);//Set VCOM Deselect Level
	LCD_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	LCD_WrCmd(0x02);//
	LCD_WrCmd(0x8d);//--set Charge Pump enable/disable
	LCD_WrCmd(0x14);//--set(0x10) disable
	LCD_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	LCD_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	LCD_WrCmd(0xaf);//--turn on oled panel
	LCD_Fill(0x00);  //--clear
	LCD_Set_Pos(0,0);  	
}

/**
  **********************************
  * @brief  显示6x8数字
  * @param  x：0~128  y:0~7  data:0~9999
  * @retval LCD_P6x8Num(32, 2, 1234)
  **********************************
*/
void LCD_P6x8Num(uint8_t x, uint8_t y, uint16_t data)
{
	uint8_t k=0;
  for(uint8_t j=0; j<4; j++)
  {
  	switch (j)
		{
		 	case 0:{k = data/1000;} break;
			case 1:{k = data%1000/100;} break;
			case 2:{k = data%100/10;} break;
			case 3:{k = data%10;} break;
		}
    LCD_Set_Pos(x,y);
  	for(uint8_t i=0; i<6; i++)
			LCD_WrData(F6x8_num[k][i]);
  	x += 6;
  }
}

/**
  **********************************
  * @brief  显示8x16的字符串
  * @param  x：0~128  y:0~7  
  * @retval LCD_P8x16Str(32, 2, "OLED")
  **********************************
*/
void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[])
{
  unsigned char c=0,i=0,j=0;
  while (ch[j]!='\0')
  {
    c =ch[j]-32;
    if(x>120){x=0;y++;}
    LCD_Set_Pos(x,y);
  	for(i=0;i<8;i++)
  	  LCD_WrData(F8X16[c*16+i]);
  	LCD_Set_Pos(x,y+1);
  	for(i=0;i<8;i++)
  	  LCD_WrData(F8X16[c*16+i+8]);
  	x += 8;
  	j++;
  }
}
