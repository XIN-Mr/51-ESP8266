#ifndef __USART_H_
#define __USART_H_

#ifndef _USART_C_
#define _USART_C_ extern
#else
#define _USART_C_
#endif

#define ReadLength 50

_USART_C_ bit UsartFlage;
_USART_C_ int UsartIdleCnt;
_USART_C_ unsigned char  UsartReadCnt;
_USART_C_ unsigned char  UsartReceive[ReadLength];
_USART_C_ unsigned char  UsartReadCntCopy;

//void InitUART(long Baud);
void InitUART();
void UartSend(unsigned char value);

void UartSendTI(unsigned char *value,int DataLen);

// void UartSendByte(unsigned char c);
// void sendstring(unsigned char *string);
// void uart_printf(const char *fmt,...);

#endif