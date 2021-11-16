/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试按键
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "bsp_led.h"  
#include "bsp_key.h" 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */ 
	
void Delay(unsigned count)
{
	for( ;count!=0;count--);
}


int main(void)
{	
	/* LED端口初始化 */
	LED_GPIO_Config();
	
	SR501_GPIO_Config();
	
	while(1)                            
	{	   
		if( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 1  )
		{
			/*LED1反转*/
			LED2_ON;
			LED1_OFF
		} 
		else
		{
			LED1_ON;
			LED2_OFF
		}
		

	}
}
/*********************************************END OF FILE**********************/
