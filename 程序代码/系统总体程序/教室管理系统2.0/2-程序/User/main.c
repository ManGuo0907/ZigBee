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

extern const unsigned char BMP1[];
extern unsigned char U1[]; //�¶�  
extern unsigned char U2[];  //������ǿ�ȡ�
extern unsigned char F16x16[];   //Ұ��Ƽ�
extern unsigned char U16x16[];   //�ĳ�Ѱ��
extern unsigned char U4[];       //��ѧ¥����ϵͳ

SData Node_data1;

int main(void)
{
//	u16 *figernum;
	//unsigned char i;
  float t;
	DHT11_Data_TypeDef DHT11_Data;
	HZ= GB16_NUM();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	DelayInit();
	usart3_init(57600);  //���ں�ָ��ʶ��ģ��ͨ��
	USART1_Config();     //��ӡ������Ϣ
	USART2_Config();     // ����ZigBeeģ�������ͨ��
	KEY_Init();
	I2C_Configuration();
	OLED_Init();
	Light_Init();
	DHT11_Init();
	OLED_CLS();//����
	
	OLED_ShowCH(0,0,"���Գ���");

	while(1)
	{
    key_num=KEY_Scan(0);
		
		
		OLED_CLS();//����
		OLED_ShowCH(0,0,"ָ��ģ����Գ���");
		OLED_ShowCH(16,2,"K1�����ָ��");
		OLED_ShowCH(16,4,"K3��ɾ��ָ��");
		OLED_ShowCH(16,6,"K5����ָ֤��");
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
			OLED_ShowCH(32,2,"�밴��ָ");
			Sign_In();
		}	
		
		
		if(DHT11_Read_TempAndHumidity(& DHT11_Data)==SUCCESS)
		{
			OLED_CLS();
			OLED_ShowCH(0,2,"ʪ�ȣ�       %");
			OLED_ShowFloat(45,2,(float)DHT11_Data.humi_int,2);
			OLED_ShowCH(0,4,"�¶ȣ�       C");
			OLED_ShowFloat(45,4,(float)DHT11_Data.temp_int,2);
			Node_data1.temp_num=DHT11_Data.temp_int;
			Node_data1.humi_num=DHT11_Data.humi_int;
		}
		
		t=bh_data_read();
		OLED_ShowCH(0,6,"����ǿ��");
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
