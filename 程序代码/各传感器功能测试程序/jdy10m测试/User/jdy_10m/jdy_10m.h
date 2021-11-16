#ifndef __JDY_10M_H
#define	__JDY_10M_H


#include "stm32f10x.h"

/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define JDY_STAT_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define JDY_STAT_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define JDY_STAT_GPIO_PIN		    GPIO_Pin_13			          /* 连接到JDY STAT引脚的GPIO */

#define JDY_PWRC_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define JDY_PWRC_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define JDY_PWRC_GPIO_PIN		    GPIO_Pin_14		          /* 连接到JDY PWRC引脚的GPIO */



#define JDY_PWRC_HIGHT  		GPIO_SetBits(JDY_PWRC_GPIO_PORT, JDY_PWRC_GPIO_PIN);
#define JDY_PWRC_LOW  			GPIO_ResetBits(JDY_PWRC_GPIO_PORT, JDY_PWRC_GPIO_PIN);

#define LED_OFF         		GPIO_SetBits(GPIOC, GPIO_Pin_13);
#define LED_ON         			GPIO_ResetBits(GPIOC, GPIO_Pin_13);

void J10M_GPIO_Init(void);
void JDY_10M_Init(void);
void LED_GPIO_Init(void);


#endif


