/**
  ************************************
  * @file    test.c
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.10.13
  * @brief   ���Ժ���
	************************************
*/

#include "test.h"
#include "string.h"

//����ȫ�ֱ���
extern uint16_t Positioning_Left;
extern uint16_t Positioning_Right;
extern uint16_t Lift;
extern uint16_t Flat;
extern uint16_t Clip;
extern uint16_t Flag;
extern uint16_t Time;
extern uint8_t Flag_Manipulator;

//����붨��
#define MANIPULATOR_ON  1

/**
  ************************************
  * @brief  �������->ʮ��->���->ʮ��
  * @param  None
  * @retval None
	************************************
*/
void Test_Start_Cross(void)
{
  while(1)
  {
    Start_Cross();//�������ߵ�ʮ��·��
    Run_Stop();
    delay_ms(1600);
    Turn_Left_ACE_Angle(0, "On");//��Ի�ɫ
    Run_Stop();
    Turn_Left_ACE_Angle(3,"Off");//������
    delay_ms(1500);
    Tracking_Slow_Distance(1500);//����ѭ��һ�ξ���
    Tracking_Slow_Double_Distance(500);//����ѭ��һ�ξ���
    Run_Stop();
    Turn_Right_180();
  }
}

/**
  ************************************
  * @brief  ������һ��ֵ��������ֵ�ı仯
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
      Tracking_Slow_Double_Distance(Time);//����ѭ��һ�ξ���
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
  * @brief  ��λ�����Ի�е��
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
  * @brief  ���Ի�е��
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
  * @brief  OLED��ʾ��������ֵ
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
  * @brief  ���Ի�е��
  * @param  None
  * @retval None
	************************************
*/
void Test_Manipulator_Go_Cross(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  Tracking_Slow_Distance(1400);//����ѭ��һ�ξ���
	Go_Cross();//�ߵ�ʮ��·��
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(1500);
  #endif
  Catch_Put(Put);//�ſ�צ�ӣ�����
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Lift_Flat(Transition_Under_Lift, Transition_Under_Flat);//����������̬��������̬
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Positioning(Transition_Under_Positioning_Left, Transition_Under_Positioning_Right, TURN_DELAY_TIME);//��������˶�
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Lift_Flat(Catch_Under_Lift, Catch_Under_Flat);//����������̬���ײ���̬
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
}

/**
  ************************************
  * @brief  ���Ե������
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
  * @brief  ��
  * @param  None
  * @retval None
	************************************
*/
void Rising_Filling(void)
{
//  Put_Catch("Catch", "On");
  uint16_t max_variable_run;
  Catch_Put(Put);
  Lift_Flat(Transition_In_Lift, Transition_In_Flat);//����������̬
  Positioning(Transition_In_Positioning_Left, Transition_In_Positioning_Right, TURN_DELAY_TIME);//��������˶�
  max_variable_run = Return_All("In");
  while(max_variable_run--)
    All_Move("In", TURN_DELAY_TIME);
  Catch_Put(Catch);
  Put_Catch("Catch", "Highest");
}

/**
  ************************************
  * @brief  ����R_5()�е����ź�
  * @param  None
  * @retval None
	************************************
*/
void Test_R5_2(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************���ź�*******************/
  //�зŵ�һ��
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(1, "On");//�����ɫ
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Put_Catch("Catch", "On");//�е�һ��
  Run_Manipulator(1, "Left", "Catch", "On");//���C��
  Tracking_Fast_Distance(3600);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle_Front(2, "On");//�����ɫ
  Put_Catch("Catch", "In");//ץ�ڶ���
  Run_Manipulator(1, "Left", "Catch", "In");//���C��
  Tracking_Fast_Distance(4100);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "In");//������
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle_Front(2, "On");//�����ɫ
  Put_Catch("Catch", "Under");//ץ������
  Run_Manipulator(1, "Left", "Catch", "Under");//���C��
  Tracking_Fast_Distance(4100);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵ�����
  Run_Manipulator(1, "Left", "Put", "On");//������
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
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************C��BD*******************/
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "Under");
  Put_Catch("Catch", "Highest");//�ŵ�һ��
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//�ŵڶ���
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "Under");//�е�����
  Put_Catch("Catch", "Highest");//�е�����
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "On");
  Put_Catch("Catch", "Highest");//�ŵ�һ��
}

/**
  ************************************
  * @brief  ����R_5()��C��B
  * @param  None
  * @retval None
	************************************
*/
void Text_R5_1(void)
{

}

/**
  ************************************
  * @brief  ����R_2()��A��C
  * @param  None
  * @retval None
	************************************
*/
void R2_3_test(void)
{
  
  /******************A��C***********************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif 
  Turn_Left_ACE_Angle(2, "On");//������
  
  Tracking_Fast_Distance(4800);//����ѭ��һ�ξ���
//  Tracking_Slow_Distance(800);//����ѭ��һ�ξ���
  Turn_Left_180();
  Tracking_Fast_Distance(2500);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  
  Turn_Left_ACE_Angle(1, "On");//���E��
  
  //A��C
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");
  Turn_Right_ACE_Angle(1, "Off");//���C��
  
  Put_Catch("Put", "Under"); //�ŵ�һ��
  Put_Catch("Catch", "Highest");
  Turn_Left_ACE_Angle(1, "Off");//���A��
  
  Put_Catch("Catch", "In"); //�еڶ���
  Put_Catch("Catch", "Highest");
  Turn_Right_ACE_Angle(1, "Off");//���C��
  
  Put_Catch("Put", "In"); //�ŵڶ���
  Put_Catch("Catch", "Highest");
  Turn_Left_ACE_Angle(1, "Off");//���A��
  
  Put_Catch("Catch", "Under"); //�е�����
  Put_Catch("Catch", "Highest");
  
  //�ŵ�һ��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_A(80);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//���A��
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//���C��
  
  Put_Catch("Catch", "In");//�еڶ���
  Run_Manipulator(1, "Left", "Catch", "In");//���A��
  
  Tracking_Fast_Distance(3900);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "In");//���A��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//���C��
  
  Put_Catch("Catch", "Under");//�еڶ���
  Run_Manipulator(1, "Left", "Catch", "Under");//���A��
  
  Tracking_Fast_Distance(3900);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "On");//���A��
}

/**
  ************************************
  * @brief  ����R_2()��E��C
  * @param  None
  * @retval None
	************************************
*/
void R2_2_test(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /**********************E��C****************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle_Front(0, "On");//���E��
  Tracking_Fast_Distance(4800);//����ѭ��һ�ξ���
//  Tracking_Slow_Distance(800);//����ѭ��һ�ξ���
  Turn_Left_180();
  Tracking_Fast_Distance(2500);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(1, "On");//���E��
  
  //E��C
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Left_ACE_Angle(1, "Off");
  Put_Catch("Put", "Under");
  Put_Catch("Catch", "Highest");//�ŵ�һ��
  
  Turn_Right_ACE_Angle(1, "Off");
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Left_ACE_Angle(1, "Off");
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//�ŵڶ���
  
  Turn_Right_ACE_Angle(1, "Off");
  Put_Catch("Catch", "Under");//�е�����
  Put_Catch("Catch", "Highest");//�е�����
  
  //�ŵ�һ��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_E(60);
  Run_Stop();
  Run_Manipulator(1, "Right", "Put", "Tracking");//���A��
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(1, "On");//���C��
  
  Put_Catch("Catch", "In");//�еڶ���
  Run_Manipulator(1, "Right", "Catch", "In");//���E��
  
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Right", "Put", "In");//���A��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(1, "On");//���C��
  
  Put_Catch("Catch", "Under");//�е�����
  Run_Manipulator(1, "Right", "Catch", "Under");//���E��
  
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵ�����
  Run_Manipulator(1, "Right", "Put", "On");//���A��
}

/**
  ************************************
  * @brief  ��������ͣ��������
  * @param  None
  * @retval None
	************************************
*/
void Test_Under(void)
{
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  while(!Run_Under_L || !Run_Under_R) 
    Run_Slow();
  Run_Stop();
}

/**
  ************************************
  * @brief  ��������ͣ��������
  * @param  None
  * @retval None
	************************************
*/
void R2_1_Test(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************C��BD*******************/
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "Under");
  Put_Catch("Catch", "Highest");//�ŵ�һ��
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//�ŵڶ���
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "Under");//�е�����
  Put_Catch("Catch", "Highest");//�е�����
  
  /*******************B��C***********************/
  //�ŵ�һ��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_BCD(60);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front_Delay(2, "On",780,1);//���A��
  Turn_Right_ACE(1, "Off",1,"Off",1);//���B��
  
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Right_ACE(1, "Off",1,"Off",1);//���C��
  
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "In");//������
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front_Delay(2, "On",780,1);//���A��
  Turn_Right_ACE(1, "Off",1,"Off",1);//���B��
  
  Put_Catch("Catch", "Under");//�е�����
  Put_Catch("Catch", "Highest");//�е�����
  
  Turn_Right_ACE(1, "Off",1,"Off",1);//���C��
  
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵ�����
  Run_Manipulator(1, "Left", "Put", "On");//������
}

/**
  ************************************
  * @brief  ����������ʱ
  * @param  None
  * @retval None
	************************************
*/
void Test_Turn_Delay(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************����********************/
  Run_Line_Fast(1000);
  
  /*******************C��BD*******************/
  Tracking_Fast_Distance(4200);//����ѭ��һ�ξ���
  
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Slow();

  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Left_ACE(1, "Off", 25,"Off",1);
  Put_Catch("Put", "Under");
  Put_Catch("Catch", "Highest");//�ŵ�һ��
  
}

/**
  ************************************
  * @brief  ����תȦ��ʱ
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
  * @brief  ����D��C��B��C
  * @param  None
  * @retval None
	************************************
*/
void Test_Run_C_B_C(void)
{
//  /*********************��������*******************************/
//  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
//    Tracking_Fast();
//  
//  Turn_Left_ACE_Angle_Front_Delay(1, "On",690,1);//������
//  Tracking_Fast_Distance(4500);//����ѭ��һ�ξ���
//  Turn_Left_180();
  
  /**********************C��B****************************/
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Left_ACE(1, "Off",20,"Off",1);
  Put_Catch("Put", "Under");//�ŵ�һ��
  Put_Catch("Put", "Special");//�ŵ�һ��
  Put_Catch("Catch", "Highest");//�ص��ٸ���̬
  
  Turn_Right_ACE(1, "Off",15,"Off",1);
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//�ŵڶ���
  
  Turn_Right_ACE(1, "Off",10,"Off",1);
  Put_Catch("Catch", "Under");//�е�����
  Put_Catch("Catch", "Highest");//�е�����
  
  /*******************B��C***********************/
  //�ŵ�һ��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_BCD(60);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front_Delay(2, "On",810,1);//���A��
  Turn_Right_ACE(1, "Off",1,"On",20);//���B��
  
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Right_ACE(1, "Off",1,"Off",20);//���C��
  
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "In");//������
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front_Delay(2, "On",770,1);//���A��
  Turn_Right_ACE(1, "Off",1,"On",15);//���B��
  
  Put_Catch("Catch", "Under");//�е�����
  Put_Catch("Catch", "Highest");//�е�����
  
  Turn_Right_ACE(1, "Off",1,"Off",1);//���C��
  
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1000);
  #endif
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵ�����
  Run_Manipulator(1, "Left", "Put", "On");//������
}
