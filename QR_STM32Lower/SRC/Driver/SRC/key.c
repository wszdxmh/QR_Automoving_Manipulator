/**
  ************************************
  * @file    key.c
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.02
  * @brief   ��������(PD0 PD1 PD2 PD3)
	************************************
*/

#include "key.h"

//����ȫ�ֱ���
uint8_t Key1_Flag, Key2_Flag, Key3_Flag, Key4_Flag;

/**
  ************************************
  * @brief  ����IO�ڵĳ�ʼ��
  * @param  None
  * @retval None
	************************************
*/
void Key_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//ʹ��PORTDʱ��
  
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3;//KEY0-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
}

/**
  ************************************
  * @brief  �ⲿ�жϳ�ʼ��
  * @param  None
  * @retval None
	************************************
*/
void EXTIX_Init(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  Key_Init();	 //	�����˿ڳ�ʼ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

  //GPIOD.1 �ж����Լ��жϳ�ʼ������   �½��ش���
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
  EXTI_InitStructure.EXTI_Line=EXTI_Line1;	//KEY2
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  //GPIOD.2	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource3);
  EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  //GPIOD.3	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  //GPIOD.0	  �ж����Լ��жϳ�ʼ������ �½��ش���
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0); 
  EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2�� 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure); 

  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2�� 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);


  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

/**
  ************************************
  * @brief  �ⲿ�ж�0������
  * @param  None
  * @retval None
	************************************
*/
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY_0 == 0)	 	 //key0����				 
		Key1_Flag = !Key1_Flag;
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}

/**
  ************************************
  * @brief  �ⲿ�ж�1������
  * @param  None
  * @retval None
	************************************
*/
void EXTI1_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY_1 == 0)	 	 //key1����
		Key2_Flag = !Key2_Flag;
	EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ  
}

/**
  ************************************
  * @brief  �ⲿ�ж�2������
  * @param  None
  * @retval None
	************************************
*/
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY_2 == 0)	 	 //key2����
		Key3_Flag = !Key3_Flag;
	EXTI_ClearITPendingBit(EXTI_Line2); //���LINE0�ϵ��жϱ�־λ  
}

/**
  ************************************
  * @brief  �ⲿ�ж�2������
  * @param  None
  * @retval None
	************************************
*/
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY_3 == 0)	 	 //key3����
		Key4_Flag = !Key4_Flag;
	EXTI_ClearITPendingBit(EXTI_Line3); //���LINE0�ϵ��жϱ�־λ  
}
