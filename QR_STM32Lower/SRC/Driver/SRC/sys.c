/**
  ************************************
  * @file    sys.c
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.08
  * @brief   �жϷ��麯��
	************************************
*/
#include "sys.h"

/**
  ************************************
  * @brief  NVIC�����ʼ������
  * @param  None
  * @retval None
	************************************
*/
void NVIC_Configuration(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
}
