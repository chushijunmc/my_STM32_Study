#include "stm32f10x.h"
#include "delay.h"

 /*void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }*/
 int main(void)
 {	
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    //ʹ��GPIOC�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;			    //PC13|PC14|PC15 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);			     //��ʼ��GPIOC
  	
  while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);					//���ö˿�λ
		GPIO_SetBits(GPIOC,GPIO_Pin_14);	
		GPIO_SetBits(GPIOC,GPIO_Pin_15);
		delay_ms(300);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);					//���ö˿�λ
		GPIO_ResetBits(GPIOC,GPIO_Pin_14);	
		GPIO_ResetBits(GPIOC,GPIO_Pin_15);
		delay_ms(300);
	}
}
