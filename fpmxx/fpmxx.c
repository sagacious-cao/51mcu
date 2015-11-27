#include "MAIN.h"
#include "USART.h"
#include "fpmxx.h"


volatile unsigned char FPMXX_RECEICE_BUFFER[24];



//FINGERPRINT通信协议定义
code unsigned char FPMXX_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //协议包头
code unsigned char FPMXX_Get_Img[6] = {0x01,0x00,0x03,0x01,0x0,0x05};    //获得指纹图像
code unsigned char FPMXX_Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //获得模版总数
code unsigned char FP_Search[11]={0x01,0x0,0x08,0x04,0x01,0x0,0x0,0x03,0xA1,0x0,0xB2}; //搜索指纹搜索范围0 - 929
code unsigned char FP_Search_0_9[11]={0x01,0x0,0x08,0x04,0x01,0x0,0x0,0x0,0x13,0x0,0x21}; //搜索0-9号指纹
code unsigned char FP_Img_To_Buffer1[7]={0x01,0x0,0x04,0x02,0x01,0x0,0x08}; //将图像放入到BUFFER1
code unsigned char FP_Img_To_Buffer2[7]={0x01,0x0,0x04,0x02,0x02,0x0,0x09}; //将图像放入到BUFFER2
code unsigned char FP_Reg_Model[6]={0x01,0x0,0x03,0x05,0x0,0x09}; //将BUFFER1跟BUFFER2合成特征模版
code unsigned char FP_Delet_All_Model[6]={0x01,0x0,0x03,0x0d,0x00,0x11};//删除指纹模块里所有的模版
volatile unsigned char  FP_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置
volatile unsigned char FP_Delete_Model[10]={0x01,0x00,0x07,0x0C,0x0,0x0,0x0,0x1,0x0,0x0}; //删除指定的模版
//volatile unsigned char FINGER_NUM;


/*------------------ FINGERPRINT命令字 --------------------------*/

void FINGERPRINT_Cmd_Send_Pack_Head(void) //发送包头
{
		int i;
	
		for(i=0;i<6;i++) //包头
    {
      UART_Send_Byte(FPMXX_Pack_Head[i]);   
    }
}



//FINGERPRINT_获得指纹图像命令
void FINGERPRINT_Cmd_Get_Img(void)
{
    unsigned char i;

    FINGERPRINT_Cmd_Send_Pack_Head(); //发送通信协议包头
	
    for(i=0;i<6;i++) //发送命令 0x1d
       UART_Send_Byte(FPMXX_Get_Img[i]);
}

//讲图像转换成特征码存放在Buffer1中
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
 	    unsigned char i;
    
	       FINGERPRINT_Cmd_Send_Pack_Head(); //发送通信协议包头
           
   		   for(i=0;i<7;i++)   //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
             {
      		   UART_Send_Byte(FP_Img_To_Buffer1[i]);
   		     }
}

//将图像转换成特征码存放在Buffer2中
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
     unsigned char i;
           for(i=0;i<6;i++)    //发送包头
	         {
    	       UART_Send_Byte(FPMXX_Pack_Head[i]);   
   		     }
           
   		   for(i=0;i<7;i++)   //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
             {
      		   UART_Send_Byte(FP_Img_To_Buffer2[i]);
   		     }
}

//将BUFFER1 跟 BUFFER2 中的特征码合并成指纹模版
void FINGERPRINT_Cmd_Reg_Model(void)
{
    unsigned char i;    

    for(i=0;i<6;i++) //包头
    {
      UART_Send_Byte(FPMXX_Pack_Head[i]);   
    }

    for(i=0;i<6;i++) //命令合并指纹模版
    {
      UART_Send_Byte(FP_Reg_Model[i]);   
    }

}

//删除指纹模块里的所有指纹模版
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
     unsigned char i;    

    for(i=0;i<6;i++) //包头
      UART_Send_Byte(FPMXX_Pack_Head[i]);   

    for(i=0;i<6;i++) //命令合并指纹模版
      UART_Send_Byte(FP_Delet_All_Model[i]);   
}



//删除指纹模块里的指定指纹模版
void FINGERPRINT_Cmd_Delete_Model(unsigned int uiID_temp)
{
    volatile unsigned int uiSum_temp = 0;
	unsigned char i;    
	 
	FP_Delete_Model[4]=(uiID_temp&0xFF00)>>8;
	FP_Delete_Model[5]=(uiID_temp&0x00FF);
	
	for(i=0;i<8;i++)
	    uiSum_temp = uiSum_temp + FP_Delete_Model[i];
	
	//UART0_Send_Byte(uiSum_temp);	
			
	FP_Delete_Model[8]=(uiSum_temp&0xFF00)>>8;
	FP_Delete_Model[9]=uiSum_temp&0x00FF;
	 

    for(i=0;i<6;i++) //包头
      UART_Send_Byte(FPMXX_Pack_Head[i]);   

    for(i=0;i<10;i++) //命令合并指纹模版
      UART_Send_Byte(FP_Delete_Model[i]);   
}




//获得指纹模板数量
void FINGERPRINT_Cmd_Get_Templete_Num()
{  unsigned int i;
   //unsigned char temp[14];

	 FINGERPRINT_Cmd_Send_Pack_Head(); //发送通信协议包头

   //发送命令 0x1d
   for(i=0;i<6;i++)
     UART_Send_Byte(FPMXX_Get_Templete_Count[i]);
   
  
}





//搜索全部用户999枚
void FINGERPRINT_Cmd_Search_Finger(void)
{
       unsigned char i;	   
	    
			 FINGERPRINT_Cmd_Send_Pack_Head(); //发送通信协议包头

       for(i=0;i<11;i++)
           {
    	      UART_Send_Byte(FP_Search[i]);   
   		   }


}


//搜索全部用户999枚
void FINGERPRINT_Cmd_Search_Finger_Admin(void)
{
       unsigned char i;	   
			 
	     FINGERPRINT_Cmd_Send_Pack_Head(); //发送通信协议包头

       for(i=0;i<11;i++)
           {
    	      UART_Send_Byte(FP_Search_0_9[i]);   
   		   }


}

void FINGERPRINT_Cmd_Save_Finger( unsigned char ucH_Char,unsigned char ucL_Char )
{
           unsigned long temp = 0;
		   unsigned char i;

//           SAVE_FINGER[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置

           FP_Save_Finger[5] = ucH_Char;
           FP_Save_Finger[6] = ucL_Char;
           
		   for(i=0;i<7;i++)   //计算校验和
		   	   temp = temp + FP_Save_Finger[i];
			    
		   FP_Save_Finger[7]=(temp & 0x00FF00) >> 8; //存放校验数据
		   FP_Save_Finger[8]= temp & 0x0000FF;
		   
          FINGERPRINT_Cmd_Send_Pack_Head(); //发送通信协议包头
	
           for(i=0;i<9;i++)  
      		   UART_Send_Byte(FP_Save_Finger[i]);      //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
}



//接收反馈数据缓冲
void FINGERPRINT_Receive_Data(unsigned char ucLength)
{
  unsigned char i;
  for (i=0;i<ucLength;i++)
     FPMXX_RECEICE_BUFFER[i] = UART_Receive_Byte();

}























/*
//指纹添加新用户
unsigned char FP_add_new_user(unsigned char ucH_user,unsigned char ucL_user)
{
		
		       do {	          		     	 
                    FINGERPRINT_Cmd_Get_Img(); //获得指纹图像
	                FINGERPRINT_Receive_Data(12); //接收12个长度的反馈码
                  }
               while ( UART1_FINGERPRINT_RECEVICE_BUFFER[9]!=0x0 ); //检测是否成功的按了指纹


			  	 FINGERPRINT_Cmd_Img_To_Buffer1(); //将图像转换成特征码存放在Buffer1中
		         FINGERPRINT_Recevice_Data(12);   //接收12个长度的反馈码

                do{ 
				     FINGERPRINT_Cmd_Get_Img(); //获得指纹图像
				     FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码			 
				 }
				 while( UART1_FINGERPRINT_RECEVICE_BUFFER[9]!=0x0 );
                
				 FINGERPRINT_Cmd_Img_To_Buffer2(); //将图像转换成特征码存放在Buffer2中
		         FINGERPRINT_Recevice_Data(12);   //接收12个长度的反馈码


				 FP_Cmd_Reg_Model();//转换成特征码
                 FINGERPRINT_Recevice_Data(12); 
				 
				 FINGERPRINT_Cmd_Save_Finger(ucH_user,ucL_user);                		         
                 FINGERPRINT_Recevice_Data(12);
              
		         return 0;





}


*/