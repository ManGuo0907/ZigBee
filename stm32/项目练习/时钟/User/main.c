#include "stm32f10x.h"
#include "bsp_led.h"

void Delay(uint32_t count)
{
	for(;count!=0;count--);
}

int main(void)
{
	while(1)
	{
	LED_GPIO_Config();
	GPIO_SetBits(LED_G_GPIO_PORT,LED_GPIO_PIN);
	GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);    
	}
	
}

  //