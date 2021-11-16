/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ʹ�û��λ������ķ�ʽ���մ�������
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
#include "./usart/rx_data_queue.h"

extern char redata[100];

int NodeSendFlag_A=0;
int NodeSendFlag_B=1;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART1_Config();
	USART3_Config();
		
//	rx_queue_init();
	
	/* ����һ���ַ��� */
//	Usart_SendString( DEBUG_USARTx,"����һ�������жϽ��ջ���ʵ��\n");
//	printf("��ӭʹ�ñ���STM32������\n\n\n\n");

  while(1)
	{	
		//��ȡ���ݲ����
		//ʵ��Ӧ���пɲο�pull data�ķ�ʽ��ȡ���ݽ��д���
//		pull_data_from_queue();
//		printf("���յ�������Ϊ��%s\n",redata);
		
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
