#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"	 


#define KEY1 PAin(4)
#define KEY2 PAin(5) 
#define KEY3 PAin(6)
#define KEY4 PAin(7)
#define KEY5 PCin(4)

#define KEY1_PORT_CLK  RCC_APB2Periph_GPIOA
#define KEY1_PORT			 GPIOA
#define KEY1_PORT_PIN  GPIO_Pin_4

#define KEY2_PORT_CLK  RCC_APB2Periph_GPIOA
#define KEY2_PORT			 GPIOA
#define KEY2_PORT_PIN  GPIO_Pin_5

#define KEY3_PORT_CLK  RCC_APB2Periph_GPIOA
#define KEY3_PORT			 GPIOA
#define KEY3_PORT_PIN  GPIO_Pin_6

#define KEY4_PORT_CLK  RCC_APB2Periph_GPIOA
#define KEY4_PORT			 GPIOA
#define KEY4_PORT_PIN  GPIO_Pin_7

#define KEY5_PORT_CLK  RCC_APB2Periph_GPIOC
#define KEY5_PORT			 GPIOC
#define KEY5_PORT_PIN  GPIO_Pin_4

extern u8 key_num;

void SR501_GPIO_Config(void);
void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);//����ɨ�躯��					    
#endif
