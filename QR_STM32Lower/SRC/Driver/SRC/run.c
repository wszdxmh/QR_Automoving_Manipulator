/**
  ************************************
  * @file    run.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.11
  * @brief   舵机控制函数
	************************************
*/

#include "run.h"
#include "string.h"

/**
  ************************************
  * @brief  GPIO口初始化
  * @param  None
  * @retval None
	************************************
*/
void ST188_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);//开启GPIOC时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
  
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/**
  ************************************
  * @brief  左右行走函数
  * @param  Left:左轮速度   Right:右轮速度
  * @retval 停止：1500
	************************************
*/
void Run(uint16_t Left, uint16_t Right)
{
  TIM_SetCompare2(TIM4,Left);//PB7
  TIM_SetCompare3(TIM4,Right);//PB8
}

/**
  ************************************
  * @brief  停止函数
  * @param  None
  * @retval 停止：1500
	************************************
*/
void Run_Stop(void)
{
  TIM_SetCompare2(TIM4,1500);//PB7
  TIM_SetCompare3(TIM4,1500);//PB8
}

/**
  ************************************
  * @brief  慢速直走一段路程
  * @param  count
  * @retval None
	************************************
*/
void Run_Line_Slow(uint16_t count)
{
	Run_Slow();
	delay_ms(count);
}

/**
  ************************************
  * @brief  快速直走一段路程
  * @param  count
  * @retval None
	************************************
*/
void Run_Line_Fast(uint16_t count)
{
	Run_Fast();
  delay_ms(count);
}

/**
  ************************************
  * @brief  慢速后退一段路程
  * @param  None
  * @retval None
	************************************
*/
void Back_Slow(uint16_t count)
{
	for(uint16_t i=count; i>0; i--)
		Run_Back();
}

/**
  ************************************
  * @brief  顺时针180
  * @param  None
  * @retval None
	************************************
*/
void Turn_Right_180(void)
{
//	Clockwise();
//	delay_ms(1000);
//	while(!Run_Z);
//	delay_ms(90);
//	Run_Stop();
  Clockwise();
  delay_ms(300);
  while(!Run_Behind_L)
    Clockwise();
  delay_ms(10);
  while(Run_Behind_L)
    Clockwise();
  Run_Stop();
}

/**
  ************************************
  * @brief  逆时针180
  * @param  None
  * @retval None
	************************************
*/
void Turn_Left_180(void)
{
//	AntiClockwise();
//	delay_ms(1000);
//	while(!Run_Z);
//	delay_ms(130);
//	Run_Stop();
  AntiClockwise();
  delay_ms(350);
  while(!Run_Behind_R) //进黑线
    AntiClockwise();
  delay_ms(10);
  while(Run_Behind_R) //出黑线
    AntiClockwise();
  Run_Stop();//停车
}

/**
  ************************************
  * @brief  慢速循迹
  * @param  None
  * @retval None
	************************************
*/
void Tracking_Slow(void)
{
  if(!Run_Z && Run_R) //左偏
    Run(1519,1495);
  else if(!Run_Z && Run_L) //右偏
    Run(1505,1478);
	else if(Run_Z && Run_R)//微左偏
		Run(1519,1490);
	else if(Run_Z && Run_L)//微右偏
		Run(1510,1478);
	else
		Run_Slow();//直走
}

/**
  ************************************
  * @brief  慢速循迹一段距离
  * @param  None
  * @retval None
	************************************
*/
void Tracking_Slow_Distance(uint16_t a)
{
  uint16_t b = 1000;
  while(a--)
  {
    b=1000;
    while(b--)
      Tracking_Slow();//慢速循迹
  }
}

/**
  ************************************
  * @brief  双头慢速循迹
  * @param  None
  * @retval None
	************************************
*/
void Tracking_Slow_Double(void)
{
  if(Run_L)
    Run(1510,1485);
  else if(Run_R)
    Run(1515,1490);
  else if(Run_Behind_L)
    Run(1515,1490);
  else if(Run_Behind_R)
    Run(1510,1485);
  else
    Run_Slow();
}

/**
  ************************************
  * @brief  双头慢速循迹一段时间
  * @param  None
  * @retval None
	************************************
*/
void Tracking_Slow_Double_Distance(uint16_t a)
{
  uint16_t b = 1000;
  while(a--)
  {
    b = 1000;
    while(b--)
      Tracking_Slow_Double();
  }
}

/**
  ************************************
  * @brief  快速循迹
  * @param  None
  * @retval None
	************************************
*/
void Tracking_Fast(void)
{
	if(Run_L && !Run_Z)//右偏
		Run(1530,1425);
	else if(Run_R && !Run_Z)//左偏
		Run(1581,1470);
	else if(Run_Z && Run_R)//微左偏
		Run(1581,1465);
	else if(Run_Z && Run_L)//微右偏
		Run(1540,1425);
	else
		Run_Fast();//直走
}

/**
  ************************************
  * @brief  快速循迹一段距离
  * @param  
  * @retval None
	************************************
*/
void Tracking_Fast_Distance(uint16_t a)
{
  uint16_t b=100;
  while(a--)
  {
    b = 100;
    while(b--)
      Tracking_Fast();
  }
}

/**
  ************************************
  * @brief  快速过渡到慢速
  * @param  
  * @retval None
	************************************
*/
void Fast_To_Slow(void)
{
  uint8_t a=101;
  uint16_t left=1581, right=1425;
  while(a--)
  {
    if(left > 1519)
      TIM_SetCompare3(TIM3,left--);//PB0
    if(right < 1478)
      TIM_SetCompare4(TIM3,right++);//PB1
    delay_ms(2);
  }
}

/**
  ************************************
  * @brief  逆时针45_ACE
  * @param  num:数线的条数  count:直走延时(1900)
  * @retval None
	************************************
*/
void Turn_Left_ACE(uint8_t num, char c[], uint16_t a, char b[], uint16_t d)
{
  if(!strcmp(c, "On"))
  {
    while(!Run_Under_L || !Run_Under_R) 
      Run_Slow();
    Run_Stop();
  }
  Run_Stop();
	//出线，入线
	while(num--)
	{
//		while(Run_L)//出黑线
		AntiClockwise();
		delay_ms(300);//延时去抖
		while(!Run_L)//进黑线
			AntiClockwise();
		delay_ms(130);
		while(Run_L)//出黑线
			AntiClockwise();
	}
  AntiClockwise();
  delay_ms(a);
  Run_Stop();
  if(!strcmp(b, "On"))
  {
    Clockwise();
    delay_ms(d);
    Run_Stop();
  }
  Run_Stop();
}

/**
  ************************************
  * @brief  顺时针45_ACE
  * @param  num:数线的条数  count:直走延时(1500)
  * @retval None
	************************************
*/
void Turn_Right_ACE(uint8_t num, char c[], uint16_t a, char b[], uint16_t d)
{
  if(!strcmp(c, "On"))
  {
    while(!Run_Under_L || !Run_Under_R) 
      Run_Slow();
    Run_Stop();
  }
  Run_Stop();
	//出线，入线
	while(num--)
	{
//		while(Run_R)//出黑线
		Clockwise();
		delay_ms(250);//延时去抖
		while(!Run_R)//进黑线
			Clockwise();
		delay_ms(130);
		while(Run_R)//出黑线
			Clockwise();
	}
  delay_ms(a); //延时归位
  Run_Stop();
  if(!strcmp(b, "On"))
  {
    AntiClockwise();
    delay_ms(d);
  }
  Run_Stop();
}

/**
  ************************************
  * @brief  逆时针90_ACE
  * @param  num:数线的条数  count:直走延时(1900)
  * @retval None
	************************************
*/
void Turn_Left_ACE_Angle(uint8_t num, char c[])
{
  if(!strcmp(c, "On"))
  {
    while(!Run_Under_L || !Run_Under_R) 
      Run_Slow();
    Run_Stop();
  }
  Run_Stop();
	//出线，入线
	while(num--)
	{
//    while(Run_Behind_R)//出黑线
    AntiClockwise();
    delay_ms(250);
    while(!Run_Behind_R)//入黑线
      AntiClockwise();
    delay_ms(15);
    while(Run_Behind_R)//出黑线
      AntiClockwise();
	}
  Run_Stop();
  delay_ms(15);
  while(Run_Behind_R)
    AntiClockwise();
  Run_Stop();
}

/**
  ************************************
  * @brief  逆时针90_ACE
  * @param  num:数线的条数  count:直走延时(1900)
  * @retval None
	************************************
*/
void Turn_Left_ACE_Angle_Front(uint8_t num, char c[])
{
  if(!strcmp(c, "On"))
  {
    while(!Run_Under_L || !Run_Under_R) 
      Run_Slow();
    Run_Stop();
  }
  Run_Stop();
	//出线，入线
	while(num--)
	{
//    while(Run_Behind_R)//出黑线
    AntiClockwise();
    delay_ms(250);
    while(!Run_Behind_R)//入黑线
      AntiClockwise();
    delay_ms(10);
    while(Run_Behind_R)//出黑线
      AntiClockwise();
	}
  Run_Stop();
}

/**
  ************************************
  * @brief  逆时针90_ACE
  * @param  num:数线的条数  count:直走延时(1900)
  * @retval None
	************************************
*/
void Turn_Left_ACE_Angle_Front_Delay(uint8_t num, char c[], uint16_t a, uint16_t b)
{
  if(!strcmp(c, "On"))
  {
    while(!Run_Under_L || !Run_Under_R) 
      Run_Slow();
    Run_Line_Slow(a);
    Run_Stop();
  }
  Run_Stop();
	//出线，入线
	while(num--)
	{
//    while(Run_Behind_R)//出黑线
    AntiClockwise();
    delay_ms(300);
    while(!Run_Behind_R)//入黑线
      AntiClockwise();
    delay_ms(10);
    while(Run_Behind_R)//出黑线
      AntiClockwise();
	}
  AntiClockwise();
  delay_ms(b);
  Run_Stop();
}

/**
  ************************************
  * @brief  顺时针90_ACE
  * @param  num:数线的条数  count:直走延时(1500)
  * @retval None
	************************************
*/
void Turn_Right_ACE_Angle(uint8_t num, char c[])
{
  if(!strcmp(c,"On"))
  {
    while(!Run_Under_L || !Run_Under_R) 
      Run_Slow();
    Run_Stop();
  }
  Run_Stop();
	//出线，入线
	while(num--)
	{
//    while(Run_Behind_L)//出黑线
    Clockwise();
    delay_ms(250);
    while(!Run_Behind_L)//入黑线
      Clockwise();
    delay_ms(10);
    while(Run_Behind_L)//出黑线
      Clockwise();
	}
  Run_Stop();
}

/**
  ************************************
  * @brief  顺时针90_ACE
  * @param  num:数线的条数  count:直走延时(1500)
  * @retval None
	************************************
*/
void Turn_Right_ACE_Angle_Front(uint8_t num, char c[])
{
  if(!strcmp(c,"On"))
  {
    while(!Run_Under_L || !Run_Under_R) 
      Run_Slow();
    Run_Stop();
  }
  Run_Stop();
	//出线，入线
	while(num--)
	{
//    while(Run_Behind_L)//出黑线
    Clockwise();
    delay_ms(250);
    while(!Run_Behind_L)//入黑线
      Clockwise();
    delay_ms(10);
    while(Run_Behind_L)//出黑线
      Clockwise();
	}
  Run_Stop();
}

/**
  ************************************
  * @brief  顺时针90_ACE
  * @param  num:数线的条数  count:直走延时(1500)
  * @retval None
	************************************
*/
void Turn_Right_ACE_Angle_Front_Delay(uint8_t num, char c[], uint16_t a, uint16_t b)
{
  if(!strcmp(c,"On"))
  {
    while(!Run_Under_L || !Run_Under_R) 
      Run_Slow();
    Run_Line_Slow(a);
    Run_Stop();
  }
  Run_Stop();
	//出线，入线
	while(num--)
	{
    Clockwise();
    delay_ms(250);
    while(!Run_Behind_L)//入黑线
      Clockwise();
    delay_ms(10);
    while(Run_Behind_L)//出黑线
      Clockwise();
	}
  Clockwise();
  delay_ms(b);
  Run_Stop();
}

/**
  ************************************
  * @brief  逆时针45_BD
  * @param  num:数线的条数  count:直走延时(350)
  * @retval None
	************************************
*/
void Turn_Left_BD(uint8_t num, uint16_t count)
{
	Run_Line_Slow(1500);
	Run_Line_Slow(count);
	//出线，入线
	while(num--)
	{
		while(Run_Z)
			AntiClockwise();
		delay_ms(10);
		while(!Run_Z)
			AntiClockwise();
		delay_ms(10);
	}
	//纠正对中
	delay_ms(110);
  Run_Stop();
}

/**
  ************************************
  * @brief  逆时针旋转一段时间
  * @param  a
  * @retval None
	************************************
*/
void Turn_Left_Delay(uint16_t a)
{
  AntiClockwise();
  delay_ms(a);
  Run_Stop();
}

/**
  ************************************
  * @brief  顺时针旋转一段时间
  * @param  a
  * @retval None
	************************************
*/
void Turn_Right_Delay(uint16_t a)
{
  Clockwise();
  delay_ms(a);
  Run_Stop();
}

/**
  ************************************
  * @brief  逆时针45_BD
  * @param  num:数线的条数  count:直走延时(350)
  * @retval None
	************************************
*/
void Turn_Right_BD(uint8_t num, uint16_t count)
{
	Run_Line_Slow(1500);
	Run_Line_Slow(count);
//	Run(1500,1500);
//	while(1);
	//出线，入线
	while(num--)
	{
		while(Run_Z)
			Clockwise();
		delay_ms(10);//延时去抖
		while(!Run_Z)
			Clockwise();
		delay_ms(10);
	}
	//纠正对中
	delay_ms(100);
  Run_Stop();
}

/**
  ************************************
  * @brief  走到十字路口
  * @param  None
  * @retval None
	************************************
*/
void Go_Cross(void)
{
	while(!Run_L || !Run_R)
  {
    delay_ms(1);
    if(!Run_L || !Run_R)
      Tracking_Slow();
    else
      break;
  }
}

/**
  ************************************
  * @brief  走到十字路口
  * @param  None
  * @retval None
	************************************
*/
void Go_Cross_Double(void)
{
	while(!Run_L || !Run_R)
  {
    delay_ms(1);
    if(!Run_L || !Run_R)
      Tracking_Slow_Double();
    else
      break;
  }
}


/**
  ************************************
  * @brief  走到十字路口--AE专用
  * @param  None
  * @retval None
	************************************
*/
void Go_Cross_Front(void)
{
	while(!Run_Front_L || !Run_Front_R)
  {
    delay_ms(1);
    if(!Run_Front_L || !Run_Front_R)
      Tracking_Slow_Double();
    else
      break;
  }
}

/**
  ************************************
  * @brief  启动并走到十字路口
  * @param  None
  * @retval None
	************************************
*/
void Start_Cross(void)
{
	delay_ms(1000);
	Go_Cross();
}

/**
  ************************************
  * @brief  回到起点
  * @param  None
  * @retval None
	************************************
*/
void Go_Start(void)
{
	//当都是黑线
	while(!Run_L || !Run_Z || !Run_R)
		Tracking_Fast();
	Run_Line_Fast(40);//直走一段路程
	//停车
	while(1)
		Run_Stop();
}
