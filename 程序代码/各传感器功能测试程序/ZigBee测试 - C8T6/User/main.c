/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
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
#include "bsp_usart.h"
#include "bsp_usart1.h"
#include "delay.h"
#include "timer.h"
#include "rx_data_queue.h"
#include "string.h"


extern char redata[100];

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	int i=0;
//	u8 len,t;
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	USART1_Config();
	DelayInit();
	rx_queue_init();
	/* ����һ���ַ��� */ 
	//Usart_SendString( USART1,"Zigbee����ͨ�Ų���\n");
//	for(i=0;i<3;i++)
//	{
//		Usart_SendString( USART1,"A123A\n");
//		DelayMs(1000);
//	}
	
//	for(i=0;i<5;i++)
//	{
//		Usart_SendString( USART3,"A123A\n");
//		DelayMs(1000);
//	}
	
//	USART_Cmd(USART3, DISABLE);
  while(1)
	{	
	
		Usart_SendString( USART3,"B456B\n");
		USART_Cmd(USART3, DISABLE);
		DelayMs(2000);
		USART_Cmd(USART3, ENABLE);
		pull_data_from_queue();
		printf("redata��%s\n",redata);
//		if(sizeof(redata) != 0)
//		{
//	  printf("���գ�%s\n",redata);
//		Usart_SendString( USART3,"OK\n");
//		}
//		else
//		{
//			printf("no data\n");
//		}
//		DelayMs(500);
		
	
//		Usart_SendString( USART3,"B456B\n");
//		DelayMs(500);
		
	}	
}
/*********************************************END OF FILE**********************/
