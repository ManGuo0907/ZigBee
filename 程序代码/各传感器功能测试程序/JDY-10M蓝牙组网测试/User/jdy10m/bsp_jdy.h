#ifndef __BSP_JDY_H
#define	__BSP_JDY_H


#include "stm32f10x.h"
#include "./systick/bsp_SysTick.h"

#define delay_ms 			mdelay
#define JDY10M_USART  USART2


/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define JDY_STAT_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define JDY_STAT_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define JDY_STAT_GPIO_PIN		    GPIO_Pin_13			          /* ���ӵ�JDY STAT���ŵ�GPIO */

#define JDY_PWRC_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define JDY_PWRC_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define JDY_PWRC_GPIO_PIN		    GPIO_Pin_14		          /* ���ӵ�JDY PWRC���ŵ�GPIO */



#define JDY_PWRC_HIGHT  		GPIO_SetBits(JDY_PWRC_GPIO_PORT, JDY_PWRC_GPIO_PIN);
#define JDY_PWRC_LOW  			GPIO_ResetBits(JDY_PWRC_GPIO_PORT, JDY_PWRC_GPIO_PIN);
#define JDY_STAT_LOW  			GPIO_ResetBits(JDY_STAT_GPIO_PORT, JDY_STAT_GPIO_PIN);
//IS_HC05_CONNECTED���ڼ��ģ���Ƿ������״̬
#define IS_JDY10M_CONNECTED() 	GPIO_ReadInputDataBit(JDY_STAT_GPIO_PORT,JDY_STAT_GPIO_PIN)


/*��Ϣ���*/
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







