//Filename: key.c

#include "includes.h"

void KEYInit(void)
{
		RCC->APB2ENR |= (1uL<<2);     //ʹ��GPIOAʱ��
		RCC->APB2ENR |= (1uL<<0);     //AFIO Enable
		   
	  
    GPIOA->CRL &= ~(0xF << 4);  // ���PA1����λ
    GPIOA->CRL |= (0x8 << 4);   // ����ģʽ(0b1000)	
		GPIOA->ODR |= (1uL << 1);
}


