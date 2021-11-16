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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	int tempvalue,humivalue;
	float dustvalue,lightvalue;
	char test[]={"38,65,157.9,1500.6"};
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	USART3_Config();	
	TIM3_Int_Init(999,71);
	rx_queue_init();
	
	/* 发送一个字符串 */
//	Usart_SendString( DEBUG_USARTx,"这是一个串口中断接收回显实验\n");
//	printf("欢迎使用秉火STM32开发板\n\n\n\n");
	// atoi() 字符串转整型函数。atof() 字符串转浮点 使用需添加头文件 stdilb.h
  // printf("字符串\"12345.6\"转换为数字：%d\n",atoi("12345.6"));
//	  Extraction_str(test);
//		printf("温度：%s\n",temp);
//		printf("湿度：%s\n",humi);
//	  printf("粉尘：%s\n",pm);
//		printf("光照：%s\n",light);
		
  while(1)
	{	
		//获取数据并输出
		//实际应用中可参考pull data的方式获取数据进行处理
		pull_data_from_queue();
		Extraction_str(redata);
		tempvalue=atoi(temp);
		humivalue=atoi(humi);
		dustvalue=atof(pm);
		lightvalue=atof(light);
		if(time_flag == 1000)
		{
			time_flag=0;
			printf("温度：%d\n",tempvalue);
			printf("湿度：%d\n",humivalue);
			printf("粉尘：%0.1f\n",dustvalue);
			printf("光照：%0.1f\n",lightvalue);
		}
		
	}	
}
/*********************************************END OF FILE**********************/
