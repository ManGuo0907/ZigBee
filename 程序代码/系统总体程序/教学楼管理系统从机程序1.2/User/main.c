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
#include "IR_record.h"



// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue; 

int admID=0;

SData Node_data1;

int a1 = 0;
int  a2 = 0;

int redata1[LEN];
int redata2[LEN];
int redata[LEN];

u8 auto_flag=0;
u8 send_data[10];


int main(void)
{
//	u16 *figernum;
	//unsigned char i;
	int i;
	int a3;
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
//	USART2_Config();      // 用于ZigBee模块的无线通信
	KEY_Init();
	IR_Init();
	LED_GPIO_Config();
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
		OLED_ShowCH(0,0,"教学楼管理系统  ");
		OLED_ShowCH(0,2,"K1键添加指纹 ");
		OLED_ShowCH(0,4,"K3键删除指纹 ");
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
		a1 = GPIO_ReadInputDataBit(IR1_PORT,IR1_PORT_PIN);
  	a2 = GPIO_ReadInputDataBit(IR2_PORT,IR2_PORT_PIN);
	
		a3 = (a1 ? 1:2) * (a2 ? 3:4);
		
		Arry_Insert(redata,0,a3);
		Arry_Insert(redata2,0,a2);
		Arry_Insert(redata1,0,a1);
		
		if(redata[0]==4 && redata[1]==3 &&(redata[2]!=6))
		{
			Node_data1.io_number = Node_data1.io_number+1;
		}
		if(redata[0]==6 && redata[1]==3)
		{
			if(Node_data1.io_number <=0)
			{
			Node_data1.io_number =0;
			}
			else
			{
			Node_data1.io_number--;
			}
		}
/*		
		printf("ring1_data:");
		for(i=0;i<LEN;i++)
		{
		printf("%d",redata1[i]);
		}	
		printf("\r\n");
		
		printf("ring2_data:");
		for(i=0;i<LEN;i++)
		{
		printf("%d",redata2[i]);
		}	
		printf("\r\n");  
	
		printf("ringdata:  ");
		for(i=0;i<LEN;i++)
		{
		printf("%d",redata[i]);
		}	
		printf("\r\n");
		printf("number=  %d\r\n",Node_data1.io_number);
	*/
   	key_num=KEY_Scan(0);
    if(key_num==1)  //添加指纹
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(32,2,"请按管理员指纹");
			press_FR();
		}
		else if(key_num==3)  //删除指纹
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(32,2,"请按管理员指纹");
			press_FR1();
			
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
			OLED_ShowCH(0,0,"Dust:      ug/m3");
			OLED_ShowFloat(45,0,DustValue,2);
			OLED_ShowCH(0,2,"湿度:       %");
			OLED_ShowFloat(45,2,(float)humi,2);
			OLED_ShowCH(0,4,"温度:       C");
			OLED_ShowFloat(45,4,(float)temp,2);

			OLED_ShowCH(0,6,"光照强度:");
			OLED_ShowFloat(77,6,t,2);
			DelayS(2);
			OLED_CLS();
			OLED_ShowCH(0,0,"实际人数: ");
			OLED_ShowFloat(65,0,Node_data1.io_number,2);
			DelayS(2);
			OLED_CLS();
		}		
		
	if(auto_flag == 0)
	{		
		
		if((t<100) && (Node_data1.io_number != 0))
		{
			
			Node_data1.LampFlag = 1;
			LED3_ON;
		}
		else
		{
			Node_data1.LampFlag = 0;
			LED3_OFF;
		}
		
		
		if(DustValue >=200)
		{
			TIM_SetCompare1(ADVANCE_TIM,185);
			Node_data1.MotorFlag =1;
		}
		else
		{
			TIM_SetCompare1(ADVANCE_TIM,195);
			Node_data1.MotorFlag =0;
		}
		
		if(temp >= 35)
		{
			Node_data1.AirFlag = 1;
			LED1_ON;
		}
		else
		{
			Node_data1.AirFlag = 0;
			LED1_OFF;
		}
		
		if(Node_data1.io_number == 0)
		{
			Node_data1.LampFlag = 0;
			LED3_OFF;
		}
			
	}
		
		printf("%d,%d,%0.1f,%0.1f,%d,%d,%d,%d,%d,%d",Node_data1.temp_num,\
		Node_data1.humi_num,Node_data1.pm,Node_data1.light_num,\
		Node_data1.signnum,Node_data1.relnum,Node_data1.io_number,\
		Node_data1.MotorFlag,Node_data1.LampFlag,Node_data1.AirFlag);
		
	}
}


