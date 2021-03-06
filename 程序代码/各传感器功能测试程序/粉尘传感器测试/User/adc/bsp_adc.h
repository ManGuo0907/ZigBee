#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC1输入通道（引脚）配置**************************/
#define    ADCx                          ADC1
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA

// PC1-通道11 独立IO
#define    ADC_PIN                       GPIO_Pin_0
#define    ADC_CHANNEL                   ADC_Channel_0
#define    ADC_DMA_CHANNEL               DMA1_Channel1

#define LIMIT(x,min,max)  ((x)<(min)?(min):((x)>(max)?(max):(x))) //限幅函数，三元表达式。
#define GP2Y10_LED_ON()    GPIO_ResetBits(GPIOC,GPIO_Pin_14)
#define GP2Y10_LED_OFF()   GPIO_SetBits(GPIOC,GPIO_Pin_14)

#define GP2Y10_SAMP_TIME    280 //传感器采样时间280us
#define GP2Y10_LEDON_TIME    320  //LED灯开持续时间
#define GP2Y10_PULSE_TIME    10000 // 测量脉冲周期时间（单位US）

void ADCx_Init(void);
float GP2Y10_Value(void);

#endif /* __ADC_H */

