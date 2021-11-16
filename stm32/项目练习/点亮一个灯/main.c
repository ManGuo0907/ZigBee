#include "stm32f10x.h"

int main (void)
{
	# if 0
	*(unsigned int*)0x40021018 |=( (1)<<3);
	*(unsigned int*)0x40010C00 |=( (1)<<(4*0));
	*(unsigned int*)0x40010C0C &=~(1<<0);
	#else
	RCC_APB2ENR |=((1) <<3);
	GPIOB_CRL |=((1)<<(4*0));
	GPIOB_ODR &=~(1<<0);
	
	#endif
}

void  SystemInit(void)
{
	//?
	
}

