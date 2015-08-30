/****
	*����11.0592M
	*
	****/
#include<stc15.h>

#define uchar unsigned char 
#define uint  unsigned int
#define ulong unsigned long

sbit Trig  = P1^0; //������������
sbit Echo  = P3^2; //�ز�����
sbit test  = P1^1; //����������

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
	distance_data=h;                //��������ĸ�8λ
    distance_data<<=8;                   //����16λ�ĸ�8λ
	distance_data=distance_data|l;//���8λ�ϲ���Ϊ16λ�������
    distance_data/=58; 					//��λΪcm
	return distance_data;	
}
void Int0_Isr() interrupt 0
{
	outcomeH =TH1;    //ȡ����ʱ����ֵ
    outcomeL =TL1;    //ȡ����ʱ����ֵ
    EX0=0; 
}



void main()
{
	uint distance;
   	Trig = 0;
	AUXR |= 0x80;	//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;	//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0x00;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 0;		//��ʱ��0����ʱ
	IT0=0;        //�ɸߵ�ƽ��͵�ƽ�������ⲿ�ж�
	EX0=0;        //�ر��ⲿ�ж�
	EA=1;         //�����ж�0

	while(1)
	{
			
		EA=0;
		distance = getDistance(outcomeH,outcomeL);
	    Trig=1;
       	Delay15us();
        Trig=0;         //����һ��15us�����壬��Trig����  
        while(Echo==0); //�ȴ�Echo�ز����ű�ߵ�ƽ
	    EX0=1;          //���ⲿ�ж�
	 	TH1=0;          //��ʱ��1����
        TL1=0;          //��ʱ��1����
	    TF1=0;          //
        TR1=0;          //������ʱ��0
   		EA=1;
	}
}