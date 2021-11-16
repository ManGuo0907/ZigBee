/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "jdy_10m.h"
#include "bsp_SysTick.h"

uint8_t uart_buff[UART_BUFF_SIZE];
unsigned int Task_Delay[NumOfTask]; 

char str[]={"AAFB002B33323134"};
uint8_t strhex1[]={0xAA,0xFB,0xFF,0xFF,0x41,0x42,0x43};
uint8_t strhex2[]={0xAA,0xFB,0xFF,0xFF,0x44,0x45,0x46};
uint8_t strhex3[]={0xAA,0xFB,0xFF,0xFF,0x47,0x48,0x49};

uint8_t strdec1[]={170,251,255,255,97,98,99};
uint8_t strdec2[]={170,251,255,255,97,98,99};
uint8_t strdec3[]={170,251,255,255,97,98,99};
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	
	//初始化systick
	SysTick_Init();
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART1_Config();
	USART2_Config();
	J10M_GPIO_Init();
  LED_GPIO_Init();
//	JDY_PWRC_LOW;
	
//	printf("AT+NAME\r\n");
//	
	Usart_SendString(USART2,"AT+NETID123456789ABC\r\n");
	delayms(1000);
	Usart_SendString(USART2,"AT+NAMEBOY0\r\n");
	delayms(1000);
////	Usart_SendString(USART2,"AT+MADDR01\r\n");
////	delayms(1000);
	Usart_SendString(USART2,"AT+RESET\r\n");
	delayms(1000);
	
//	StringToHex(str,strhex);
//	printf("%s\n",strhex);
//  printf("%x\n",str);
//	
   // JDY_PWRC_HIGHT;
  while(1)
	{			
		printf_Usart2("%s\n",strhex1);
		//Usart_SendArray(USART2,strdec,7);
	  delayms(1000);
//		USART_Cmd(USART2,DISABLE);
//		delayms(500);
//		USART_Cmd(USART2,ENABLE);
//		JDY_PWRC_HIGHT;
//		printf_Usart2("%s\n",strhex);
	//	Usart_SendString(USART2,strhex);
		LED_ON;
		delayms(1000);
		LED_OFF;
		
	}
}
/*********************************************END OF FILE**********************/
