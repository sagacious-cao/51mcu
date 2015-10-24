#include"ch451.h"
#include"config.h"
// CH451 
// AT89C51 C���Գ���
//Web:http//winchiphead.com
//Author: yhw  2003.7



//����������Ĳ���
// sbit ch451_dclk=P1^7;                            //��������ʱ�������Ӽ���
// sbit ch451_din=P1^6;		                    // ���������������CH451����������
// sbit ch451_load=P1^5;                            //����������أ������Ӽ���
// sbit ch451_dout=P3^3;        	                     //INT1�������жϺͼ�ֵ�������룬��CH451���������
// uchar  ch451_key;		                    // ��ż����ж��ж�ȡ�ļ�ֵ
//********************************************

//��ʼ���ӳ���
		                    // ��ż����ж��ж�ȡ�ļ�ֵ
void ch451_init()
{
  ch451_din=0;                                     //�ȵͺ�ߣ�ѡ��4������
  ch451_din=1;

}
//*****************************************************

 //��������ӳ���
 //����һ�޷������ͱ����洢12�ֽڵ������֡�
 void ch451_write(unsigned int command)
{
  unsigned char i;	
  ch451_load=0;                                  //���ʼ       
  for(i=0;i<12;i++){                             //����12λ���ݣ���λ��ǰ
    ch451_din=command&1;				
    ch451_dclk=0;
    command>>=1;
    ch451_dclk=1;                               //��������Ч
  }
  ch451_load=1;                                 //��������
}



//*************************************************
//���������ӳ���MCU��451��һ�ֽ�
 unsigned char ch451_read()
{
  unsigned char i;
  unsigned char command,keycode;		//���������֣������ݴ洢��
  command=0x07;			               //�����451������	
  ch451_load=0;
  for(i=0;i<4;i++){
 
    ch451_din=command&1;		      //�������λ
    ch451_dclk=0;			 
    command>>=1;			      //������һλ
    ch451_dclk=1;			      //����ʱ����������֪ͨCH451����λ����
 }
  ch451_load=1;				      //��������������֪ͨCH451������������
  keycode=0;				      //���keycode
  for(i=0;i<7;i++){
    keycode<<=1;			      //��������keycode,��λ��ǰ,��λ�ں�
    keycode|=ch451_dout;		      //�Ӹߵ��Ͷ���451������
    ch451_dclk=0;			      //����ʱ��������֪ͨCH451�����һλ
    ch451_dclk=1;
 }
  return(keycode);			     //���ؼ�ֵ
}

