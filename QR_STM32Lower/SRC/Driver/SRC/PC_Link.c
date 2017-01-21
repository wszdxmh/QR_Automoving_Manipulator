/**
  ************************************
  * @file    PC_Link.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.09.27
  * @brief   机械手串口调试函数
	************************************
*/

#include "PC_Link.h"

extern struct MANIPULATOR_VALUE Action_table;

//定义全局变量
uint16_t Flag,Time;

/**
  ************************************
  * @brief  发送int型给PC
  * @param  header:头码   date:要发送的数据
  * @retval None
	************************************
*/
void Send_PC(uint8_t header, uint16_t date)
{
  uint8_t buf[4];
  buf[0] = header;
  buf[1] = date >> 8;
  buf[2] = date & 0xff;
  buf[3] = ~header;
  for(uint8_t i=0; i<4; i++)
  {
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
    USART_SendData(USART1, buf[i]);
  }
}

/**
  ************************************
  * @brief  串口1中断函数
  * @param  buf[0]为头码  buf[2]为尾码,即头码取反  buf[1]指令位
  * @retval None
	************************************
*/
void USART1_IRQHandler(void)
{
	static uint8_t i = 0;
  static uint8_t buf[3] = {0xff, 0xff, 0xff};
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		buf[i] = USART_ReceiveData(USART1);
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		i++;
	}
  if(i == 3)
  {
    i = 0;
    if(buf[0] == 0x00 && buf[1] == 0x01 && buf[2] == 0xff)
    {
      Action_table.Waist += 10;
      Send_PC(0x00, Action_table.Waist);
    }
    else if(buf[0] == 0x00 && buf[1] == 0x02 && buf[2] == 0xff)
    {
      Action_table.Waist -= 10;
      Send_PC(0x00, Action_table.Waist);
    }
    else if(buf[0] == 0x01 && buf[1] == 0x03 && buf[2] == 0xfe)
    {
      Action_table.Big_Arm += 10;
      Send_PC(0x01, Action_table.Big_Arm);
    }
    else if(buf[0] == 0x01 && buf[1] == 0x04 && buf[2] == 0xfe)
    {
      Action_table.Big_Arm -= 10;
      Send_PC(0x01, Action_table.Big_Arm);
    }
    else if(buf[0] == 0x02 && buf[1] == 0x05 && buf[2] == 0xfd)
    {
      Action_table.Little_Arm += 10;
      Send_PC(0x02, Action_table.Little_Arm);
    }
    else if(buf[0] == 0x02 && buf[1] == 0x06 && buf[2] == 0xfd)
    {
      Action_table.Little_Arm -= 10;
      Send_PC(0x02, Action_table.Little_Arm);
    }
    else if(buf[0] == 0x03 && buf[1] == 0x07 && buf[2] == 0xfc)
    {
      Action_table.Wrist += 10;
      Send_PC(0x03, Action_table.Wrist);
    }
    else if(buf[0] == 0x03 && buf[1] == 0x08 && buf[2] == 0xfc)
    {
      Action_table.Wrist -= 10;
      Send_PC(0x03, Action_table.Wrist);
    }
    else if(buf[0] == 0x04 && buf[1] == 0x09 && buf[2] == 0xfb)
    {
      Action_table.Gripper += 10;
      Send_PC(0x04, Action_table.Gripper);
    }
    else if(buf[0] == 0x04 && buf[1] == 0x0a && buf[2] == 0xfb)
    {
      Action_table.Gripper -= 10;
      Send_PC(0x04, Action_table.Gripper);
    }
		else if(buf[0] == 0x05 && buf[1] == 0x0b && buf[2] == 0xfa)
			Flag = 1;
		else if(buf[0] == 0x05 && buf[1] == 0x0c && buf[2] == 0xfa)
			Flag = 2;
		else if(buf[0] == 0x05 && buf[1] == 0x0d && buf[2] == 0xfa)
			Flag = 3;
		else if(buf[0] == 0x05 && buf[1] == 0x0e && buf[2] == 0xfa)
			Flag = 4;
		else if(buf[0] == 0x06 && buf[1] == 0x10 && buf[2] == 0xfa)
			Flag = 5;
  }
}
