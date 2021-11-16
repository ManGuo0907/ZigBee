/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   HC05蓝牙模块测试程序
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./usart/bsp_usart_blt.h"
#include "./systick/bsp_SysTick.h"
#include "bsp_jdy.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h" 
#include <string.h>
#include <stdlib.h>


char sendData[1024];
char linebuff[1024];

extern uint8_t   uart_buff[UART_BUFF_SIZE];
unsigned int Task_Delay[NumOfTask]; 
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	char* redata;
	uint16_t len;
		
	  //初始化systick
	SysTick_Init();
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;

	USART_Config();
	
	LED_GPIO_Config();
	Key_GPIO_Config();
	
  //JDY10M_Init();
  JDY10M_GPIO_Config();
	BLT_USART_Config();
	
	while(1)
	{
		JDY10M_Send_CMD( "AT+RESET\r\n",1);
		delay_ms(500);
		printf("响应：%s\n",uart_buff);
		
	}
}

/*********************************************END OF FILE**********************/
