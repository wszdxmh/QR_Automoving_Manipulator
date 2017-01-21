/**
  ************************************
  * @file    manipulator.h
  * @author  �ѻ�
  * @version V3.5.0
  * @date    2015.08.22
  * @brief   ��е�ֿ��ƺ���
	************************************
*/

#ifndef __MANIPULATOR_H
#define __MANIPULATOR_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#include "debug.h"
#include "tim.h"
#include "sys.h"
#include "run.h"
#include "PC_Link.h"

////�����궨��
//#define MANIPULATOR_DELAY_TIME  5
//#define TURN_DELAY_TIME  5

//���ź궨��
#define Put_Left_Out  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)
#define Put_Left_Mid  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)
#define Put_Right_Mid  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11)
#define Put_Right_Out  GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)

//
//�����궨��
//
//ѭ����̬    9.28�������
#define Tracking_Positioning_Left   1858
#define Tracking_Positioning_Right  1493
#define Tracking_Lift   1040
#define Tracking_Flat   640
#define Tracking_Clip   1650
//�ٸ�   9.28�������
#define Highest_Positioning_Left   2440
#define Highest_Positioning_Right  894
#define Highest_Lift   2170
#define Highest_Flat   1120
//ץ����������    9.28�������
#define Catch_On_Positioning_Left   2174
#define Catch_On_Positioning_Right  1167
#define Catch_On_Lift   1290
#define Catch_On_Flat   1240
//ץ�м�����    9.28�������
#define Catch_In_Positioning_Left   2024
#define Catch_In_Positioning_Right  1322
#define Catch_In_Lift   1220
#define Catch_In_Flat   1000
//ץ���µ����    9.28�������
#define Catch_Under_Positioning_Left   1500
#define Catch_Under_Positioning_Right  1540
#define Catch_Under_Lift   1600
#define Catch_Under_Flat   2280
#define Catch_Under_Clip   1250
//�ŵ���������̬
#define Put_Special_Positioning_Left  1764
#define Put_Special_Positioning_Right 1589
#define Put_Special_Lift  1300
#define Put_Special_Flat  730

//������̬   9.28�������
//ץ���������̬
#define Transition_On_Positioning_Left   2455
#define Transition_On_Positioning_Right  878
#define Transition_On_Lift   1050
#define Transition_On_Flat   1250
//ץ�м������̬
#define Transition_In_Positioning_Left   2316
#define Transition_In_Positioning_Right  1021
#define Transition_In_Lift   960
#define Transition_In_Flat   960
//ץ���������̬
#define Transition_Under_Positioning_Left   1959
#define Transition_Under_Positioning_Right  1389
#define Transition_Under_Lift   1000
#define Transition_Under_Flat   580

//ץ�����
#define Put  1480
#define Catch  1820

//��������Run_Manipulator()����
//������
#define Put_On_Positioning_Left 2363
#define Put_On_Positioning_Right 973
//������
#define Put_In_Positioning_Left 2187
#define Put_In_Positioning_Right 1154
//������
#define Put_Under_Positioning_Left 1968
#define Put_Under_Positioning_Right 1379
//ѭ������
#define Put_Tracking_Positioning_Left 2038
#define Put_Tracking_Positioning_Right 1307

uint16_t Abs_16(uint16_t a, uint16_t b);
uint16_t Cmp_Fh_16(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
uint16_t Cmp_Th_16(uint16_t a, uint16_t b, uint16_t c);
uint16_t Cmp_Tw_16(uint16_t a, uint16_t b);
uint16_t Return_All(char a[]);
void Lift_Flat(uint16_t lift, uint16_t flat);
void Positioning_Lift(uint16_t left, uint16_t right, uint16_t lift, uint16_t delay_time);
void Flat_Move(uint16_t flat);
void Positioning(uint16_t left, uint16_t right, uint16_t delay_time);
void Catch_Put(uint16_t clip);
void Attitude_Tracking(void);
void Attitude_Highest(void);
void Attitude_Catch_On(void);
void Attitude_Catch_In(void);
void Attitude_Catch_Under(void);
void Transition(void);
void Put_BCD(uint16_t a);
void Put_A(uint16_t a);
void Put_E(uint16_t a);
void Put_Catch(char a[], char b[]);
void All_Move(char a[], uint16_t b);
void Run_Manipulator(uint8_t num, char c[], char a[], char b[]);

#endif
