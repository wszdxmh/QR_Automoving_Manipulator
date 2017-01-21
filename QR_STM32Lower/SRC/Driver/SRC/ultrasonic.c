/**
  ************************************
  * @file    ultrasonic.c
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.10
  * @brief   ��������������
	************************************
*/

#include "ultrasonic.h"

extern uint16_t TIM5CH1_CAPTURE_VAL;
extern uint8_t TIM5CH1_CAPTURE_STA;

/**
  ************************************
  * @brief  ��������ʱ���ĳ�ʼ������
  * @param  arr: �Զ���װ����ֵ   psc:Ԥ��Ƶֵ
  * @retval arr=59999  psc=71     һ���ж�Ϊ50ms
	************************************
*/
void Ultrasonic_TIM5_Init(uint16_t arr, uint16_t psc)
{
	TIM_ICInitTypeDef TIM_ICInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	//ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//ʹ��TIM5��ʱ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	//��ʼ��TIM5��ʱ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
	//��ʼ��TIM5���벶��
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;//ͨ��1
	TIM_ICInitStruct.TIM_ICFilter = 0x00;//���˲�
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;//����Ϊ�����ز���
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;//����Ƶ
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;//ӳ��TI1
	TIM_ICInit(TIM5, &TIM_ICInitStruct);
	//��ʼ�����벶������ ECHO
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//��ʼ���������������� TRIG
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);//TRIG����
	//��ʼ���жϷ���
	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	//ʹ��TIM5
	TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);//��������жϣ�����CC1�����ж�
	TIM_Cmd(TIM5, ENABLE);//ʹ��TIM5��ʱ��
}

/**
  ************************************
  * @brief  �����������ȡ
  * @param  arr:5999   psc:72
  * @retval None
	************************************
*/
uint16_t Ultrasonic_Value(uint16_t arr, uint16_t psc)
{
	uint16_t value=0;
	GPIO_SetBits(GPIOA, GPIO_Pin_1);//TRIG����
	delay_us(15);//��ʱ15us
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);//TRIG����
	Ultrasonic_TIM5_Init(arr, psc);
	while(TIM5CH1_CAPTURE_STA&0x80)//�ɹ�����
	{
		TIM5CH1_CAPTURE_STA &= 0x3f;//�����־λ
		value = (10.0)*(TIM5CH1_CAPTURE_STA * arr + TIM5CH1_CAPTURE_VAL) / 58;  //cm=us/58   mm=cm*10
		TIM5CH1_CAPTURE_STA = 0;//������һ���ж�
	}
	return value;
}

/**
  ************************************
  * @brief  ����������ƽ��ֵ����
  * @param  arr:5999   psc:72
  * @retval None
	************************************
*/
uint16_t Ultrasonic_Mean_Value(uint16_t arr, uint16_t psc)
{
	uint16_t buf_value[5];
	uint16_t value;
	//�ɼ�10������
	for(uint8_t i=0; i<5; i++)
	{
		buf_value[i] = Ultrasonic_Value(arr, psc);
		delay_ms(30);
	}
	//����
	for(uint8_t i=0; i<4; i++)
	{
		for(uint8_t j=i+1; j<5; j++)
		{
			if(buf_value[i] < buf_value[j])
			{
				value = buf_value[i];
				buf_value[i] = buf_value[j];
				buf_value[j] = value;
			}
		}
	}
	value = 0;
	//ȥ�����ֵ����Сֵ�����ֵ
	for(uint8_t k=1; k<4; k++)
		value += buf_value[k];
	value = value/3;
	return value;
}
