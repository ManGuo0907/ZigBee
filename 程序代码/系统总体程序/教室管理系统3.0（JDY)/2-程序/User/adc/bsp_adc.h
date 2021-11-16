#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADCx                          ADC1
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA

// PC1-ͨ��11 ����IO
#define    ADC_PIN                       GPIO_Pin_0
#define    ADC_CHANNEL                   ADC_Channel_0
#define    ADC_DMA_CHANNEL               DMA1_Channel1

#define LIMIT(x,min,max)  ((x)<(min)?(min):((x)>(max)?(max):(x))) //�޷���������Ԫ���ʽ��
#define GP2Y10_LED_ON()    GPIO_ResetBits(GPIOC,GPIO_Pin_14)
#define GP2Y10_LED_OFF()   GPIO_SetBits(GPIOC,GPIO_Pin_14)

#define GP2Y10_SAMP_TIME    280 //����������ʱ��280us
#define GP2Y10_LEDON_TIME    320  //LED�ƿ�����ʱ��
#define GP2Y10_PULSE_TIME    10000 // ������������ʱ�䣨��λUS��

void ADCx_Init(void);
float GP2Y10_Value(void);

#endif /* __ADC_H */

