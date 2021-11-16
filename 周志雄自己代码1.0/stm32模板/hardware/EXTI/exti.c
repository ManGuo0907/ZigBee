/********************************End of File************************************//********************************Copyright (c)**********************************\
**
**                   (c) Copyright 2019, temp_duan, China, DY.
**                           All Rights Reserved
**
**                           By(�������ɿƼ����޹�˾)
**                             http://www.kpiot.top
**
**----------------------------------�ļ���Ϣ------------------------------------
** �ļ�����: exti.c
** ������Ա: temp_duan
** ��������: 2019-07-09
** �ĵ�����: 
**
**----------------------------------�汾��Ϣ------------------------------------
** �汾����: V0.1
** �汾˵��: ��ʼ�汾
**
**------------------------------------------------------------------------------
\********************************End of Head************************************/
 
/********************************End of File************************************/
#include "exti.h"


/*******************************************************************************
** ��������: EXTIX_Init
** ��������: 
** ����˵��: None
** ����˵��: None
** ������Ա: temp_duan
** ��������: 2019-07-09
**------------------------------------------------------------------------------
** �޸���Ա:
** �޸�����:
** �޸�����:
**------------------------------------------------------------------------------
********************************************************************************/
void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);

    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/*******************************************************************************
** ��������: EXTI3_IRQHandler
** ��������: 
** ����˵��: None
** ����˵��: None
** ������Ա: temp_duan
** ��������: 2019-07-09
**------------------------------------------------------------------------------
** �޸���Ա:
** �޸�����:
** �޸�����:
**------------------------------------------------------------------------------
********************************************************************************/
void EXTI3_IRQHandler(void)
{

    EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE15��·����λ
}
