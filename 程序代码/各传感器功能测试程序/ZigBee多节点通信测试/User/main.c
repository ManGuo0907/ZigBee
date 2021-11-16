/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   使用环形缓冲区的方式接收串口数据
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
#include "./usart/rx_data_queue.h"

extern char redata[100];

int NodeSendFlag_A=0;
int NodeSendFlag_B=1;

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART1_Config();
	USART3_Config();
		
//	rx_queue_init();
	
	/* 发送一个字符串 */
//	Usart_SendString( DEBUG_USARTx,"这是一个串口中断接收回显实验\n");
//	printf("欢迎使用秉火STM32开发板\n\n\n\n");

  while(1)
	{	
		//获取数据并输出
		//实际应用中可参考pull data的方式获取数据进行处理
//		pull_data_from_queue();
//		printf("接收到的数据为：%s\n",redata);
		
/*		
		if(NodeSendFlag_B)
		{
			USART_Cmd(USART3, ENABLE);
			Usart_SendString( USART3,"A123A\n");
			
		}
*/		
		
		if(NodeSendFlag_A)
		{
			USART_Cmd(USART3, ENABLE);
			Usart_SendString( USART3,"B456B\n");
			
		}
		
		
	}	
}
/*********************************************END OF FILE**********************/
