#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"	 


#define KEY1 PBin(5)
#define KEY2 PBin(3) 
#define KEY3 PBin(4)
#define KEY4 PBin(8)
#define KEY5 PBin(9)

#define KEY1_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY1_PORT			 GPIOB
#define KEY1_PORT_PIN  GPIO_Pin_5

#define KEY2_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY2_PORT			 GPIOB
#define KEY2_PORT_PIN  GPIO_Pin_3

#define KEY3_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY3_PORT			 GPIOB
#define KEY3_PORT_PIN  GPIO_Pin_4

#define KEY4_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY4_PORT			 GPIOB
#define KEY4_PORT_PIN  GPIO_Pin_8

#define KEY5_PORT_CLK  RCC_APB2Periph_GPIOB
#define KEY5_PORT			 GPIOB
#define KEY5_PORT_PIN  GPIO_Pin_9

#define KEY_OFF    GPIO_SetBits(GPIOB,KEY1_PORT_PIN|KEY2_PORT_PIN|KEY3_PORT_PIN|KEY4_PORT_PIN|KEY5_PORT_PIN)

extern u8 key_num;

void SR501_GPIO_Config(void);
void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);//按键扫描函数					    
#endif
