#ifndef __JDY_10M_H
#define	__JDY_10M_H


#include "stm32f10x.h"

/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define JDY_STAT_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define JDY_STAT_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define JDY_STAT_GPIO_PIN		    GPIO_Pin_13			          /* ���ӵ�JDY STAT���ŵ�GPIO */

#define JDY_PWRC_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define JDY_PWRC_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define JDY_PWRC_GPIO_PIN		    GPIO_Pin_14		          /* ���ӵ�JDY PWRC���ŵ�GPIO */



#define JDY_PWRC_HIGHT  		GPIO_SetBits(JDY_PWRC_GPIO_PORT, JDY_PWRC_GPIO_PIN);
#define JDY_PWRC_LOW  			GPIO_ResetBits(JDY_PWRC_GPIO_PORT, JDY_PWRC_GPIO_PIN);

#define LED_OFF         		GPIO_SetBits(GPIOC, GPIO_Pin_13);
#define LED_ON         			GPIO_ResetBits(GPIOC, GPIO_Pin_13);

void J10M_GPIO_Init(void);
void JDY_10M_Init(void);
void LED_GPIO_Init(void);


#endif


