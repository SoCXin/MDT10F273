
#include "mdt10F273.h"

#ifndef _UART_H_
#define _UART_H_
//需要使用Uart功能打开宏定义
#define UART_EN		// 打开改功能请修改TOUCH_SCAN_TIME参数，把扫描时间适当增加一些


#define SET_UART_OUTPUT()		do {CPIOA &= ~0X10;} while (0)		/* 配置UART 为输出口*/
#define UART_H()					do {PORTA |= 0X10;} while (0)
#define UART_L()					do {PORTA &= ~0X10;} while (0)

extern void UartSend(unsigned char dat);

extern void UartString(const char *s);

extern void UartSendUintByDecimal(unsigned short *p, unsigned char num);

extern void UartSendUcharByHex(unsigned char *p, unsigned char num);


#endif

