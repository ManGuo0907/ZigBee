#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"

#define KEY1    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) //��ȡ����1
#define KEY2    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)//��ȡ����2
#define KEY3    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//��ȡ����3
#define KEY4    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) //��ȡ����4
#define KEY5    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3) //��ȡ����5


void KEY_Init(void);//IO��ʼ��

#endif

