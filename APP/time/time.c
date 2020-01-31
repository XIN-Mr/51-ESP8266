#define _TIME_C_
#include "include.h"

int TimeCnt = 0;

void Delay10uS()
{
  nop_();
	nop_();
	nop_();
	nop_();
	nop_();
	nop_();
}

void DelayMs(int s)
{
	while(s--)
  {
    delay1ms();
  }
}

void delay1ms(void)   //误差 -0.651041666667us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}

//定时器初始化
void InitTimer0(void)
{
    TMOD |= 0x01;//用|=防止配置冲突
    TH0 = (65536 - 5000)/256;
    TL0 = (65536 - 5000)%256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void Timer0Interrupt(void) interrupt 1
{
	TH0 = (65536 - 5000)/256;
	TL0 = (65536 - 5000)%256;
	
	TimeCnt ++;
	
	if (UsartReadCnt != 0)//如果接收到数据了
	{
			if (UsartIdleCnt == UsartReadCnt)//数据个数一段时间没了变化
			{
				UsartReadCntCopy = UsartReadCnt;
				UsartReadCnt = 0;//清零数据个数
				UsartIdleCnt = 0;//清零
				UsartFlage = 1;
			}
			else
			{
				UsartIdleCnt = UsartReadCnt;
			}
	}
}
