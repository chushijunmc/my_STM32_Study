#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Encoder.h"

int16_t Encoder_Count;

void Encoder_Init(void){

GPIO_InitTypeDef GPIO_InitStructrue;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //����GPIOB����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //����AFIO����
	/***
	AFIO���� Alternate function I/O�����ù��� IO��
	����Ҫ���������ܣ�һ���������ŵĸ��ù����ض��򣨱����ԣ���
	���������ж�����ѡ������������Ҳ�Ǹ��ù������ã�
	ֻ�������õĲ������ŵĸ��ã������ж�ͨ���ĸ��ã���
	����ʹ�õ��Ǻ��ߡ�
	*/
	
	GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_IPU; //�������룬Ĭ�ϸߵ�ƽģʽ
	GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  //����ΪPin14
	GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructrue);
	
	//GPIO_AFIODeInit(); //ȡ����ʼ�����ú���������ӳ�䡢�¼������Լ�EXTI���ã����Ĵ�������Ϊ��Ĭ������ֵ
	
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);	//ѡ������EXTI�ߵ�GPIO���ţ�ִ��AFIO��14������ѡ�������ӵ�GPIOB��ӦPB14����
	
	
	/**ִ��AFIO��14������ѡ�������ӵ�GPIOB��ӦPB14����
					EXTI14
						|						
		-----------------
	 /    /            \
	 -------------------
				|  
			B14
	*/
	
	
	/**��ʼ��ʼ��EXTI**/
	EXTI_InitStructure.EXTI_Line=EXTI_Line0 | EXTI_Line1;  //���õ��ж��ߣ�ѡ��EXTI��14�ж���
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  //ָ��ѡ���ж��ߵ���״̬
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; //�����ⲿ�ж���ģʽ�����ж�ģʽ��Ŀǰ����EXTI_Mode_Interrupt�������¼�ģʽ��EXTI_Mode_Event��
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//ָ�������źŵ���Ч���أ������½��ش�������NVIC�����ж�
	/**
	EXTI_Trigger_Rising �����ش���
  EXTI_Trigger_Falling �½��ش���
  EXTI_Trigger_Rising_Falling �������½��ض�����
	*/
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����жϷ���ķ�ʽ�������м�����ռ���ȼ�����Ӧ���ȼ����ܹ����ĸ��飬��n����n����ռ���ȼ�����4-n����Ӧ���ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn; //ָ���ж�ͨ�������ر� ͨ����IRQn_Type������GotoDefinition�����ļ�stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ָ���ж�ͨ����ʹ�ܻ���ʧ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //ָ����ѡͨ����ռ���ȼ� �����ֵ��0-15��ֵ��NVIC_Priority_Table
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //ָ����ѡͨ����Ӧ���ȼ������ֵ��0-15��ֵ��NVIC_Priority_Table
	
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn; //ָ���ж�ͨ�������ر� ͨ����IRQn_Type������GotoDefinition�����ļ�stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ָ���ж�ͨ����ʹ�ܻ���ʧ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //ָ����ѡͨ����ռ���ȼ� �����ֵ��0-15��ֵ��NVIC_Priority_Table
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2; //ָ����ѡͨ����Ӧ���ȼ������ֵ��0-15��ֵ��NVIC_Priority_Table
	
	NVIC_Init(&NVIC_InitStructure);


}

int16_t Encoder_Get(void)
{
	int16_t tmp;
	tmp= Encoder_Count;
	Encoder_Count=0;
	return tmp;
}

void EXTI0_IRQHandler(){

if(EXTI_GetITStatus(EXTI_Line0)==SET){

		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0){
			Delay_ms(100);
		
			Encoder_Count ++;					//����ֵ����һ��
			}
			
		}
		
		
		//EXTI_ClearITPendingBit(EXTI_LineX)����жϱ�־λ�������жϱ�־λ��1�᲻�������жϺ�����ס���жϺ�����
		EXTI_ClearITPendingBit(EXTI_Line0);
	}

}

void EXTI1_IRQHandler(){

if(EXTI_GetITStatus(EXTI_Line1)==SET){

		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			if (GPIO_ReadInput  
	
				Encoder_Count --;					//����ֵ����һ��
			}
			
		}
		
		
		//EXTI_ClearITPendingBit(EXTI_LineX)����жϱ�־λ�������жϱ�־λ��1�᲻�������жϺ�����ס���жϺ�����
		EXTI_ClearITPendingBit(EXTI_Line1);
	}

}
