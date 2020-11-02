#ifndef	__273CFG_H__
#define	__273CFG_H__


//***************************	内部振荡器频率(Fosc)选择位	********************************

#define IRCF_31K		0X00
#define IRCF_250K		0X10
#define IRCF_500K		0X20
#define IRCF_1M			0X30
#define IRCF_2M			0X40
#define IRCF_4M			0X50		/*default*/
#define IRCF_8M			0X60
#define IRCF_16M		0X70

#define SET_HIRC(val)		do {OSCCON = val;} while (0)


//***************************	Timer1输入时钟源选择	*****************************************

#define T1SCKSEL_FOSC()		{T1SELEN=0; TMR1CS=0;}				//选择 系统时钟 ( Fosc )
#define T1SCKSEL_T12CKI()	{T1SELEN=0; TMR1CS=1; T1OSCEN=0;}	//选择 T12CKI 引脚外部时钟源
#define T1SCKSEL_OSC12()	{T1SELEN=0; TMR1CS=1; T1OSCEN=1;}	//选择 OSC1/OSC2 引脚上的 LP 振荡电路
#define T1SCKSEL_31KHZ()	{T1SELEN=1; T1FOSC=0;}				//选择 内部慢时钟 31KHz
#define T1SCKSEL_16MHZ()	{T1SELEN=1; T1FOSC=1;}				//选择 内部快时钟 16MHz

//***************************	Timer1输入时钟预分频比选择位	***************************

#define		T1PSDIV_1()		{T1CKPS1=0; T1CKPS0=0;}			//MCU上电 默认值	1:1
#define		T1PSDIV_2()		{T1CKPS1=0; T1CKPS0=1;}
#define		T1PSDIV_4()		{T1CKPS1=1; T1CKPS0=0;}
#define		T1PSDIV_8()		{T1CKPS1=1; T1CKPS0=1;}

//***************************	Timer2输入时钟源选择	*****************************************

#define T2SCKSEL_FOSC()		{T2SELEN=0; TMR2CS=0;}				//选择 系统时钟 ( Fosc )
#define T2SCKSEL_T12CKI()	{T2SELEN=0; TMR2CS=1; T2OSCEN=0;}	//选择 T12CKI 引脚外部时钟源
#define T2SCKSEL_OSC12()	{T2SELEN=0; TMR2CS=1; T2OSCEN=1;}	//选择 OSC1/OSC2 引脚上的 LP 振荡电路
#define T2SCKSEL_31KHZ()	{T2SELEN=1; T2FOSC=0;}				//选择 内部慢时钟 31KHz
#define T2SCKSEL_16MHZ()	{T2SELEN=1; T2FOSC=1;}				//选择 内部快时钟 16MHz

//***************************	Timer2输入时钟预分频比选择位	***************************

#define		T2PSDIV_1()		{T2CKPS1=0; T2CKPS0=0;}			//MCU上电 默认值	1:1
#define		T2PSDIV_2()		{T2CKPS1=0; T2CKPS0=1;}
#define		T2PSDIV_4()		{T2CKPS1=1; T2CKPS0=0;}
#define		T2PSDIV_8()		{T2CKPS1=1; T2CKPS0=1;}

//*************************	WDT与Timer0共用的8bit预分频器--预分频比选择位	***************

#define		WDTPSDIV_1()	{PSC=1;   PS2=0; PS1=0; PS0=0;}
#define		WDTPSDIV_2()	{PSC=1;   PS2=0; PS1=0; PS0=1;}
#define		WDTPSDIV_4()	{PSC=1;   PS2=0; PS1=1; PS0=0;}
#define		WDTPSDIV_8()	{PSC=1;   PS2=0; PS1=1; PS0=1;}
#define		WDTPSDIV_16()	{PSC=1;   PS2=1; PS1=0; PS0=0;}
#define		WDTPSDIV_32()	{PSC=1;   PS2=1; PS1=0; PS0=1;}
#define		WDTPSDIV_64()	{PSC=1;   PS2=1; PS1=1; PS0=0;}
#define		WDTPSDIV_128()	{PSC=1;   PS2=1; PS1=1; PS0=1;}	//MCU上电 默认值

#define		T0PSDIV_2()		{PSC=0;   PS2=0; PS1=0; PS0=0;}
#define		T0PSDIV_4()		{PSC=0;   PS2=0; PS1=0; PS0=1;}
#define		T0PSDIV_8()		{PSC=0;   PS2=0; PS1=1; PS0=0;}
#define		T0PSDIV_16()	{PSC=0;   PS2=0; PS1=1; PS0=1;}
#define		T0PSDIV_32()	{PSC=0;   PS2=1; PS1=0; PS0=0;}
#define		T0PSDIV_64()	{PSC=0;   PS2=1; PS1=0; PS0=1;}
#define		T0PSDIV_128()	{PSC=0;   PS2=1; PS1=1; PS0=0;}
#define		T0PSDIV_256()	{PSC=0;   PS2=1; PS1=1; PS0=1;}



//***************************	16位 WDT 预分频器--预分频比选择位	***********************

#define		WDTDIV_32()		{WDTPS3=0; WDTPS2=0; WDTPS1=0; WDTPS0=0;}
#define		WDTDIV_64()		{WDTPS3=0; WDTPS2=0; WDTPS1=0; WDTPS0=1;}
#define		WDTDIV_128()	{WDTPS3=0; WDTPS2=0; WDTPS1=1; WDTPS0=0;}
#define		WDTDIV_256()	{WDTPS3=0; WDTPS2=0; WDTPS1=1; WDTPS0=1;}
#define		WDTDIV_512()	{WDTPS3=0; WDTPS2=1; WDTPS1=0; WDTPS0=0;}	//MCU上电 默认值
#define		WDTDIV_1024()	{WDTPS3=0; WDTPS2=1; WDTPS1=0; WDTPS0=1;}
#define		WDTDIV_2048()	{WDTPS3=0; WDTPS2=1; WDTPS1=1; WDTPS0=0;}
#define		WDTDIV_4096()	{WDTPS3=0; WDTPS2=1; WDTPS1=1; WDTPS0=1;}
#define		WDTDIV_8192()	{WDTPS3=1; WDTPS2=0; WDTPS1=0; WDTPS0=0;}
#define		WDTDIV_16384()	{WDTPS3=1; WDTPS2=0; WDTPS1=0; WDTPS0=1;}
#define		WDTDIV_32768()	{WDTPS3=1; WDTPS2=0; WDTPS1=1; WDTPS0=0;}
#define		WDTDIV_65536()	{WDTPS3=1; WDTPS2=0; WDTPS1=1; WDTPS0=1;}

//***************************	AD输入通道初始化设置	**********************************

//作为AD输入的脚位需设为 {模拟输入功能; 设为输入口; }
#define		ADCHSET_PA0AN0()	{AN0=1;  CPIOA0=1; }
#define		ADCHSET_PA1AN1()	{AN1=1;  CPIOA1=1; }
#define		ADCHSET_PA2AN2()	{AN2=1;  CPIOA2=1; }
#define		ADCHSET_PA4AN3()	{AN3=1;  CPIOA4=1; }
#define		ADCHSET_PA5AN4()	{AN4=1;  CPIOA5=1; }

#define		ADCHSET_PC0AN5()	{AN5=1;  CPIOC0=1;}
#define		ADCHSET_PC1AN6()	{AN6=1;  CPIOC1=1;}
#define		ADCHSET_PC2AN7()	{AN7=1;  CPIOC2=1;}
#define		ADCHSET_PC3AN8()	{AN8=1;  CPIOC3=1;}
#define		ADCHSET_PC4AN9()	{AN9=1;  CPIOC4=1;}
#define		ADCHSET_PC5AN10()	{AN10=1; CPIOC5=1;}
#define		ADCHSET_PC6AN11()	{AN11=1; CPIOC6=1;}
#define		ADCHSET_PC7AN12()	{AN12=1; CPIOC7=1;}


//***************************	AD模拟通道选择位	*************************************

#define		ANCHSEL_AN0	0x00
#define		ANCHSEL_AN1	0x10
#define		ANCHSEL_AN2	0x20
#define		ANCHSEL_AN3	0x30
#define		ANCHSEL_AN4	0x40
#define		ANCHSEL_AN5	0x50
#define		ANCHSEL_AN6	0x60
#define		ANCHSEL_AN7	0x70
#define		ANCHSEL_AN8	0x80
#define		ANCHSEL_AN9 0x90
#define		ANCHSEL_AN10 0xa0
#define		ANCHSEL_AN11 0xb0
#define		ANCHSEL_AN12 0xc0
#define		ANCHSEL_VSS 0xd0
#define		ANCHSEL_VDD4 0xe0
#define		ANCHSEL_OFF 0xf0//MCU上电 默认值

//***************************	PC 模拟选择位	*****************************************

//#define		PCANSEL_OFF()	{ADINC=0x00;}
//#define		PCANSEL_OFF()	{ADINC=0x00;}

//***************************		AD时钟预分频选择位		*****************************

#define		ADSCKDIV_8()		{SC1=0; SC0=0;}			//MCU上电 默认值	1:1
#define		ADSCKDIV_16()		{SC1=0; SC0=1;}
#define		ADSCKDIV_32()		{SC1=1; SC0=0;}
#define		ADSCKDIV_64()		{SC1=1; SC0=1;}

//***************************		AD启动转换模式选择位		*************************

#define		ADSTASEL_BUZY()		{CM1=0; CM0=0;}			//MCU上电 默认值	1:1
//#define	ADSTASEL_BUZY()		{CM1=0; CM0=1;}
#define		ADSTASEL_T0()		{CM1=1; CM0=0;}
#define		ADSTASEL_T1()		{CM1=1; CM0=1;}

//***************************	ADC电压参考选择	*****************************************

#define		REFSEL_VDD		0x08	//ADC 电压参考是 VDD pin
#define		REFSEL_PC1		0x0c	//ADC 电压参考是 PC1/VREF pin	(MCU上电 默认值)

//***************************	ADC内部电压参考选择	*************************************

#define		VREFSEL_1024MV		0x00	// 内部电压参考选择 1.024V
#define		VREFSEL_2048MV		0x01	// 内部电压参考选择 2.048V
#define		VREFSEL_4096MV		0x03	// 内部电压参考选择 4.096V	(MCU上电 默认值)

//***************************		*****************************************************
//PWM输出的脚位需设为 {PWM功能转移到PA口输出;  设为数字IO功能; 设为输出口; 禁止内部上拉; 禁止内部下拉; 禁止电平变化中断}
#define		PWMA0SEL_PA0OUT()	{PWMA0TR=1;  AN0=0;  CPIOA0=0; PAPHR0=0; PAPDR0=0; PAINTR0=0;}
#define		PWMA1SEL_PA1OUT()	{PWMA1TR=1;  AN1=0;  CPIOA1=0; PAPHR1=0; PAPDR1=0; PAINTR1=0;}
#define		PWMB0SEL_PA2OUT()	{PWMB0TR=1;  AN2=0;  CPIOA2=0; PAPHR2=0; PAPDR2=0; PAINTR2=0;}
#define		PWMB1SEL_PA5OUT()	{PWMB1TR=1;  AN4=0;  CPIOA5=0; PAPHR5=0; PAPDR5=0; PAINTR5=0;}

//PWM输出的脚位需设为 {PWM功能由PC口输出;  设为数字IO功能; 设为输出口; 禁止内部上拉; 禁止内部下拉;}
#define		PWMA0SEL_PC5OUT()	{PWMA0TR=0;  AN10=0; CPIOC5=0; PCPHR5=0; PCPDR5=0;}
#define		PWMA1SEL_PC4OUT()	{PWMA1TR=0;  AN9=0;  CPIOC4=0; PCPHR4=0; PCPDR4=0;}
#define		PWMB0SEL_PC3OUT()	{PWMB0TR=0;  AN8=0;  CPIOC3=0; PCPHR3=0; PCPDR3=0;}
#define		PWMB1SEL_PC0OUT()	{PWMB1TR=0;  AN5=0;  CPIOC0=0; PCPHR0=0; PCPDR0=0;}
	
//关闭PWM输出设置		 {禁止PWM输出;	禁止PWM模块}
#define		PWMA0OUTOFF()	{PWMA0ON=0;  PWMA0EN=0;}
#define		PWMA1OUTOFF()	{PWMA1ON=0;  PWMA1EN=0;}
#define		PWMB0OUTOFF()	{PWMB0ON=0;  PWMB0EN=0;}
#define		PWMB1OUTOFF()	{PWMB1ON=0;  PWMB1EN=0;}
	
//开启PWM输出设置		 {使能PWM输出;	使能PWM模块}
#define		PWMA0OUTON()	{PWMA0ON=1;  PWMA0EN=1;}
#define		PWMA1OUTON()	{PWMA1ON=1;  PWMA1EN=1;}
#define		PWMB0OUTON()	{PWMB0ON=1;  PWMB0EN=1;}
#define		PWMB1OUTON()	{PWMB1ON=1;  PWMB1EN=1;}

#define	DIE_NUM_0 0x00
#define	DIE_NUM_1 0x10
#define	DIE_NUM_2 0x20
#define	DIE_NUM_3 0x30
#define	DIE_NUM_4 0x40
#define	DIE_NUM_5 0x50
#define	DIE_NUM_6 0x60
#define	DIE_NUM_7 0x70

//***************************		*****************************************
#endif	//#ifndef	__DEFINE_H__

