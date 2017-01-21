/**
  ************************************
  * @file    led.c
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.02
  * @brief   Led������(PB8)
	************************************
*/

#include "led.h"

/**
  ************************************
  * @brief  Led��IO�ڵĳ�ʼ��
  * @param  None
  * @retval None
	************************************
*/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure1;//����ṹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);//GPIOB�ⲿʱ��ʹ�ܣ��ر���Ҫ������
//	//��PB4ʱҪ����JTAG������Ҫ�ȿ�AFIOʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_15;//����IO��
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;//����Ϊ��ͨ�������
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;//Ƶ��50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure1);//��ʼ��
  
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10;//����IO��
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;//����Ϊ��ͨ�������
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;//Ƶ��50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure1);//��ʼ��
}

/**
  **********************************
  * @brief  Led�ƵĿ���
  * @param  status: 0 or 1
  * @retval None
  **********************************
*/
void LED_Open(uint8_t num, uint8_t status)
{
	if(status)
  {
    switch (num)
    {
      case 0: GPIO_SetBits(GPIOA, GPIO_Pin_15);break;//��1
      case 1: GPIO_SetBits(GPIOC, GPIO_Pin_10);break;//��1
      case 2: GPIO_SetBits(GPIOC, GPIO_Pin_11);break;//��1
      case 3: GPIO_SetBits(GPIOC, GPIO_Pin_12);break;//��1
    }
  }		
		//GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);//��1
	else
  {
    switch (num)
    {
      case 0: GPIO_ResetBits(GPIOA, GPIO_Pin_15);break;//��0
      case 1: GPIO_ResetBits(GPIOC, GPIO_Pin_10);break;//��0
      case 2: GPIO_ResetBits(GPIOC, GPIO_Pin_11);break;//��0
      case 3: GPIO_ResetBits(GPIOC, GPIO_Pin_12);break;//��0
    }
  }
		//GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);//��0
}

