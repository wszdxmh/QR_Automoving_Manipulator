/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

//����ȫ�ֱ���
uint16_t Temp;//TIM4_IRQHeader
extern uint16_t TIM5CH1_CAPTURE_VAL;
extern uint8_t  TIM5CH1_CAPTURE_STA;
extern uint16_t Positioning_Left;
extern uint16_t Positioning_Right;
extern uint16_t Lift;
extern uint16_t Flat;
extern uint16_t Clip;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		if(Temp == 0)
		{
			LED_Open(0,0);
      LED_Open(1,0);
      LED_Open(2,0);
      LED_Open(3,0);
			Temp = 1;
		}
		else if(Temp == 1)
		{
			LED_Open(0,1);
      LED_Open(1,1);
      LED_Open(2,1);
      LED_Open(3,1);
			Temp = 0;
		}
		else
			Temp = 0;
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIMx�����жϱ�־ 
	}
}

/**
  * @}
  */ 
void TIM5_IRQHandler(void)
{
	if((TIM5CH1_CAPTURE_STA & 0x80) == 0)//δ�ɹ�����������
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) == 1)//���������ж�
		{
			if(TIM5CH1_CAPTURE_STA & 0x40)//�Ѿ������˸ߵ�ƽ
			{
				if((TIM5CH1_CAPTURE_STA & 0x01) == 0x01)//�ߵ�ƽ̫��
				{
					TIM5CH1_CAPTURE_STA |= 0x80;
					TIM5CH1_CAPTURE_VAL = 0x01;
				}
				else
				{
					TIM5CH1_CAPTURE_STA++;
				}
			}
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) == 1)
		{
			if(TIM5CH1_CAPTURE_STA & 0x40)//�Ѿ������˸ߵ�ƽ
			{
				TIM5CH1_CAPTURE_STA |= 0x80;
				TIM5CH1_CAPTURE_VAL = TIM_GetCapture1(TIM5);
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);//����Ϊ�����ز���
			}
			else
			{
				TIM5CH1_CAPTURE_STA = 0;
				TIM5CH1_CAPTURE_VAL = 0;
				TIM5CH1_CAPTURE_STA |= 0x40;
				TIM_SetCounter(TIM5, 0);//�����������ֵ
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update | TIM_IT_CC1);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
