#include "includes.h"


EXTI_InitTypeDef EXTI_InitStructure;

void exit_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

    NVIC_InitTypeDef NVIC_InitStructure;

    /* 1. ʹ��GPIOE��AFIOʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	    /* 2. ����PC9Ϊ�������� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // ��������
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /* 2. ����PE9Ϊ�������� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // ��������
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* 3. ��PE9ӳ�䵽EXTI9 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);

    /* 4. ����EXTI9Ϊ�����ش��� */
    EXTI_InitStructure.EXTI_Line = EXTI_Line9|EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // �����ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
		

    /* 5. ����NVIC�����ȼ����ж�ʹ�ܣ� */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; // EXTI9~5�����ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F; // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F; // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		
		    /* 5. ����NVIC�����ȼ����ж�ʹ�ܣ� */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn; // EXTI9~5�����ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F; // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F; // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
}

unsigned char EXIT_Flag = 0;


void EXTI4_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) // ����Ƿ���EXTI9����
    {
			EXTI_ClearITPendingBit(EXTI_Line9); // ����жϱ�־
			
			//EXIT_Flag++;
			if((EXIT_Flag++)%2){
				LED(0,LED_OFF);
				LED(1,LED_OFF);
			}else{
				LED(0,LED_ON);
				LED(1,LED_ON);
			}
        

        
    }
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) // ����Ƿ���EXTI9����
    {
			EXTI_ClearITPendingBit(EXTI_Line9); // ����жϱ�־
			
			//EXIT_Flag++;
			if((EXIT_Flag++)%2){
				LED(0,LED_OFF);
				LED(1,LED_OFF);
			}else{
				LED(0,LED_ON);
				LED(1,LED_ON);
			}
        

        
    }
}
