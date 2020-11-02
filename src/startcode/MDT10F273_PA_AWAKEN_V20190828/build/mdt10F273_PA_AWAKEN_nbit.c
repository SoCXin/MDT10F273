#include	"mdt10F273_PA_AWAKEN_bitname.h"
/***********************************************************************************
;Company : Yspring ------深圳市汇春科技股份有限公司
;File Name :MDT10F272
;Author : Zhu_Chuan_rong
;Create Data : 2018-09
;Last Modified :2018-09
;Description :  MDT10F272_PA_AWAKEN_范例程序
;Version : 1.0
************************************************************************************/


#include <mdt.h>		//用 <> 包含的头文件，直接到IDE安装目录去查找
#include "mdt10F273.h"	//用 " "  包含的头文件，先到工程目录下查找（找不到，再到IDE安装目录去查找）
#include "273cfg.h"

//--------------------------------------------数据类型重定义

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;


//--------------------------------------------函数声明

void Init_IRCF(void);
void CLR_RAM(void);
void Init_Timer0_WDT(void);
void Init_Timer1(void);
void Init_Timer2(void);
void Init_GPIO(void);
void Init_INT(void);
void Led_Flash_Ten(void);
void Sleep_Mode(void);




//--------------------------------------------联合体(共用体) 定义

typedef union
  {
  	struct
  	{
	  unsigned b0                 : 1;
	  unsigned b1                 : 1;
	  unsigned b2                 : 1;
	  unsigned b3                 : 1;
	  unsigned b4                 : 1;
	  unsigned b5                 : 1;
	  unsigned b6                 : 1;
	  unsigned b7                 : 1;
  	}bit_type;
  	unsigned char byte;
   }FLAG;

FLAG FLAG0;		//结构变量声明

//--------------------------------------------结构类型变量位域宏定义
#define flag_t0		FLAG0.bit_type.b0 
#define flag_t1		FLAG0.bit_type.b1
#define flag_t2	 	FLAG0.bit_type.b2
#define flag_key	FLAG0.bit_type.b3
#define flag_sleep	FLAG0.bit_type.b4
#define flag_5		FLAG0.bit_type.b5
#define flag_6		FLAG0.bit_type.b6
#define flag_7		FLAG0.bit_type.b7



//--------------------------------------------宏定义


#define TRUE	1
#define FALSE	0

#define CLR_BYTE	0x00
#define CLR_WORD	0x0000
#define CLR_LONG	0x00000000


#define	T100MS	50	//100ms = 50 * 2ms
#define	T40MS	20	//40ms = 20 * 2ms
	
#define SLEEP_LED_ON()	(PC1 = 1)
#define SLEEP_LED_OFF()	(PC1 = 0)

	
//--------------------------------------------变量定义


volatile u8 Timer_2ms_ctr;
volatile u8 Flash_10_ctr;

volatile u8 Sleep_ctr;



/*******************************************************************
;
;函数名: main 
;
;函数说明:	主函数入口
;
;程序功能说明：
;			
;	MCU接5V供电，PC2接LED，PA0~PA5接开关（此程序未使能总中断,PA口电平变化也可唤醒MCU）
;
;	上电LED快闪10次，然后进入睡眠。
;
;	波动开关状态改变可唤醒MCU，唤醒后LED快闪10后又进入睡眠。
;
;	所有波动开关断开，MCU睡眠功耗1uA 
;
;	（注意：PA口开了内部上拉，接到GND时，会有电流流过内部上拉电阻）
;
********************************************************************/
void main(void)         
{
	Init_IRCF();
	CLR_RAM();
	Init_Timer0_WDT();
//	Init_Timer1();
//	Init_Timer2();
	Init_GPIO();
	Init_INT();

//==========================================主循环
	while(1)
	{
		CLRWDT();	//清除 看门狗 
		
		if(TIF == 1)
		{
			TIF = 0;		//T0 带自动重载功能 不需要重置初始值
			
			PORTC ^= 0x01;	//Timer0 定时 2ms中断溢出	PC0 取反输出
			flag_t0 = TRUE;
		}
			
		if(flag_t0 == TRUE)
		{
			flag_t0 = FALSE;
			Led_Flash_Ten();
			Sleep_Mode();
		}
	}
}


/*******************************************************************
;
;函数名: Led_Flash_Ten

;函数说明:	LED快闪10次函数
;
********************************************************************/

void Led_Flash_Ten(void)
{
	if(flag_sleep == FALSE)
	{
		Timer_2ms_ctr ++ ;
		if(Timer_2ms_ctr >= T100MS)
		{
			Timer_2ms_ctr = CLR_BYTE;
			
			PORTC ^= 0x04;		//Timer2 定时100ms中断溢出	PC2 取反输出
			if(PC2 == 0)
			{
				Flash_10_ctr ++ ;
				if(Flash_10_ctr >= 10)	//灯闪10次后，MCU 进入睡眠
				{
					Flash_10_ctr = CLR_BYTE;
				 
					flag_sleep = TRUE;
				}
			}
		}
	}
}		

/*******************************************************************
;
;函数名: Sleep_Mode

;函数说明:	MCU睡眠处理
;
********************************************************************/

void Sleep_Mode(void)
{
	if(flag_sleep == TRUE)
	{
		Sleep_ctr ++ ;
		if(Sleep_ctr >= T40MS)
		{	
			Sleep_ctr = CLR_BYTE;

//272同型号不同脚位封装的MCU是同一颗晶圆，272_sop8只封装了PA口，没封PC口，但初始化与睡眠等要将PC口也考虑进去，PC口未处理好也会有漏电流存在
			PORTA = 0x00;	//PA口 全输出"L"
			PORTC = 0x00;	//PC口 全输出"L"
			
//272睡眠 漏电注意事项:  	MCU 上电默认选择外部参考输入脚(PC1/VREF) 作为AD参考电压，睡眠前需改成内部参考，否则会有漏电。
//						当使用默认的外部参考时，PC1设置为数字输出口，输出高，睡眠时会有45uA 的漏电流存在。	
//			REFSEL_PC1();	//
//			PC1 = 1;	

			REFSEL_INT();	//
			
			T1SELEN = 0;	
			T2SELEN = 0;	//注意:	T1SELEN为"1"或者T2SELEN为"1"时，MCU将一直处于工作状态，无法进入睡眠
			
			SLEEP_LED_ON();			//睡眠时 输出高，唤醒后输出低(用来指示当前的 睡眠/唤醒 状态)	
			
			PAIE = 1;				//使能 PA电平变化中断 
			PAINTR = 0x3f;			//PA电平变化中断允许位		1:使能		0:禁止
			PORTA = PORTA;			//采用电平变化唤醒时须在睡眠前读(或者写)整个端口状态，然后清除PAIF，否则 PAIF会被重复置1，导致 MCU重复唤醒 不能正常睡眠
			PAIF = 0;				//清除PA电平变化中断标志 
									
									
			SWDTEN = 0; 			//关 WDT
			IRCF_500KHZ();			//睡眠之前 系统时钟 切换到	500KHz 或小于 500KHz（不可大于500KHz）--------（这里将Fosc设置为500KHz）
			CLRWDT();
			asm("nop"); 			//切换“系统时钟”后，需加至少两个以上的NOP指令，等待时钟稳定
			asm("nop");
			asm("nop");
			
									
			SLEEP();	//MCU 进入睡眠
			
			CLRWDT();				//MCU唤醒后 需做 清除WDT操作
			
									//当MCU供电电压“低于4.5V”时，不可使用16MHz作为“系统时钟 ”
			IRCF_4MHZ();			//唤醒后，“系统时钟”切换到所需“时钟频率”--------（这里将Fosc设置为4MHz）
			asm("nop"); 			//切换“系统时钟”后，需加至少两个以上的NOP指令，等待时钟稳定
			asm("nop");
			asm("nop");
			
			SWDTEN = 1; 			//开 WDT
			CLRWDT();
			
									
			SLEEP_LED_OFF();		//睡眠时 输出高，唤醒后输出低(用来指示当前的 睡眠/唤醒 状态)	

			flag_sleep = FALSE;
			
			
		}

	}
	else
	{
		Sleep_ctr = CLR_BYTE;
	}

}



/*******************************************************************
;
;函数名: ISR 
;
;函数说明:	中断服务程序
;
;	所有中断都是同一个入口，区分不同的中断源直接判断对应的中断标志即可，无优先级之区分
;
;
********************************************************************/
//void ISR(void) __interrupt 		//YSDCC 编译 中断函数定义
void interrupt ISR(void)		//PICC 编译 中断函数定义
{
	//此程序未使能总中断,所以不会进入中断函数，但PA口电平变化可以唤醒MCU
}




/*******************************************************************
;
;函数名: Init_GPIO

;函数说明:	初始化IO口
;
********************************************************************/

void Init_GPIO(void)
{
	ADINA = 0x00;	//PA模拟/数字IO设置 		1:模拟功能		0:数字I/O功能
	ADINC = 0x00;	//PC模拟/数字IO设置 		1:模拟功能		0:数字I/O功能
	

	CPIOA = 0x3f;	//PA口输入输出控制			1:输入		0:输出
	CPIOC = 0x00;	//PC口输入输出控制			1:输入		0:输出
	
	PAPHR = 0x3f;	//PA弱上拉控制位			1:使能		0:禁止

	PAPDR = 0x00;	//PA弱下拉控制位			1:使能		0:禁止
	
	PCPHR = 0x00;	//PC弱上拉控制位			1:使能		0:禁止
	PCPDR = 0x00;	//PC弱下拉控制位			1:使能		0:禁止
		
	PAINTR= 0x3f;	//PA电平变化中断允许位		1:使能		0:禁止
	PORTA = 0x00;	//PA全输出"L"
	PORTC = 0x00;	//PC全输出"L"
}


/*******************************************************************
;
;函数名: Init_Timer0_WDT

;函数说明:	初始化Timer0、WDT
;
********************************************************************/

void Init_Timer0_WDT(void)
{
	TCS = 0;		//TMR0时钟源选择位		1:PA2/T0CKI引脚上信号的跳变 	0:内部指令周期时钟（ Fosc/4）
	T0PSDIV_8();	//Timer0预分频比选择1:8 单步8us (Fosc = 4MHz)  (Fcpu = Fosc/4 = 1MHz)
	TMR0 = 6;		//250 = 256 - 6 	2ms = 250 * 8us 
	TMR0EN = 1; 	//Tiemr0 启动/停止位	1:启动Timer0		0:停止Timer0
	
//	WDTDIV_512();
	WDTDIV_32768();
	SWDTEN = 1; 
}



/*******************************************************************
;
;函数名: Init_Timer1

;函数说明:	初始化Timer1
;
********************************************************************/
void Init_Timer1(void)
{
	
}


/*******************************************************************
;
;函数名: Init_Timer2

;函数说明:	初始化Timer2
;
********************************************************************/
void Init_Timer2(void)
{

}


/*******************************************************************
;
;函数名: Init_INT

;函数说明:	初始化 中断
;
********************************************************************/

void Init_INT(void)
{
	INTS = 0x00;	//中断相关寄存器 清零
	PIFB0 = 0x00;
	PIFB1 = 0x00;

	PAIE = 1;		//使能 PA电平变化中断 
	
	TIF = 0;
	TIS = 1;		//使能 T0中断

//	PEIE = 1;			//使能  外设中断
//	GIE = 1;			//使能  总中断	
	GIE = 0;		//禁止  总中断	(此程序不使用中断)
}



/*******************************************************************
;
;函数名: Init_IRCF 
;
;函数说明:	初始化 内部系统时钟
;
********************************************************************/

void Init_IRCF(void)
{
	SCS = 1;		//系统时钟选择位		1:内部振荡器用于系统时钟		0:时钟源由FOSC<2:0>决定
	
//	IRCF_16MHZ();	//内部振荡器频率选择16MHz
//	IRCF_8MHZ();	//内部振荡器频率选择8MHz
	IRCF_4MHZ();	//内部振荡器频率选择4MHz
	asm("nop");		//切换了 Fosc 需延时 两个 "nop" 指令 等待时钟稳定
	asm("nop");
	while(HTS == 0)	//等待内部快时钟稳定
		asm("clrwdt");		
}




/*******************************************************************
;
;函数名: CLR_RAM 
;
;函数说明:	清内存
;
********************************************************************/

void CLR_RAM(void)
{
	MSR = 0x20;
	while(MSR <= 0x7f)	//将0x20 ~ 0x7f  的RAM 清零
	{
		IAR = 0;
		MSR ++ ;
	}
	
	MSR = 0xa0;
	while(MSR <= 0xbf)	//将0xa0 ~ 0xbf  的RAM 清零
	{
		IAR = 0;
		MSR ++ ;
	}
}




