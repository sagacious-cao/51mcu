#include<stc15.h>

unsigned int numof10us = 0;
unsigned int time = 0;
sbit servo = P1^0;

/*��ʱ��0��ʼ������ ����11.0592MHZ,ʱ��10��s*/
void Timer0Init(void)		//10΢��@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x91;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

/*����ת���ĽǶ�*/
void servo(int angle)
{
	time = angle/180*200;	
}

void Timer0Isr() interrupt 1
{
	if(numof10us ==2000)
	{
		numof10us = 0;
		servo = 1;
	}
	numof10us++;	
}


void main()
{
	
	servo = 0;
	Timer0Init();
	ET0 = 1;
	EA = 1;
	while(1)
	{
		servo(50); //ת��50��
		if(numof10us >= time)
			servo = 0;
	}
}