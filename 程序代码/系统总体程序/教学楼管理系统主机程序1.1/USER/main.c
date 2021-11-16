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
#include "stdio.h"
#include "key.h"
#include "timer.h"
#include "usart3.h"
#include "usart.h"
#include "gizwits_protocol.h"
#include "gizwits_product.h"
#include "rx_data_queue.h"
#include "bsp_usart2.h"

volatile int time_flag;
dataPoint_t currentDataPoint;
extern char redata[100];
extern u8 wifi_flag;
extern u8 led_flag;
char temp[4],humi[4];
char pm[6];
char light[7];
char signnum[4],realnum[4],io_num[4],motorflag[2],lampflag[2],airflag[2];
int tempvalue,humivalue,signnum_i,realnum_i,io_num_i,motor,lamp,air;
float dustvalue,lightvalue;




void Gizetis_Init()
{
	TIM3_Int_Init(9,7199);
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
	gizwitsInit();
}

void userHandle(void)
{
	if(wifi_flag == 1)
	{
		
		
		currentDataPoint.valuetemp1 = tempvalue;
		currentDataPoint.valuehumi1 = humivalue;
		currentDataPoint.valuedust1 = dustvalue;
		currentDataPoint.valuelight1 = lightvalue;
		currentDataPoint.valuesignnumber = signnum_i;
		currentDataPoint.valuerealnumber = realnum_i;
		currentDataPoint.valueinounumber = io_num_i;
		
		currentDataPoint.valueservo1 = motor;
		currentDataPoint.valueledflag1 = lamp;
		currentDataPoint.valueairflag1 = air;
	}
//	if(led_flag == 1)
//	{
//		Usart_SendByte(USART2,0x01);
//	}
//	else
//	{
//		Usart_SendByte(USART2,0x00);
//	}
}


int main(void)
{		
	int key_num;

	USART2_Config();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	uart_init(115200);

	TIM4_Int_Init(999,71);
	usart3_init(9600);
	rx_queue_init();
	KEY_Init();
	Gizetis_Init();
	printf("��ʼ�����\r\n");
	while(1)
	{		
		
		pull_data_from_queue();
		Extraction_str(redata,temp,humi,pm,light,signnum,realnum,io_num,motorflag,lampflag,airflag);
		tempvalue=atoi(temp);        //atoi���������ַ���ת��Ϊ����int
		humivalue=atoi(humi);
		motor=atoi(motorflag);
		lamp=atoi(lampflag);
		air=atoi(airflag);
		signnum_i=atoi(signnum);        //atoi���������ַ���ת��Ϊ����int
		realnum_i=atoi(realnum);
		io_num_i=atoi(io_num);
		dustvalue=atof(pm);         //atof���������ַ���ת��Ϊfloat��
		lightvalue=atof(light);

		key_num=KEY_Scan(0);
		if(key_num==5)
		{
			key_num=0;
		//	__disable_irq();
	//		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);	
			gizwitsSetMode(WIFI_AIRLINK_MODE);  //����
		//	gizwitsSetMode(WIFI_SOFTAP_MODE);    
			printf("�������\r\n");
		//	__enable_irq();
	//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
		}
//		if(time_flag == 500)
//		{
//			time_flag=0;
//			pull_data_from_queue();
//			Extraction_str(redata,temp,humi,pm,light);
//			tempvalue=atoi(temp);
//			humivalue=atoi(humi);
//			dustvalue=atof(pm);
//			lightvalue=atof(light);

//			userHandle();
//		}
		
     userHandle();
		gizwitsHandle((dataPoint_t *)&currentDataPoint); //Э�鴦��
	}
}


