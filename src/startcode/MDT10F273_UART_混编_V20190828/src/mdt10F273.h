#ifndef	__MDT10F273_H__
#define	__MDT10F273_H__

#define CLRWDT() do {asm("clrwdt");} while (0)
#define SLEEP() 	do {asm("sleep");  asm("NOP"); asm("NOP"); ;} while (0)//asm("clrwdt");asm("clrwdt")


volatile unsigned char		IAR				@	0x0000;
volatile unsigned char		TMR0				@	0x0001;
volatile unsigned char		PCL				@	0x0002;
volatile unsigned char		STATUS				@	0x0003;
//        STATUS  Bits
volatile bit		C			@	 ((unsigned)&STATUS*8)+0;
volatile bit		HC			@	 ((unsigned)&STATUS*8)+1;
volatile bit		Z			@	 ((unsigned)&STATUS*8)+2;
volatile bit		PF			@	 ((unsigned)&STATUS*8)+3;
volatile bit		TF			@	 ((unsigned)&STATUS*8)+4;
volatile bit		RP0			@	 ((unsigned)&STATUS*8)+5;
volatile bit		RP1			@	 ((unsigned)&STATUS*8)+6;
volatile bit		IRP			@	 ((unsigned)&STATUS*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	C			: 1;
	unsigned	HC			: 1;
	unsigned	Z			: 1;
	unsigned	PF			: 1;
	unsigned	TF			: 1;
	unsigned	RP0			: 1;
	unsigned	RP1			: 1;
	unsigned	IRP			: 1;
	};
} _STATUSbits @ 0x0003;
#endif
volatile unsigned char		MSR				@	0x0004;
volatile unsigned char		PORTA				@	0x0005;
//        PORTA  Bits
volatile bit		PA0			@	 ((unsigned)&PORTA*8)+0;
volatile bit		PA1			@	 ((unsigned)&PORTA*8)+1;
volatile bit		PA2			@	 ((unsigned)&PORTA*8)+2;
volatile bit		PA3			@	 ((unsigned)&PORTA*8)+3;
volatile bit		PA4			@	 ((unsigned)&PORTA*8)+4;
volatile bit		PA5			@	 ((unsigned)&PORTA*8)+5;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PA0			: 1;
	unsigned	PA1			: 1;
	unsigned	PA2			: 1;
	unsigned	PA3			: 1;
	unsigned	PA4			: 1;
	unsigned	PA5			: 1;
	};
} _PORTAbits @ 0x0005;
#endif
volatile unsigned char		PORTC				@	0x0007;
//        PORTC  Bits
volatile bit		PC0			@	 ((unsigned)&PORTC*8)+0;
volatile bit		PC1			@	 ((unsigned)&PORTC*8)+1;
volatile bit		PC2			@	 ((unsigned)&PORTC*8)+2;
volatile bit		PC3			@	 ((unsigned)&PORTC*8)+3;
volatile bit		PC4			@	 ((unsigned)&PORTC*8)+4;
volatile bit		PC5			@	 ((unsigned)&PORTC*8)+5;
volatile bit		PC6			@	 ((unsigned)&PORTC*8)+6;
volatile bit		PC7			@	 ((unsigned)&PORTC*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PC0			: 1;
	unsigned	PC1			: 1;
	unsigned	PC2			: 1;
	unsigned	PC3			: 1;
	unsigned	PC4			: 1;
	unsigned	PC5			: 1;
	unsigned	PC6			: 1;
	unsigned	PC7			: 1;
	};
} _PORTCbits @ 0x0007;
#endif
volatile unsigned char		PCLATH				@	0x000A;
volatile unsigned char		INTS				@	0x000B;
//        INTS  Bits
volatile bit		PAIF			@	 ((unsigned)&INTS*8)+0;
volatile bit		INT0F			@	 ((unsigned)&INTS*8)+1;
volatile bit		TIF			@	 ((unsigned)&INTS*8)+2;
volatile bit		PAIE			@	 ((unsigned)&INTS*8)+3;
volatile bit		INT0E			@	 ((unsigned)&INTS*8)+4;
volatile bit		TIS			@	 ((unsigned)&INTS*8)+5;
volatile bit		PEIE			@	 ((unsigned)&INTS*8)+6;
volatile bit		GIE			@	 ((unsigned)&INTS*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PAIF			: 1;
	unsigned	INT0F			: 1;
	unsigned	TIF			: 1;
	unsigned	PAIE			: 1;
	unsigned	INT0E			: 1;
	unsigned	TIS			: 1;
	unsigned	PEIE			: 1;
	unsigned	GIE			: 1;
	};
} _INTSbits @ 0x000B;
#endif
volatile unsigned char		PIFB0				@	0x000C;
//        PIFB0  Bits
volatile bit		TMR1IF			@	 ((unsigned)&PIFB0*8)+0;
volatile bit		OSFIF			@	 ((unsigned)&PIFB0*8)+1;
volatile bit		ADIF			@	 ((unsigned)&PIFB0*8)+2;
volatile bit		INT1F			@	 ((unsigned)&PIFB0*8)+3;
volatile bit		TMR1IE			@	 ((unsigned)&PIFB0*8)+4;
volatile bit		OSFIE			@	 ((unsigned)&PIFB0*8)+5;
volatile bit		ADIE			@	 ((unsigned)&PIFB0*8)+6;
volatile bit		INT1E			@	 ((unsigned)&PIFB0*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	TMR1IF			: 1;
	unsigned	OSFIF			: 1;
	unsigned	ADIF			: 1;
	unsigned	INT1F			: 1;
	unsigned	TMR1IE			: 1;
	unsigned	OSFIE			: 1;
	unsigned	ADIE			: 1;
	unsigned	INT1E			: 1;
	};
} _PIFB0bits @ 0x000C;
#endif
volatile unsigned char		PIFB1				@	0x000D;
//        PIFB1  Bits
volatile bit		TMR2IF			@	 ((unsigned)&PIFB1*8)+0;
volatile bit		PWMAF			@	 ((unsigned)&PIFB1*8)+1;
volatile bit		PWMBF			@	 ((unsigned)&PIFB1*8)+2;
volatile bit		INT0SEL			@	 ((unsigned)&PIFB1*8)+3;
volatile bit		TMR2IE			@	 ((unsigned)&PIFB1*8)+4;
volatile bit		PWMAIE			@	 ((unsigned)&PIFB1*8)+5;
volatile bit		PWMBIE			@	 ((unsigned)&PIFB1*8)+6;
volatile bit		INT1SEL			@	 ((unsigned)&PIFB1*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	TMR2IF			: 1;
	unsigned	PWMAF			: 1;
	unsigned	PWMBF			: 1;
	unsigned	INT0SEL			: 1;
	unsigned	TMR2IE			: 1;
	unsigned	PWMAIE			: 1;
	unsigned	PWMBIE			: 1;
	unsigned	INT1SEL			: 1;
	};
} _PIFB1bits @ 0x000D;
#endif
volatile unsigned char		TMR1L				@	0x000E;
volatile unsigned char		TMR1H				@	0x000F;
volatile unsigned char		T1STA				@	0x0010;
//        T1STA  Bits
volatile bit		TMR1ON			@	 ((unsigned)&T1STA*8)+0;
volatile bit		TMR1CS			@	 ((unsigned)&T1STA*8)+1;
volatile bit		T1SYNC			@	 ((unsigned)&T1STA*8)+2;
volatile bit		T1OSCEN			@	 ((unsigned)&T1STA*8)+3;
volatile bit		T1CKPS0			@	 ((unsigned)&T1STA*8)+4;
volatile bit		T1CKPS1			@	 ((unsigned)&T1STA*8)+5;
volatile bit		TMR1GE			@	 ((unsigned)&T1STA*8)+6;
volatile bit		T1GINV			@	 ((unsigned)&T1STA*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	TMR1ON			: 1;
	unsigned	TMR1CS			: 1;
	unsigned	T1SYNC			: 1;
	unsigned	T1OSCEN			: 1;
	unsigned	T1CKPS0			: 1;
	unsigned	T1CKPS1			: 1;
	unsigned	TMR1GE			: 1;
	unsigned	T1GINV			: 1;
	};
} _T1STAbits @ 0x0010;
#endif
volatile unsigned char		TMR2L				@	0x0011;
volatile unsigned char		TMR2H				@	0x0012;
volatile unsigned char		T2STA				@	0x0013;
//        T2STA  Bits
volatile bit		TMR2ON			@	 ((unsigned)&T2STA*8)+0;
volatile bit		TMR2CS			@	 ((unsigned)&T2STA*8)+1;
volatile bit		T2SYNC			@	 ((unsigned)&T2STA*8)+2;
volatile bit		T2OSCEN			@	 ((unsigned)&T2STA*8)+3;
volatile bit		T2CKPS0			@	 ((unsigned)&T2STA*8)+4;
volatile bit		T2CKPS1			@	 ((unsigned)&T2STA*8)+5;
volatile bit		TMR2GE			@	 ((unsigned)&T2STA*8)+6;
volatile bit		T2GINV			@	 ((unsigned)&T2STA*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	TMR2ON			: 1;
	unsigned	TMR2CS			: 1;
	unsigned	T2SYNC			: 1;
	unsigned	T2OSCEN			: 1;
	unsigned	T2CKPS0			: 1;
	unsigned	T2CKPS1			: 1;
	unsigned	TMR2GE			: 1;
	unsigned	T2GINV			: 1;
	};
} _T2STAbits @ 0x0013;
#endif
volatile unsigned char		T12CON				@	0x0014;
//        T12CON  Bits
volatile bit		T1FOSC			@	 ((unsigned)&T12CON*8)+0;
volatile bit		T1SELEN			@	 ((unsigned)&T12CON*8)+1;
volatile bit		T2FOSC			@	 ((unsigned)&T12CON*8)+2;
volatile bit		T2SELEN			@	 ((unsigned)&T12CON*8)+3;
volatile bit		DIE_EN			@	 ((unsigned)&T12CON*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	T1FOSC			: 1;
	unsigned	T1SELEN			: 1;
	unsigned	T2FOSC			: 1;
	unsigned	T2SELEN			: 1;
	unsigned	DIE_EN			: 1;
	};
} _T12CONbits @ 0x0014;
#endif
volatile unsigned char		WDTCNTL				@	0x0016;
volatile unsigned char		WDTCNTH				@	0x0017;
volatile unsigned char		WDTCON				@	0x0018;
//        WDTCON  Bits
volatile bit		SWDTEN			@	 ((unsigned)&WDTCON*8)+0;
volatile bit		WDTPS0			@	 ((unsigned)&WDTCON*8)+1;
volatile bit		WDTPS1			@	 ((unsigned)&WDTCON*8)+2;
volatile bit		WDTPS2			@	 ((unsigned)&WDTCON*8)+3;
volatile bit		WDTPS3			@	 ((unsigned)&WDTCON*8)+4;
volatile bit		PWMB1CP			@	 ((unsigned)&WDTCON*8)+6;
volatile bit		PWMB0CP			@	 ((unsigned)&WDTCON*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	SWDTEN			: 1;
	unsigned	WDTPS0			: 1;
	unsigned	WDTPS1			: 1;
	unsigned	WDTPS2			: 1;
	unsigned	WDTPS3			: 1;
	unsigned	PWMB1CP			: 1;
	unsigned	PWMB0CP			: 1;
	};
} _WDTCONbits @ 0x0018;
#endif
volatile unsigned char		ADC0CN				@	0x001C;
//        ADC0CN  Bits
volatile bit		CM0			@	 ((unsigned)&ADC0CN*8)+0;
volatile bit		CM1			@	 ((unsigned)&ADC0CN*8)+1;
volatile bit		BUSY			@	 ((unsigned)&ADC0CN*8)+2;
volatile bit		ADC_EN			@	 ((unsigned)&ADC0CN*8)+3;
volatile bit		SC0			@	 ((unsigned)&ADC0CN*8)+4;
volatile bit		SC1			@	 ((unsigned)&ADC0CN*8)+5;
volatile bit		ADFM			@	 ((unsigned)&ADC0CN*8)+6;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	CM0			: 1;
	unsigned	CM1			: 1;
	unsigned	BUSY			: 1;
	unsigned	ADC_EN			: 1;
	unsigned	SC0			: 1;
	unsigned	SC1			: 1;
	unsigned	ADFM			: 1;
	};
} _ADC0CNbits @ 0x001C;
#endif
volatile unsigned char		ADS0				@	0x001D;
//        ADS0  Bits
volatile bit		VREFSEL0			@	 ((unsigned)&ADS0*8)+0;
volatile bit		VREFSEL1			@	 ((unsigned)&ADS0*8)+1;
volatile bit		REFSEL0			@	 ((unsigned)&ADS0*8)+2;
volatile bit		REFSEL1			@	 ((unsigned)&ADS0*8)+3;
volatile bit		CHNSEL0			@	 ((unsigned)&ADS0*8)+4;
volatile bit		CHNSEL1			@	 ((unsigned)&ADS0*8)+5;
volatile bit		CHNSEL2			@	 ((unsigned)&ADS0*8)+6;
volatile bit		CHNSEL3			@	 ((unsigned)&ADS0*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	VREFSEL0			: 1;
	unsigned	VREFSEL1			: 1;
	unsigned	REFSEL0			: 1;
	unsigned	REFSEL1			: 1;
	unsigned	CHNSEL0			: 1;
	unsigned	CHNSEL1			: 1;
	unsigned	CHNSEL2			: 1;
	unsigned	CHNSEL3			: 1;
	};
} _ADS0bits @ 0x001D;
#endif
volatile unsigned char		ADRESL				@	0x001E;
volatile unsigned char		ADRESH				@	0x001F;
volatile unsigned char		OPT_REG				@	0x0081;
//        OPT_REG  Bits
volatile bit		PS0			@	 ((unsigned)&OPT_REG*8)+0;
volatile bit		PS1			@	 ((unsigned)&OPT_REG*8)+1;
volatile bit		PS2			@	 ((unsigned)&OPT_REG*8)+2;
volatile bit		PSC			@	 ((unsigned)&OPT_REG*8)+3;
volatile bit		TCE			@	 ((unsigned)&OPT_REG*8)+4;
volatile bit		TCS			@	 ((unsigned)&OPT_REG*8)+5;
volatile bit		TMR0EN			@	 ((unsigned)&OPT_REG*8)+6;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PS0			: 1;
	unsigned	PS1			: 1;
	unsigned	PS2			: 1;
	unsigned	PSC			: 1;
	unsigned	TCE			: 1;
	unsigned	TCS			: 1;
	unsigned	TMR0EN			: 1;
	};
} _OPT_REGbits @ 0x0081;
#endif
volatile unsigned char		CPIOA				@	0x0085;
//        CPIOA  Bits
volatile bit		CPIOA0			@	 ((unsigned)&CPIOA*8)+0;
volatile bit		CPIOA1			@	 ((unsigned)&CPIOA*8)+1;
volatile bit		CPIOA2			@	 ((unsigned)&CPIOA*8)+2;
volatile bit		CPIOA3			@	 ((unsigned)&CPIOA*8)+3;
volatile bit		CPIOA4			@	 ((unsigned)&CPIOA*8)+4;
volatile bit		CPIOA5			@	 ((unsigned)&CPIOA*8)+5;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	CPIOA0			: 1;
	unsigned	CPIOA1			: 1;
	unsigned	CPIOA2			: 1;
	unsigned	CPIOA3			: 1;
	unsigned	CPIOA4			: 1;
	unsigned	CPIOA5			: 1;
	};
} _CPIOAbits @ 0x0085;
#endif
volatile unsigned char		CPIOC				@	0x0087;
//        CPIOC  Bits
volatile bit		CPIOC0			@	 ((unsigned)&CPIOC*8)+0;
volatile bit		CPIOC1			@	 ((unsigned)&CPIOC*8)+1;
volatile bit		CPIOC2			@	 ((unsigned)&CPIOC*8)+2;
volatile bit		CPIOC3			@	 ((unsigned)&CPIOC*8)+3;
volatile bit		CPIOC4			@	 ((unsigned)&CPIOC*8)+4;
volatile bit		CPIOC5			@	 ((unsigned)&CPIOC*8)+5;
volatile bit		CPIOC6			@	 ((unsigned)&CPIOC*8)+6;
volatile bit		CPIOC7			@	 ((unsigned)&CPIOC*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	CPIOC0			: 1;
	unsigned	CPIOC1			: 1;
	unsigned	CPIOC2			: 1;
	unsigned	CPIOC3			: 1;
	unsigned	CPIOC4			: 1;
	unsigned	CPIOC5			: 1;
	unsigned	CPIOC6			: 1;
	unsigned	CPIOC7			: 1;
	};
} _CPIOCbits @ 0x0087;
#endif
volatile unsigned char		PSTA				@	0x008E;
//        PSTA  Bits
volatile bit		LVR			@	 ((unsigned)&PSTA*8)+0;
volatile bit		POR			@	 ((unsigned)&PSTA*8)+1;
volatile bit		IER			@	 ((unsigned)&PSTA*8)+2;
volatile bit		MCR			@	 ((unsigned)&PSTA*8)+3;
volatile bit		SLVREN			@	 ((unsigned)&PSTA*8)+4;
volatile bit		ULPWUE			@	 ((unsigned)&PSTA*8)+5;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	LVR			: 1;
	unsigned	POR			: 1;
	unsigned	IER			: 1;
	unsigned	MCR			: 1;
	unsigned	SLVREN			: 1;
	unsigned	ULPWUE			: 1;
	};
} _PSTAbits @ 0x008E;
#endif
volatile unsigned char		OSCCON				@	0x008F;
//        OSCCON  Bits
volatile bit		SCS			@	 ((unsigned)&OSCCON*8)+0;
volatile bit		LTS			@	 ((unsigned)&OSCCON*8)+1;
volatile bit		HTS			@	 ((unsigned)&OSCCON*8)+2;
volatile bit		OSTS			@	 ((unsigned)&OSCCON*8)+3;
volatile bit		IRCF0			@	 ((unsigned)&OSCCON*8)+4;
volatile bit		IRCF1			@	 ((unsigned)&OSCCON*8)+5;
volatile bit		IRCF2			@	 ((unsigned)&OSCCON*8)+6;
volatile bit		FOSCEN			@	 ((unsigned)&OSCCON*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	SCS			: 1;
	unsigned	LTS			: 1;
	unsigned	HTS			: 1;
	unsigned	OSTS			: 1;
	unsigned	IRCF0			: 1;
	unsigned	IRCF1			: 1;
	unsigned	IRCF2			: 1;
	unsigned	FOSCEN			: 1;
	};
} _OSCCONbits @ 0x008F;
#endif
volatile unsigned char		FOSCTRIM				@	0x0090;
volatile unsigned char		FOSCCFG				@	0x0091;
volatile unsigned char		ADINA				@	0x0094;
//        ADINA  Bits
volatile bit		AN0			@	 ((unsigned)&ADINA*8)+0;
volatile bit		AN1			@	 ((unsigned)&ADINA*8)+1;
volatile bit		AN2			@	 ((unsigned)&ADINA*8)+2;
volatile bit		AN3			@	 ((unsigned)&ADINA*8)+4;
volatile bit		AN4			@	 ((unsigned)&ADINA*8)+5;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	AN0			: 1;
	unsigned	AN1			: 1;
	unsigned	AN2			: 1;
	unsigned	AN3			: 1;
	unsigned	AN4			: 1;
	};
} _ADINAbits @ 0x0094;
#endif
volatile unsigned char		PAPHR				@	0x0095;
//        PAPHR  Bits
volatile bit		PAPHR0			@	 ((unsigned)&PAPHR*8)+0;
volatile bit		PAPHR1			@	 ((unsigned)&PAPHR*8)+1;
volatile bit		PAPHR2			@	 ((unsigned)&PAPHR*8)+2;
volatile bit		PAPHR3			@	 ((unsigned)&PAPHR*8)+3;
volatile bit		PAPHR4			@	 ((unsigned)&PAPHR*8)+4;
volatile bit		PAPHR5			@	 ((unsigned)&PAPHR*8)+5;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PAPHR0			: 1;
	unsigned	PAPHR1			: 1;
	unsigned	PAPHR2			: 1;
	unsigned	PAPHR3			: 1;
	unsigned	PAPHR4			: 1;
	unsigned	PAPHR5			: 1;
	};
} _PAPHRbits @ 0x0095;
#endif
volatile unsigned char		PAINTR				@	0x0096;
//        PAINTR  Bits
volatile bit		PAINTR0			@	 ((unsigned)&PAINTR*8)+0;
volatile bit		PAINTR1			@	 ((unsigned)&PAINTR*8)+1;
volatile bit		PAINTR2			@	 ((unsigned)&PAINTR*8)+2;
volatile bit		PAINTR3			@	 ((unsigned)&PAINTR*8)+3;
volatile bit		PAINTR4			@	 ((unsigned)&PAINTR*8)+4;
volatile bit		PAINTR5			@	 ((unsigned)&PAINTR*8)+5;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PAINTR0			: 1;
	unsigned	PAINTR1			: 1;
	unsigned	PAINTR2			: 1;
	unsigned	PAINTR3			: 1;
	unsigned	PAINTR4			: 1;
	unsigned	PAINTR5			: 1;
	};
} _PAINTRbits @ 0x0096;
#endif
volatile unsigned char		PAPDR				@	0x0097;
//        PAPDR  Bits
volatile bit		PAPDR0			@	 ((unsigned)&PAPDR*8)+0;
volatile bit		PAPDR1			@	 ((unsigned)&PAPDR*8)+1;
volatile bit		PAPDR2			@	 ((unsigned)&PAPDR*8)+2;
volatile bit		PAPDR4			@	 ((unsigned)&PAPDR*8)+4;
volatile bit		PAPDR5			@	 ((unsigned)&PAPDR*8)+5;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PAPDR0			: 1;
	unsigned	PAPDR1			: 1;
	unsigned	PAPDR2			: 1;
	unsigned	PAPDR4			: 1;
	unsigned	PAPDR5			: 1;
	};
} _PAPDRbits @ 0x0097;
#endif
volatile unsigned char		PCPHR				@	0x009C;
//        PCPHR  Bits
volatile bit		PCPHR0			@	 ((unsigned)&PCPHR*8)+0;
volatile bit		PCPHR1			@	 ((unsigned)&PCPHR*8)+1;
volatile bit		PCPHR2			@	 ((unsigned)&PCPHR*8)+2;
volatile bit		PCPHR3			@	 ((unsigned)&PCPHR*8)+3;
volatile bit		PCPHR4			@	 ((unsigned)&PCPHR*8)+4;
volatile bit		PCPHR5			@	 ((unsigned)&PCPHR*8)+5;
volatile bit		PCPHR6			@	 ((unsigned)&PCPHR*8)+6;
volatile bit		PCPHR7			@	 ((unsigned)&PCPHR*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PCPHR0			: 1;
	unsigned	PCPHR1			: 1;
	unsigned	PCPHR2			: 1;
	unsigned	PCPHR3			: 1;
	unsigned	PCPHR4			: 1;
	unsigned	PCPHR5			: 1;
	unsigned	PCPHR6			: 1;
	unsigned	PCPHR7			: 1;
	};
} _PCPHRbits @ 0x009C;
#endif
volatile unsigned char		PCPDR				@	0x009D;
//        PCPDR  Bits
volatile bit		PCPDR0			@	 ((unsigned)&PCPDR*8)+0;
volatile bit		PCPDR1			@	 ((unsigned)&PCPDR*8)+1;
volatile bit		PCPDR2			@	 ((unsigned)&PCPDR*8)+2;
volatile bit		PCPDR3			@	 ((unsigned)&PCPDR*8)+3;
volatile bit		PCPDR4			@	 ((unsigned)&PCPDR*8)+4;
volatile bit		PCPDR5			@	 ((unsigned)&PCPDR*8)+5;
volatile bit		PCPDR6			@	 ((unsigned)&PCPDR*8)+6;
volatile bit		PCPDR7			@	 ((unsigned)&PCPDR*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PCPDR0			: 1;
	unsigned	PCPDR1			: 1;
	unsigned	PCPDR2			: 1;
	unsigned	PCPDR3			: 1;
	unsigned	PCPDR4			: 1;
	unsigned	PCPDR5			: 1;
	unsigned	PCPDR6			: 1;
	unsigned	PCPDR7			: 1;
	};
} _PCPDRbits @ 0x009D;
#endif
volatile unsigned char		ADINC				@	0x009F;
//        ADINC  Bits
volatile bit		AN5			@	 ((unsigned)&ADINC*8)+0;
volatile bit		AN6			@	 ((unsigned)&ADINC*8)+1;
volatile bit		AN7			@	 ((unsigned)&ADINC*8)+2;
volatile bit		AN8			@	 ((unsigned)&ADINC*8)+3;
volatile bit		AN9			@	 ((unsigned)&ADINC*8)+4;
volatile bit		AN10			@	 ((unsigned)&ADINC*8)+5;
volatile bit		AN11			@	 ((unsigned)&ADINC*8)+6;
volatile bit		AN12			@	 ((unsigned)&ADINC*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	AN5			: 1;
	unsigned	AN6			: 1;
	unsigned	AN7			: 1;
	unsigned	AN8			: 1;
	unsigned	AN9			: 1;
	unsigned	AN10			: 1;
	unsigned	AN11			: 1;
	unsigned	AN12			: 1;
	};
} _ADINCbits @ 0x009F;
#endif
volatile unsigned char		PWMCON0				@	0x0110;
//        PWMCON0  Bits
volatile bit		PWMA0EN			@	 ((unsigned)&PWMCON0*8)+0;
volatile bit		PWMA1EN			@	 ((unsigned)&PWMCON0*8)+1;
volatile bit		PWMB0EN			@	 ((unsigned)&PWMCON0*8)+2;
volatile bit		PWMB1EN			@	 ((unsigned)&PWMCON0*8)+3;
volatile bit		PWMA0ON			@	 ((unsigned)&PWMCON0*8)+4;
volatile bit		PWMA1ON			@	 ((unsigned)&PWMCON0*8)+5;
volatile bit		PWMB0ON			@	 ((unsigned)&PWMCON0*8)+6;
volatile bit		PWMB1ON			@	 ((unsigned)&PWMCON0*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PWMA0EN			: 1;
	unsigned	PWMA1EN			: 1;
	unsigned	PWMB0EN			: 1;
	unsigned	PWMB1EN			: 1;
	unsigned	PWMA0ON			: 1;
	unsigned	PWMA1ON			: 1;
	unsigned	PWMB0ON			: 1;
	unsigned	PWMB1ON			: 1;
	};
} _PWMCON0bits @ 0x0110;
#endif
volatile unsigned char		PWMCON1				@	0x0111;
//        PWMCON1  Bits
volatile bit		PWMA0OL			@	 ((unsigned)&PWMCON1*8)+0;
volatile bit		PWMA1OL			@	 ((unsigned)&PWMCON1*8)+1;
volatile bit		PWMB0OL			@	 ((unsigned)&PWMCON1*8)+2;
volatile bit		PWMB1OL			@	 ((unsigned)&PWMCON1*8)+3;
volatile bit		PWMA0TR			@	 ((unsigned)&PWMCON1*8)+4;
volatile bit		PWMA1TR			@	 ((unsigned)&PWMCON1*8)+5;
volatile bit		PWMB0TR			@	 ((unsigned)&PWMCON1*8)+6;
volatile bit		PWMB1TR			@	 ((unsigned)&PWMCON1*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PWMA0OL			: 1;
	unsigned	PWMA1OL			: 1;
	unsigned	PWMB0OL			: 1;
	unsigned	PWMB1OL			: 1;
	unsigned	PWMA0TR			: 1;
	unsigned	PWMA1TR			: 1;
	unsigned	PWMB0TR			: 1;
	unsigned	PWMB1TR			: 1;
	};
} _PWMCON1bits @ 0x0111;
#endif
volatile unsigned char		PRLA0L				@	0x0112;
volatile unsigned char		PRLA1L				@	0x0113;
volatile unsigned char		PRLB0L				@	0x0114;
volatile unsigned char		PRLB1L				@	0x0115;
volatile unsigned char		T1PRLL				@	0x0117;
volatile unsigned char		ET1PRL				@	0x0118;
volatile unsigned char		T2PRLL				@	0x0119;
volatile unsigned char		ET2PRL				@	0x011A;
volatile unsigned char		PWMA0L				@	0x0192;
volatile unsigned char		PWMA1L				@	0x0193;
volatile unsigned char		PWMB0L				@	0x0194;
volatile unsigned char		PWMB1L				@	0x0195;
volatile unsigned char		EPRA0H				@	0x0197;
//        EPRA0H  Bits
volatile bit		PRA0H0			@	 ((unsigned)&EPRA0H*8)+0;
volatile bit		PRA0H1			@	 ((unsigned)&EPRA0H*8)+1;
volatile bit		PRA0H2			@	 ((unsigned)&EPRA0H*8)+2;
volatile bit		PRA0H3			@	 ((unsigned)&EPRA0H*8)+3;
volatile bit		PWMA0H0			@	 ((unsigned)&EPRA0H*8)+4;
volatile bit		PWMA0H1			@	 ((unsigned)&EPRA0H*8)+5;
volatile bit		PWMA0H2			@	 ((unsigned)&EPRA0H*8)+6;
volatile bit		PWMA0H3			@	 ((unsigned)&EPRA0H*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PRA0H0			: 1;
	unsigned	PRA0H1			: 1;
	unsigned	PRA0H2			: 1;
	unsigned	PRA0H3			: 1;
	unsigned	PWMA0H0			: 1;
	unsigned	PWMA0H1			: 1;
	unsigned	PWMA0H2			: 1;
	unsigned	PWMA0H3			: 1;
	};
} _EPRA0Hbits @ 0x0197;
#endif
volatile unsigned char		EPRA1H				@	0x0198;
//        EPRA1H  Bits
volatile bit		PRA1H0			@	 ((unsigned)&EPRA1H*8)+0;
volatile bit		PRA1H1			@	 ((unsigned)&EPRA1H*8)+1;
volatile bit		PRA1H2			@	 ((unsigned)&EPRA1H*8)+2;
volatile bit		PRA1H3			@	 ((unsigned)&EPRA1H*8)+3;
volatile bit		PWMA1H0			@	 ((unsigned)&EPRA1H*8)+4;
volatile bit		PWMA1H1			@	 ((unsigned)&EPRA1H*8)+5;
volatile bit		PWMA1H2			@	 ((unsigned)&EPRA1H*8)+6;
volatile bit		PWMA1H3			@	 ((unsigned)&EPRA1H*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PRA1H0			: 1;
	unsigned	PRA1H1			: 1;
	unsigned	PRA1H2			: 1;
	unsigned	PRA1H3			: 1;
	unsigned	PWMA1H0			: 1;
	unsigned	PWMA1H1			: 1;
	unsigned	PWMA1H2			: 1;
	unsigned	PWMA1H3			: 1;
	};
} _EPRA1Hbits @ 0x0198;
#endif
volatile unsigned char		EPRB0H				@	0x0199;
//        EPRB0H  Bits
volatile bit		PRB0H0			@	 ((unsigned)&EPRB0H*8)+0;
volatile bit		PRB0H1			@	 ((unsigned)&EPRB0H*8)+1;
volatile bit		PRB0H2			@	 ((unsigned)&EPRB0H*8)+2;
volatile bit		PRB0H3			@	 ((unsigned)&EPRB0H*8)+3;
volatile bit		PWMB0H0			@	 ((unsigned)&EPRB0H*8)+4;
volatile bit		PWMB0H1			@	 ((unsigned)&EPRB0H*8)+5;
volatile bit		PWMB0H2			@	 ((unsigned)&EPRB0H*8)+6;
volatile bit		PWMB0H3			@	 ((unsigned)&EPRB0H*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PRB0H0			: 1;
	unsigned	PRB0H1			: 1;
	unsigned	PRB0H2			: 1;
	unsigned	PRB0H3			: 1;
	unsigned	PWMB0H0			: 1;
	unsigned	PWMB0H1			: 1;
	unsigned	PWMB0H2			: 1;
	unsigned	PWMB0H3			: 1;
	};
} _EPRB0Hbits @ 0x0199;
#endif
volatile unsigned char		EPRB1H				@	0x019A;
//        EPRB1H  Bits
volatile bit		PRB1H0			@	 ((unsigned)&EPRB1H*8)+0;
volatile bit		PRB1H1			@	 ((unsigned)&EPRB1H*8)+1;
volatile bit		PRB1H2			@	 ((unsigned)&EPRB1H*8)+2;
volatile bit		PRB1H3			@	 ((unsigned)&EPRB1H*8)+3;
volatile bit		PWMB1H0			@	 ((unsigned)&EPRB1H*8)+4;
volatile bit		PWMB1H1			@	 ((unsigned)&EPRB1H*8)+5;
volatile bit		PWMB1H2			@	 ((unsigned)&EPRB1H*8)+6;
volatile bit		PWMB1H3			@	 ((unsigned)&EPRB1H*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	PRB1H0			: 1;
	unsigned	PRB1H1			: 1;
	unsigned	PRB1H2			: 1;
	unsigned	PRB1H3			: 1;
	unsigned	PWMB1H0			: 1;
	unsigned	PWMB1H1			: 1;
	unsigned	PWMB1H2			: 1;
	unsigned	PWMB1H3			: 1;
	};
} _EPRB1Hbits @ 0x019A;
#endif
volatile unsigned char		T1PRLH				@	0x019B;
//        T1PRLH  Bits
volatile bit		T1PRLH0			@	 ((unsigned)&T1PRLH*8)+0;
volatile bit		T1PRLH1			@	 ((unsigned)&T1PRLH*8)+1;
volatile bit		T1PRLH2			@	 ((unsigned)&T1PRLH*8)+2;
volatile bit		T1PRLH3			@	 ((unsigned)&T1PRLH*8)+3;
volatile bit		ET1PRH0			@	 ((unsigned)&T1PRLH*8)+4;
volatile bit		ET1PRH1			@	 ((unsigned)&T1PRLH*8)+5;
volatile bit		ET1PRH2			@	 ((unsigned)&T1PRLH*8)+6;
volatile bit		ET1PRH3			@	 ((unsigned)&T1PRLH*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	T1PRLH0			: 1;
	unsigned	T1PRLH1			: 1;
	unsigned	T1PRLH2			: 1;
	unsigned	T1PRLH3			: 1;
	unsigned	ET1PRH0			: 1;
	unsigned	ET1PRH1			: 1;
	unsigned	ET1PRH2			: 1;
	unsigned	ET1PRH3			: 1;
	};
} _T1PRLHbits @ 0x019B;
#endif
volatile unsigned char		T2PRLH				@	0x019C;
//        T2PRLH  Bits
volatile bit		T2PRLH0			@	 ((unsigned)&T2PRLH*8)+0;
volatile bit		T2PRLH1			@	 ((unsigned)&T2PRLH*8)+1;
volatile bit		T2PRLH2			@	 ((unsigned)&T2PRLH*8)+2;
volatile bit		T2PRLH3			@	 ((unsigned)&T2PRLH*8)+3;
volatile bit		ET2PRH0			@	 ((unsigned)&T2PRLH*8)+4;
volatile bit		ET2PRH1			@	 ((unsigned)&T2PRLH*8)+5;
volatile bit		ET2PRH2			@	 ((unsigned)&T2PRLH*8)+6;
volatile bit		ET2PRH3			@	 ((unsigned)&T2PRLH*8)+7;
#ifndef _LIB_BUILD 
volatile union
{
	struct
	{
	unsigned	T2PRLH0			: 1;
	unsigned	T2PRLH1			: 1;
	unsigned	T2PRLH2			: 1;
	unsigned	T2PRLH3			: 1;
	unsigned	ET2PRH0			: 1;
	unsigned	ET2PRH1			: 1;
	unsigned	ET2PRH2			: 1;
	unsigned	ET2PRH3			: 1;
	};
} _T2PRLHbits @ 0x019C;
#endif
#endif // #ifndef __MDT10F273_H__
