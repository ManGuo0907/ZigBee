#ifndef __BSP_JDY_H
#define	__BSP_JDY_H


#include "stm32f10x.h"
#include "./systick/bsp_SysTick.h"

#define delay_ms 			mdelay
#define JDY10M_USART  USART2


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define JDY_STAT_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define JDY_STAT_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define JDY_STAT_GPIO_PIN		    GPIO_Pin_13			          /* 连接到JDY STAT引脚的GPIO */

#define JDY_PWRC_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define JDY_PWRC_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define JDY_PWRC_GPIO_PIN		    GPIO_Pin_14		          /* 连接到JDY PWRC引脚的GPIO */



#define JDY_PWRC_HIGHT  		GPIO_SetBits(JDY_PWRC_GPIO_PORT, JDY_PWRC_GPIO_PIN);
#define JDY_PWRC_LOW  			GPIO_ResetBits(JDY_PWRC_GPIO_PORT, JDY_PWRC_GPIO_PIN);
#define JDY_STAT_LOW  			GPIO_ResetBits(JDY_STAT_GPIO_PORT, JDY_STAT_GPIO_PIN);
//IS_HC05_CONNECTED用于检查模块是否处于配对状态
#define IS_JDY10M_CONNECTED() 	GPIO_ReadInputDataBit(JDY_STAT_GPIO_PORT,JDY_STAT_GPIO_PIN)


/*信息输出*/
#define HC05_DEBUG_ON        1
#define HC05_DEBUG_FUNC_ON   1

#define HC05_INFO(fmt,arg...)           printf("<<-HC05-INFO->> "fmt"\n",##arg)
#define HC05_ERROR(fmt,arg...)          printf("<<-HC05-ERROR->> "fmt"\n",##arg)
#define HC05_DEBUG(fmt,arg...)          do{\
                                          if(HC05_DEBUG_ON)\
                                          printf("<<-HC05-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

#define HC05_DEBUG_FUNC()               do{\
                                         if(HC05_DEBUG_FUNC_ON)\
                                         printf("<<-HC05-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
                                       }while(0)

																			 
void JDY10M_Init(void);
uint8_t JDY10M_Send_CMD(char* cmd,uint8_t clean);
void JDY10M_SendString(char* str);	
void JDY10M_GPIO_Config(void);
#endif 







