#ifndef _ADCX_H
#define _ADCX_H

#include "stm32f10x.h"

// ת��ͨ������
#define    macNOFCHANEL											2



// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define    macADCx                          ADC1
#define    macADC_DMA_CHANNEL               DMA1_Channel1


/**************************��������********************************/
void               ADCx_Init                               (void);
void AD_Read(u8 *adc1, u8 *adc2);

#endif

