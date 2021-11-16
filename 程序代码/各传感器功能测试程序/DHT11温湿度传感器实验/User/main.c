/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   dht11��ʪ�ȴ���������ʵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� �Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
	DHT11_Data_TypeDef DHT11_Data;
	HZ= GB16_NUM();
	/* ����SysTick Ϊ1us�ж�һ�� */
//	SysTick_Init();
	delay_init();
	USART_Config();//��ʼ������1
//	printf("\r\n***���ܽ�ѧ¥����ϵͳ ��ʪ�ȴ�����ʵ��***\r\n");

	/*��ʼ��DTT11������*/
	DHT11_Init ();
  OLED_Init();
	OLED_Clear();
	while(1)
	{	
			/*����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ����ɹ����������Ϣ*/
			if( DHT11_Read_TempAndHumidity ( & DHT11_Data )== SUCCESS)
	  	{			
				//OLED_Clear();
				OLED_ShowCH(12,0,"ʪ��:");
				OLED_ShowNum(60, 0, DHT11_Data.humi_int, 2, 1);
				OLED_ShowCH(12,2,"�¶�:");
				OLED_ShowNum(60, 2, DHT11_Data.temp_int, 2, 1);
				//delay_ms(1000);
			}			
			
		 delay_ms(1000);
   }
}
	/*********************************************END OF FILE**********************/
