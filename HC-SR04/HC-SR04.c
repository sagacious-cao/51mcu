/****
	*晶振11.0592M
	*
	****/
#include<stc15.h>

#define uchar unsigned char 
#define uint  unsigned int
#define ulong unsigned long

sbit Trig  = P1^0; //产生脉冲引脚
sbit Echo  = P3^2; //回波引脚
sbit test  = P1^1; //测试用引脚

uchar outcomeH = 0x00;
uchar outcomeL = 0x00;

void Delay15us()	
{
	unsigned char i;

	i = 39;
	while (--i);
}

uint getDistance(uchar h, uchar l)
{
	uint distance_data = 0;
	distance_data=h;                //测量结果的高8位
    distance_data<<=8;                   //放入16位的高8位
	distance_data=distance_data|l;//与低8位合并成为16位结果数据
    distance_data/=58; 					//单位为cm
	return distance_data;	
}
void Int0_Isr() interrupt 0
{
	outcomeH =TH1;    //取出定时器的值
    outcomeL =TL1;    //取出定时器的值
    EX0=0; 
}



void main()
{
	uint distance;
   	Trig = 0;
	AUXR |= 0x80;	//定时器时钟1T模式
	TMOD &= 0xF0;	//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x00;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时
	IT0=0;        //由高电平变低电平，触发外部中断
	EX0=0;        //关闭外部中断
	EA=1;         //打开总中断0

	while(1)
	{
			
		EA=0;
		distance = getDistance(outcomeH,outcomeL);
	    Trig=1;
       	Delay15us();
        Trig=0;         //产生一个15us的脉冲，在Trig引脚  
        while(Echo==0); //等待Echo回波引脚变高电平
	    EX0=1;          //打开外部中断
	 	TH1=0;          //定时器1清零
        TL1=0;          //定时器1清零
	    TF1=0;          //
        TR1=0;          //启动定时器0
   		EA=1;
	}
}