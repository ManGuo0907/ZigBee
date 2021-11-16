/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   dht11温湿度传感器测试实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./systick/bsp_SysTick.h"
#include "./dht11/bsp_dht11.h"
#include "./usart/bsp_usart.h"
#include "delay.h"
#include "oled_iic.h"
#include "bsp_led.h"
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	DHT11_Data_TypeDef DHT11_Data;
	HZ= GB16_NUM();
	/* 配置SysTick 为1us中断一次 */
//	SysTick_Init();
	delay_init();
	USART_Config();//初始化串口1
//	printf("\r\n***智能教学楼管理系统 温湿度传感器实验***\r\n");

	/*初始化DTT11的引脚*/
	DHT11_Init ();
  OLED_Init();
	OLED_Clear();
	while(1)
	{	
			/*调用DHT11_Read_TempAndHumidity读取温湿度，若成功则输出该信息*/
			if( DHT11_Read_TempAndHumidity ( & DHT11_Data )== SUCCESS)
	  	{			
				//OLED_Clear();
				OLED_ShowCH(12,0,"湿度:");
				OLED_ShowNum(60, 0, DHT11_Data.humi_int, 2, 1);
				OLED_ShowCH(12,2,"温度:");
				OLED_ShowNum(60, 2, DHT11_Data.temp_int, 2, 1);
				//delay_ms(1000);
			}			
			
		 delay_ms(1000);
   }
}
	/*********************************************END OF FILE**********************/
