#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "CountSensor.h"
#include "Encoder.h"

int16_t Num;

int main(void)
{
	OLED_Init();
	OLED_ShowString(2,3,"Booting.....");
	Delay_ms(500);
	OLED_Clear();
	LED_Init();
	CountSensor_Init();
	Encoder_Init();
	OLED_Clear();
	
	/*��ʾ��̬�ַ���*/
	
	
	OLED_ShowString(2, 1, "Count:");	//1��1����ʾ�ַ���Count
	
	while (1)
	{
		OLED_ShowNum(2, 7, CountSensor_Get(), 5);		//OLED����ˢ����ʾCountSensor_Get�ķ���ֵ
		OLED_ShowSignedNum(3, 7, Num+=Encoder_Get(), 5);		//OLED����ˢ����ʾCountSensor_Get�ķ���ֵ
	}
}
