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
#include "bsp_Advance_tim.h"
#include "bsp_adc.h"
#include "bsp_led.h"
#include "jdy_10m.h"

extern const unsigned char BMP1[];
extern unsigned char U1[]; //温度  
extern unsigned char U2[];  //“光照强度”
extern unsigned char F16x16[];   //野火科技
extern unsigned char U16x16[];   //夏虫寻冰
extern unsigned char U4[];       //教学楼管理系统
// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue; 

//u8 strhex[10]={170,251,255,255};


SData Node_data1;

u8 motor_flag=0;
u8 send_data[10]={170,251,255,255};
int main(void)
{
//	u16 *figernum;
	//unsigned char i;
  float t;      //光照强度数值
	float DustValue; //粉尘浓度
	int temp=0;
	int humi=0;
	DHT11_Data_TypeDef DHT11_Data;
	
	HZ= GB16_NUM();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	DelayInit();
	TIM_Init();
	usart3_init(57600);  //用于和指纹识别模块通信
	USART1_Config();     //打印串口信息
	USART2_Config();     // 用于ZigBee模块的无线通信
	KEY_Init();
	LED_GPIO_Config();
	JDY_10M_Init();
	I2C_Configuration();
	OLED_Init();
	Light_Init();
	DHT11_Init();
	ADCx_Init();       //用于粉尘传感器检测
	
	OLED_CLS();//清屏
	OLED_ShowCH(0,0,"测试程序");
	
  OLED_CLS();//清屏	

	while(1)
	{
		//OLED_CLS();//清屏	
		OLED_ShowCH(0,0,"指纹模块测试程序");
		OLED_ShowCH(0,2,"K1键添加指纹");
		OLED_ShowCH(0,4,"K3键删除指纹");
		OLED_ShowCH(0,6,"K5键验证指纹    ");
		//DelayS(3);
		if(DHT11_Read_TempAndHumidity(& DHT11_Data)==SUCCESS)
		{
			temp=DHT11_Data.temp_int;
			humi=DHT11_Data.humi_int;
		}
		
		t=bh_data_read();
		DustValue=GP2Y10_Value();
		Node_data1.temp_num=temp;
		Node_data1.humi_num=humi;
		Node_data1.light_num=t;
		Node_data1.pm=DustValue;
		send_data[4]=temp+32;
		send_data[5]=humi+32;
//		send_data[2]=t;
//		send_data[3]=DustValue;
		
   	key_num=KEY_Scan(0);
    if(key_num==1)  //添加指纹
		{
			key_num=0;
			OLED_CLS();
			Add_FR();
		}
		else if(key_num==3)  //删除指纹
		{
			key_num=0;
			OLED_CLS();
			Del_FR();
		}
		else if(key_num==5) //签到验证指纹
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(32,2,"请按手指");
			Sign_In();
		}	
		else if(key_num == 4)    //显示温湿度、光照强度等数据
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(0,0,"Dust：       ug/m3");
			OLED_ShowFloat(45,0,DustValue,2);
			OLED_ShowCH(0,2,"湿度：       %");
			OLED_ShowFloat(45,2,(float)humi,2);
			OLED_ShowCH(0,4,"温度：       C");
			OLED_ShowFloat(45,4,(float)temp,2);

			OLED_ShowCH(0,6,"光照强度");
			OLED_ShowFloat(77,6,t,2);
			DelayS(2);
		}	
		Usart_SendArray(USART1,send_data,6);
  //  printf("%d,%d,%0.1f,%0.1f,",Node_data1.temp_num,Node_data1.humi_num,Node_data1.pm,Node_data1.light_num);
		//printf("%d,%d,%0.1f,%0.1f,",Node_data1.temp_num,Node_data1.humi_num,Node_data1.pm,Node_data1.light_num);
   //  USART_SendData(USART1,Node_data1.light_num);	
	  // while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		//	printf("dust is %0.1f,light is %0.1f\n",Node_data1.pm,Node_data1.light_num);
		
		
		
		if(t<100)
		{
			motor_flag=1;
		}
		else
		{
			motor_flag=0;
		}
		if(motor_flag==1)
		{
			TIM_SetCompare1(ADVANCE_TIM,185);   // 占空比为（200-185）/200=7.5% 舵机转到90°位置
		}
		else
		{
			TIM_SetCompare1(ADVANCE_TIM,195);   // 占空比为（200-195）/200=2.5% 舵机转到0°位置
		}
				
	}
}


