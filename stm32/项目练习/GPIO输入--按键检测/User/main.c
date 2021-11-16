#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"

void Delay(uint32_t count)
{
	for(;count!=0;count--);
}

int main(void)
{
	LED_GPIO_Config();
	KEY_GPIO_Config();
	
	while(1)
	{
		if(Key_Scan(KEY1_G_GPIO_PORT,KEY1_G_GPIO_PIN) ==KEY_ON)
			LED_G_TOGGLE;
		
	}
	
}

  //