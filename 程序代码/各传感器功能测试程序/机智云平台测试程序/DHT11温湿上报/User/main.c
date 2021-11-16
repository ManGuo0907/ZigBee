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
#include "bsp_usart3.h"
#include "bsp_usart2.h"
#include "bsp_key.h"
#include "timer.h"
#include "rx_data_queue.h"
#include "gizwits_protocol.h"
#include "gizwits_product.h"


dataPoint_t currentDataPoint;

extern u8 wifi_flag;
int key_num;

char redata[100];
char temp[4],humi[4];
char pm[6];
char light[7];
int tempvalue,humivalue;
float dustvalue,lightvalue;

void Gizeits_Init()
{
	TIM3_Int_Init(9,7199);
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
	gizwitsInit();
}

void userHandle(void)
{
 /*
    currentDataPoint.valuetemp = ;//Add Sensor Data Collection

    */
	
	if(wifi_flag == 1)
	{
		currentDataPoint.valuetemp = tempvalue;
		currentDataPoint.valuehumi = humivalue;
		currentDataPoint.valuedust = dustvalue;
		currentDataPoint.valuelight = lightvalue;
	}
    
}

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	
	int key_num;
	
	/* 配置SysTick 为1us中断一次 */
	SysTick_Init();
  
	Key_GPIO_Config();
	USART3_Config(); //初始化串口3
	USART_Config(); //初始化串口1
	
	
	
	USART2_Config();
  rx_queue_init();
	Gizeits_Init();
	printf("初始化完成\r\n");
	while(1)
	{	
		pull_data_from_queue();
		Extraction_str(redata,temp,humi,pm,light);
		tempvalue=atoi(temp);
		humivalue=atoi(humi);
		dustvalue=atof(pm);
		lightvalue=atof(light);
		
		
		key_num=Key_Scan();
		if(key_num == 2)
		{
			key_num=0;
			gizwitsSetMode(WIFI_AIRLINK_MODE);  //配网
			printf("配网完成\r\n");
		}
		userHandle();		
		gizwitsHandle((dataPoint_t *)&currentDataPoint); //协议处理
	}
}
/*********************************************END OF FILE**********************/
