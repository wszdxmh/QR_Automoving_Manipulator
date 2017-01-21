/**
  ************************************
  * @file    manipulator.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.22
  * @brief   机械手控制函数
	************************************
	*@attention
	*matlab曲线拟合方程式：y = 3405 - 1.029 * x     x:左边舵机值   y:右边舵机值
	*上升：左加右减; 下降：左减右加
	*
	************************************
*/

#include "manipulator.h"
#include "math.h"
#include "string.h"

//定义全局变量
uint16_t Positioning_Left, Positioning_Right, Lift, Flat, Clip;
uint8_t Flag_Manipulator;

/**
  ************************************
  * @brief  求绝对值
  * @param  a  b
  * @retval None
	************************************
*/
uint16_t Abs_16(uint16_t a, uint16_t b)
{
  uint16_t mid = 0;
  if(a < b)
  {
    mid = a;
    a = b;
    b = mid;
  }
  return (a - b);
}

/**
  ************************************
  * @brief  输出最大值
  * @param  a  b c d
  * @retval None
	************************************
*/
uint16_t Cmp_Fh_16(uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
  if(a < b)
    a = b;
  if(a < c)
    a = c;
  if(a < d)
    a = d;
    return a;
}

/**
  ************************************
  * @brief  输出最大值
  * @param  a  b c
  * @retval None
	************************************
*/
uint16_t Cmp_Th_16(uint16_t a, uint16_t b, uint16_t c)
{
  uint16_t mid = 0;
  if(a < b)
    mid = b;
  else
    mid = a;
  if(mid < c)
    return c;
  else
    return mid;
}

/**
  ************************************
  * @brief  输出最大值
  * @param  a  b
  * @retval None
	************************************
*/
uint16_t Cmp_Tw_16(uint16_t a, uint16_t b)
{
  if(a < b)
    return b;
  else
    return a;
}

/**
  ************************************
  * @brief  返回最大值
  * @param  char a[]
  * @retval None
	************************************
*/
uint16_t Return_All(char a[])
{
  uint16_t max;
  uint16_t left, right, lift, flat;
  if(!strcmp(a, "On"))
  {
    left = Catch_On_Positioning_Left;
    right = Catch_On_Positioning_Right;
    lift = Catch_On_Lift;
    flat = Catch_On_Flat;
  }
  else if(!strcmp(a, "In"))
  {
    left = Catch_In_Positioning_Left;
    right = Catch_In_Positioning_Right;
    lift = Catch_In_Lift;
    flat = Catch_In_Flat;
  }
  else if(!strcmp(a, "Under"))
  {
    left = Catch_Under_Positioning_Left;
    right = Catch_Under_Positioning_Right;
    lift = Catch_Under_Lift;
    flat = Catch_Under_Flat;
  }
  else if(!strcmp(a, "Highest"))
  {
    left = Highest_Positioning_Left;
    right = Highest_Positioning_Right;
    lift = Highest_Lift;
    flat = Highest_Flat;
  }
  else if(!strcmp(a, "Transition_On"))
  {
    left = Transition_On_Positioning_Left;
    right = Transition_On_Positioning_Right;
    lift = Transition_On_Lift;
    flat = Transition_On_Flat;
  }
  else if(!strcmp(a, "Transition_In"))
  {
    left = Transition_In_Positioning_Left;
    right = Transition_In_Positioning_Right;
    lift = Transition_In_Lift;
    flat = Transition_In_Flat;
  }
  else if(!strcmp(a, "Transition_Under"))
  {
    left = Transition_Under_Positioning_Left;
    right = Transition_Under_Positioning_Right;
    lift = Transition_Under_Lift;
    flat = Transition_Under_Flat;
  }
  max = Cmp_Fh_16(fabs((left - Positioning_Left)), fabs((right - Positioning_Right)), fabs((lift - Lift)), fabs((flat - Flat)));
  return max;
}

/**
  ************************************
  * @brief  手臂舵机运动函数
  * @param  left  right
  * @retval None
	************************************
*/
void Lift_Flat(uint16_t lift, uint16_t flat)
{
  uint16_t max_variable = 0;
  max_variable = Cmp_Tw_16(fabs((lift - Lift)), fabs((flat - Flat)));
  while(max_variable--)
  {
    if(lift >= Lift)
      Lift ++;
    else
      Lift --;
    if(flat <= Flat)
      Flat --;
    else
      Flat ++;
    TIM_SetCompare1(TIM3,Lift);//PB4
    TIM_SetCompare1(TIM4,Flat);//PB6
    delay_ms(MANIPULATOR_DELAY_TIME);//机械手运动延时
  }
}

/**
  ************************************
  * @brief  机械手底座和手臂舵机运动函数
  * @param  left  right lift
  * @retval None
	************************************
*/
void Positioning_Lift(uint16_t left, uint16_t right, uint16_t lift, uint16_t delay_time)
{
  uint16_t max_variable = 0;
  max_variable = Cmp_Th_16(fabs((left - Positioning_Left)), fabs((right - Positioning_Right)) ,fabs((lift - Lift)));
  if((left >= Positioning_Left) && (right <= Positioning_Right))//左加右减为上升
  {
    for(uint16_t i=0; i<max_variable; i++)
    {
      if(left >= Positioning_Left)
        Positioning_Left ++;
      if(right <= Positioning_Right)
        Positioning_Right --;
      if(lift < Lift)
        Lift --;
      else if(lift > Lift)
        Lift ++;
      TIM_SetCompare4(TIM3,Positioning_Left);//PB1
      TIM_SetCompare3(TIM3,Positioning_Right);//PB0
      TIM_SetCompare1(TIM3,Lift);//PB4
      delay_ms(delay_time);//机械手运动延时
    }
  }
  else if((left < Positioning_Left) && (right > Positioning_Right))//下降
  {
    for(uint16_t i=0; i<max_variable; i++)
    {
      if(left <= Positioning_Left)
        Positioning_Left --;
      if(right >= Positioning_Right)
        Positioning_Right ++;
      if(lift < Lift)
        Lift --;
      else if(lift > Lift)
        Lift ++;
      TIM_SetCompare4(TIM3,Positioning_Left);//PB1
      TIM_SetCompare3(TIM3,Positioning_Right);//PB0
      TIM_SetCompare1(TIM3,Lift);//PB4
      delay_ms(delay_time);//机械手运动延时
    }
  }
}

/**
  ************************************
  * @brief  水平舵机运动函数
  * @param  flat
  * @retval None
	************************************
*/
void Flat_Move(uint16_t flat)
{
  uint16_t max_variable = 0;
  max_variable = fabs((flat - Flat));
  while(max_variable--)
  {
    if(flat < Flat)
      Flat --;
    else if(flat > Flat)
      Flat ++;
    TIM_SetCompare1(TIM4,Flat);//PB6
    delay_ms(TURN_DELAY_TIME);//机械手运动延时
  }
}

/**
  ************************************
  * @brief  机械手底座运动函数
  * @param  left  right lift
  * @retval None
	************************************
*/
void Positioning(uint16_t left, uint16_t right, uint16_t delay_time)
{
  uint16_t max_variable = 0;
  max_variable = Cmp_Tw_16(fabs((left - Positioning_Left)), fabs((right - Positioning_Right)));
  if((left >= Positioning_Left) && (right <= Positioning_Right))//左加右减为上升
  {
    for(uint16_t i=0; i<max_variable; i++)
    {
      if(left >= Positioning_Left)
        Positioning_Left ++;
      if(right <= Positioning_Right)
        Positioning_Right --;
      TIM_SetCompare4(TIM3,Positioning_Left);//PB1
      TIM_SetCompare3(TIM3,Positioning_Right);//PB0
      delay_ms(delay_time);//机械手运动延时
    }
  }
  else if((left < Positioning_Left) && (right > Positioning_Right))//下降
  {
    for(uint16_t i=0; i<max_variable; i++)
    {
      if(left <= Positioning_Left)
        Positioning_Left --;
      if(right >= Positioning_Right)
        Positioning_Right ++;
      TIM_SetCompare4(TIM3,Positioning_Left);//PB1
      TIM_SetCompare3(TIM3,Positioning_Right);//PB0
      delay_ms(delay_time);//机械手运动延时
    }
  }
}

/**
  ************************************
  * @brief  机械手抓放物块
  * @param  clip
  * @retval None
	************************************
*/
void Catch_Put(uint16_t clip)
{
  for(uint16_t i=0; i<1000; i++)
  {
    if(clip < Clip)
      Clip --;
    else if(clip > Clip)
      Clip ++;
    TIM_SetCompare4(TIM4,Clip);//PB9
    delay_ms(1);
  }
}

/**
  ************************************
  * @brief  机械手循迹姿态
  * @param  None
  * @retval  底左：915   底右：1235   上1：1160  上2：1820  放：1600
	************************************
*/
void Attitude_Tracking(void)
{
	TIM_SetCompare4(TIM3,Tracking_Positioning_Left);//PB1
	TIM_SetCompare3(TIM3,Tracking_Positioning_Right);//PB0
	TIM_SetCompare1(TIM3,Tracking_Lift);//PB4
	TIM_SetCompare1(TIM4,Tracking_Flat);//PB6
	TIM_SetCompare4(TIM4,Tracking_Clip);//PB9
  Positioning_Left = Tracking_Positioning_Left;
  Positioning_Right = Tracking_Positioning_Right;
  Lift = Tracking_Lift;
  Flat = Tracking_Flat;
  Clip = Tracking_Clip;
}

/**
  ************************************
  * @brief  机械手举高姿态
  * @param  None
  * @retval  底左：915   底右：1235   上1：1160  上2：1820  放：1600
	************************************
*/
void Attitude_Highest(void)
{
	TIM_SetCompare4(TIM3,Highest_Positioning_Left);//PB1
	TIM_SetCompare3(TIM3,Highest_Positioning_Right);//PB0
	TIM_SetCompare1(TIM3,Highest_Lift);//PB4
	TIM_SetCompare1(TIM4,Highest_Flat);//PB6
  Positioning_Left = Highest_Positioning_Left;
  Positioning_Right = Highest_Positioning_Right;
  Lift = Highest_Lift;
  Flat = Highest_Flat;
  Clip = Put;
}

/**
  ************************************
  * @brief  机械手抓上面的物块
  * @param  None
  * @retval  底左：915   底右：1235   上1：1160  上2：1820  放：1600
	************************************
*/
void Attitude_Catch_On(void)
{
	TIM_SetCompare4(TIM3,Catch_On_Positioning_Left);//PB1
	TIM_SetCompare3(TIM3,Catch_On_Positioning_Right);//PB0
	TIM_SetCompare1(TIM3,Catch_On_Lift);//PB4
	TIM_SetCompare1(TIM4,Catch_On_Flat);//PB6
  Positioning_Left = Catch_On_Positioning_Left;
  Positioning_Right = Catch_On_Positioning_Right;
  Lift = Catch_On_Lift;
  Flat = Catch_On_Flat;
}

/**
  ************************************
  * @brief  机械手抓中间的物块
  * @param  None
  * @retval  底左：915   底右：1235   上1：1160  上2：1820  放：1600
	************************************
*/
void Attitude_Catch_In(void)
{
	TIM_SetCompare4(TIM3,Catch_In_Positioning_Left);//PB1
	TIM_SetCompare3(TIM3,Catch_In_Positioning_Right);//PB0
	TIM_SetCompare1(TIM3,Catch_In_Lift);//PB4
	TIM_SetCompare1(TIM4,Catch_In_Flat);//PB6
  Positioning_Left = Catch_In_Positioning_Left;
  Positioning_Right = Catch_In_Positioning_Right;
  Lift = Catch_In_Lift;
  Flat = Catch_In_Flat;
}

/**
  ************************************
  * @brief  机械手抓下面的物块
  * @param  None
  * @retval  底左：915   底右：1235   上1：1160  上2：1820  放：1600
	************************************
*/
void Attitude_Catch_Under(void)
{
	TIM_SetCompare4(TIM3,Catch_Under_Positioning_Left);//PB1
	TIM_SetCompare3(TIM3,Catch_Under_Positioning_Right);//PB0
	TIM_SetCompare1(TIM3,Catch_Under_Lift);//PB4
	TIM_SetCompare1(TIM4,Catch_Under_Flat);//PB6
  Positioning_Left = Catch_Under_Positioning_Left;
  Positioning_Right = Catch_Under_Positioning_Right;
  Lift = Catch_Under_Lift;
  Flat = Catch_Under_Flat;
}

/**
  ************************************
  * @brief  机械手过渡姿态
  * @param  None
  * @retval  底左：915   底右：1235   上1：1160  上2：1820  放：1600
	************************************
*/
void Transition(void)
{
	TIM_SetCompare4(TIM3,Transition_Under_Positioning_Left);//PB1
	TIM_SetCompare3(TIM3,Transition_Under_Positioning_Right);//PB0
	TIM_SetCompare1(TIM3,Transition_Under_Lift);//PB4
	TIM_SetCompare1(TIM4,Transition_Under_Flat);//PB6
  Positioning_Left = Transition_Under_Positioning_Left;
  Positioning_Right = Transition_Under_Positioning_Right;
  Lift = Transition_Under_Lift;
  Flat = Transition_Under_Flat;
}

/**
  ************************************
  * @brief  放置BCD点物块
  * @param  a：放置前的循迹时间   b：放置后出来的循迹时间
  * @retval None
	************************************
*/
void Put_BCD(uint16_t a)
{
	while(!Put_Left_Out || !Put_Right_Out)
		Tracking_Slow_Double();
	Tracking_Slow_Double_Distance(a);//慢速循迹一段距离
  Run_Stop();
  Catch_Put(Put);//张开爪子！！！
}

/**
  ************************************
  * @brief  放置A点物块
  * @param  a：100
  * @retval None
	************************************
*/
void Put_A(uint16_t a)
{
	while(!Put_Left_Mid || !Put_Right_Out)
		Tracking_Slow_Double();
	Tracking_Slow_Double_Distance(a);//慢速循迹一段距离
  Run_Stop();
  Catch_Put(Put);//张开爪子！！！
}

/**
  ************************************
  * @brief  放置E点物块
  * @param  a：100
  * @retval None
	************************************
*/
void Put_E(uint16_t a)
{
	while(!Put_Left_Out || !Put_Right_Mid)
		Tracking_Slow_Double();
  Tracking_Slow_Double_Distance(a);//慢速循迹一段距离
  Run_Stop();
  Catch_Put(Put);//张开爪子！！！
}

/**
  ************************************
  * @brief  机械手抓放物块函数
  * @param  a[]："Put" or "Catch"  b[]："On" or "In" or "Under"
  * @retval None
	************************************
*/
void Put_Catch(char a[], char b[])
{
  uint16_t max_variable=0;
  Flag_Manipulator = 0;//完成标志位置0
  if(!strcmp(a, "Catch")) //抓的情况！！！
  {
    if(!strcmp(b, "On")) //抓上面的
    {
      Catch_Put(Put);//张开爪子！！！
      //调整至过渡姿态
      Lift_Flat(Transition_On_Lift, Transition_On_Flat);//调整上面姿态
      Positioning(Transition_On_Positioning_Left, Transition_On_Positioning_Right, MANIPULATOR_DELAY_TIME);//底座舵机运动
      //调整至正常姿态
      max_variable = Return_All("On");
      while(max_variable--)
        All_Move("On", MANIPULATOR_DELAY_TIME);
      
      Catch_Put(Catch);//抓！！！
      Flag_Manipulator = 1;//标记完成
    }
    else if(!strcmp(b, "In")) //抓中间的
    {
      Catch_Put(Put);//张开爪子！！！
      //调整至过渡姿态
      Lift_Flat(Transition_In_Lift, Transition_In_Flat);//调整上面姿态
      Positioning(Transition_In_Positioning_Left, Transition_In_Positioning_Right, MANIPULATOR_DELAY_TIME);//底座舵机运动
      //调整至正常姿态
      max_variable = Return_All("In");
      while(max_variable--)
        All_Move("In", MANIPULATOR_DELAY_TIME);
      
      Catch_Put(Catch);//抓！！！
      Flag_Manipulator = 1;//标记完成
    }
    else if(!strcmp(b, "Under")) //抓下面的！！！
    {
      Catch_Put(Put);//张开爪子！！！
      //调整至过渡姿态
      Lift_Flat(Transition_Under_Lift, Transition_Under_Flat);//调整上面姿态至过渡姿态
      Positioning(Transition_Under_Positioning_Left, Transition_Under_Positioning_Right, MANIPULATOR_DELAY_TIME);//底座舵机运动
      //调整至正常姿态
      max_variable = Return_All("Under");
      while(max_variable--)
        All_Move("Under", MANIPULATOR_DELAY_TIME);
      
      Catch_Put(Catch);//抓！！！
      Flag_Manipulator = 1;//标记完成
    }
    else if(!strcmp(b, "Highest"))
    {
      Positioning_Lift(Highest_Positioning_Left, Highest_Positioning_Right, Highest_Lift, TURN_DELAY_TIME);//调整为举高姿态
      Flat_Move(Highest_Flat);//调整为举高水平度
      Flag_Manipulator = 1;//标记完成
    }
  }
  else if(!strcmp(a, "Put")) //放的情况！！！
  {
    if(!strcmp(b, "On")) //放上面的
    {
      Lift_Flat(Catch_On_Lift, Catch_On_Flat);//调整上面姿态
      Positioning(Catch_On_Positioning_Left, Catch_On_Positioning_Right, MANIPULATOR_DELAY_TIME);//底座舵机运动
      Catch_Put(Put);//放！！！
      Flag_Manipulator = 1;//标记完成
    }
    else if(!strcmp(b, "In")) //放中间的
    {
      Lift_Flat(Catch_In_Lift, Catch_In_Flat);//调整上面姿态
      Positioning(Catch_In_Positioning_Left, Catch_In_Positioning_Right, MANIPULATOR_DELAY_TIME);//底座舵机运动
      Catch_Put(Put);//放！！！
      Flag_Manipulator = 1;//标记完成
    }
    else if(!strcmp(b, "Under")) //放下面的
    {
      Lift_Flat(Catch_Under_Lift, Catch_Under_Flat);//调整上面姿态
      Positioning(Catch_Under_Positioning_Left, Catch_Under_Positioning_Right, MANIPULATOR_DELAY_TIME);//底座舵机运动
      Catch_Put(Put);//放！！！
      Flag_Manipulator = 1;//标记完成
    }
    else if(!strcmp(b, "Tracking"))
    {
      Lift_Flat(Tracking_Lift, Tracking_Flat);//调整上面姿态
      Positioning(Tracking_Positioning_Left, Tracking_Positioning_Right, MANIPULATOR_DELAY_TIME);//底座舵机运动
      Catch_Put(Catch);//抓！！！
      Flag_Manipulator = 1;//标记完成
    }
    else if(!strcmp(b,"Special"))
    {
//      Catch_Put(Put);//抓！！！
      //调整至过渡姿态
      Lift_Flat(Transition_Under_Lift, Transition_Under_Flat);//调整上面姿态
      Positioning(Transition_Under_Positioning_Left, Transition_Under_Positioning_Right, MANIPULATOR_DELAY_TIME);//底座舵机运动
      Flag_Manipulator = 1;//标记完成
    }
  }
}

/**
  ************************************
  * @brief  机械手全部一起动
  * @param  None
  * @retval None
	************************************
*/
void All_Move(char a[], uint16_t b)
{
  uint16_t left, right, lift, flat;
  if(!strcmp(a, "On"))
  {
    left = Catch_On_Positioning_Left;
    right = Catch_On_Positioning_Right;
    lift = Catch_On_Lift;
    flat = Catch_On_Flat;
  }
  else if(!strcmp(a, "In"))
  {
    left = Catch_In_Positioning_Left;
    right = Catch_In_Positioning_Right;
    lift = Catch_In_Lift;
    flat = Catch_In_Flat;
  }
  else if(!strcmp(a, "Under"))
  {
    left = Catch_Under_Positioning_Left;
    right = Catch_Under_Positioning_Right;
    lift = Catch_Under_Lift;
    flat = Catch_Under_Flat;
  }
  else if(!strcmp(a, "Highest"))
  {
    left = Highest_Positioning_Left;
    right = Highest_Positioning_Right;
    lift = Highest_Lift;
    flat = Highest_Flat;
  }
  if(left > Positioning_Left)
    Positioning_Left ++;
  else if(left < Positioning_Left)
    Positioning_Left --;
  if(right < Positioning_Right)
    Positioning_Right --;
  else if(right > Positioning_Right)
    Positioning_Right ++;
  if(lift >= Lift)
    Lift ++;
  else
    Lift --;
  if(flat <= Flat)
    Flat --;
  else
    Flat ++;
	TIM_SetCompare4(TIM3,Positioning_Left);//PB1
	TIM_SetCompare3(TIM3,Positioning_Right);//PB0
	TIM_SetCompare1(TIM3,Lift);//PB4
	TIM_SetCompare1(TIM4,Flat);//PB6
  delay_ms(b);//机械手运动延时
}

/**
  ************************************
  * @brief  同步电机机械手
  * @param  None
  * @retval None
	************************************
*/
void Run_Manipulator(uint8_t num, char c[], char a[], char b[])
{
  uint16_t max_variable_run = 0;
  /**************判断位置******************/
  if(!strcmp(a, "Put"))
  {
    if(!strcmp(b, "On"))
      Positioning(Put_On_Positioning_Left, Put_On_Positioning_Right, TURN_DELAY_TIME);
    else if(!strcmp(b, "In"))
      Positioning(Put_In_Positioning_Left, Put_In_Positioning_Right, TURN_DELAY_TIME);
    else if(!strcmp(b, "Under"))
      Positioning(Put_Under_Positioning_Left, Put_Under_Positioning_Right, TURN_DELAY_TIME);
    else if(!strcmp(b, "Tracking"))
      Positioning(Put_Tracking_Positioning_Left, Put_Tracking_Positioning_Right, TURN_DELAY_TIME);    
  }
  else if(!strcmp(a, "Catch"))
  {
    if(!strcmp(b, "In"))
      Positioning(Put_In_Positioning_Left, Put_In_Positioning_Right, TURN_DELAY_TIME);
  }
  /*******************旋转直立*********************/
  //取四个值中的最大值
  max_variable_run = Return_All("Highest");  
  //数线
  while(num--)
  {
    if(!strcmp(c, "Left"))
    {
      AntiClockwise();
      delay_ms(250);
//      while(Run_Behind_R) //出黑线
//      {
//        AntiClockwise();
//        if(max_variable_run > 0)
//        {
//          All_Move("Highest", TURN_DELAY_TIME);
//          max_variable_run--;
//        }
//      }
//      delay_ms(10);
      while(!Run_Behind_R) //进黑线
      {
        AntiClockwise();
        if(max_variable_run > 0)
        {
          All_Move("Highest", TURN_DELAY_TIME);
          max_variable_run--;
        }
      }
      delay_ms(10);
      while(Run_Behind_R) //出黑线
      {
        AntiClockwise();
        if(max_variable_run > 0)
        {
          All_Move("Highest", TURN_DELAY_TIME);
          max_variable_run--;
        }
      }
    }
    else if(!strcmp(c, "Right"))
    {
      Clockwise();
      delay_ms(250);
//      while(Run_Behind_L) //出黑线
//      {
//        Clockwise();
//        if(max_variable_run > 0)
//        {
//          All_Move("Highest", TURN_DELAY_TIME);
//          max_variable_run--;
//        }
//      }
//      delay_ms(10);
      while(!Run_Behind_L) //进黑线
      {
        Clockwise();
        if(max_variable_run > 0)
        {
          All_Move("Highest", TURN_DELAY_TIME);
          max_variable_run--;
        }
      }
      delay_ms(10);
      while(Run_Behind_L) //出黑线
      {
        Clockwise();
        if(max_variable_run > 0)
        {
          All_Move("Highest", TURN_DELAY_TIME);
          max_variable_run--;
        }
      }
    }
  }
  Run_Stop();//停车
  //如果停下来还没到指定位置则继续运动
  while(max_variable_run > 0)
  {
    All_Move("Highest", TURN_DELAY_TIME);
    max_variable_run--;
  }
}
