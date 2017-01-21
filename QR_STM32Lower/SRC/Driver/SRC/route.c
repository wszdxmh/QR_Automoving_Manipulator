/**
  ************************************
  * @file    route.c
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.20
  * @brief   ·�߹滮
	************************************
*/

#include "route.h"

/**
  ************************************
  * @brief  ����--A����  C����  E����
  * @param  None
  * @retval None
	************************************
*/
void R_1(void) //��ʱ7��05��
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************�쵽���*******************/
  //�зŵ�һ��
  Tracking_Fast_Distance(2000);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();

  Put_Catch("Catch", "On");//�е�һ��
  Run_Manipulator(3,"Left", "Catch", "On");
  Tracking_Fast_Distance(2000);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(800);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Under");//�ŵ�һ��
  Run_Manipulator(1,"Left", "Put", "Under");
  
  //�зŵڶ���
  Tracking_Fast_Distance(2500);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Put_Catch("Catch", "In");//�еڶ���
  Run_Manipulator(3, "Left", "Catch", "In");//������
  Tracking_Fast_Distance(2600);//����ѭ��һ�ξ���
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
  Run_Stop();
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1,"Left", "Put", "In");//������
  
  //�зŵ�����
  Tracking_Fast_Distance(2500);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Put_Catch("Catch", "Under");//�е�����
  Run_Manipulator(3, "Left", "Catch", "Under");//������
  Tracking_Fast_Distance(2600);//����ѭ��һ�ξ���
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
  Run_Stop();
  Put_Catch("Put", "On");//�ŵ�����
  Run_Manipulator(1,"Left", "Put", "On");//������
  
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
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
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
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
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
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
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
  
  /*******************�Ʒ���*******************/
  //�зŵ�һ��
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle_Front(2, "On");//��Ի�ɫ
  Put_Catch("Catch", "On");//�е�һ��
  Run_Manipulator(4, "Left", "Put", "On");//������
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_E(50);
  Run_Stop();
  Run_Manipulator(1, "Right", "Put", "Tracking");//������
  
  //�зŵڶ���
  Tracking_Fast_Distance(3200);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Slow();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(0, "On");//��Ի�ɫ
  Put_Catch("Catch", "In");//�еڶ���
  Run_Manipulator(4, "Left", "Catch", "In");//�����ɫ
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
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
  Run_Stop();
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Right", "Put", "In");//������
  
  //�зŵ�����
  Tracking_Fast_Distance(3200);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Slow();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(0, "On");//��Ի�ɫ
  Put_Catch("Catch", "Under");//�е�����
  Run_Manipulator(4, "Left", "Catch", "Under");//�����ɫ
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
  Run_Stop();
  Put_Catch("Put", "On");//�ŵڶ���
  Run_Manipulator(1, "Right", "Put", "On");//������
  
  /*******************��Ż�*******************/
  //�зŵ�һ��
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(2, "On");//������
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Tracking_Fast_Distance(2600);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Catch", "On");//����������
  Run_Manipulator(1, "Left", "Catch", "On");//������
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//��Ի�ɫ
  Tracking_Fast_Distance(3700);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_A(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�еڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(2, "On");//������
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Tracking_Fast_Distance(2600);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Run_Stop();
  Put_Catch("Catch", "In");//���м�����
  Run_Manipulator(1, "Left", "Catch", "In");//���C��
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//��Ի�ɫ
  Tracking_Fast_Distance(3900);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Run_Stop();
  Put_Catch("Put", "In");//���м�����
  Run_Manipulator(1, "Left", "Put", "In");//���C��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(2, "On");//������
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Tracking_Fast_Distance(2600);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Catch", "Under");//����������
  Run_Manipulator(1, "Left", "Catch", "Under");//���C��
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//��Ի�ɫ
  Tracking_Fast_Distance(3700);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(700);//����ѭ��һ�ξ���
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//����������
  Run_Manipulator(1, "Left", "Put", "On");//���E��
  
  /*******************�س�*******************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(2, "On");//������
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  while(!Run_Front_L || !Run_Front_R) //����ѭ�������
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//ͣ��������
}

/**
  ************************************
  * @brief  �෽��--A����  C����  E����
  * @param  None
  * @retval None
	************************************
*/
void R_2(void) //��ʱ4��35��
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************����********************/
  Run_Line_Fast(1000);
  
  /*******************C��BD*******************/
//  Tracking_Fast_Distance(5000);//����ѭ��һ�ξ���
  
  while(!Run_Front_L || !Run_Front_R)
    Tracking_Fast();

  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Left_ACE(1, "Off", 20,"Off",1);
  Put_Catch("Put", "Special");
  Put_Catch("Catch", "Highest");//�ŵ�һ��
  
  Turn_Right_ACE(1, "Off", 1,"Off",1);
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Left_ACE(1, "Off",15,"Off",1);
  Put_Catch("Put", "In");
  Put_Catch("Catch", "Highest");//�ŵڶ���
  
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "Under");//�е�����
  Put_Catch("Catch", "Highest");//�е�����
  
  Turn_Left_ACE(1, "Off",15,"Off",1);
  Put_Catch("Put", "On");
  Put_Catch("Catch", "Highest");//�ŵ�һ��
  
  /*******************���ź�*******************/
  //�зŵ�һ��
  Turn_Right_ACE_Angle(2, "Off");//�����ɫ
  Run_Stop();
  #if DELAY_SWITCH
    delay_ms(100);
  #endif
  Put_Catch("Catch", "On");//�е�һ��
  Run_Manipulator(1, "Left", "Catch", "On");//���C��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
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
  Turn_Left_ACE_Angle_Front_Delay(2, "On",780,1);//���E��
  Put_Catch("Catch", "In");//ץ�ڶ���
  Run_Manipulator(1, "Left", "Catch", "In");//���C��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
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
  Turn_Left_ACE_Angle_Front_Delay(2, "On",780,1);//���E��
  Put_Catch("Catch", "Under");//ץ������
  Run_Manipulator(1, "Left", "Catch", "Under");//���C��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
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
  
  /*******************�Ʒ���*******************/
  
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
  
  
  //�зŵ�һ��
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle_Front(1, "On");//���A��
  Put_Catch("Catch", "On");//�е�һ��
  Run_Manipulator(2, "Right", "Put", "On");//���E��
  Tracking_Fast_Distance(3900);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_E(50);
  Run_Stop();
  Run_Manipulator(1, "Right", "Put", "Tracking");//������
  
  //�зŵڶ���
  Tracking_Fast_Distance(3200);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Slow();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(0, "On");//��Ի�ɫ
  Put_Catch("Catch", "In");//�еڶ���
  Run_Manipulator(4, "Left", "Catch", "In");//�����ɫ
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
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
  Run_Stop();
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Right", "Put", "In");//������
  
  //�зŵ�����
  Tracking_Fast_Distance(3200);//����ѭ��һ�ξ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Slow();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(0, "On");//��Ի�ɫ
  Put_Catch("Catch", "Under");//�е�����
  Run_Manipulator(4, "Left", "Catch", "Under");//�����ɫ
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
  Run_Stop();
  Put_Catch("Put", "On");//�ŵڶ���
  Run_Manipulator(1, "Right", "Put", "On");//������
  
  /*******************���Ż�*******************/
  //�зŵ�һ��
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(0, "On");//������
  Turn_Right_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�еڶ���
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Tracking_Fast_Distance(3700);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Put_A(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�еڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//���C��
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "In");//�е�һ��
  Put_Catch("Catch", "Highest");//�еڶ���
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Tracking_Fast_Distance(4100);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Run_Stop();
  Put_Catch("Put", "In");//���м�����
  Run_Manipulator(1, "Left", "Put", "In");//���C��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Left_ACE_Angle(1, "On");//������
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Put_Catch("Catch", "Under");//�е�����
  Put_Catch("Catch", "Highest");//�е�����
  Turn_Left_ACE(1, "Off",1,"Off",1);
  Tracking_Fast_Distance(3600);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(700);//����ѭ��һ�ξ���
  Run_Stop();
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//����������
  Run_Manipulator(1, "Left", "Put", "On");//���E��
  
  /*******************�س�*******************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  Turn_Right_ACE_Angle(2, "On");//������
  #if DELAY_SWITCH
    Run_Stop();
    delay_ms(1600);
  #endif
  while(!Run_Front_L || !Run_Front_R) //����ѭ�������
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//ͣ��������
}

/**
  ************************************
  * @brief  �෽��--A����  C����  E����
  * @param  None
  * @retval None
	************************************
*/
void R_3(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************����********************/
  Run_Line_Fast(1000);
  
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
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
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
  Turn_Right_ACE(1, "Off",1,"On",40);//���B��
  
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Right_ACE(1, "Off",1,"Off",30);//���C��
  
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
  Turn_Right_ACE(1, "Off",1,"On",30);//���B��
  
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
  
  /********************E��C********************************/
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Left_ACE_Angle(1, "Off");
  Put_Catch("Put", "Under");
  Put_Catch("Put", "Special");//�ŵ�һ��
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
  
  /******************C��E******************************/
  //�ŵ�һ��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
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
  
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
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
  Run_Manipulator(1, "Right", "Put", "On");//���A��
  
  
  /*******************A��C******************************/
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");
  Turn_Right_ACE_Angle(1, "Off");//���C��
  
  Put_Catch("Put", "Under"); //�ŵ�һ��
  Put_Catch("Put", "Special");//�ŵ�һ��
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
  
  Tracking_Fast_Distance(4100);//����ѭ��һ�ξ���
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
  
  Tracking_Fast_Distance(4100);//����ѭ��һ�ξ���
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
  
  /**********************�س�***************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Turn_Right_ACE_Angle(1, "On");//��Ժ�ɫ
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//ͣ��������
}

/**
  ************************************
  * @brief  �෽��--A����  C����  E����
  * @param  None
  * @retval None
	************************************
*/
void R_4(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************����********************/
  Run_Line_Fast(1000);
  
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  /************************A��B*******************************/
  
  //�зŵ�һ��
  Turn_Left_ACE_Angle(1, "On"); //���A��
  Run_Stop();
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Right_ACE(1, "Off", 1,"Off",1); //����B��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
//  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Right_ACE_Angle_Front_Delay(3, "On",690,30);//���A��
  Put_Catch("Catch", "In");//ץ�ڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  Turn_Right_ACE(1, "Off", 1,"Off",1); //����B��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "In"); //���ʮ��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Turn_Right_ACE_Angle_Front_Delay(3, "On",690,30);//���A��
  Put_Catch("Catch", "Under");//ץ������
  Put_Catch("Catch", "Highest");//�ص��ٸ���̬
  Turn_Right_ACE(1, "Off", 1,"Off",1); //����B��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵ�����
  Run_Manipulator(1, "Left", "Put", "On"); //���ʮ��
  
  /*******************E��D************************/
  
  //�зŵ�һ��
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",690,1);//���E��
  Run_Stop();
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�ص��ٸ�״̬
  Turn_Left_ACE(1, "Off", 1,"Off",1); //����B��
  
  Tracking_Fast_Distance(4000);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//���ʮ��
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(3, "On",690,1);//���E��
  Put_Catch("Catch", "In");//ץ�ڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  Turn_Left_ACE(1, "Off", 1,"Off",1); //����D��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "In"); //���ʮ��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(3, "On",690,1);//���E��
  Put_Catch("Catch", "Under");//ץ������
  Put_Catch("Catch", "Highest");//�ص��ٸ���̬
  Turn_Left_ACE(1, "Off", 1,"Off",1); //����D��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵ�����
  Run_Manipulator(1, "Left", "Put", "On"); //���ʮ��
  
  /*********************��������*******************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",690,1);//������
  Tracking_Fast_Distance(4500);//����ѭ��һ�ξ���
  Turn_Left_180();
  
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
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
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
  Turn_Right_ACE(1, "Off",1,"On",35);//���B��
  
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Right_ACE(1, "Off",1,"Off",30);//���C��
  
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
  Turn_Right_ACE(1, "Off",1,"On",20);//���B��
  
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
  
  /**********************�س�***************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//ͣ��������
}

/**
  ************************************
  * @brief  �෽��--A����  C����  E����
  * @param  None
  * @retval None
	************************************
*/
void R_5(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************����********************/
  Run_Line_Fast(1000);
  
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
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Put_BCD(60);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();

  Turn_Left_ACE_Angle_Front(0,"On");
  Tracking_Fast_Distance(4000);//����ѭ��һ�ξ���
  Turn_Left_180();
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Turn_Left_ACE(1, "On",20,"Off",10);//����B��
  
  Put_Catch("Catch", "In");//�еڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  
  Turn_Right_ACE(1, "Off",1,"Off",30);//���C��
  
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

  Turn_Left_ACE_Angle_Front(0,"On");
  Tracking_Fast_Distance(4000);//����ѭ��һ�ξ���
  Turn_Left_180();
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Turn_Left_ACE(1, "On",20,"Off",10);//����B��
  
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
  
  /********************E��C********************************/
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Left_ACE_Angle(1, "Off");
  Put_Catch("Put", "Under");
  Put_Catch("Put", "Special");//�ŵ�һ��
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
  
  /******************C��E******************************/
  //�ŵ�һ��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
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
  
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
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
  Run_Manipulator(1, "Right", "Put", "On");//���A��
  
  
  /*******************A��C******************************/
  
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Turn_Right_ACE_Angle(0, "On");//���A��
  
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");
  Turn_Right_ACE_Angle(1, "Off");//���C��
  
  Put_Catch("Put", "Under"); //�ŵ�һ��
  Put_Catch("Put", "Special");//�ŵ�һ��
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
  
  Tracking_Fast_Distance(4100);//����ѭ��һ�ξ���
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
  
  Tracking_Fast_Distance(4100);//����ѭ��һ�ξ���
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
  Run_Manipulator(2, "Left", "Put", "On");//���A��
  
  /**********************�س�***************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Turn_Right_ACE_Angle(1, "On");//��Ժ�ɫ
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//ͣ��������
}

/**
  ************************************
  * @brief  �෽��--A����  C����  E����
  * @param  None
  * @retval None
	************************************
*/
void R_6(void)
{
  Attitude_Highest();//��ʼ״̬Ϊ�ٸ�״̬
  Catch_Put(Put);//�ſ�צ�ӣ�����
  
  /*******************����********************/
  Run_Line_Fast(1000);
  
  /********************C��D*****************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  //�зŵ�һ��
  Turn_Left_ACE_Angle(0, "On");//��Ժ�ɫ
  Run_Stop();
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  
  Turn_Right_ACE(1, "Off", 1,"Off",1); //����D��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
//  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Right_ACE_Angle_Front_Delay(2, "On",690,30);//���A��
  Put_Catch("Catch", "In");//ץ�ڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  Turn_Right_ACE(1, "Off", 1,"Off",1); //����D��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "In"); //���ʮ��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Right_ACE_Angle_Front_Delay(2, "On",690,30);//���A��
  Put_Catch("Catch", "Under");//ץ������
  Put_Catch("Catch", "Highest");//�е�����
  Turn_Right_ACE(1, "Off", 1,"Off",1); //����D��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵ�����
  Run_Manipulator(1, "Left", "Put", "On"); //���ʮ��
  
  /*****************�����߹���****************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",690,30);//���A��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Turn_Left_180();
  
  //�зŵ�һ��
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Turn_Right_ACE_Angle(1, "On");//���E��
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  Turn_Left_ACE_Angle(1, "On");//���C��
  Turn_Left_ACE(1, "On",20,"Off",10);//����B��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
//  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_BCD(50);
  Run_Stop();
  Run_Manipulator(1, "Left", "Put", "Tracking");//������
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",770,20);//���E��
  Put_Catch("Catch", "In");//ץ�ڶ���
  Put_Catch("Catch", "Highest");//�еڶ���
  Turn_Left_ACE_Angle(1, "On");//���C��
  Turn_Left_ACE(1, "On",20,"Off",10);//����B��
  Tracking_Fast_Distance(4000);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "In"); //���ʮ��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Left_ACE_Angle_Front_Delay(1, "On",740,10);//���E��
  Put_Catch("Catch", "Under");//ץ������
  Put_Catch("Catch", "Highest");//�е�����
  Turn_Left_ACE_Angle(1, "On");//���C��
  Turn_Left_ACE(1, "On",20,"Off",10);//����B��
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵڶ���
  Run_Manipulator(1, "Left", "Put", "On"); //���ʮ��
  
  /**********************��������****************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  Turn_Right_ACE_Angle_Front_Delay(1, "On",690,30);//������
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Turn_Left_180();
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  
  /*************************A��E*******************************/
  //�зŵ�һ��
  Turn_Left_ACE_Angle(1, "On");//���A��
  Put_Catch("Catch", "On");//�е�һ��
  Put_Catch("Catch", "Highest");//�е�һ��
  Turn_Right_ACE_Angle(2, "On");//���E��
  Tracking_Fast_Distance(3500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_Catch("Put", "Tracking");//ѭ����̬
//  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();
  Put_E(50);
  Run_Stop();
  Run_Manipulator(1, "Right", "Put", "Tracking");//������
  
  //�зŵڶ���
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();

  Turn_Right_ACE_Angle(0, "On");//���C��
  
  Put_Catch("Catch", "In");//�еڶ���
  Run_Manipulator(2, "Right", "Catch", "In");//���E��
  
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "In");//�ŵڶ���
  Run_Manipulator(1, "Right", "Put", "In"); //���ʮ��
  
  //�зŵ�����
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();

  Turn_Right_ACE_Angle(0, "On");//���C��
  
  Put_Catch("Catch", "Under");//�еڶ���
  Run_Manipulator(2, "Right", "Catch", "Under");//���E��
  
  Tracking_Fast_Distance(3800);//����ѭ��һ�ξ���
  Tracking_Slow_Distance(500);//����ѭ��һ�ξ���
  Run_Stop();//ͣ������ֹ�պõ���ָ�����벻ͣ��
  
  while(Ultrasonic_Mean_Value(5999, 72) > ULTRASONIC_THRESHOLD) //���������
  {
    Tracking_Slow_Double_Distance(20);//����ѭ��һ�ξ���
    Run_Stop();
  }
  Put_Catch("Put", "On");//�ŵڶ���
  Run_Manipulator(1, "Right", "Put", "On"); //���ʮ��
  
  /***********************�س�**********************************/
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();

  Turn_Left_ACE_Angle(2, "On");//������
  while(!Run_Front_L || !Run_Front_R) //����ѭ����ʮ��
    Tracking_Fast();
  Run_Line_Fast(1600);
  Run_Line_Fast(800);
  Run_Stop();//ͣ��������
}
