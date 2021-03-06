/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
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
#include "bsp_usart.h"
#include "bsp_usart1.h"
#include "delay.h"
#include "timer.h"
#include "rx_data_queue.h"

extern char redata[100];

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	int i=0;
//	u8 len,t;
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	USART1_Config();
	DelayInit();
	rx_queue_init();
	/* 发送一个字符串 */ 
	//Usart_SendString( USART1,"Zigbee串口通信测试\n");
//	for(i=0;i<3;i++)
//	{
//		Usart_SendString( USART1,"A123A\n");
//		DelayMs(1000);
//	}
	
	
  while(1)
	{	
	
		pull_data_from_queue();
	
    printf("响应：%s\n",redata);
		DelayMs(200);
		
	
		
		Usart_SendString( USART3,"B456B\n");
		DelayMs(500);
		
	}	
}
/*********************************************END OF FILE**********************/
