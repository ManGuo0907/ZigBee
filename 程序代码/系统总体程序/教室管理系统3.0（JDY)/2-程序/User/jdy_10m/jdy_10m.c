#include "jdy_10m.h"
#include "delay.h"
#include "usart3.h"

void J10M_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		/*????GPIOʱ??*/
		RCC_APB2PeriphClockCmd( JDY_STAT_GPIO_CLK|JDY_PWRC_GPIO_CLK, ENABLE); 

		GPIO_InitStructure.GPIO_Pin = JDY_STAT_GPIO_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(JDY_STAT_GPIO_PORT, &GPIO_InitStructure);	
	
		
		GPIO_InitStructure.GPIO_Pin = JDY_PWRC_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(JDY_PWRC_GPIO_PORT, &GPIO_InitStructure);	

}

void JDY_10M_Init(void)
{
	//J10M_GPIO_Init();
	
	Usart_SendString(USART1,"AT+NETID123456789ABC\r\n");
	DelayMs(1000);
	Usart_SendString(USART1,"AT+NAMEBOY0\r\n");
	DelayMs(1000);
//	Usart_SendString(USART2,"AT+MADDR01\r\n");
//	delayms(1000);
	Usart_SendString(USART1,"AT+RESET\r\n");
	DelayMs(1000);
	
	
}

void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

		/*????GPIOʱ??*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
}


