#include"config.h"
//����������Ĳ���
 sbit ch451_dclk=P1^7;                            //��������ʱ�������Ӽ���
 sbit ch451_din=P1^6;		                    // ���������������CH451����������
 sbit ch451_load=P1^5;                            //����������أ������Ӽ���
 sbit ch451_dout=P3^3;        	                     //INT1�������жϺͼ�ֵ�������룬��CH451���������

#define CH451_RESET     0x0201                           //��λ
#define CH451_LEFTMOV   0x0300		            //�����ƶ���ʽ-����
#define CH451_LEFTCYC   0x0301		            //�����ƶ���ʽ-��ѭ
#define CH451_RIGHTMOV  0x0302		            //�����ƶ���ʽ-����
#define CH451_RIGHTCYC  0x0303		            //�����ƶ���ʽ-��ѭ	
#define CH451_SYSOFF    0x0400                      //����ʾ�����̡����Ź�
#define CH451_SYSON1    0x0401                      //����ʾ
#define CH451_SYSON2    0x0403                      //����ʾ������
#define CH451_SYSON3    0x0407                      //����ʾ�����̡����Ź�����
#define CH451_DSP       0x0500                      //����Ĭ����ʾ��ʽ
#define CH451_BCD       0x0580                      //����BCD���뷽ʽ
#define CH451_TWINKLE   0x0600		            //������˸����
#define CH451_DIG0      0x0800                      //�����λ0��ʾ
#define CH451_DIG1      0x0900		            //�����λ1��ʾ 
#define CH451_DIG2      0x0a00		            //�����λ2��ʾ
#define CH451_DIG3      0x0b00		            //�����λ3��ʾ
#define CH451_DIG4      0x0c00		            //�����λ4��ʾ
#define CH451_DIG5      0x0d00	                    //�����λ5��ʾ	
#define CH451_DIG6      0x0e00	                    //�����λ6��ʾ	
#define CH451_DIG7      0x0f00		            //�����λ7��ʾ

//********************************************
void ch451_init();
void ch451_write(unsigned int command);
unsigned char ch451_read();