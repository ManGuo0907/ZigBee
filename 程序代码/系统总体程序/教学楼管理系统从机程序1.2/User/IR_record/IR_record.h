#ifndef __IR_RECORD_H
#define __IR_RECORD_H

#include "sys.h"	 
#include "stm32f10x.h"

#define LEN 10



#define IR1_PORT_CLK  RCC_APB2Periph_GPIOA
#define IR1_PORT			 GPIOA
#define IR1_PORT_PIN  GPIO_Pin_11

#define IR2_PORT_CLK  RCC_APB2Periph_GPIOB
#define IR2_PORT			 GPIOB
#define IR2_PORT_PIN  GPIO_Pin_1


void IR_Init(void);
void Arry_Insert(int *a,int index,int data);

#endif



