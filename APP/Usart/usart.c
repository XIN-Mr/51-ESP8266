#define _USART_C_
#include "include.h"

/**
* 介绍:  串口函数
* 说明:  利用定时器2达到 115200 hZ
* 说明:  可以用串口中断发送数据
* 说明:  利用定时器做了接收空闲检测
* 说明:  None
* 支持:  QQ946029359 --群 607064330
* 淘宝:  https://shop411638453.taobao.com/
* 作者:  小五
**/

#define FOSC 12000000L      //System frequency
#define BAUD 2400       //UART baudrate


bit UsartFlage = 0;
int UsartIdleCnt =0;
unsigned char  UsartReadCnt = 0;
unsigned char  UsartReadCntCopy = 0;
unsigned char  UsartReceive[ReadLength] = {0};

unsigned char *UsartSendData;
unsigned char UsartSendDataCnt;

/**
* @brief  串口初始化函数
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
//void InitUART(long Baud)
//{
//	if(Baud == 115200)
//	{
//    SCON=0x50; //串口工作方式1，8位UART，波特率可变  
//		TH2=0xFF;           
//		TL2=0xFD;    //波特率:115200 晶振=11.0592MHz 
//		RCAP2H=0xFF;   
//		RCAP2L=0xFD; //16位自动再装入值

//		/*****************/
//		TCLK=1;   
//		RCLK=1;   
//		C_T2=0;   
//		EXEN2=0; //波特率发生器工作方式
//    
//		/*****************/
//		TR2=1 ; //定时器2开始
//  }
//	else
//	{
//		TMOD |= 0x20;
//		SCON = 0x50;
//    switch(Baud)
//		{
//      case 2400  :TH1 = 0xF4;TL1 = TH1;PCON = 0x00;break;
//			case 4800  :TH1 = 0xFA;TL1 = TH1;PCON = 0x00;break;
//			case 9600  :TH1 = 0xFD;TL1 = TH1;PCON = 0x00;break;
//			case 14400 :TH1 = 0xFE;TL1 = TH1;PCON = 0x00;break;
//			case 19200 :TH1 = 0xFD;TL1 = TH1;PCON = 0x80;break;
//			default    :TH1 = 0xFD;TL1 = TH1;PCON = 0x00;break;
//    }
//		
//	  TR1 = 1;
//  }
//	EA = 1;//总中断
//	ES = 1;//串口中断
//}



void InitUART()
{
    SCON = 0x50;            //8-bit variable UART
    TL2 = RCAP2L = (65536-(FOSC/32/BAUD));            //Set auto-reload vaule  65,506
    TH2 = RCAP2H = (65536-(FOSC/32/BAUD)) >> 8;
    T2CON = 0x34;           //Timer2 start run
    ES = 1;                 //Enable UART interrupt
    EA = 1;                 //Open master interrupt switch
}


/**
* @brief  串口发送函数
* @param  value--发送的数据
* @param  None
* @param  None
* @retval None
* @example 
**/
void UartSend(unsigned char value) 
{
	ES=0;  //关闭串口中断--使用Printf 需要屏蔽 
	TI=0;   //清发送完毕中断请求标志位   
	SBUF=value; //发送  
	while(TI==0); //等待发送完毕   
	TI=0;   //清发送完毕中断请求标志位 --使用Printf 需要屏蔽   
	ES=1;  //允许串口中断  --使用Printf 需要屏蔽 
}

/**
* @brief  串口发送函数中断发送
* @param  *value--数据的地址
* @param  DataLen--数据的个数
* @param  None
* @retval None
* @example 
**/
void UartSendTI(unsigned char *value,int DataLen) 
{
	UsartSendData = value;
	UsartSendDataCnt = DataLen;
	TI = 1;
}


/**
* @brief  串口中断函数
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void UARTInterrupt(void) interrupt 4
{
	if(RI)
	{
		RI=0;
		UsartReceive[UsartReadCnt]=SBUF;//接收串口数据
		UsartReadCnt++;
		if(UsartReadCnt>ReadLength-2)//防止溢出
		{
			UsartReadCnt = 0;
    }
	}
	if(TI)
	{
		TI = 0;
		if(UsartSendDataCnt>0)
		{
      SBUF = *UsartSendData++;
		  UsartSendDataCnt--;
    }
		else
		{
      TI = 0;
    }
  }
}
/**
* @brief  加入此函数可使用printf 发送数据
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
char putchar(char c)  
{  
    UartSend(c);  
    return c;  
}  

/*

//以下代码是自己写的printf发送 
void UartSendByte(unsigned char c)  
{  
    if(c=='\n')//如果遇到\n就换行  
    {  
        //发送CR(carriage return)  
        SBUF=0x0D;   
        while(!TI);//等待发送完成  
        TI=0;  
          
        //发送 LF(NL line feed,new line)  
        SBUF=0x0A;   
        while(!TI);//等待发送完成  
        TI=0;         
    }  
    else  
    {  
        SBUF=c;  
        while(!TI);//等待发送完成  
        TI=0;  
    }  
}  

void sendstring(unsigned char *string)//此处*string相当于数组  
{  
    while(*string!='\0')//判断是否到字符串末尾  
    {  
        UartSendByte(*string);  
        string++;  
    }  
}  
  
void uart_printf(const char *fmt,...)  
{ 
    va_list ap;  
    char xdata string[100];//访问内部拓展RAM，非访问外部RAM，不能超过内部拓展RAM大小(此处为1024) 
      
    va_start(ap,fmt);  
    vsprintf(string,fmt,ap);//此处也可以使用sprintf函数，用法差不多，稍加修改即可，此处略去  
    sendstring(string);  
    va_end(ap);  
}  

*/