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
#include "jdy_10m.h"

extern const unsigned char BMP1[];
extern unsigned char U1[]; //�¶�  
extern unsigned char U2[];  //������ǿ�ȡ�
extern unsigned char F16x16[];   //Ұ��Ƽ�
extern unsigned char U16x16[];   //�ĳ�Ѱ��
extern unsigned char U4[];       //��ѧ¥����ϵͳ
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue; 

//u8 strhex[10]={170,251,255,255};


SData Node_data1;

u8 motor_flag=0;
u8 send_data[10]={170,251,255,255};
int main(void)
{
//	u16 *figernum;
	//unsigned char i;
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
	USART2_Config();     // ����ZigBeeģ�������ͨ��
	KEY_Init();
	LED_GPIO_Config();
	JDY_10M_Init();
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
		OLED_ShowCH(0,0,"ָ��ģ����Գ���");
		OLED_ShowCH(0,2,"K1�����ָ��");
		OLED_ShowCH(0,4,"K3��ɾ��ָ��");
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
		send_data[4]=temp+32;
		send_data[5]=humi+32;
//		send_data[2]=t;
//		send_data[3]=DustValue;
		
   	key_num=KEY_Scan(0);
    if(key_num==1)  //���ָ��
		{
			key_num=0;
			OLED_CLS();
			Add_FR();
		}
		else if(key_num==3)  //ɾ��ָ��
		{
			key_num=0;
			OLED_CLS();
			Del_FR();
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
			OLED_ShowCH(0,0,"Dust��       ug/m3");
			OLED_ShowFloat(45,0,DustValue,2);
			OLED_ShowCH(0,2,"ʪ�ȣ�       %");
			OLED_ShowFloat(45,2,(float)humi,2);
			OLED_ShowCH(0,4,"�¶ȣ�       C");
			OLED_ShowFloat(45,4,(float)temp,2);

			OLED_ShowCH(0,6,"����ǿ��");
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
			TIM_SetCompare1(ADVANCE_TIM,185);   // ռ�ձ�Ϊ��200-185��/200=7.5% ���ת��90��λ��
		}
		else
		{
			TIM_SetCompare1(ADVANCE_TIM,195);   // ռ�ձ�Ϊ��200-195��/200=2.5% ���ת��0��λ��
		}
				
	}
}


