#ifndef __DHT11_H_
#define __DHT11_H_

#ifndef _DHT11_C_
#define _DHT11_C_ extern
#else
#define _DHT11_C_
#endif

#define uchar unsigned char
#define uint  unsigned int  

sbit DHT11Pin = P3^6;   //定义数据线

_DHT11_C_ uchar DHT11Data[4];//温湿度数据(温度高位,温度低位,湿度高位,湿度低位)
//主要显示的是整数；即： 温度Temp='TH/10'+'TH%10' ;  湿度Humi='RH/10'+'RH%10'

void DHT11_start();
void DHT11_Receive();     //接收40位的数据

#endif