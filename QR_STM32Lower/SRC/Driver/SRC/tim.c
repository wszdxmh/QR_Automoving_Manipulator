/**
  ************************************
  * @file    tim.c
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.05
  * @brief   ��ʱ������
	************************************
	*��ʱ�����㹫ʽ��((1+TIM_Prescaler )/72M)*(1+TIM_Period ) = ���жϼ��ʱ��
	*Ƶ�ʼ��㹫ʽ��((1+TIM_Prescaler)*(1+TIM_Period)) = PWMƵ��
	*���ù�����ӳ����ο���STM32���Ĳο��ֲᡷP119
	*TIM3: PA6(CH_1) PA7(CH_2) PB0(CH_3) PB1(CH_4) TIM4: PB6(CH_1) PB7(CH_2) PB8(CH_3) PB9(CH_4)
	************************************
*/

#include "tim.h"

/**
  ************************************
  * @brief  TIM4��ʱ���ĳ�ʼ������
  * @param  period: �Զ���װ����ֵ   prescaler:Ԥ��Ƶֵ
  * @retval None
	************************************
*/
void TIM1_Init(uint16_t period, uint16_t prescaler)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��
	//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = period; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM4�ж�,��������ж�
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx			
}

/**
  ************************************
  * @brief  PWM�ĳ�ʼ������
  * @param  arr: �Զ���װ����ֵ   psc:Ԥ��Ƶֵ
  * @retval arr=19999  psc=71     f=72000000/((19999+1)*(71+1))=50Hz
	************************************
*/
void TIM_PWM_Init(uint16_t arr, uint16_t psc)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��4ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//����JTAG��Ҫ�ȿ�AFIOʱ��
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
	
	//���ø�����Ϊ�����������,���TIM3 CH3 CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO

	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	
	//��ʼ��TIM3 PWMȫ��ͨ��
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC4
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	
	//��ʼ��TIM4 PWMȫ��ͨ��
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC3
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC4
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
}
