#define _DHT11_C_
#include "include.h"

/**
* 介绍:  DHT11采集源文件
* 说明:  采集的引脚为:P0^0 可在DHT11.h文件中修改
* 说明:  采集的温湿度数据存储--DHT11Data[4]
* 说明:  None
* 说明:  None
* 支持:  QQ946029359 --群 607064330
* 淘宝:  https://shop411638453.taobao.com/
* 作者:  小五
**/


uchar DHT11Data[4]={0};//温湿度数据(温度高位,温度低位,湿度高位,湿度低位)
uchar OvertimeCnt = 0;//每一次引脚检测while循环超时变量
uchar GatherRrrorCnt = 0;//采集出错的次数
uchar LastT=0,LastR=0;//记录上一次的温湿度

/**
* @brief  DHT11开始信号
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void DHT11_start()
{
   DHT11Pin=1;
   Delay10uS();
   DHT11Pin=0;
   DelayMs(20);//延时18ms以上
   DHT11Pin=1;
   Delay10uS();Delay10uS();
	 Delay10uS();Delay10uS();
}

/**
* @brief  读取DHT11的8位返回数据
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
uchar DHT11_ReadByte()      //接收一个字节
{
   uchar i=0,dat=0;
   for(i=0;i<8;i++)//循环接收8位数据
   {        
      OvertimeCnt=0;		 
		  while(DHT11Pin==0 && OvertimeCnt<60)//等待50us低电平过去
		  {
        OvertimeCnt++;
      }
		  if(OvertimeCnt >60) goto ReadByteEnd;
			
      
			Delay10uS();
	    Delay10uS();//等待20uS之后再去判断引脚的电平
      
      dat<<=1;           //接收数居前先移动一位,否则数据会丢失一位
      if(DHT11Pin==1)    //数据为1时，使dat加1来接收数据1
			{
         dat = dat + 1;
      }
      
			OvertimeCnt=0;
      while(DHT11Pin==1 && OvertimeCnt<40)//如果数据是1的话还会有大约30uS的高电平存在
			{
				OvertimeCnt++;
      }
			if(OvertimeCnt >40) goto  ReadByteEnd;
    }  
    return dat;
		
		ReadByteEnd:
		return 0;//出错返回0数据,,,这样的话数据最后校验和的时候应该是错误的
}


/**
* @brief  读取DHT11温湿度数据
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void DHT11_Receive()//接收40位的数据
{
	uchar RH,RL,TH,TL,revise; 
	DHT11_start();
	if(DHT11Pin==0)//响应拉低了信号
	{ 
		OvertimeCnt = 0;
		while(DHT11Pin==0 && OvertimeCnt < 80)//等待80uS低电平过去
		{
      OvertimeCnt++;
			nop_();
    }
		if(OvertimeCnt >80) goto  ReceiveEnd;
		
		while(DHT11Pin==1 && OvertimeCnt < 80)//等待80uS高电平过去
		{
      OvertimeCnt++;
			nop_();
    }
		if(OvertimeCnt >80) goto  ReceiveEnd;
		
		RH=DHT11_ReadByte();    //接收湿度高八位  
		RL=DHT11_ReadByte();    //接收湿度低八位(DHT11实际上没有小数)  
		TH=DHT11_ReadByte();    //接收温度高八位  
		TL=DHT11_ReadByte();    //接收温度低八位(DHT11实际上没有小数) 
		revise=DHT11_ReadByte(); //接收校正位
    
		Delay10uS();Delay10uS();
		Delay10uS();Delay10uS();
		Delay10uS();Delay10uS();//延时60uS让最后的50uS低电平过去
		DHT11Pin = 1;//通信完拉高
		
		
		if((RH+RL+TH+TL)==revise)//检测校验和是否正确
		{
			LastT = TH;
			LastR = RH;
			DHT11Data[0]=TH;
		  DHT11Data[1]=TL;
		  DHT11Data[2]=RH;
		  DHT11Data[3]=RL;
			GatherRrrorCnt = 0;
		} 
		else
		{ 
			if(abs(LastT-TH)<3 && abs(LastR-RH)<3)//如果误差不是很大也认为是正确的数据
			{
        DHT11Data[0]=TH;
				DHT11Data[1]=TL;
				DHT11Data[2]=RH;
				DHT11Data[3]=RL;
				GatherRrrorCnt = 0;
      }
			else
			{
        GatherRrrorCnt++;
      }
    }
	}
	ReceiveEnd:
	GatherRrrorCnt ++ ;
	if(GatherRrrorCnt>5)//超过5次采集错误
	{
    GatherRrrorCnt = 0;
		DHT11Data[0]=0xff;
		DHT11Data[1]=0xff;
		DHT11Data[2]=0xff;
		DHT11Data[3]=0xff;
  }
}
