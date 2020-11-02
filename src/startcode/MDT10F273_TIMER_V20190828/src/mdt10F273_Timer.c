/***********************************************************************************
;Company : Yspring ------深圳市汇春科技股份有限公司
;File Name :10F273
;Description :  MDT10F273_TIMER_范例程序
              TMR0定时2ms通过计数使PC3输出1Hz方波
              timer1定时10ms通过计数使PC4输出2Hz方波
              timer2定时100ms通过计数使PC5输出0.25Hz方波
************************************************************************************/
#include "mdt10F273.h"
#include "273cfg.h"
//----------------------------- 数据类型重定义--------------------------------------

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

//------------------------------函数声明--------------------------------------------
void Init_Timer0_WDT(void);	     //初始化timer0和WDT
void Init_Timer1(void);          //初始化timer1
void Init_Timer2(void);          //初始化timer2
void Init_GPIO(void);            //初始化IO
void Init_INT(void);             //初始化中断

//-------------------------------宏定义---------------------------------------------

#define CLR_BYTE	0x00

#define	T2S		20	//2s = 20 * 100ms
#define	T1S		100	//1s = 100 * 10ms
#define	T500MS	250	//500ms = 250 * 2ms
	
//-------------------------------变量定义-------------------------------------------

u8 Timer_2ms_ctr;                //2ms计数器
u8 Timer_10ms_ctr;               //10ms计数器
u8 Timer_100ms_ctr;              //100ms计数器

bit flag_t0 = 0;                 //2ms标志
bit flag_t1 = 0;                 //10ms标志
bit flag_t2 = 0;                 //100ms标志
/***********************************************************************************
;
;函数名: main 
;
;函数说明:	主函数入口
;
***********************************************************************************/
void main(void)         
{
	
	CLRWDT();                    //清看门狗

	SET_HIRC(IRCF_4M);           //内部振荡器频率选择4MHz
	Init_Timer0_WDT();           //初始化timer0和WDT
	Init_Timer1();               //初始化timer1
	Init_Timer2();               //初始化timer2
	Init_GPIO();                 //初始化IO
	Init_INT();                  //初始化中断

//=============================主循环===============================================
	while(1)
	{
		CLRWDT();                           //清除 看门狗 
			
		if(flag_t0 == 1)                    //2ms判断
		{
			flag_t0 = 0;                    //2ms标志清0
			
			Timer_2ms_ctr ++ ;              //2ms计数器加 1
			if(Timer_2ms_ctr >= T500MS)     //500ms判断
			{
				Timer_2ms_ctr = CLR_BYTE;   //2ms计数器清0
				
				PORTC ^= 0x08;	            //PC3 	500ms 取反输出
			}
		}
		
		if(flag_t1 == 1)                    //10ms判断
		{
			flag_t1 = 0;                    //10ms标志清0
			
			Timer_10ms_ctr ++ ;             //10ms计数器加 1
			if(Timer_10ms_ctr >= T1S)       //1s判断
			{
				Timer_10ms_ctr = CLR_BYTE;  //10ms计数器清0
				
				PORTC ^= 0x010;             //PC4 	1s 取反输出
			}
		}

		
		if(flag_t2 == 1)                    //100ms判断
		{
			flag_t2 = 0;                    //100ms标志清0
			
			Timer_100ms_ctr ++ ;            //100ms计数器加1
			if(Timer_100ms_ctr >= T2S)      //2s判断
			{
				Timer_100ms_ctr = CLR_BYTE; //100ms计数器清0
				
				PORTC ^= 0x20;              //PC5 	2s 取反输出
			}
		}
			
	}
}


/*******************************************************************
;
;函数名: ISR 
;
;函数说明:	中断服务程序
;
********************************************************************/
void interrupt ISR(void)		//PICC 编译 中断函数定义
{
	
	if(TIF == 1)                //timer0 定时中断 判断  
	{
		TIF = 0;                //T0中断标志清0
		
		PORTC ^= 0x01;          //Timer0 定时 2ms中断溢出	PC0 取反输出，测试用
		flag_t0 = 1;            //2ms标志置1
	}
	
	if(TMR1IF == 1)             //tmr1中断判断
	{
		TMR1IF = 0;             //tmr1中断标志清0
		
		TMR1ON = 0;             //T1需重置初始值
		TMR1H = 0x63;           //25536 = 65536 - 40000	(0x63c0 = 25536)
		TMR1L = 0xc0;           //10ms = 40000 * 0.25us	( Fosc = 4MHz  __ T = 0.25us)
		TMR1ON = 1;             //使能timer1	
		
		PORTC ^= 0x02;          //Timer1 定时 10ms中断溢出	PC1 取反输出
		flag_t1 = 1;            //10ms标志置1
	}
	
	if(TMR2IF == 1)             //timer2中断判断
	{
		TMR2IF = 0;             //timer2中断标志清0
		
		TMR2ON = 0;             //T2需重置初始值
		TMR2H = 0x3c;           //15536 = 65536 - 50000	(0x3cb0 = 15536)
		TMR2L = 0xb0;           //100ms = 50000 * 2us
		TMR2ON = 1;	            //使能timer2
		
		PORTC ^= 0x04;          //Timer2 定时100ms中断溢出	PC2 取反输出
		flag_t2 = 1;            //100ms标志置1
	}
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
	
	CPIOA = 0b00001000;	//PA口输入输出控制		1:输入		0:输出
	CPIOC = 0b00000000;	//PC口输入输出控制		1:输入		0:输出
	
	PAPHR = 0x00;	//PA弱上拉控制位			1:使能		0:禁止
	PAPDR = 0x00;	//PA弱下拉控制位			1:使能		0:禁止
	
	PCPHR = 0x00;	//PC弱上拉控制位			1:使能		0:禁止
	PCPDR = 0x00;	//PC弱下拉控制位			1:使能		0:禁止
		
	PAINTR = 0x00;	//PA电平变化中断允许位		1:使能		0:禁止
	
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
	TCS = 0;		//TMR0时钟源选择位		1:PA2/T0CKI引脚上信号的跳变		0:内部指令周期时钟（ Fosc/4）
	T0PSDIV_8();	//Timer0预分频比选择1:8	单步8us	(Fosc = 4MHz)  (Fcpu = Fosc/4 = 1MHz)
	TMR0 = 6;		//250 = 256 - 6		2ms = 250 * 8us	
	TMR0EN = 1;		//Tiemr0 启动/停止位	1:启动Timer0		0:停止Timer0
	
//	WDTDIV_512();
	WDTDIV_32768(); //WDT设置
	SWDTEN = 1;	    //使能WDT（仅在OPTION中disable WDT时有效）

}


/*******************************************************************
;
;函数名: Init_Timer1

;函数说明:	初始化Timer1
;
********************************************************************/
void Init_Timer1(void)
{
	
	T1SELEN = 0;    //Timer1 时钟源选择位				0: Timer1 时钟源由TMR1CS位确定
//	T1SELEN = 1;	//Timer1 时钟源选择位				1: Timer1 时钟源由 T1FOSC位确定

	T1FOSC = 0;     //Timer1 时钟源选择内部快时钟使能位 	0: Timer1 时钟源选择内部 " 慢时钟 " 	(当 T1SELEN = 1时)
//	T1FOSC = 1;     //Timer1 时钟源选择内部快时钟使能位 	1: Timer1 时钟源选择内部 " 快时钟 " (当 T1SELEN = 1时)
		

	T1GINV = 0;     //Timer1门控翻转位					0: Timer1门控为低电平有效（门控为低电平时Timer1计数）
//	T1GINV = 1; 	//Timer1门控翻转位				1: Timer1门控为高电平有效（门控为高电平时Timer1计数）

	TMR1GE = 0;     //Timer1门控使能位					0: Timer1打开
//	TMR1GE = 1; 	//Timer1门控使能位				1: Timer1在Timer1门控不活动时打开

	T1PSDIV_1();	//Timer1输入时钟预分频比选择1:1	( Fosc = 4MHz  __ T = 0.25us)	

	T1SYNC = 0; 	//Timer1外部时钟输入同步控制位		0: 同步外部时钟输入
//	T1SYNC = 1; 	//Timer1外部时钟输入同步控制位		1: 不同步外部时钟输入

	TMR1CS = 0; 	//Timer1时钟源选择位			0: 内部时钟（FOSC）
//	TMR1CS = 1; 	//Timer1时钟源选择位			1: 来自T12CK1引脚（上升沿）的外部时钟

	T1OSCEN = 0;	//LP振荡器使能控制位			0:	LP振荡器关闭
//	T1OSCEN = 1;	//LP振荡器使能控制位			1:	LP振荡器被使能用于Timer1时钟	


	TMR1H = 0x63;	//25536 = 65536 - 40000	(0x63c0 = 25536)
	TMR1L = 0xc0;	//10ms = 40000 * 0.25us	( Fosc = 4MHz  __ T = 0.25us)

	TMR1ON = 1;		//Timer1启动/停止位		1: 启动 Timer1		0: 停止Timer1

}


/*******************************************************************
;
;函数名: Init_Timer2

;函数说明:	初始化Timer2
;
********************************************************************/
void Init_Timer2(void)
{
	
	T2SELEN = 0;    //Timer2 时钟源选择位					0: Timer2 时钟源由TMR2CS位确定
//	T2SELEN = 1;    //Timer2 时钟源选择位					1: Timer2 时钟源由 T2FOSC位确定

	T2FOSC = 0;     //Timer2 时钟源选择内部快时钟使能位 		0: Timer2 时钟源选择内部 " 慢时钟 " 	(当 T2SELEN = 1时)
//	T2FOSC = 1;     //Timer2 时钟源选择内部快时钟使能位 	1: Timer2 时钟源选择内部 " 快时钟 " (当 T2SELEN = 1时)
		

	T2GINV = 0;     //Timer2门控翻转位					0: Timer2门控为低电平有效（门控为低电平时Timer2计数）
//	T2GINV = 1;     //Timer2门控翻转位				1: Timer2门控为高电平有效（门控为高电平时Timer2计数）

	TMR2GE = 0;     //Timer2门控使能位					0: Timer2打开
//	TMR2GE = 1;     //Timer2门控使能位				1: Timer2在Timer2门控不活动时打开

	T2PSDIV_8();    //Timer2输入时钟预分频比选择1:8	( Fosc = 4MHz  __ T = 2us)

	T2SYNC = 0;     //Timer2外部时钟输入同步控制位		0: 同步外部时钟输入
//	T2SYNC = 1;     //Timer2外部时钟输入同步控制位		1: 不同步外部时钟输入

	TMR2CS = 0;     //Timer2时钟源选择位			0: 内部时钟（SYS_CLK）
//	TMR2CS = 1;     //Timer2时钟源选择位			1: 来自T12CK1引脚（上升沿）的外部时钟

	T2OSCEN = 0;    //LP振荡器使能控制位			0:  LP振荡器关闭
//	T2OSCEN = 1;    //LP振荡器使能控制位			1:  LP振荡器被使能用于Timer2时钟	

	
	TMR2H = 0x3c;   //15536 = 65536 - 50000	(0x3cb0 = 15536)
	TMR2L = 0xb0;   //100ms = 50000 * 2us
	
	TMR2ON = 1;     //Timer2启动/停止位		1: 启动 Timer2		0: 停止Timer2

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
	
	TIF = 0;        //timer0中断标志清0
	TIS = 1;		//使能 T0中断
	
	TMR1IF = 0;     //timer1中断标志清0
	TMR1IE = 1;		//使能  T1中断		用到 T1中断 需同时使能 T1中断、外设中断、总中断 
	
	TMR2IF = 0;     //timer2中断标志清0
	TMR2IE = 1;		//使能  T2中断		用到 T2中断 需同时使能 T2中断、外设中断、总中断 
	
	PEIE = 1;		//使能  外设中断
	GIE = 1;		//使能  总中断

}

//*******************************************************************


