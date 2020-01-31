#define _DHT11_C_
#include "include.h"

/**
* ����:  DHT11�ɼ�Դ�ļ�
* ˵��:  �ɼ�������Ϊ:P0^0 ����DHT11.h�ļ����޸�
* ˵��:  �ɼ�����ʪ�����ݴ洢--DHT11Data[4]
* ˵��:  None
* ˵��:  None
* ֧��:  QQ946029359 --Ⱥ 607064330
* �Ա�:  https://shop411638453.taobao.com/
* ����:  С��
**/


uchar DHT11Data[4]={0};//��ʪ������(�¶ȸ�λ,�¶ȵ�λ,ʪ�ȸ�λ,ʪ�ȵ�λ)
uchar OvertimeCnt = 0;//ÿһ�����ż��whileѭ����ʱ����
uchar GatherRrrorCnt = 0;//�ɼ�����Ĵ���
uchar LastT=0,LastR=0;//��¼��һ�ε���ʪ��

/**
* @brief  DHT11��ʼ�ź�
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
   DelayMs(20);//��ʱ18ms����
   DHT11Pin=1;
   Delay10uS();Delay10uS();
	 Delay10uS();Delay10uS();
}

/**
* @brief  ��ȡDHT11��8λ��������
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
uchar DHT11_ReadByte()      //����һ���ֽ�
{
   uchar i=0,dat=0;
   for(i=0;i<8;i++)//ѭ������8λ����
   {        
      OvertimeCnt=0;		 
		  while(DHT11Pin==0 && OvertimeCnt<60)//�ȴ�50us�͵�ƽ��ȥ
		  {
        OvertimeCnt++;
      }
		  if(OvertimeCnt >60) goto ReadByteEnd;
			
      
			Delay10uS();
	    Delay10uS();//�ȴ�20uS֮����ȥ�ж����ŵĵ�ƽ
      
      dat<<=1;           //��������ǰ���ƶ�һλ,�������ݻᶪʧһλ
      if(DHT11Pin==1)    //����Ϊ1ʱ��ʹdat��1����������1
			{
         dat = dat + 1;
      }
      
			OvertimeCnt=0;
      while(DHT11Pin==1 && OvertimeCnt<40)//���������1�Ļ������д�Լ30uS�ĸߵ�ƽ����
			{
				OvertimeCnt++;
      }
			if(OvertimeCnt >40) goto  ReadByteEnd;
    }  
    return dat;
		
		ReadByteEnd:
		return 0;//������0����,,,�����Ļ��������У��͵�ʱ��Ӧ���Ǵ����
}


/**
* @brief  ��ȡDHT11��ʪ������
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void DHT11_Receive()//����40λ������
{
	uchar RH,RL,TH,TL,revise; 
	DHT11_start();
	if(DHT11Pin==0)//��Ӧ�������ź�
	{ 
		OvertimeCnt = 0;
		while(DHT11Pin==0 && OvertimeCnt < 80)//�ȴ�80uS�͵�ƽ��ȥ
		{
      OvertimeCnt++;
			nop_();
    }
		if(OvertimeCnt >80) goto  ReceiveEnd;
		
		while(DHT11Pin==1 && OvertimeCnt < 80)//�ȴ�80uS�ߵ�ƽ��ȥ
		{
      OvertimeCnt++;
			nop_();
    }
		if(OvertimeCnt >80) goto  ReceiveEnd;
		
		RH=DHT11_ReadByte();    //����ʪ�ȸ߰�λ  
		RL=DHT11_ReadByte();    //����ʪ�ȵͰ�λ(DHT11ʵ����û��С��)  
		TH=DHT11_ReadByte();    //�����¶ȸ߰�λ  
		TL=DHT11_ReadByte();    //�����¶ȵͰ�λ(DHT11ʵ����û��С��) 
		revise=DHT11_ReadByte(); //����У��λ
    
		Delay10uS();Delay10uS();
		Delay10uS();Delay10uS();
		Delay10uS();Delay10uS();//��ʱ60uS������50uS�͵�ƽ��ȥ
		DHT11Pin = 1;//ͨ��������
		
		
		if((RH+RL+TH+TL)==revise)//���У����Ƿ���ȷ
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
			if(abs(LastT-TH)<3 && abs(LastR-RH)<3)//������Ǻܴ�Ҳ��Ϊ����ȷ������
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
	if(GatherRrrorCnt>5)//����5�βɼ�����
	{
    GatherRrrorCnt = 0;
		DHT11Data[0]=0xff;
		DHT11Data[1]=0xff;
		DHT11Data[2]=0xff;
		DHT11Data[3]=0xff;
  }
}
