/**
  ******************************************************************************
  * @file    OLED_I2C.c
  * @author  fire
  * @version V1.0
  * @date    2014-xx-xx
  * @brief   128*64�����OLED��ʾ���Թ��̣���������SD1306����IICͨ�ŷ�ʽ��ʾ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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



// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
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
  float t;      //����ǿ����ֵ
	float DustValue; //�۳�Ũ��
	int temp=0;
	int humi=0;
	DHT11_Data_TypeDef DHT11_Data;
	
	HZ= GB16_NUM();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	DelayInit();
	TIM_Init();
	usart3_init(57600);  //���ں�ָ��ʶ��ģ��ͨ��
	USART1_Config();     //��ӡ������Ϣ
//	USART2_Config();      // ����ZigBeeģ�������ͨ��
	KEY_Init();
	IR_Init();
	LED_GPIO_Config();
	I2C_Configuration();
	OLED_Init();
	Light_Init();
	DHT11_Init();
	ADCx_Init();       //���ڷ۳����������
	
	OLED_CLS();//����
	OLED_ShowCH(0,0,"���Գ���");
	
  OLED_CLS();//����	

	while(1)
	{
		
		//OLED_CLS();//����	
		OLED_ShowCH(0,0,"��ѧ¥����ϵͳ  ");
		OLED_ShowCH(0,2,"K1�����ָ�� ");
		OLED_ShowCH(0,4,"K3��ɾ��ָ�� ");
		OLED_ShowCH(0,6,"K5����ָ֤��    ");
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
    if(key_num==1)  //���ָ��
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(32,2,"�밴����Աָ��");
			press_FR();
		}
		else if(key_num==3)  //ɾ��ָ��
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(32,2,"�밴����Աָ��");
			press_FR1();
			
		}
		else if(key_num==5) //ǩ����ָ֤��
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(32,2,"�밴��ָ");
			Sign_In();
		}	
		else if(key_num == 4)    //��ʾ��ʪ�ȡ�����ǿ�ȵ�����
		{
			key_num=0;
			OLED_CLS();
			OLED_ShowCH(0,0,"Dust:      ug/m3");
			OLED_ShowFloat(45,0,DustValue,2);
			OLED_ShowCH(0,2,"ʪ��:       %");
			OLED_ShowFloat(45,2,(float)humi,2);
			OLED_ShowCH(0,4,"�¶�:       C");
			OLED_ShowFloat(45,4,(float)temp,2);

			OLED_ShowCH(0,6,"����ǿ��:");
			OLED_ShowFloat(77,6,t,2);
			DelayS(2);
			OLED_CLS();
			OLED_ShowCH(0,0,"ʵ������: ");
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


