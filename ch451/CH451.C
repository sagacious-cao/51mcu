#include"ch451.h"
#include"config.h"
// CH451 
// AT89C51 C语言程序
//Web:http//winchiphead.com
//Author: yhw  2003.7



//须主程序定义的参数
// sbit ch451_dclk=P1^7;                            //串行数据时钟上升延激活
// sbit ch451_din=P1^6;		                    // 串行数据输出，接CH451的数据输入
// sbit ch451_load=P1^5;                            //串行命令加载，上升延激活
// sbit ch451_dout=P3^3;        	                     //INT1，键盘中断和键值数据输入，接CH451的数据输出
// uchar  ch451_key;		                    // 存放键盘中断中读取的键值
//********************************************

//初始化子程序
		                    // 存放键盘中断中读取的键值
void ch451_init()
{
  ch451_din=0;                                     //先低后高，选择4线输入
  ch451_din=1;

}
//*****************************************************

 //输出命令子程序
 //定义一无符号整型变量存储12字节的命令字。
 void ch451_write(unsigned int command)
{
  unsigned char i;	
  ch451_load=0;                                  //命令开始       
  for(i=0;i<12;i++){                             //送入12位数据，低位在前
    ch451_din=command&1;				
    ch451_dclk=0;
    command>>=1;
    ch451_dclk=1;                               //上升沿有效
  }
  ch451_load=1;                                 //加载数据
}



//*************************************************
//输入命令子程序，MCU从451读一字节
 unsigned char ch451_read()
{
  unsigned char i;
  unsigned char command,keycode;		//定义命令字，和数据存储器
  command=0x07;			               //输入读451命令字	
  ch451_load=0;
  for(i=0;i<4;i++){
 
    ch451_din=command&1;		      //送入最低位
    ch451_dclk=0;			 
    command>>=1;			      //往右移一位
    ch451_dclk=1;			      //产生时钟上升沿锁通知CH451输入位数据
 }
  ch451_load=1;				      //产生加载上升沿通知CH451处理命令数据
  keycode=0;				      //清除keycode
  for(i=0;i<7;i++){
    keycode<<=1;			      //数据移入keycode,高位在前,低位在后
    keycode|=ch451_dout;		      //从高到低读入451的数据
    ch451_dclk=0;			      //产生时钟下升沿通知CH451输出下一位
    ch451_dclk=1;
 }
  return(keycode);			     //反回键值
}


