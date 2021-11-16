/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ���԰���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-�Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "bsp_led.h"  
#include "bsp_key.h" 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */ 
	
void Delay(unsigned count)
{
	for( ;count!=0;count--);
}


int main(void)
{	
	/* LED�˿ڳ�ʼ�� */
	LED_GPIO_Config();
	
	SR501_GPIO_Config();
	
	while(1)                            
	{	   
		if( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0 )
		{
			led1on;
		} 
		else
		{
			led1off;
		}
		

	}
}
/*********************************************END OF FILE**********************/
