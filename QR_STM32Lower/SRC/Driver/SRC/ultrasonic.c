/**
  ************************************
  * @file    ultrasonic.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.10
  * @brief   超声波驱动函数
	************************************
*/

#include "ultrasonic.h"

extern uint16_t TIM5CH1_CAPTURE_VAL;
extern uint8_t TIM5CH1_CAPTURE_STA;

/**
  ************************************
  * @brief  超声波定时器的初始化函数
  * @param  arr: 自动重装周期值   psc:预分频值
  * @retval arr=59999  psc=71     一个中断为50ms
	************************************
*/
void Ultrasonic_TIM5_Init(uint16_t arr, uint16_t psc)
{
	TIM_ICInitTypeDef TIM_ICInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	//使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//使能TIM5定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
	//初始化TIM5定时器
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
	//初始化TIM5输入捕获
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;//通道1
	TIM_ICInitStruct.TIM_ICFilter = 0x00;//不滤波
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;//极性为上升沿捕获
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;//不分频
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;//映射TI1
	TIM_ICInit(TIM5, &TIM_ICInitStruct);
	//初始化输入捕获引脚 ECHO
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//初始化超声波触发引脚 TRIG
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);//TRIG拉低
	//初始化中断分组
	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	//使能TIM5
	TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);//允许更新中断，允许CC1捕获中断
	TIM_Cmd(TIM5, ENABLE);//使能TIM5定时器
}

/**
  ************************************
  * @brief  超声波距离获取
  * @param  arr:5999   psc:72
  * @retval None
	************************************
*/
uint16_t Ultrasonic_Value(uint16_t arr, uint16_t psc)
{
	uint16_t value=0;
	GPIO_SetBits(GPIOA, GPIO_Pin_1);//TRIG拉高
	delay_us(15);//延时15us
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);//TRIG拉低
	Ultrasonic_TIM5_Init(arr, psc);
	while(TIM5CH1_CAPTURE_STA&0x80)//成功捕获
	{
		TIM5CH1_CAPTURE_STA &= 0x3f;//清除标志位
		value = (10.0)*(TIM5CH1_CAPTURE_STA * arr + TIM5CH1_CAPTURE_VAL) / 58;  //cm=us/58   mm=cm*10
		TIM5CH1_CAPTURE_STA = 0;//开启下一次中断
	}
	return value;
}

/**
  ************************************
  * @brief  超声波距离平均值计算
  * @param  arr:5999   psc:72
  * @retval None
	************************************
*/
uint16_t Ultrasonic_Mean_Value(uint16_t arr, uint16_t psc)
{
	uint16_t buf_value[5];
	uint16_t value;
	//采集10个样本
	for(uint8_t i=0; i<5; i++)
	{
		buf_value[i] = Ultrasonic_Value(arr, psc);
		delay_ms(30);
	}
	//排序
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
	//去除最大值和最小值，求均值
	for(uint8_t k=1; k<4; k++)
		value += buf_value[k];
	value = value/3;
	return value;
}
