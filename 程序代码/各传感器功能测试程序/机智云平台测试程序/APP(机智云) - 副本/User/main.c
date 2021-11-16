/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����led
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
#include <stdlib.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "gizwits_product.h"
#include "gizwits_protocol.h"
#include "delay.h"
//#include "key.h"
#include "timer.h"
#include "bsp_key.h"
#include "bsp_usart1.h"
//#include "bsp_usart2.h"
//#include "rx_data_queue.h"


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




int main(void)
{	
	
	delay_init();
	//Key_Init();
  Key_GPIO_Config();
//	TIM4_Int_Init(1999,35999);  //��ʱ1S  ��ȡ����ʱ��
	
	USART1_Config();
//	USART2_Config();   //zigbee��������ͨ��
	USART3_Config();   //��esp8266
	LED_GPIO_Config();
//	rx_queue_init();
	Gizeits_Init();
	printf("��ʼ�����\r\n");
	while (1)
	{
//		pull_data_from_queue();
//		Extraction_str(redata,temp,humi,pm,light);
//		tempvalue=atoi(temp);
//		humivalue=atoi(humi);
//		dustvalue=atof(pm);
//		lightvalue=atof(light);
	
		if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_OFF  )
		{
			gizwitsSetMode(WIFI_AIRLINK_MODE);  //����
			//gizwitsSetMode(WIFI_SOFTAP_MODE);
			printf("�������\r\n");
		}
 	//	userHandle();

		
	
		gizwitsHandle((dataPoint_t *)&currentDataPoint); //Э�鴦��
	}
}

