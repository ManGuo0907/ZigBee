#include "IR_record.h"


//���ⷴ�䴫������ʼ������
void IR_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(IR1_PORT_CLK|IR2_PORT_CLK,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_InitStructure.GPIO_Pin  = IR1_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(IR1_PORT, &GPIO_InitStructure);//��ʼ��GPIOA

	GPIO_InitStructure.GPIO_Pin  = IR2_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(IR2_PORT, &GPIO_InitStructure);//��ʼ��GPIOA
	
}

// ������Ĳ������ݣ�indexΪ���ݲ���λ�ã��±��0��ʼ
void Arry_Insert(int *a,int index,int data)
{
	int i;
	for(i=LEN-1;i>=index;i--)
	{
		a[i] = a[i-1];
	}
	
	a[index] = data;
}


