#include"bsp_key.h"

void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin =KEY1_G_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(KEY1_GPIO_PORT,GPIO_InitStruct);
}
