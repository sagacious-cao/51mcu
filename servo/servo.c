#include<stc15.h>

unsigned int numof10us = 0;
unsigned int time = 0;
sbit servo = P1^0;

/*定时器0初始化函数 晶振11.0592MHZ,时间10μs*/
void Timer0Init(void)		//10微秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x91;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

/*传入转动的角度*/
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
		servo(50); //转动50°
		if(numof10us >= time)
			servo = 0;
	}
}