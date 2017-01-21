/**
  ************************************
  * @file    route.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.20
  * @brief   路线规划
	************************************
*/

#include "route.h"

/**
  ************************************
  * @brief  起点版--A：蓝  C：红  E：黄
  * @param  None
  * @retval None
	************************************
*/
void R_1(void) //用时7分05秒
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************红到起点*******************/
  //夹放第一个
  Tracking_Fast_Distance(2000);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();

  Put_Catch("Catch", "On");//夹第一个
  Run_Manipulator(3,"Left", "Catch", "On");
  Tracking_Fast_Distance(2000);//快速循迹一段距离
  Tracking_Slow_Distance(800);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Under");//放第一个
  Run_Manipulator(1,"Left", "Put", "Under");
  
  //夹放第二个
  Tracking_Fast_Distance(2500);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Put_Catch("Catch", "In");//夹第二个
  Run_Manipulator(3, "Left", "Catch", "In");//面对起点
  Tracking_Fast_Distance(2600);//快速循迹一段距离
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
  Run_Stop();
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1,"Left", "Put", "In");//面对起点
  
  //夹放第三个
  Tracking_Fast_Distance(2500);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Put_Catch("Catch", "Under");//夹第三个
  Run_Manipulator(3, "Left", "Catch", "Under");//面对起点
  Tracking_Fast_Distance(2600);//快速循迹一段距离
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
  Run_Stop();
  Put_Catch("Put", "On");//放第三个
  Run_Manipulator(1,"Left", "Put", "On");//面对起点
  
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
  Tracking_Fast_Distance(3500);//快速循迹一段距离
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
  Tracking_Fast_Distance(3500);//快速循迹一段距离
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
  Tracking_Fast_Distance(3500);//快速循迹一段距离
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
  
  /*******************黄放蓝*******************/
  //夹放第一个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front(2, "On");//面对黄色
  Put_Catch("Catch", "On");//夹第一个
  Run_Manipulator(4, "Left", "Put", "On");//面对起点
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_E(50);
  Run_Stop();
  Run_Manipulator(1, "Right", "Put", "Tracking");//面对起点
  
  //夹放第二个
  Tracking_Fast_Distance(3200);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Slow();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(0, "On");//面对黄色
  Put_Catch("Catch", "In");//夹第二个
  Run_Manipulator(4, "Left", "Catch", "In");//面对蓝色
  Tracking_Fast_Distance(3500);//快速循迹一段距离
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
  Run_Stop();
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Right", "Put", "In");//面对起点
  
  //夹放第三个
  Tracking_Fast_Distance(3200);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Slow();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(0, "On");//面对黄色
  Put_Catch("Catch", "Under");//夹第三个
  Run_Manipulator(4, "Left", "Catch", "Under");//面对蓝色
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
  Run_Stop();
  Put_Catch("Put", "On");//放第二个
  Run_Manipulator(1, "Right", "Put", "On");//面对起点
  
  /*******************红放黄*******************/
  //夹放第一个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(2, "On");//面对起点
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Tracking_Fast_Distance(2600);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Catch", "On");//夹上面的物块
  Run_Manipulator(1, "Left", "Catch", "On");//面对起点
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//面对黄色
  Tracking_Fast_Distance(3700);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_A(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(2, "On");//面对起点
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Tracking_Fast_Distance(2600);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Run_Stop();
  Put_Catch("Catch", "In");//夹中间的物块
  Run_Manipulator(1, "Left", "Catch", "In");//面对C点
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//面对黄色
  Tracking_Fast_Distance(3900);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Run_Stop();
  Put_Catch("Put", "In");//放中间的物块
  Run_Manipulator(1, "Left", "Put", "In");//面对C点
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(2, "On");//面对起点
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Tracking_Fast_Distance(2600);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Catch", "Under");//夹上面的物块
  Run_Manipulator(1, "Left", "Catch", "Under");//面对C点
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//面对黄色
  Tracking_Fast_Distance(3700);//快速循迹一段距离
  Tracking_Slow_Distance(700);//慢速循迹一段距离
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放上面的物块
  Run_Manipulator(1, "Left", "Put", "On");//面对E点
  
  /*******************回城*******************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(2, "On");//面对起点
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  while(!Run_Front_L || !Run_Front_R) //快速循迹到起点
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//停车！！！
}

/**
  ************************************
  * @brief  侧方版--A：蓝  C：红  E：黄
  * @param  None
  * @retval None
	************************************
*/
void R_2(void) //用时4分35秒
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************出城********************/
  Run_Line_Fast(1000);
  
  /*******************C放BD*******************/
//  Tracking_Fast_Distance(5000);//快速循迹一段距离
  
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Left_ACE(1, "Off", 20,"Off",1);
  Put_Catch("Put", "Special");
  Put_Catch("Catch", "Highest");//放第一个
  
  Turn_Right_ACE(1, "Off", 1,"Off",1);
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Left_ACE(1, "Off",15,"Off",1);
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//放第二个
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "Under");//夹第三个
  Put_Catch("Catch", "Highest");//夹第三个
  
  Turn_Left_ACE(1, "Off",15,"Off",1);
  Put_Catch("Put", "On");
  Put_Catch("Catch", "Highest");//放第一个
  
  /*******************蓝放红*******************/
  //夹放第一个
  Turn_Right_ACE_Angle(2, "Off");//面对蓝色
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Put_Catch("Catch", "On");//夹第一个
  Run_Manipulator(1, "Left", "Catch", "On");//面对C点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
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
  Turn_Left_ACE_Angle_Front_Delay(2, "On",780,1);//面对E点
  Put_Catch("Catch", "In");//抓第二个
  Run_Manipulator(1, "Left", "Catch", "In");//面对C点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
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
  Turn_Left_ACE_Angle_Front_Delay(2, "On",780,1);//面对E点
  Put_Catch("Catch", "Under");//抓第三个
  Run_Manipulator(1, "Left", "Catch", "Under");//面对C点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
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
  
  /*******************黄放蓝*******************/
  
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
  
  
  //夹放第一个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle_Front(1, "On");//面对A点
  Put_Catch("Catch", "On");//夹第一个
  Run_Manipulator(2, "Right", "Put", "On");//面对E点
  Tracking_Fast_Distance(3900);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_E(50);
  Run_Stop();
  Run_Manipulator(1, "Right", "Put", "Tracking");//面对起点
  
  //夹放第二个
  Tracking_Fast_Distance(3200);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Slow();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(0, "On");//面对黄色
  Put_Catch("Catch", "In");//夹第二个
  Run_Manipulator(4, "Left", "Catch", "In");//面对蓝色
  Tracking_Fast_Distance(3800);//快速循迹一段距离
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
  Run_Stop();
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Right", "Put", "In");//面对起点
  
  //夹放第三个
  Tracking_Fast_Distance(3200);//快速循迹一段距离
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Slow();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(0, "On");//面对黄色
  Put_Catch("Catch", "Under");//夹第三个
  Run_Manipulator(4, "Left", "Catch", "Under");//面对蓝色
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
  Run_Stop();
  Put_Catch("Put", "On");//放第二个
  Run_Manipulator(1, "Right", "Put", "On");//面对起点
  
  /*******************起点放黄*******************/
  //夹放第一个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(0, "On");//面对起点
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第二个
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Tracking_Fast_Distance(3700);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Put_A(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//面对C点
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "In");//夹第一个
  Put_Catch("Catch", "Highest");//夹第二个
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Tracking_Fast_Distance(4100);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Run_Stop();
  Put_Catch("Put", "In");//放中间的物块
  Run_Manipulator(1, "Left", "Put", "In");//面对C点
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//面对起点
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "Under");//夹第三个
  Put_Catch("Catch", "Highest");//夹第三个
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Tracking_Fast_Distance(3600);//快速循迹一段距离
  Tracking_Slow_Distance(700);//慢速循迹一段距离
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放上面的物块
  Run_Manipulator(1, "Left", "Put", "On");//面对E点
  
  /*******************回城*******************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(2, "On");//面对起点
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  while(!Run_Front_L || !Run_Front_R) //快速循迹到起点
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//停车！！！
}

/**
  ************************************
  * @brief  侧方版--A：黄  C：红  E：蓝
  * @param  None
  * @retval None
	************************************
*/
void R_3(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************出城********************/
  Run_Line_Fast(1000);
  
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
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Tracking_Slow_Distance(500);//慢速循迹一段距离
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
  Turn_Right_ACE(1, "Off",1,"On",40);//面对B点
  
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Right_ACE(1, "Off",1,"Off",30);//面对C点
  
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
  Turn_Right_ACE(1, "Off",1,"On",30);//面对B点
  
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
  
  /********************E放C********************************/
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Left_ACE_Angle(1, "Off");
  Put_Catch("Put", "Under");
  Put_Catch("Put", "Special");//放第一个
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
  
  /******************C放E******************************/
  //放第一个
  Tracking_Fast_Distance(3500);//快速循迹一段距离
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
  
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
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
  Run_Manipulator(1, "Right", "Put", "On");//面对A点
  
  
  /*******************A放C******************************/
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");
  Turn_Right_ACE_Angle(1, "Off");//面对C点
  
  Put_Catch("Put", "Under"); //放第一个
  Put_Catch("Put", "Special");//放第一个
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
  
  Tracking_Fast_Distance(4100);//快速循迹一段距离
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
  
  Tracking_Fast_Distance(4100);//快速循迹一段距离
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
  
  /**********************回城***************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Turn_Right_ACE_Angle(1, "On");//面对红色
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//停车！！！
}

/**
  ************************************
  * @brief  侧方版--A：白  C：红  E：黑
  * @param  None
  * @retval None
	************************************
*/
void R_4(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************出城********************/
  Run_Line_Fast(1000);
  
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  /************************A放B*******************************/
  
  //夹放第一个
  Turn_Left_ACE_Angle(1, "On"); //面对A点
  Run_Stop();
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Right_ACE(1, "Off", 1,"Off",1); //面向B点
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
//  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Right_ACE_Angle_Front_Delay(3, "On",690,30);//面对A点
  Put_Catch("Catch", "In");//抓第二个
  Put_Catch("Catch", "Highest");//夹第二个
  Turn_Right_ACE(1, "Off", 1,"Off",1); //面向B点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Left", "Put", "In"); //面对十字
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Turn_Right_ACE_Angle_Front_Delay(3, "On",690,30);//面对A点
  Put_Catch("Catch", "Under");//抓第三个
  Put_Catch("Catch", "Highest");//回到举高姿态
  Turn_Right_ACE(1, "Off", 1,"Off",1); //面向B点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第三个
  Run_Manipulator(1, "Left", "Put", "On"); //面对十字
  
  /*******************E放D************************/
  
  //夹放第一个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",690,1);//面对E点
  Run_Stop();
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//回到举高状态
  Turn_Left_ACE(1, "Off", 1,"Off",1); //面向B点
  
  Tracking_Fast_Distance(4000);//快速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对十字
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(3, "On",690,1);//面对E点
  Put_Catch("Catch", "In");//抓第二个
  Put_Catch("Catch", "Highest");//夹第二个
  Turn_Left_ACE(1, "Off", 1,"Off",1); //面向D点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Left", "Put", "In"); //面对十字
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(3, "On",690,1);//面对E点
  Put_Catch("Catch", "Under");//抓第三个
  Put_Catch("Catch", "Highest");//回到举高姿态
  Turn_Left_ACE(1, "Off", 1,"Off",1); //面向D点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第三个
  Run_Manipulator(1, "Left", "Put", "On"); //面对十字
  
  /*********************回起点归中*******************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",690,1);//面对起点
  Tracking_Fast_Distance(4500);//快速循迹一段距离
  Turn_Left_180();
  
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
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Tracking_Slow_Distance(500);//慢速循迹一段距离
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
  Turn_Right_ACE(1, "Off",1,"On",35);//面对B点
  
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Right_ACE(1, "Off",1,"Off",30);//面对C点
  
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
  Turn_Right_ACE(1, "Off",1,"On",20);//面对B点
  
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
  
  /**********************回城***************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Turn_Left_ACE_Angle(0, "On");//面对红色
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//停车！！！
}

/**
  ************************************
  * @brief  侧方版--A：黄  C：红  E：蓝
  * @param  None
  * @retval None
	************************************
*/
void R_5(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************出城********************/
  Run_Line_Fast(1000);
  
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
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Put_BCD(60);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();

  Turn_Left_ACE_Angle_Front(0,"On");
  Tracking_Fast_Distance(4000);//快速循迹一段距离
  Turn_Left_180();
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Turn_Left_ACE(1, "On",20,"Off",10);//面向B点
  
  Put_Catch("Catch", "In");//夹第二个
  Put_Catch("Catch", "Highest");//夹第二个
  
  Turn_Right_ACE(1, "Off",1,"Off",30);//面对C点
  
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

  Turn_Left_ACE_Angle_Front(0,"On");
  Tracking_Fast_Distance(4000);//快速循迹一段距离
  Turn_Left_180();
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Turn_Left_ACE(1, "On",20,"Off",10);//面向B点
  
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
  
  /********************E放C********************************/
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Left_ACE_Angle(1, "Off");
  Put_Catch("Put", "Under");
  Put_Catch("Put", "Special");//放第一个
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
  
  /******************C放E******************************/
  //放第一个
  Tracking_Fast_Distance(3500);//快速循迹一段距离
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
  
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
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
  Run_Manipulator(1, "Right", "Put", "On");//面对A点
  
  
  /*******************A放C******************************/
  
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Turn_Right_ACE_Angle(0, "On");//面对A点
  
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");
  Turn_Right_ACE_Angle(1, "Off");//面对C点
  
  Put_Catch("Put", "Under"); //放第一个
  Put_Catch("Put", "Special");//放第一个
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
  
  Tracking_Fast_Distance(4100);//快速循迹一段距离
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
  
  Tracking_Fast_Distance(4100);//快速循迹一段距离
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
  Run_Manipulator(2, "Left", "Put", "On");//面对A点
  
  /**********************回城***************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Turn_Right_ACE_Angle(1, "On");//面对红色
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//停车！！！
}

/**
  ************************************
  * @brief  侧方版--A：蓝  C：黑  E：白
  * @param  None
  * @retval None
	************************************
*/
void R_6(void)
{
  Attitude_Highest();//初始状态为举高状态
  Catch_Put(Put);//张开爪子！！！
  
  /*******************出城********************/
  Run_Line_Fast(1000);
  
  /********************C放D*****************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  //夹放第一个
  Turn_Left_ACE_Angle(0, "On");//面对红色
  Run_Stop();
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  
  Turn_Right_ACE(1, "Off", 1,"Off",1); //面向D点
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
//  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Right_ACE_Angle_Front_Delay(2, "On",690,30);//面对A点
  Put_Catch("Catch", "In");//抓第二个
  Put_Catch("Catch", "Highest");//夹第二个
  Turn_Right_ACE(1, "Off", 1,"Off",1); //面向D点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Left", "Put", "In"); //面对十字
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Right_ACE_Angle_Front_Delay(2, "On",690,30);//面对A点
  Put_Catch("Catch", "Under");//抓第三个
  Put_Catch("Catch", "Highest");//夹第三个
  Turn_Right_ACE(1, "Off", 1,"Off",1); //面向D点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第三个
  Run_Manipulator(1, "Left", "Put", "On"); //面对十字
  
  /*****************回中线归中****************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",690,30);//面对A点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Turn_Left_180();
  
  //夹放第一个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Turn_Right_ACE_Angle(1, "On");//面对E点
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  Turn_Left_ACE_Angle(1, "On");//面对C点
  Turn_Left_ACE(1, "On",20,"Off",10);//面向B点
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
//  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//面对起点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",770,20);//面对E点
  Put_Catch("Catch", "In");//抓第二个
  Put_Catch("Catch", "Highest");//夹第二个
  Turn_Left_ACE_Angle(1, "On");//面对C点
  Turn_Left_ACE(1, "On",20,"Off",10);//面向B点
  Tracking_Fast_Distance(4000);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Left", "Put", "In"); //面对十字
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",740,10);//面对E点
  Put_Catch("Catch", "Under");//抓第三个
  Put_Catch("Catch", "Highest");//夹第三个
  Turn_Left_ACE_Angle(1, "On");//面对C点
  Turn_Left_ACE(1, "On",20,"Off",10);//面向B点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第二个
  Run_Manipulator(1, "Left", "Put", "On"); //面对十字
  
  /**********************回起点归中****************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  Turn_Right_ACE_Angle_Front_Delay(1, "On",690,30);//面对起点
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Turn_Left_180();
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  
  /*************************A放E*******************************/
  //夹放第一个
  Turn_Left_ACE_Angle(1, "On");//面对A点
  Put_Catch("Catch", "On");//夹第一个
  Put_Catch("Catch", "Highest");//夹第一个
  Turn_Right_ACE_Angle(2, "On");//面对E点
  Tracking_Fast_Distance(3500);//快速循迹一段距离
  Run_Stop();
  Put_Catch("Put", "Tracking");//循迹姿态
//  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();
  Put_E(50);
  Run_Stop();
  Run_Manipulator(1, "Right", "Put", "Tracking");//面对起点
  
  //夹放第二个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();

  Turn_Right_ACE_Angle(0, "On");//面对C点
  
  Put_Catch("Catch", "In");//夹第二个
  Run_Manipulator(2, "Right", "Catch", "In");//面对E点
  
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "In");//放第二个
  Run_Manipulator(1, "Right", "Put", "In"); //面对十字
  
  //夹放第三个
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();

  Turn_Right_ACE_Angle(0, "On");//面对C点
  
  Put_Catch("Catch", "Under");//夹第二个
  Run_Manipulator(2, "Right", "Catch", "Under");//面对E点
  
  Tracking_Fast_Distance(3800);//快速循迹一段距离
  Tracking_Slow_Distance(500);//慢速循迹一段距离
  Run_Stop();//停车，防止刚好到了指定距离不停车
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //超声波测距
  {
    Tracking_Slow_Double_Distance(20);//慢速循迹一段距离
    Run_Stop();
  }
  Put_Catch("Put", "On");//放第二个
  Run_Manipulator(1, "Right", "Put", "On"); //面对十字
  
  /***********************回城**********************************/
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();

  Turn_Left_ACE_Angle(2, "On");//面对起点
  while(!Run_Front_L || !Run_Front_R) //快速循迹到十字
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//停车！！！
}
