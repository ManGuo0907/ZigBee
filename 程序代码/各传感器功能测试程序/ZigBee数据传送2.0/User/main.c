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
#include <stdlib.h>
#include "timer.h"

volatile int time_flag;
char redata[100];
char temp[4],humi[4];
char pm[6];
char light[7];

void Extraction_str(char* str)
{
	int i=0;
	int j=0,t=0;
	while(str[i] != '\0')
	{
		if(t==0)
		{
			if(str[i]==',')
			{
				t++;
				temp[j]='\0';
				j=0;
				i++;
			}
			else
			{
				temp[j]=str[i];
				j++;
			}
		}
		
		if(t==1)
		{
			if(str[i]==',')
			{
				t++;
				humi[j]='\0';
				j=0;
				i++;
			}
			else
			{
				humi[j]=str[i];
				j++;
			}
		}
		
		if(t==2)
		{
			if(str[i]==',')
			{
				t++;
				pm[j]='\0';
				j=0;
				i++;
			}
			else
			{
				pm[j]=str[i];
				j++;
			}
		}
			
		if(t==3)
		{
			if(str[i]==',')
			{
				t++;
				light[j]='\0';
				j=0;
				i++;
			}
			else
			{
				light[j]=str[i];
				j++;
			}
		}
			
		i++;
	}
	
}
	

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	int tempvalue,humivalue;
	float dustvalue,lightvalue;
	char test[]={"38,65,157.9,1500.6"};
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	USART3_Config();	
	TIM3_Int_Init(999,71);
	rx_queue_init();
	
	/* ����һ���ַ��� */
//	Usart_SendString( DEBUG_USARTx,"����һ�������жϽ��ջ���ʵ��\n");
//	printf("��ӭʹ�ñ���STM32������\n\n\n\n");
	// atoi() �ַ���ת���ͺ�����atof() �ַ���ת���� ʹ�������ͷ�ļ� stdilb.h
  // printf("�ַ���\"12345.6\"ת��Ϊ���֣�%d\n",atoi("12345.6"));
//	  Extraction_str(test);
//		printf("�¶ȣ�%s\n",temp);
//		printf("ʪ�ȣ�%s\n",humi);
//	  printf("�۳���%s\n",pm);
//		printf("���գ�%s\n",light);
		
  while(1)
	{	
		//��ȡ���ݲ����
		//ʵ��Ӧ���пɲο�pull data�ķ�ʽ��ȡ���ݽ��д���
		pull_data_from_queue();
		Extraction_str(redata);
		tempvalue=atoi(temp);
		humivalue=atoi(humi);
		dustvalue=atof(pm);
		lightvalue=atof(light);
		if(time_flag == 1000)
		{
			time_flag=0;
			printf("�¶ȣ�%d\n",tempvalue);
			printf("ʪ�ȣ�%d\n",humivalue);
			printf("�۳���%0.1f\n",dustvalue);
			printf("���գ�%0.1f\n",lightvalue);
		}
		
	}	
}
/*********************************************END OF FILE**********************/
