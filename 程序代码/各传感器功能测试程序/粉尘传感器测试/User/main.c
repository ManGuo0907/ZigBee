
// ADC 单通道采集

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_SysTick.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal;        

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	float value;
	float v_fen;
	// 配置串口
	USART_Config();
	
	SysTick_Init();
	// ADC 初始化
	ADCx_Init();
	
	//printf("\r\n ----这是一个ADC单通道DMA读取实验----\r\n");
	
	while (1)
	{
		//value=GP2Y10_Value();
		value= ADC_ConvertedValue * 3.3f / 4095;
		printf("转换后的电压为 :%f V\n",value);
		printf("转换后的数值为 :%d \n",ADC_ConvertedValue);
		GP2Y10_LED_ON();
	 SysTick_Delay_Us(280);
  	v_fen=ADC_ConvertedValue * 3.3f / 4095;
//	v_fen = LIMIT(ADC_ConvertedValue * 3.3f / 4095, 0.5846f, 3.5229f);
	SysTick_Delay_Us(19);
	//SysTick_Delay_Us(GP2Y10_LEDON_TIME-GP2Y10_SAMP_TIME);
	GP2Y10_LED_OFF();
	SysTick_Delay_Us(9680);
//	SysTick_Delay_Us(GP2Y10_PULSE_TIME-GP2Y10_LEDON_TIME);
	

		
		printf("粉尘浓度为 :%f ug/m3\n",(v_fen*0.1767f + 0.1564)*1000);
		SysTick_Delay_Ms(100);
		
		
		
//		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
//	
//		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue); 
//		printf("\r\n The current AD value = %f V \r\n",ADC_ConvertedValueLocal); 

//		Delay(0xffffee);  
	}
}
/*********************************************END OF FILE**********************/

