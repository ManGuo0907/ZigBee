#include "stm32f10x.h"
#include "key.h"
#include "delay.h"
#include "gizwits_product.h"
#include "bsp_usart.h"


//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY1_PORT_CLK|KEY2_PORT_CLK|KEY3_PORT_CLK|\
	KEY4_PORT_CLK|KEY5_PORT_CLK,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_InitStructure.GPIO_Pin  = KEY1_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);//��ʼ��GPIOA

	GPIO_InitStructure.GPIO_Pin  = KEY2_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);//��ʼ��GPIOA
	
	GPIO_InitStructure.GPIO_Pin  = KEY3_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(KEY3_PORT, &GPIO_InitStructure);//��ʼ��GPIOA
	
	GPIO_InitStructure.GPIO_Pin  = KEY4_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(KEY4_PORT, &GPIO_InitStructure);//��ʼ��GPIOA
	
	GPIO_InitStructure.GPIO_Pin  = KEY5_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(KEY5_PORT, &GPIO_InitStructure);//��ʼ��GPIOA
}




//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3����
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)
		{
			gizwitsSetMode(WIFI_AIRLINK_MODE);//����
			printf("wifiģ�������ɹ�\r\n");
		}
		
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1)key_up=1; 	    
 	return 0;// �ް�������
}
