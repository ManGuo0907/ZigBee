#include "IR_record.h"


//红外反射传感器初始化函数
void IR_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(IR1_PORT_CLK|IR2_PORT_CLK,ENABLE);//使能PORTA,PORTC时钟

	GPIO_InitStructure.GPIO_Pin  = IR1_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(IR1_PORT, &GPIO_InitStructure);//初始化GPIOA

	GPIO_InitStructure.GPIO_Pin  = IR2_PORT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(IR2_PORT, &GPIO_InitStructure);//初始化GPIOA
	
}

// 在数组的插入数据，index为数据插入位置，下标从0开始
void Arry_Insert(int *a,int index,int data)
{
	int i;
	for(i=LEN-1;i>=index;i--)
	{
		a[i] = a[i-1];
	}
	
	a[index] = data;
}


