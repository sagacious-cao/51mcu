#include"config.h"
//须主程序定义的参数
 sbit ch451_dclk=P1^7;                            //串行数据时钟上升延激活
 sbit ch451_din=P1^6;		                    // 串行数据输出，接CH451的数据输入
 sbit ch451_load=P1^5;                            //串行命令加载，上升延激活
 sbit ch451_dout=P3^3;        	                     //INT1，键盘中断和键值数据输入，接CH451的数据输出

#define CH451_RESET     0x0201                           //复位
#define CH451_LEFTMOV   0x0300		            //设置移动方式-作移
#define CH451_LEFTCYC   0x0301		            //设置移动方式-左循
#define CH451_RIGHTMOV  0x0302		            //设置移动方式-右移
#define CH451_RIGHTCYC  0x0303		            //设置移动方式-右循	
#define CH451_SYSOFF    0x0400                      //关显示、键盘、看门狗
#define CH451_SYSON1    0x0401                      //开显示
#define CH451_SYSON2    0x0403                      //开显示、键盘
#define CH451_SYSON3    0x0407                      //开显示、键盘、看门狗功能
#define CH451_DSP       0x0500                      //设置默认显示方式
#define CH451_BCD       0x0580                      //设置BCD译码方式
#define CH451_TWINKLE   0x0600		            //设置闪烁控制
#define CH451_DIG0      0x0800                      //数码管位0显示
#define CH451_DIG1      0x0900		            //数码管位1显示 
#define CH451_DIG2      0x0a00		            //数码管位2显示
#define CH451_DIG3      0x0b00		            //数码管位3显示
#define CH451_DIG4      0x0c00		            //数码管位4显示
#define CH451_DIG5      0x0d00	                    //数码管位5显示	
#define CH451_DIG6      0x0e00	                    //数码管位6显示	
#define CH451_DIG7      0x0f00		            //数码管位7显示

//********************************************
void ch451_init();
void ch451_write(unsigned int command);
unsigned char ch451_read();
