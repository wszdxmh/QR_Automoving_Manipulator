/**
  ************************************
  * @file    key.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.02
  * @brief   按键驱动(PD0 PD1 PD2 PD3)
	************************************
*/

#include "key.h"

//定义全局变量
uint8_t Key1_Flag, Key2_Flag, Key3_Flag, Key4_Flag;

/**
  ************************************
  * @brief  按键IO口的初始化
  * @param  None
  * @retval None
	************************************
*/
void Key_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//使能PORTD时钟
  
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3;//KEY0-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
}

/**
  ************************************
  * @brief  外部中断初始化
  * @param  None
  * @retval None
	************************************
*/
void EXTIX_Init(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  Key_Init();	 //	按键端口初始化
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

  //GPIOD.1 中断线以及中断初始化配置   下降沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
  EXTI_InitStructure.EXTI_Line=EXTI_Line1;	//KEY2
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  //GPIOD.2	  中断线以及中断初始化配置 下降沿触发 //KEY1
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource3);
  EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  //GPIOD.3	  中断线以及中断初始化配置  下降沿触发	//KEY0
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  //GPIOD.0	  中断线以及中断初始化配置 下降沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0); 
  EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure); 

  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY2所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);


  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY1所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY0所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

/**
  ************************************
  * @brief  外部中断0服务函数
  * @param  None
  * @retval None
	************************************
*/
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY_0 == 0)	 	 //key0按键				 
		Key1_Flag = !Key1_Flag;
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}

/**
  ************************************
  * @brief  外部中断1服务函数
  * @param  None
  * @retval None
	************************************
*/
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY_1 == 0)	 	 //key1按键
		Key2_Flag = !Key2_Flag;
	EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位  
}

/**
  ************************************
  * @brief  外部中断2服务函数
  * @param  None
  * @retval None
	************************************
*/
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY_2 == 0)	 	 //key2按键
		Key3_Flag = !Key3_Flag;
	EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE0上的中断标志位  
}

/**
  ************************************
  * @brief  外部中断2服务函数
  * @param  None
  * @retval None
	************************************
*/
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY_3 == 0)	 	 //key3按键
		Key4_Flag = !Key4_Flag;
	EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE0上的中断标志位  
}
