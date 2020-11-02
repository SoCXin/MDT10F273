
#include "mdt10F273.h"

#ifndef _UART_H_
#define _UART_H_
//��Ҫʹ��Uart���ܴ򿪺궨��
#define UART_EN		// �򿪸Ĺ������޸�TOUCH_SCAN_TIME��������ɨ��ʱ���ʵ�����һЩ


#define SET_UART_OUTPUT()		do {CPIOA &= ~0X10;} while (0)		/* ����UART Ϊ�����*/
#define UART_H()					do {PORTA |= 0X10;} while (0)
#define UART_L()					do {PORTA &= ~0X10;} while (0)

extern void UartSend(unsigned char dat);

extern void UartString(const char *s);

extern void UartSendUintByDecimal(unsigned short *p, unsigned char num);

extern void UartSendUcharByHex(unsigned char *p, unsigned char num);


#endif

