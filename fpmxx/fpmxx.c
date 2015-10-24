#include "MAIN.h"
#include "USART.h"
#include "fpmxx.h"


volatile unsigned char FPMXX_RECEICE_BUFFER[24];



//FINGERPRINTͨ��Э�鶨��
code unsigned char FPMXX_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //Э���ͷ
code unsigned char FPMXX_Get_Img[6] = {0x01,0x00,0x03,0x01,0x0,0x05};    //���ָ��ͼ��
code unsigned char FPMXX_Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //���ģ������
code unsigned char FP_Search[11]={0x01,0x0,0x08,0x04,0x01,0x0,0x0,0x03,0xA1,0x0,0xB2}; //����ָ��������Χ0 - 929
code unsigned char FP_Search_0_9[11]={0x01,0x0,0x08,0x04,0x01,0x0,0x0,0x0,0x13,0x0,0x21}; //����0-9��ָ��
code unsigned char FP_Img_To_Buffer1[7]={0x01,0x0,0x04,0x02,0x01,0x0,0x08}; //��ͼ����뵽BUFFER1
code unsigned char FP_Img_To_Buffer2[7]={0x01,0x0,0x04,0x02,0x02,0x0,0x09}; //��ͼ����뵽BUFFER2
code unsigned char FP_Reg_Model[6]={0x01,0x0,0x03,0x05,0x0,0x09}; //��BUFFER1��BUFFER2�ϳ�����ģ��
code unsigned char FP_Delet_All_Model[6]={0x01,0x0,0x03,0x0d,0x00,0x11};//ɾ��ָ��ģ�������е�ģ��
volatile unsigned char  FP_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//��BUFFER1�е��������ŵ�ָ����λ��
volatile unsigned char FP_Delete_Model[10]={0x01,0x00,0x07,0x0C,0x0,0x0,0x0,0x1,0x0,0x0}; //ɾ��ָ����ģ��
//volatile unsigned char FINGER_NUM;


/*------------------ FINGERPRINT������ --------------------------*/

void FINGERPRINT_Cmd_Send_Pack_Head(void) //���Ͱ�ͷ
{
		int i;
	
		for(i=0;i<6;i++) //��ͷ
    {
      UART_Send_Byte(FPMXX_Pack_Head[i]);   
    }
}



//FINGERPRINT_���ָ��ͼ������
void FINGERPRINT_Cmd_Get_Img(void)
{
    unsigned char i;

    FINGERPRINT_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
	
    for(i=0;i<6;i++) //�������� 0x1d
       UART_Send_Byte(FPMXX_Get_Img[i]);
}

//��ͼ��ת��������������Buffer1��
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
 	    unsigned char i;
    
	       FINGERPRINT_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
           
   		   for(i=0;i<7;i++)   //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
             {
      		   UART_Send_Byte(FP_Img_To_Buffer1[i]);
   		     }
}

//��ͼ��ת��������������Buffer2��
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
     unsigned char i;
           for(i=0;i<6;i++)    //���Ͱ�ͷ
	         {
    	       UART_Send_Byte(FPMXX_Pack_Head[i]);   
   		     }
           
   		   for(i=0;i<7;i++)   //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
             {
      		   UART_Send_Byte(FP_Img_To_Buffer2[i]);
   		     }
}

//��BUFFER1 �� BUFFER2 �е�������ϲ���ָ��ģ��
void FINGERPRINT_Cmd_Reg_Model(void)
{
    unsigned char i;    

    for(i=0;i<6;i++) //��ͷ
    {
      UART_Send_Byte(FPMXX_Pack_Head[i]);   
    }

    for(i=0;i<6;i++) //����ϲ�ָ��ģ��
    {
      UART_Send_Byte(FP_Reg_Model[i]);   
    }

}

//ɾ��ָ��ģ���������ָ��ģ��
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
     unsigned char i;    

    for(i=0;i<6;i++) //��ͷ
      UART_Send_Byte(FPMXX_Pack_Head[i]);   

    for(i=0;i<6;i++) //����ϲ�ָ��ģ��
      UART_Send_Byte(FP_Delet_All_Model[i]);   
}



//ɾ��ָ��ģ�����ָ��ָ��ģ��
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
	 

    for(i=0;i<6;i++) //��ͷ
      UART_Send_Byte(FPMXX_Pack_Head[i]);   

    for(i=0;i<10;i++) //����ϲ�ָ��ģ��
      UART_Send_Byte(FP_Delete_Model[i]);   
}




//���ָ��ģ������
void FINGERPRINT_Cmd_Get_Templete_Num()
{  unsigned int i;
   //unsigned char temp[14];

	 FINGERPRINT_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ

   //�������� 0x1d
   for(i=0;i<6;i++)
     UART_Send_Byte(FPMXX_Get_Templete_Count[i]);
   
  
}





//����ȫ���û�999ö
void FINGERPRINT_Cmd_Search_Finger(void)
{
       unsigned char i;	   
	    
			 FINGERPRINT_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ

       for(i=0;i<11;i++)
           {
    	      UART_Send_Byte(FP_Search[i]);   
   		   }


}


//����ȫ���û�999ö
void FINGERPRINT_Cmd_Search_Finger_Admin(void)
{
       unsigned char i;	   
			 
	     FINGERPRINT_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ

       for(i=0;i<11;i++)
           {
    	      UART_Send_Byte(FP_Search_0_9[i]);   
   		   }


}

void FINGERPRINT_Cmd_Save_Finger( unsigned char ucH_Char,unsigned char ucL_Char )
{
           unsigned long temp = 0;
		   unsigned char i;

//           SAVE_FINGER[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//��BUFFER1�е��������ŵ�ָ����λ��

           FP_Save_Finger[5] = ucH_Char;
           FP_Save_Finger[6] = ucL_Char;
           
		   for(i=0;i<7;i++)   //����У���
		   	   temp = temp + FP_Save_Finger[i];
			    
		   FP_Save_Finger[7]=(temp & 0x00FF00) >> 8; //���У������
		   FP_Save_Finger[8]= temp & 0x0000FF;
		   
          FINGERPRINT_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
	
           for(i=0;i<9;i++)  
      		   UART_Send_Byte(FP_Save_Finger[i]);      //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
}



//���շ������ݻ���
void FINGERPRINT_Receive_Data(unsigned char ucLength)
{
  unsigned char i;
  for (i=0;i<ucLength;i++)
     FPMXX_RECEICE_BUFFER[i] = UART_Receive_Byte();

}























/*
//ָ��������û�
unsigned char FP_add_new_user(unsigned char ucH_user,unsigned char ucL_user)
{
		
		       do {	          		     	 
                    FINGERPRINT_Cmd_Get_Img(); //���ָ��ͼ��
	                FINGERPRINT_Receive_Data(12); //����12�����ȵķ�����
                  }
               while ( UART1_FINGERPRINT_RECEVICE_BUFFER[9]!=0x0 ); //����Ƿ�ɹ��İ���ָ��


			  	 FINGERPRINT_Cmd_Img_To_Buffer1(); //��ͼ��ת��������������Buffer1��
		         FINGERPRINT_Recevice_Data(12);   //����12�����ȵķ�����

                do{ 
				     FINGERPRINT_Cmd_Get_Img(); //���ָ��ͼ��
				     FINGERPRINT_Recevice_Data(12); //����12�����ȵķ�����			 
				 }
				 while( UART1_FINGERPRINT_RECEVICE_BUFFER[9]!=0x0 );
                
				 FINGERPRINT_Cmd_Img_To_Buffer2(); //��ͼ��ת��������������Buffer2��
		         FINGERPRINT_Recevice_Data(12);   //����12�����ȵķ�����


				 FP_Cmd_Reg_Model();//ת����������
                 FINGERPRINT_Recevice_Data(12); 
				 
				 FINGERPRINT_Cmd_Save_Finger(ucH_user,ucL_user);                		         
                 FINGERPRINT_Recevice_Data(12);
              
		         return 0;





}


*/