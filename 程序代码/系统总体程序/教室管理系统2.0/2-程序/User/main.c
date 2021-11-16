/**
  ******************************************************************************
  * @file    OLED_I2C.c
  * @author  fire
  * @version V1.0
  * @date    2014-xx-xx
  * @brief   128*64点阵的OLED显示测试工程，仅适用于SD1306驱动IIC通信方式显示屏
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 ISO STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
	*
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "OLED_I2C.h"
#include "delay.h"
#include "light.h"
#include "bsp_dht11.h"
#include "usart3.h"
#include "as608.h"
#include "key.h"

extern const unsigned char BMP1[];
extern unsigned char U1[]; //温度  
extern unsigned char U2[];  //“光照强度”
extern unsigned char F16x16[];   //野火科技
extern unsigned char U16x16[];   //夏虫寻冰
extern unsigned char U4[];       //教学楼管理系统

SData Node_data1;

int main(void)
{
//	u16 *figernum;
	//unsigned char i;
  float t;
	DHT11_Data_TypeDef DHT11_Data;
	HZ= GB16_NUM();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	DelayInit();
	usart3_init(57600);  //用于和指纹识别模块通信
	USART1_Config();     //打印串口信息
	USART2_Config();     // 用于ZigBee模块的无线通信
	KEY_Init();
	I2C_Configuration();
	OLED_Init();
	Light_Init();
	DHT11_Init();
	OLED_CLS();//清屏
	
	OLED_ShowCH(0,0,"测试程序");

	while(1)
	{
    key_num=KEY_Scan(0);
		
		
		OLED_CLS();//清屏
		OLED_ShowCH(0,0,"指纹模块测试程序");
		OLED_ShowCH(16,2,"K1键添加指纹");
		OLED_ShowCH(16,4,"K3键删除指纹");
		OLED_ShowCH(16,6,"K5键验证指纹");
		DelayS(3);
		
		if(key_num==1)
		{
			key_num=0;
			OLED_CLS();
			Add_FR();
		}
		if(key_num==3)
		{
			key_num=0;
			OLED_CLS();
			Del_FR();
		}
		if(key_num==5)
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(32,2,"请按手指");
			Sign_In();
		}	
		
		
		if(DHT11_Read_TempAndHumidity(& DHT11_Data)==SUCCESS)
		{
			OLED_CLS();
			OLED_ShowCH(0,2,"湿度：       %");
			OLED_ShowFloat(45,2,(float)DHT11_Data.humi_int,2);
			OLED_ShowCH(0,4,"温度：       C");
			OLED_ShowFloat(45,4,(float)DHT11_Data.temp_int,2);
			Node_data1.temp_num=DHT11_Data.temp_int;
			Node_data1.humi_num=DHT11_Data.humi_int;
		}
		
		t=bh_data_read();
		OLED_ShowCH(0,6,"光照强度");
		OLED_ShowFloat(77,6,t,2);
		Node_data1.light_num=t;
		DelayS(2);
		
	//	SendDatatozigbee();
		
		printf("%d\n",Node_data1.temp_num);
		printf("%.1f\n",Node_data1.light_num);
		printf("%d\n",Node_data1.signnum);
		printf("%d\n",Node_data1.relnum);
	// PS_ValidNum();
	// PS_ValidTempleteNum(figernum);
	}
}
