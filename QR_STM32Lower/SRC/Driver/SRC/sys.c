/**
  ************************************
  * @file    sys.c
  * @author  缪辉
  * @version V3.5.0
  * @date    2015.08.08
  * @brief   中断分组函数
	************************************
*/
#include "sys.h"

/**
  ************************************
  * @brief  NVIC分组初始化函数
  * @param  None
  * @retval None
	************************************
*/
void NVIC_Configuration(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
}
