/*
1.��Ŀ���ƣ������콢��-STM32�ۺϲ��԰�ָ��ģ����Գ���
2.��ʾģ�飺0.96������OLED��
3.����APP����
4.������λ������
5.��Ŀ��ɣ�0.96������OLED����AS608ָ��ģ�顢����STM32�ۺϲ��԰�
6.��Ŀ���ܣ���ӡ�ɾ������ָ֤�ơ���������뿴��ʾ��Ƶ
7.��Ҫԭ������ο�AS608ָ��ģ�������ֲ�
8.�����ַ��https://lssz.tmall.com ���Ա��������������콢�ꡱ
9.��ʾ��Ƶ����������ҳ��������ͷ���Ҫ��
10.��Ȩ�����������콢�����г��������������Ȩ�����뱾���Ʒ���׳��ۣ��벻Ҫ����������׷���䷨�����Σ�
*/
#include "sys.h"
#include "delay.h"
#include "oled_iic.h"
#include "stdio.h"
#include "key.h"
#include "timer.h"
#include "as608.h"
#include "usart3.h"
#include "bsp_dht11.h"
#include "bsp_led.h"
#include "bsp_SysTick.h"
#include "light.h"


int main(void)
{		
	
	extern const u8 BMP1[];
	DHT11_Data_TypeDef DHT11_Data;
	float t;
	HZ= GB16_NUM();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
//	SysTick_Init();
	usart3_init(57600);
	KEY_Init();
	DHT11_Init();
	Light_Init();
	OLED_Init();
	OLED_Clear();
//	OLED_ShowCH(0,0,"ʪ��:");
//	OLED_ShowNum(70, 0, DHT11_Data.humi_int, 2, 1);
//	OLED_ShowCH(0,2,"�¶�:");
//	OLED_ShowNum(70, 2, DHT11_Data.temp_int, 2, 1);
//	OLED_ShowCH(0,0,"ָ��ģ����Գ���");
//	OLED_ShowCH(16,2,"K1�����ָ��");
//	OLED_ShowCH(16,4,"K3��ɾ��ָ��");
//	OLED_ShowCH(16,6,"K5����ָ֤��");
	while(1)
	{	
		t=bh_data_read();
		OLED_ShowCH(0,4,"����ǿ��:");
		OLED_ShowNum(70, 4, t, 2, 1);
		/*����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ����ɹ����������Ϣ*/
//		if(DHT11_Read_TempAndHumidity(& DHT11_Data)==SUCCESS)
//		{
//			//OLED_Clear();
//			OLED_ShowCH(0,0,"ʪ��:");
//			OLED_ShowNum(70, 0, DHT11_Data.humi_int, 2, 1);
//			OLED_ShowCH(0,2,"�¶�:");
//			OLED_ShowNum(70, 2, DHT11_Data.temp_int, 2, 1);
////			delay_ms(1000);
////			printf("\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n",\
////			DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
//		}	

		delay_ms(1000);
		
//		key_num=KEY_Scan(0);
//		if(key_num==1)
//		{
//			key_num=0;
//			OLED_Clear();
//			Add_FR();
//		}
//		if(key_num==3)
//		{
//			key_num=0;
//			OLED_Clear();
//			Del_FR();
//		}
//		if(key_num==5)
//		{
//			key_num=0;
//			OLED_Clear();
//			OLED_ShowCH(32,2,"�밴��ָ");
//			press_FR();
//		}	
	}
}


