//Filename: exti.c

#include "includes.h"

void EXTIKeyInit(void)
{
    // ����EXTIӳ��
    AFIO->EXTICR[0] &= ~(0xF << 4);  // EXTI1 -> PA1
		AFIO->EXTICR[0] |= (0x0 << 4);   // ��ȷӳ�䵽PA1

	    // �����½��ش���
    EXTI->FTSR |= (1uL<<1) ;
	  EXTI->RTSR |= (1uL<<1);      
    EXTI->IMR |= (1uL<<1);

	
	NVIC_EnableIRQ(EXTI1_IRQn);  //Open EXTI1

	NVIC_SetPriority(EXTI1_IRQn,1);

}

// EXTI0�жϷ�����
void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1<<1)) {
        // ���PA1��ǰ״̬����LED״̬
        if (GPIOA->IDR & (1<<1)) {
              LED(1,LED_OFF);  // �����ͷš���
        } else {
            LED(1,LED_ON);   // �������¡���
        }
        EXTI->PR = (1<<1);          // ����жϱ�־
    }
}
