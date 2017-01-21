/**
  ****************************************************
  *@file: 2016毕业设计
  *@author: 张广洪
  *@version: V1.0
  *@date: 2016.04.02
  *@brief:
  ****************************************************
	*@attention
	*
	*
	****************************************************
  */

/*引用头文件*/
#include "stm32f10x.h"
#include "stm32_eval.h"
#include "led.h"
#include "tim.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "spi.h"
#include "stdio.h"
#include "PC_Link.h"
#include "ZGH.h"

/*定义全局变量*/
uint16_t TIM5CH1_CAPTURE_VAL;//TIM5_IRQHeader
uint8_t TIM5CH1_CAPTURE_STA;//TIM5_IRQHearder
extern struct MANIPULATOR_VALUE Manipulator_Value,Action_table;
extern uint16_t Flag;

int main(void)
{
	//初始化硬件
	delay_init();
	LED_Init();
	LED_Open(0,0);
	NVIC_Configuration(); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	TIM1_Init(2499,7199);
	TIM_PWM_Init(19999, 71);//72000000/((19999+1)*(71+1))=50Hz
	Usart_Init(9600);
  //初始化机械手
	Action_table.Waist = INIT_Waist;
	Action_table.Big_Arm = INIT_Big_Arm;
	Action_table.Little_Arm = INIT_Little_Arm;
	Action_table.Wrist = INIT_Wrist;
	Action_table.Gripper = INIT_Gripper;
	Manipulator_Init();
	while(1)
	{
		while(Flag == 5)
			Test_Manipulator_Upper_Monitor();		
		QR_Control();
//		while(1);
	}
}
