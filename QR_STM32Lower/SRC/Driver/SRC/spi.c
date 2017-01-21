/**
  ************************************
  * @file    spi.c
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.09
  * @brief   spi��������
	* SPI2:  SCK(PB13) SDA|MOSI(PB15) MISO(PB14) RST(PD9) DC(PD8)
	************************************
*/

#include "spi.h"
#include "oled_library.h"

/**
  **********************************
  * @brief  SPI2��д����
  * @param  TxData
  * @retval None
  **********************************
*/
uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{		
	uint8_t retry = 0;
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200) return 0;
	}			  
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	retry = 0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200) return 0;
	}
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����
}

/**
  **********************************
  * @brief  OLEDд����
  * @param  cmd
  * @retval None
  **********************************
*/
uint8_t LCD_SPI2_WrCmd(uint8_t cmd)
{
	uint8_t read = 0;
	GPIO_ResetBits(GPIOD, GPIO_Pin_8);
	read = SPI2_ReadWriteByte(cmd);
	return read;
}

/**
  **********************************
  * @brief  OLEDд����
  * @param  data
  * @retval None
  **********************************
*/
uint8_t LCD_SPI2_WrData(uint8_t data)
{
	uint8_t read = 0;
	GPIO_SetBits(GPIOD, GPIO_Pin_8);
	read = SPI2_ReadWriteByte(data);
	return read;
}

/**
  **********************************
  * @brief  OLED��������
  * @param  x��0~127  y:0~7
  * @retval None
  **********************************
*/
void LCD_SPI2_Set_Pos(uint8_t x, uint8_t y)
{
	LCD_SPI2_WrCmd(0xb0+y);
	LCD_SPI2_WrCmd(((x&0xf0)>>4)|0x10);
	LCD_SPI2_WrCmd((x&0x0f)|0x01);
}

/**
  **********************************
  * @brief  OLED����
  * @param  bmp_dat: д0x00�ﵽ����
  * @retval None
  **********************************
*/
void LCD_SPI2_Fill(uint8_t bmp_dat)
{
	uint8_t x,y;
	LCD_SPI2_Set_Pos(0,0);
	for(y=0; y<8; y++)
	{
		LCD_SPI2_Set_Pos(0,y);
		for(x=0; x<128;x++)
			LCD_SPI2_WrData(0x00);
	}
}

/**
  **********************************
  * @brief  SPI2��ʼ��
  * @param  None
  * @retval None
  **********************************
*/
void SPI2_Init(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	//ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);//����SPI2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//����GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//����GPIODʱ��
	//��ʼ��GPIO��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);//���ߵ�ƽ
	//��ʼ��RST DC
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	GPIO_SetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_9);//���ߵ�ƽ
	//��ʼ��SPI2
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//ʹ��2��Ƶ
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;//�ڵ�һ�������ر��ɼ�
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;//���м���Ϊ�͵�ƽ
	SPI_InitStruct.SPI_CRCPolynomial = 7;//CRCУ��
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;//�������ݳ���
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//˫��ȫ˫��
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;//�ȴ����ֽ�
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;//����ģʽ
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//Ƭѡ��ʽΪ���
	SPI_Init(SPI2, &SPI_InitStruct);
	SPI_Cmd(SPI2, ENABLE);//ʹ��SPI2
}

void LCD_SPI2_Init(void)
{
	SPI2_Init();
	//��ʼ��OLED
	RST_SPI2 = 0;//RST����
	delay_ms(1);
	RST_SPI2 = 1;//RST����
	delay_ms(1);
	//д���ʼ������
	LCD_SPI2_WrCmd(0xae);//--turn off oled panel
	LCD_SPI2_WrCmd(0x00);//---set low column address
	LCD_SPI2_WrCmd(0x10);//---set high column address
	LCD_SPI2_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	LCD_SPI2_WrCmd(0x81);//--set contrast control register
	LCD_SPI2_WrCmd(0xcf); // Set SEG Output Current Brightness
	LCD_SPI2_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0???? 0xa1??
	LCD_SPI2_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	LCD_SPI2_WrCmd(0xa6);//--set normal display
	LCD_SPI2_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	LCD_SPI2_WrCmd(0x3f);//--1/64 duty
	LCD_SPI2_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	LCD_SPI2_WrCmd(0x00);//-not offset
	LCD_SPI2_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	LCD_SPI2_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	LCD_SPI2_WrCmd(0xd9);//--set pre-charge period
	LCD_SPI2_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	LCD_SPI2_WrCmd(0xda);//--set com pins hardware configuration
	LCD_SPI2_WrCmd(0x12);
	LCD_SPI2_WrCmd(0xdb);//--set vcomh
	LCD_SPI2_WrCmd(0x40);//Set VCOM Deselect Level
	LCD_SPI2_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	LCD_SPI2_WrCmd(0x02);//
	LCD_SPI2_WrCmd(0x8d);//--set Charge Pump enable/disable
	LCD_SPI2_WrCmd(0x14);//--set(0x10) disable
	LCD_SPI2_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	LCD_SPI2_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	LCD_SPI2_WrCmd(0xaf);//--turn on oled panel
	LCD_SPI2_Fill(0x00);  //--clear
	LCD_SPI2_Set_Pos(0,0);  
}

/**
  **********************************
  * @brief  ��ʾ6x8����
  * @param  x��0~128  y:0~7  data:0~9999
  * @retval LCD_SPI2_P6x8Num(32, 2, 1234)
  **********************************
*/
void LCD_SPI2_P6x8Num(uint8_t x, uint8_t y, uint16_t data)
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
    LCD_SPI2_Set_Pos(x,y);
  	for(uint8_t i=0; i<6; i++)
			LCD_SPI2_WrData(F6x8_num[k][i]);
  	x += 6;
  }
}

/**
  **********************************
  * @brief  ��ʾ8x16���ַ���
  * @param  x��0~128  y:0~7  
  * @retval LCD_SPI2_P8x16Str(32, 2, "OLED")
  **********************************
*/
void LCD_SPI2_P8x16Str(uint8_t x,uint8_t y,char ch[])
{
  uint8_t c=0,i=0,j=0;
  while (ch[j]!='\0')
  {
    c =ch[j]-32;
    if(x>120){x=0;y++;}
    LCD_SPI2_Set_Pos(x,y);    
  	for(i=0;i<8;i++)
  	  LCD_SPI2_WrData(F8X16[c*16+i]);
  	LCD_SPI2_Set_Pos(x,y+1);
  	for(i=0;i<8;i++)     
  	  LCD_SPI2_WrData(F8X16[c*16+i+8]);  
  	x += 8;
  	j++;
  }
}
