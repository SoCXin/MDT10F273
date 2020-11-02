/***********************************************************************************
;Company : Yspring ------深圳市汇春科技股份有限公司
;File Name :10F273
;Description :  MDT10F273_PWM_范例程序
;功能说明：
          1.PWMA0与PWMA1带死区的PWM输出，PWM周期为1KHz、占空比为50%
          2.将PWMA0和PWMA1的PWM信号复制到PWMB0和PWMB1脚上并输出
************************************************************************************/

#include "mdt10F273.h"	
#include "273cfg.h"

//-----------------------------数据类型重定义---------------------------------------

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

//------------------------------函数声明--------------------------------------------

void Init_IRCF(void);           //初始化内部振荡器
void Init_Timer0_WDT(void);     //初始化timer0和WDT
void Init_Timer1(void);         //初始化timer1
void Init_Timer2(void);         //初始化timer2
void Init_GPIO(void);           //初始化IO
void Init_INT(void);            //初始化INT
void Init_PWM(void);            //初始化PWM

void pwm_output(void);          //PWM输出控制
void key_scan(void);            //按键扫描

//-------------------------------宏定义---------------------------------------------


//------------------------------变量定义--------------------------------------------

u16 temp_cyc;                   //PWM周期
u16 temp_duty;                  //PWM占空比

//-----------------------------变量定义--------------------------------------------
bit flag_t0=0;

/**********************************************************************************
;
;函数名: main 
;
;函数说明:	主函数入口
;
**********************************************************************************/
void main(void)         
{
	CLRWDT();                  //清门狗  

	SET_HIRC(IRCF_4M);         //内部振荡器频率选择4MHz

	Init_Timer0_WDT();         //初始化timer0和WDT
	Init_Timer1();             //初始化timer1
	Init_Timer2();             //初始化timer2
	Init_GPIO();               //初始化IO
	Init_INT();                //初始化INT、
	
	Init_PWM();                //初始化PWM
	
//==========================================主循环
	while(1)
	{
		CLRWDT();             //清除 看门狗 
			
		if(flag_t0 == 1)      //2ms判断
		{
			flag_t0 = 0;      //2ms标志清0
		}	
	}
}

/*******************************************************************
;
;函数名: delay 
;
;函数说明:	延时子程序
;
********************************************************************/

void delay(unsigned char i)
{
	while(i--);
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
	
	if(TIF == 1)                //2ms判断
	{
		TIF = 0;                //T0中断标志清0
		
		PORTC ^= 0x80;          //Timer0 定时 2ms中断溢出	PC0 取反输出
		flag_t0 = 1;            //2ms标志置1
	}
/*
	if(PWMAF == 1)
	{
		PWMAF = 0;
		
	}
	
	if(PWMBF == 1)
	{
		PWMBF = 0;
		
	}
*/
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
	CPIOC = 0b01000110;	//PC口输入输出控制		1:输入		0:输出
	
	PAPHR = 0x00;	//PA弱上拉控制位			1:使能		0:禁止
	PAPDR = 0x00;	//PA弱下拉控制位			1:使能		0:禁止
	
	PCPHR = 0b01000110;	//PC弱上拉控制位			1:使能		0:禁止
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
	SWDTEN = 1;     //WDT使能（仅在OPTION中disable WDT时有效）
}

/*******************************************************************
;
;函数名: Init_Timer1

;函数说明:	初始化Timer1
;
********************************************************************/
void Init_Timer1(void)
{

	T1GINV = 0; 	//Timer1门控翻转位				0: Timer1门控为低电平有效（门控为低电平时Timer1计数）
//	T1GINV = 1; 	//Timer1门控翻转位				1: Timer1门控为高电平有效（门控为高电平时Timer1计数）

	TMR1GE = 0; 	//Timer1门控使能位				0: Timer1打开
//	TMR1GE = 1; 	//Timer1门控使能位				1: Timer1在Timer1门控不活动时打开

	T1SCKSEL_FOSC();//Timer1 时钟源 选择内部系统时钟
	T1PSDIV_4();	//Timer1输入时钟预分频比选择1:1 ( 4MHz  __ T = 1us)

	T1SYNC = 0; 	//Timer1外部时钟输入同步控制位	0: 同步外部时钟输入
//	T1SYNC = 1; 	//Timer1外部时钟输入同步控制位	1: 不同步外部时钟输入


	TMR1H = 0x00;
	TMR1L = 0x00;

	TMR1ON = 1; 	//Timer1启动/停止位 	1: 启动 Timer1		0: 停止Timer1

}

/*******************************************************************
;
;函数名: Init_Timer2

;函数说明:	初始化Timer2
;
********************************************************************/
void Init_Timer2(void)
{
	
	T2GINV = 0;             //Timer2门控翻转位					0: Timer2门控为低电平有效（门控为低电平时Timer2计数）
//	T2GINV = 1;             //Timer2门控翻转位				1: Timer2门控为高电平有效（门控为高电平时Timer2计数）

	TMR2GE = 0;             //Timer2门控使能位					0: Timer2打开
//	TMR2GE = 1;             //Timer2门控使能位				1: Timer2在Timer2门控不活动时打开

	//T2SCKSEL_FOSC();
	//T2SCKSEL_16MHZ();//Timer1 时钟源 选择内部16M时钟
	T2SCKSEL_31KHZ();       //时钟源选择31KHz
	T2PSDIV_1();			//Timer2输入时钟预分频比选择1:1 

	T2SYNC = 0;             //Timer2外部时钟输入同步控制位		0: 同步外部时钟输入
//	T2SYNC = 1;             //Timer2外部时钟输入同步控制位		1: 不同步外部时钟输入

	
	TMR2H = 0x00;           //timer2计数器/计时器高位清0
	TMR2L = 0x00;           //timer2计数器/计时器低位清0
	
	TMR2ON = 1;            //Timer2启动/停止位 	1: 启动 Timer2		0: 停止Timer2
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
	
	TIF = 0;        //timer0中断标志 清零
	TIS = 1;		//使能 T0中断

	PWMAF = 0;		//PWMA中断标志清零
//	PWMAIE = 1;		//使能 Timer1的PWM中断		用到 PWM中断 需同时使能 PWM中断、外设中断、总中断 
	
	PWMBF = 0;		//PWMB中断标志清零
//	PWMBIE = 1;		//使能 Timer2的PWM中断		用到 PWM中断 需同时使能 PWM中断、外设中断、总中断 
	
//	PEIE = 1;		//使能  外设中断
	GIE = 1;		//使能  总中断

}

/*******************************************************************
;
;函数名: Init_PWM

;函数说明:	初始化PWM模块
;
********************************************************************/

void Init_PWM(void)
{

/*	PWMA0、PWMA1 共用 定时器资源 Timer1 ，
	两路 PWM输出的 周期 相同 ，每路 PWM的 占空比单独可调，
	需要PWMB0/1输出时要打开Timer1定时器，需要设置Tiemr1相关寄存器
*/
	
	temp_cyc = 1000;                 //设置频率为1KHz
	temp_duty = temp_cyc >> 1;       //占空比50 %


	T1PRLH = temp_cyc >> 8;          //PWMA0/1  周期寄存器的高4位_b<3:0>
	T1PRLL = temp_cyc & 0x00ff;      //PWMA0/1  周期寄存器的低字节。
		
	T2PRLH = temp_cyc >> 8;          //PWMB0/1  周期寄存器的高4位_b<3:0>
	T2PRLL = temp_cyc & 0x00ff;      //PWMB0/1  周期寄存器的低字节。
		
		

	EPRA0H = temp_duty >> 8;         //PWMA0 占空比重载寄存器高4位__b<3:0>
	PRLA0L = temp_duty & 0x00ff;     //PWMA0 占空比重载寄存器低字节

	EPRA1H = temp_duty >> 8;         //PWMA1 占空比重载寄存器高4位__b<3:0>
	PRLA1L = temp_duty & 0x00ff;     //PWMA1 占空比重载寄存器低字节


	EPRB0H = temp_duty >> 8;         //PWMB0 占空比重载寄存器高4位__b<3:0>
	PRLB0L = temp_duty & 0x00ff;     //PWMB0 占空比重载寄存器低字节

	EPRB1H = temp_duty >> 8;         //PWMB1 占空比重载寄存器高4位__b<3:0>
	PRLB1L = temp_duty & 0x00ff;     //PWMB1 占空比重载寄存器低字节


	
	DIE_EN = 1;                      //bit7=1使能死区延时，并设置PWMA0与PWMA1的死区时间(NUM+1)/Fsys
	T12CON |= DIE_NUM_3;             //注意使能死区延时后，Timer1和Timer2的时钟源都自动切换为系统时钟

	PWMB0CP = 1;	//复制PWM信号
	PWMB1CP = 1;	//复制PWM信号

	PWMA0OL = 0;		//PWMA0 极性输出不反向
	PWMA0SEL_PC5OUT();	//PWMA0选择 由PC5输出		(PWMA0 可以选择 由 PC5或者PA0 输出)
//	PWMA0SEL_PA0OUT();	//PWMA0选择 由PA0输出
//	PWMA0OUTOFF();		//PWMA0禁止输出
	PWMA0OUTON();		//PWMA0使能输出

	PWMA1OL = 0;		//PWMA1 极性输出不反向
	PWMA1SEL_PC4OUT();	//PWMA1选择 由PC4输出		(PWMA1 可以选择 由 PC4或者PA1 输出)
//	PWMA1SEL_PA1OUT();	//PWMA1选择 由PA1输出
//	PWMA1OUTOFF();		//PWMA1禁止输出
	PWMA1OUTON();		//PWMA1使能输出




/*	PWMB0、PWMB1 共用 定时器资源 Timer2 ，
	两路 PWM输出的 周期 相同 ，每路 PWM的 占空比单独可调，
	需要PWMB0/1输出时要打开Timer2定时器，需要设置Tiemr2相关寄存器
*/
	PWMB0OL = 0;		//PWMB0 极性输出不反向
	PWMB0SEL_PC3OUT();	//PWMB0选择 由PC3输出		(PWMB0 可以选择 由 PC3或者PA2 输出)
//	PWMB0SEL_PA2OUT();	//PWMB0选择 由PA2输出
//	PWMB0OUTOFF();		//PWMB0禁止输出
	PWMB0OUTON();		//PWMB0使能输出

	PWMB1OL = 0;		//PWMB1 输出极性不反向
	PWMB1SEL_PC0OUT();	//PWMB1选择 由PC0输出		(PWMB1 可以选择 由 PC0或者PA5 输出)
//	PWMB1SEL_PA5OUT();	//PWMB1选择 由PA5输出
	//PWMB1OUTOFF();		//PWMB1禁止输出
	PWMB1OUTON();		//PWMB1使能输出
		
}


//*******************************************************************



