
// ADC ��ͨ���ɼ�

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_SysTick.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;        

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	float value;
	float v_fen;
	// ���ô���
	USART_Config();
	
	SysTick_Init();
	// ADC ��ʼ��
	ADCx_Init();
	
	//printf("\r\n ----����һ��ADC��ͨ��DMA��ȡʵ��----\r\n");
	
	while (1)
	{
		//value=GP2Y10_Value();
		value= ADC_ConvertedValue * 3.3f / 4095;
		printf("ת����ĵ�ѹΪ :%f V\n",value);
		printf("ת�������ֵΪ :%d \n",ADC_ConvertedValue);
		GP2Y10_LED_ON();
	 SysTick_Delay_Us(280);
  	v_fen=ADC_ConvertedValue * 3.3f / 4095;
//	v_fen = LIMIT(ADC_ConvertedValue * 3.3f / 4095, 0.5846f, 3.5229f);
	SysTick_Delay_Us(19);
	//SysTick_Delay_Us(GP2Y10_LEDON_TIME-GP2Y10_SAMP_TIME);
	GP2Y10_LED_OFF();
	SysTick_Delay_Us(9680);
//	SysTick_Delay_Us(GP2Y10_PULSE_TIME-GP2Y10_LEDON_TIME);
	

		
		printf("�۳�Ũ��Ϊ :%f ug/m3\n",(v_fen*0.1767f + 0.1564)*1000);
		SysTick_Delay_Ms(100);
		
		
		
//		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
//	
//		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
//		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

//		Delay(0xffffee);  
	}
}
/*********************************************END OF FILE**********************/

