/**
  ************************************
  * @file    test.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.10.13
  * @brief   测试函数
	************************************
*/

#include "test.h"
#include "string.h"

//引用全局变量
extern uint16_t Positioning_Left;
extern uint16_t Positioning_Right;
extern uint16_t Lift;
extern uint16_t Flat;
extern uint16_t Clip;
extern uint16_t Flag;
extern uint16_t Time;
extern uint8_t Flag_Manipulator;

//宏编译定义
#define MANIPULATOR_ON  1

/**
  ************************************
  * @brief  测试起点->十字->起点->十字
  * @param  None
  * @retval None
	************************************
*/
void Test_Start_Cross(void)
{
  while(1)
  {
    Start_Cross();//启动并走到十字路口
    Run_Stop();
    delay_ms(1600);
    Turn_Left_ACE_Angle(0, "On");//面对黄色
    Run_Stop();
    Turn_Left_ACE_Angle(3,"Off");//面对起点
    delay_ms(1500);
    Tracking_Slow_Distance(1500);//慢速循迹一段距离
    Tracking_Slow_Double_Distance(500);//慢速循迹一段距离
    Run_Stop();
    Turn_Right_180();
  }
}

/**
  ************************************
  * @brief  测试走一定值超声波数值的变化
  * @param  None
  * @retval None
	************************************
*/
void Test_Ultrasonic(void)
{
  uint16_t value_cm = 0;
  while(1)
  {
    if(Flag)
    {
      Flag = 0;
      Tracking_Slow_Double_Distance(Time);//慢速循迹一段距离
      Run_Stop();
    }
    #if MANIPULATOR_ON
      TIM_SetCompare4(TIM3,Positioning_Left);//PB1
      TIM_SetCompare3(TIM3,Positioning_Right);//PB0
      TIM_SetCompare1(TIM3,Lift);//PB4
      TIM_SetCompare1(TIM4,Flat);//PB6
    #endif
    value_cm = Ultrasonic_Mean_Value(5999, 72);
    Send_PC(0x04, value_cm);
//    delay_ms(40);
  }
}

/**
  ************************************
  * @brief  上位机调试机械手
  * @param  None
  * @retval None
	************************************
*/
void Test_Manipulator_Upper_Monitor(void)
{
  while(1)
  {
    TIM_SetCompare1(TIM3,Positioning_Left);//PB4 Tracking_Positioning_Left
    TIM_SetCompare1(TIM4,Positioning_Right);//PB6 Tracking_Positioning_Right
    TIM_SetCompare2(TIM4,Lift);//PB7 Tracking_Lift
    TIM_SetCompare3(TIM4,Flat);//PB8 Tracking_Flat
		TIM_SetCompare4(TIM4,Clip);//PB9
  }
}

/**
  ************************************
  * @brief  调试机械手
  * @param  None
  * @retval None
	************************************
*/
void Test_Manipulator(void)
{
  TIM_SetCompare1(TIM3,1300);//PB4
  TIM_SetCompare2(TIM3,1700);//PB5
  TIM_SetCompare3(TIM3,1300);//PB0
  TIM_SetCompare4(TIM3,1700);//PB1
  
  TIM_SetCompare1(TIM4,1300);//PB6
  TIM_SetCompare2(TIM4,1700);//PB7
  TIM_SetCompare3(TIM4,1300);//PB8
  TIM_SetCompare4(TIM4,1700);//PB9
}

/**
  ************************************
  * @brief  OLED显示超声波数值
  * @param  None
  * @retval None
	************************************
*/
void Test_Ultrasonic_OLED(void)
{
  uint16_t value_cm = 0;
  LCD_SPI2_P8x16Str(48,6,"OLED");
  LCD_SPI2_P6x8Num(48,2,8888);
  value_cm = Ultrasonic_Mean_Value(5999, 72);
  USART_SendData(USART1, value_cm);
  LCD_SPI2_P6x8Num(48,4,value_cm);
}

/**
  ************************************
  * @brief  调试机械手
  * @param  None
  * @retval None
	************************************
*/
void Test_Manipulator_Go_Cross(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  Tracking_Slow_Distance(1400);//慢速循迹一段距离
	Go_Cross();//走到十字路口
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(1500);
  #endif
  Catch_Put(Put);//张开爪子！！！
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Lift_Flat(Transition_Under_Lift, Transition_Under_Flat);//调整上面姿态至过渡姿态
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Positioning(Transition_Under_Positioning_Left, Transition_Under_Positioning_Right, TURN_DELAY_TIME);//底座舵机运动
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Lift_Flat(Catch_Under_Lift, Catch_Under_Flat);//调整上面姿态至底部姿态
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
}

/**
  ************************************
  * @brief  调试电机差速
  * @param  None
  * @retval None
	************************************
*/
void Test_Run_Turn(void)
{
  Run(1500,1460);
  delay_ms(1500);
  delay_ms(1500);
  delay_ms(200);
  
  Run_Stop();
  delay_ms(1500);
  delay_ms(1500);
  
  Run(1458,1500);
  delay_ms(1500);
  delay_ms(1500);
  delay_ms(200);
  
  Run_Stop();
}

/**
  ************************************
  * @brief  起降
  * @param  None
  * @retval None
	************************************
*/
void Rising_Filling(void)
{
//  Put_Catch("Catch", "On");
  uint16_t max_variable_run;
  Catch_Put(Put);
  Lift_Flat(Transition_In_Lift, Transition_In_Flat);//调整上面姿态
  Positioning(Transition_In_Positioning_Left, Transition_In_Positioning_Right, TURN_DELAY_TIME);//底座舵机运动
  max_variable_run = Return_All("In");
  while(max_variable_run--)
    All_Move("In", TURN_DELAY_TIME);
  Catch_Put(Catch);
  Put_Catch("Catch", "Highest");
}

/**
  ************************************
  * @brief  测试R_5()中的蓝放红
  * @param  None
  * @retval None
	************************************
*/
void Test_R5_2(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************蓝放红*******************/
  //夹放第一个
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(1, "On");//面对蓝色
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Put_Catch("Catch", "On");//夹第一个
  Run_Manipulator(1, "Left", "Catch", "On");//面对C点
  Tracking_Fast_Distance(3600);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle_Front(2, "On");//面对蓝色
  Put_Catch("Catch", "In");//抓第二个
  Run_Manipulator(1, "Left", "Catch", "In");//面对C点
  Tracking_Fast_Distance(4100);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Left", "Put", "In");//面对起点
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle_Front(2, "On");//面对蓝色
  Put_Catch("Catch", "Under");//抓第三个
  Run_Manipulator(1, "Left", "Catch", "Under");//面对C点
  Tracking_Fast_Distance(4100);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第三个
  Run_Manipulator(1, "Left", "Put", "On");//面对起点
}

/**
  ************************************
  * @brief  
  * @param  None
  * @retval None
	************************************
*/
void Run_BD(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************C放BD*******************/
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "Under");
  Put_Catch("Catch", "Highest");//放第一个
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//放第二个
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "Under");//夹第三个
  Put_Catch("Catch", "Highest");//夹第三个
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "On");
  Put_Catch("Catch", "Highest");//放第一个
}

/**
  ************************************
  * @brief  测试R_5()中C放B
  * @param  None
  * @retval None
	************************************
*/
void Text_R5_1(void)
{

}

/**
  ************************************
  * @brief  测试R_2()中A放C
  * @param  None
  * @retval None
	************************************
*/
void R2_3_test(void)
{
  
  /******************A放C***********************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif 
  Turn_Left_ACE_Angle(2, "On");//面对起点
  
  Tracking_Fast_Distance(4800);//快速循迹一段距离
//  Tracking_Slow_Distance(800);//慢速循迹一段距离
  Turn_Left_180();
  Tracking_Fast_Distance(2500);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  
  Turn_Left_ACE_Angle(1, "On");//面对E点
  
  //A放C
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");
  Turn_Right_ACE_Angle(1, "Off");//面对C点
  
  Put_Catch("Put", "Under"); //放第一个
  Put_Catch("Catch", "Highest");
  Turn_Left_ACE_Angle(1, "Off");//面对A点
  
  Put_Catch("Catch", "In"); //夹第二个
  Put_Catch("Catch", "Highest");
  Turn_Right_ACE_Angle(1, "Off");//面对C点
  
  Put_Catch("Put", "In"); //放第二个
  Put_Catch("Catch", "Highest");
  Turn_Left_ACE_Angle(1, "Off");//面对A点
  
  Put_Catch("Catch", "Under"); //夹第三个
  Put_Catch("Catch", "Highest");
  
  //放第一个
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_A(80);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对A点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//面对C点
  
  Put_Catch("Catch", "In");//夹第二个
  Run_Manipulator(1, "Left", "Catch", "In");//面对A点
  
  Tracking_Fast_Distance(3900);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Left", "Put", "In");//面对A点
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//面对C点
  
  Put_Catch("Catch", "Under");//夹第二个
  Run_Manipulator(1, "Left", "Catch", "Under");//面对A点
  
  Tracking_Fast_Distance(3900);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第二个
  Run_Manipulator(1, "Left", "Put", "On");//面对A点
}

/**
  ************************************
  * @brief  测试R_2()中E放C
  * @param  None
  * @retval None
	************************************
*/
void R2_2_test(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /**********************E放C****************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle_Front(0, "On");//面对E点
  Tracking_Fast_Distance(4800);//快速循迹一段距离
//  Tracking_Slow_Distance(800);//慢速循迹一段距离
  Turn_Left_180();
  Tracking_Fast_Distance(2500);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(1, "On");//面对E点
  
  //E放C
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Left_ACE_Angle(1, "Off");
  Put_Catch("Put", "Under");
  Put_Catch("Catch", "Highest");//放第一个
  
  Turn_Right_ACE_Angle(1, "Off");
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Left_ACE_Angle(1, "Off");
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//放第二个
  
  Turn_Right_ACE_Angle(1, "Off");
  Put_Catch("Catch", "Under");//夹第三个
  Put_Catch("Catch", "Highest");//夹第三个
  
  //放第一个
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_E(60);
  Run_Stop();
  Run_Manipulator(1, "Right", "Put", "Tracking");//面对A点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(1, "On");//面对C点
  
  Put_Catch("Catch", "In");//夹第二个
  Run_Manipulator(1, "Right", "Catch", "In");//面对E点
  
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Right", "Put", "In");//面对A点
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(1, "On");//面对C点
  
  Put_Catch("Catch", "Under");//夹第三个
  Run_Manipulator(1, "Right", "Catch", "Under");//面对E点
  
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第三个
  Run_Manipulator(1, "Right", "Put", "On");//面对A点
}

/**
  ************************************
  * @brief  测试下面停车传感器
  * @param  None
  * @retval None
	************************************
*/
void Test_Under(void)
{
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  while(!Run_Under_L || !Run_Under_R) 
    Run_Slow();
  Run_Stop();
}

/**
  ************************************
  * @brief  测试下面停车传感器
  * @param  None
  * @retval None
	************************************
*/
void R2_1_Test(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************C放BD*******************/
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "Under");
  Put_Catch("Catch", "Highest");//放第一个
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//放第二个
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "Under");//夹第三个
  Put_Catch("Catch", "Highest");//夹第三个
  
  /*******************B放C***********************/
  //放第一个
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_BCD(60);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front_Delay(2, "On",780,1);//面对A点
  Turn_Right_ACE(1, "Off",1,"Off",1);//面对B点
  
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Right_ACE(1, "Off",1,"Off",1);//面对C点
  
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Left", "Put", "In");//面对起点
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front_Delay(2, "On",780,1);//面对A点
  Turn_Right_ACE(1, "Off",1,"Off",1);//面对B点
  
  Put_Catch("Catch", "Under");//夹第三个
  Put_Catch("Catch", "Highest");//夹第三个
  
  Turn_Right_ACE(1, "Off",1,"Off",1);//面对C点
  
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第三个
  Run_Manipulator(1, "Left", "Put", "On");//面对起点
}

/**
  ************************************
  * @brief  测试数线延时
  * @param  None
  * @retval None
	************************************
*/
void Test_Turn_Delay(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************出城********************/
  Run_Line_Fast(1000);
  
  /*******************C放BD*******************/
  Tracking_Fast_Distance(4200);//快速循迹一段距离
  
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Slow();

  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Left_ACE(1, "Off", 25,"Off",1);
  Put_Catch("Put", "Under");
  Put_Catch("Catch", "Highest");//放第一个
  
}

/**
  ************************************
  * @brief  测试转圈延时
  * @param  None
  * @retval None
	************************************
*/
void Test_Run_1(void)
{
  AntiClockwise();
  delay_ms(250);
  Run_Stop();
}

/**
  ************************************
  * @brief  测试D到C放B搬C
  * @param  None
  * @retval None
	************************************
*/
void Test_Run_C_B_C(void)
{
//  /*********************回起点归中*******************************/
//  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
//    Tracking_Fast();
//  
//  Turn_Left_ACE_Angle_Front_Delay(1, "On",690,1);//面对起点
//  Tracking_Fast_Distance(4500);//快速循迹一段距离
//  Turn_Left_180();
  
  /**********************C放B****************************/
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Left_ACE(1, "Off",20,"Off",1);
  Put_Catch("Put", "Under");//放第一个
  Put_Catch("Put", "Special");//放第一个
  Put_Catch("Catch", "Highest");//回到举高姿态
  
  Turn_Right_ACE(1, "Off",15,"Off",1);
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//放第二个
  
  Turn_Right_ACE(1, "Off",10,"Off",1);
  Put_Catch("Catch", "Under");//夹第三个
  Put_Catch("Catch", "Highest");//夹第三个
  
  /*******************B放C***********************/
  //放第一个
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_BCD(60);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front_Delay(2, "On",810,1);//面对A点
  Turn_Right_ACE(1, "Off",1,"On",20);//面对B点
  
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Right_ACE(1, "Off",1,"Off",20);//面对C点
  
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Left", "Put", "In");//面对起点
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front_Delay(2, "On",770,1);//面对A点
  Turn_Right_ACE(1, "Off",1,"On",15);//面对B点
  
  Put_Catch("Catch", "Under");//夹第三个
  Put_Catch("Catch", "Highest");//夹第三个
  
  Turn_Right_ACE(1, "Off",1,"Off",1);//面对C点
  
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第三个
  Run_Manipulator(1, "Left", "Put", "On");//面对起点
}
