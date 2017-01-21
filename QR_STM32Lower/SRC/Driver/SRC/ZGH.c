
#include "ZGH.h"

struct MANIPULATOR_VALUE Manipulator_Value, Action_table;

extern uint16_t Flag;

/**
  ************************************
  * @brief  上位机调试机械手
  * @param  None
  * @retval None
	************************************
*/
void Test_Manipulator_Upper_Monitor(void)
{
    TIM_SetCompare1(TIM3,Action_table.Waist);//PB4 Tracking_Positioning_Left
    TIM_SetCompare1(TIM4,Action_table.Big_Arm);//PB6 Tracking_Positioning_Right
    TIM_SetCompare2(TIM4,Action_table.Little_Arm);//PB7 Tracking_Lift
    TIM_SetCompare3(TIM4,Action_table.Wrist);//PB8 Tracking_Flat
		TIM_SetCompare4(TIM4,Action_table.Gripper);//PB9
}

/**
  ************************************
  * @brief  手臂初始化
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_Init(void)
{
	TIM_SetCompare1(TIM3,INIT_Waist); //PB4 Tracking_Positioning_Left
	TIM_SetCompare1(TIM4,INIT_Big_Arm);//PB6 Tracking_Positioning_Right
	TIM_SetCompare2(TIM4,INIT_Little_Arm);//PB7 Tracking_Lift
	TIM_SetCompare3(TIM4,INIT_Wrist);//PB8 Tracking_Flat
	TIM_SetCompare4(TIM4,INIT_Gripper);//PB9
  Manipulator_Value.Waist = INIT_Waist;
  Manipulator_Value.Big_Arm = INIT_Big_Arm;
  Manipulator_Value.Little_Arm = INIT_Little_Arm;
  Manipulator_Value.Wrist = INIT_Wrist;
  Manipulator_Value.Gripper = INIT_Gripper;
}

/**
  ************************************
  * @brief  手臂单独运动子函数
  * @param  None
  * @retval None
	************************************
*/
static void Manipulator_Move_Part(uint16_t variable, uint16_t *pVariable, uint8_t ON)
{
	static uint8_t a;
  uint16_t max_variable = 0;
  max_variable = fabs((variable - (*pVariable)));
	if(max_variable != 0)
	{
		while(max_variable--)
		{
			if(variable < (*pVariable))
				(*pVariable) --;
			else if(variable > (*pVariable))
				(*pVariable) ++;
			if(ON == 1)
				switch(a)
				{
					case 0:TIM_SetCompare4(TIM4,*pVariable);break;
					case 1:TIM_SetCompare3(TIM4,*pVariable);break;
					case 2:TIM_SetCompare2(TIM4,*pVariable);break;
					case 3:TIM_SetCompare1(TIM4,*pVariable);break;
					case 4:TIM_SetCompare1(TIM3,*pVariable);break;
					default:break;
				}
			else 
				switch(a)
				{
					case 4:TIM_SetCompare4(TIM4,*pVariable);break;
					case 3:TIM_SetCompare3(TIM4,*pVariable);break;
					case 2:TIM_SetCompare2(TIM4,*pVariable);break;
					case 1:TIM_SetCompare1(TIM4,*pVariable);break;
					case 0:TIM_SetCompare1(TIM3,*pVariable);break;
					default:break;
				}
			delay_ms(TURN_DELAY_TIME);//机械手运动延时
		}
	}
	a++;
	if(a == 5) a=0;
}

/**
  ************************************
  * @brief  夹
  * @param  None
  * @retval None
	************************************
*/
void Catch_On(uint16_t variable, uint16_t *pVariable)
{
  uint16_t max_variable = 0;
  max_variable = fabs((variable - (*pVariable)));
	if(max_variable != 0)
	{
		while(max_variable--)
		{
			if(variable < (*pVariable))
				(*pVariable) --;
			else if(variable > (*pVariable))
				(*pVariable) ++;
			TIM_SetCompare4(TIM4,*pVariable);
			delay_ms(TURN_DELAY_TIME);//机械手运动延时
		}
	}
}

/**
  ************************************
  * @brief  手臂联动
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_ALL_Positive(struct MANIPULATOR_VALUE *manipulator)
{
	//手
	Manipulator_Move_Part(manipulator->Gripper,&Manipulator_Value.Gripper,1);	
	//腕
	Manipulator_Move_Part(manipulator->Wrist,&Manipulator_Value.Wrist,1);	
	//小臂动
	Manipulator_Move_Part(manipulator->Little_Arm,&Manipulator_Value.Little_Arm,1);	
	//大臂动
	Manipulator_Move_Part(manipulator->Big_Arm,&Manipulator_Value.Big_Arm,1);	
	//云台
	Manipulator_Move_Part(manipulator->Waist,&Manipulator_Value.Waist,1);	
}

/**
  ************************************
  * @brief  手臂联动-反向
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_ALL_Reverse(struct MANIPULATOR_VALUE *manipulator)
{
	//云台
	Manipulator_Move_Part(manipulator->Waist,&Manipulator_Value.Waist,0);
	//大臂动
	Manipulator_Move_Part(manipulator->Big_Arm,&Manipulator_Value.Big_Arm,0);
	//小臂动
	Manipulator_Move_Part(manipulator->Little_Arm,&Manipulator_Value.Little_Arm,0);
	//腕
	Manipulator_Move_Part(manipulator->Wrist,&Manipulator_Value.Wrist,0);
	//手
	Manipulator_Move_Part(manipulator->Gripper,&Manipulator_Value.Gripper,0);
}

/**
  ************************************
  * @brief  手臂初始状态
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_Init_Start(char a[])
{
  Action_table.Waist = INIT_Waist;
  Action_table.Big_Arm = INIT_Big_Arm;
  Action_table.Little_Arm = INIT_Little_Arm;
  Action_table.Wrist = INIT_Wrist;
  Action_table.Gripper = INIT_Gripper;
	if(!strcmp(a,"Waist"))
		Manipulator_ALL_Reverse(&Action_table);
	else if(!strcmp(a,"Gripper"))
		Manipulator_ALL_Positive(&Action_table);
}

/**
  ************************************
  * @brief  手臂举高状态
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_HIGHT_Start(char a[])
{
	Action_table.Waist = HIGHT_Waist;
	Action_table.Big_Arm = HIGHT_Big_Arm;
	Action_table.Little_Arm = HIGHT_Little_Arm;
	Action_table.Wrist = HIGHT_Wrist;
	if(!strcmp(a,"Catch"))
		Action_table.Gripper = 1550;
	else
		Action_table.Gripper = HIGHT_Gripper;
	Manipulator_ALL_Positive(&Action_table);
}

/**
  ************************************
  * @brief  手臂位置1状态
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_Location_One_Start(void)
{
  Action_table.Waist = Location_One_Waist;
  Action_table.Big_Arm = Location_One_Big_Arm;
  Action_table.Little_Arm = Location_One_Little_Arm;
  Action_table.Wrist = Location_One_Wrist;
  Action_table.Gripper = Location_One_Gripper;
	Manipulator_ALL_Reverse(&Action_table);
}

/**
  ************************************
  * @brief  手臂位置2状态
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_Location_Two_Start(void)
{
  Action_table.Waist = Location_Two_Waist;
  Action_table.Big_Arm = Location_Two_Big_Arm;
  Action_table.Little_Arm = Location_Two_Little_Arm;
  Action_table.Wrist = Location_Two_Wrist;
  Action_table.Gripper = Location_Two_Gripper;
	Manipulator_ALL_Reverse(&Action_table);
}

/**
  ************************************
  * @brief  手臂位置3状态
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_Location_Thr_Start(void)
{
  Action_table.Waist = Location_Thr_Waist;
  Action_table.Big_Arm = Location_Thr_Big_Arm;
  Action_table.Little_Arm = Location_Thr_Little_Arm;
  Action_table.Wrist = Location_Thr_Wrist;
  Action_table.Gripper = Location_Thr_Gripper;
	Manipulator_ALL_Reverse(&Action_table);
}

/**
  ************************************
  * @brief  手臂位置4状态
  * @param  None
  * @retval None
	************************************
*/
void Manipulator_Location_Fho_Start(void)
{
  Action_table.Waist = Location_Fho_Waist;
  Action_table.Big_Arm = Location_Fho_Big_Arm;
  Action_table.Little_Arm = Location_Fho_Little_Arm;
  Action_table.Wrist = Location_Fho_Wrist;
  Action_table.Gripper = Location_Fho_Gripper;
	Manipulator_ALL_Reverse(&Action_table);
}

/**
  ************************************
  * @brief  举高->位置num->举高->初始
  * @param  None
  * @retval None
	************************************
*/
void Hight_To_Location_To_Init(uint8_t num)
{
	Catch_On(1550,&Manipulator_Value.Gripper);
	Manipulator_HIGHT_Start("Catch");
//	delay_ms(1500);
	if(num == 1)
		Manipulator_Location_One_Start();
	else if(num == 2)
		Manipulator_Location_Two_Start();
	else if(num == 3)
		Manipulator_Location_Thr_Start();
	else if(num == 4)
		Manipulator_Location_Fho_Start();
//	delay_ms(1500);
	Manipulator_HIGHT_Start("On");
//	delay_ms(1500);
	Manipulator_Init_Start("Gripper");
}

/**
  ************************************
  * @brief  二维码自动控制
  * @param  None
  * @retval None
	************************************
*/
void QR_Control(void)
{
	switch(Flag)
	{
		case 1:Hight_To_Location_To_Init(1);break;
		case 2:Hight_To_Location_To_Init(2);break;
		case 3:Hight_To_Location_To_Init(3);break;
		case 4:Hight_To_Location_To_Init(4);break;
		default:break;
	}
	Flag = 5;
//	//举高->位置1->举高->初始
//	if(Flag == 1)
//		Hight_To_Location_To_Init(1);
//	//举高->位置2->举高->初始
//	if(Flag == 2)
//		Hight_To_Location_To_Init(2);
//	//举高->位置3->举高->初始
//	if(Flag == 3)
//		Hight_To_Location_To_Init(3);
//	//举高->位置4->举高->初始
//	if(Flag == 4)
//		Hight_To_Location_To_Init(4);
//	Flag = 0;
}
