//Filename: led.c

#include "includes.h"

//#define  GPIOB_ODR   *(unsigned int *)0x40010C0C

void LEDInit(void)
{
	
	//��ʼ��ʹ�ܼĴ���
	RCC->APB2ENR = 0x00000010;  //0b0000 0000 00110000 00000000 00010000 IOPC = 1;
	//��ʼ��GPIOC��13,14,15�ܽ�
	GPIOC->CRH = 0x33300000; //0b0011 0011 0011 0000 0000 0000 0000 0000 CNF15,14,13 = 00 MODE15,14,13 = 11;
	

}

void LED(Int08U w, LEDState s) //w-which(1or2), s-state(LED_ONorLED_OFF)
{
	switch(w)
	{
		case 0:
			if(s==LED_ON)
				//GPIOC_Pin13_���øߵ�λ
				GPIOC->BRR = 0x00002000; 
			/*(1uL<<13)*/

			else
				//GPIOC_Pin13_���õ͵�λ
			  GPIOC->BSRR = 0x00002000;
			/*(1uL<<13);*/
			  //GPIOB_ODR |= (1uL<<5);
			break;
		case 1:
			if(s==LED_ON)
				//GPIOC_Pin14_���øߵ�λ
			  GPIOC->BRR = 0x00004000;
			/*(1uL<<14);*/	
			else
				//GPIOC_Pin14_���õ͵�λ
				//GPIOE->ODR |= (1uL<<5);
			  GPIOC->BSRR = 0x00004000;
			/* (1uL<<14);*/
		case 2:
			if(s==LED_ON)
				//GPIOC_Pin15_���øߵ�λ
				//GPIOE->ODR &= ~(1uL<<5);
			  GPIOC->BRR = 0x00008000;
			/* (1uL<<15);	*/
			else
				//GPIOC_Pin15_���õ͵�λ
			  GPIOC->BSRR = 0x00008000;
			/*(1uL<<15);*/
			break;
		default:
			break;
	}	
}

