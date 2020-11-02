
;========================================================================
W	EQU	0
R	EQU	1
;===========================================宏及指令别名定义，宏定义请参阅IDE帮文档
BANK0 MACRO
	BCR	RP0
	BCR	RP1
	ENDM
BANK1 MACRO
	BSR	RP0
	BCR	RP1
	ENDM
BANK2 MACRO
	BCR	RP0
	BSR	RP1
	ENDM
BANK3 MACRO
	BSR	RP0
	BSR	RP1
	ENDM
	
;--------------------------以下定义切BANK为省指令时可用，但要注意预防出错	
#define BK0TOBK1 BSR	RP0
#define BK1TOBK0 BCR	RP0
#define BK0TOBK2 BSR	RP1
#define BK2TOBK0 BCR	RP1
#define BK2TOBK3 BSR	RP0
#define BK3TOBK2 BCR	RP0


;===========================================特殊功能寄存
	
;--------------------------bank0
IAR						EQU		000H
TMR0					EQU		001H
PCL						EQU		002H
STATUS				EQU		003H
MSR						EQU		004H
PORTA					EQU		005H
PORTC					EQU		007H
PCLATH				EQU		00AH
INTS					EQU		00BH
PIFB0					EQU		00CH
PIFB1					EQU		00DH
TMR1L					EQU		00EH
TMR1H					EQU		00FH
T1STA					EQU		010H
TMR2L					EQU		011H
TMR2H					EQU		012H
T2STA					EQU		013H
T12CON				EQU		014H
WDTCNTL				EQU		016H
WDTCNTH				EQU		017H
WDTCON				EQU		018H
ADC0CN				EQU		01CH
ADS0					EQU		01DH
ADRESL				EQU		01EH
ADRESH				EQU		01FH

;--------------------------bank1
OPT_REG				EQU		081H
CPIOA					EQU		085H
CPIOC					EQU		087H
PSTA					EQU		08EH
OSCCON				EQU		08FH
FOSCTRIM			EQU		090H
FOSCCFG				EQU		091H
ADINA					EQU		094H
PAPHR					EQU		095H
PAINTR				EQU		096H
PAPDR					EQU		097H
PCPHR					EQU		09CH
PCPDR					EQU		09DH
ADINC					EQU		09FH


;--------------------------bank2
PWMCON0				EQU		110H
PWMCON1				EQU		111H
PRLA0L				EQU		112H
PRLA1L				EQU		113H
PRLB0L				EQU		114H
PRLB1L				EQU		115H
T1PRLL				EQU		117H
ET1PRL				EQU		118H
T2PRLL				EQU		119H
ET2PRL				EQU		11AH


;--------------------------bank3
PWMA0L				EQU		192H
PWMA1L				EQU		193H
PWMB0L				EQU		194H
PWMB1L				EQU		195H
EPRA0H				EQU		197H
EPRA1H				EQU		198H
EPRB0H				EQU		199H
EPRB1H				EQU		19AH
T1PRLH				EQU		19BH
T2PRLH				EQU		19CH



;----------------------bank0
;------STATUS Bits --
#define		C						STATUS,0
#define		HC					STATUS,1
#define		Z						STATUS,2
#define		PF					STATUS,3
#define		TF					STATUS,4
#define		RP0					STATUS,5
#define		RP1					STATUS,6
#define		IRP					STATUS,7
;-------PORTA Bits --
#define		PA0					PORTA,0
#define		PA1					PORTA,1
#define		PA2					PORTA,2
#define		PA3					PORTA,3
#define		PA4					PORTA,4
#define		PA5					PORTA,5
;-------PORTC Bits --
#define		PC0					PORTC,0
#define		PC1					PORTC,1
#define		PC2					PORTC,2
#define		PC3					PORTC,3
#define		PC4					PORTC,4
#define		PC5					PORTC,5
#define		PC6					PORTC,6
#define		PC7					PORTC,7
;-------INTS Bits ---
#define		PAIF				INTS,0
#define		INT0F				INTS,1
#define		TIF					INTS,2
#define		PAIE				INTS,3
#define		INT0E				INTS,4
#define		TIS					INTS,5
#define		PEIE				INTS,6
#define		GIE					INTS,7
;-------PIFB0 Bits --
#define		TMR1IF			PIFB0,0
#define		OSFIF				PIFB0,1
#define		ADIF				PIFB0,2
#define		INT1F				PIFB0,3
#define		TMR1IE			PIFB0,4
#define		OSFIE				PIFB0,5
#define		ADIE				PIFB0,6
#define		INT1E				PIFB0,7
;-------PIFB1 Bits --
#define		TMR2IF			PIFB1,0
#define		PWMAF				PIFB1,1
#define		PWMBF				PIFB1,2
#define		INT0SEL			PIFB1,3
#define		TMR2IE			PIFB1,4
#define		PWMAIE			PIFB1,5
#define		PWMBIE			PIFB1,6
#define		INT1SEL			PIFB1,7
;-------T1STA Bits --
#define		TMR1ON			T1STA,0
#define		TMR1CS			T1STA,1
#define		T1SYNC			T1STA,2
#define		T1OSCEN			T1STA,3
#define		T1CKPS0			T1STA,4
#define		T1CKPS1			T1STA,5
#define		TMR1GE			T1STA,6
#define		T1GINV			T1STA,7
;-------T2STA Bits --
#define		TMR2ON			T2STA,0
#define		TMR2CS			T2STA,1
#define		T2SYNC			T2STA,2
#define		T2OSCEN			T2STA,3
#define		T2CKPS0			T2STA,4
#define		T2CKPS1			T2STA,5
#define		TMR2GE			T2STA,6
#define		T2GINV			T2STA,7
;-------T12CON Bits -
#define		T1FOSC			T12CON,0
#define		T1SELEN			T12CON,1
#define		T2FOSC			T12CON,2
#define		T2SELEN			T12CON,3
#define		DIE_NUM0		T12CON,4
#define		DIE_NUM1		T12CON,5
#define		DIE_NUM2		T12CON,6
#define		DIE_EN			T12CON,7
;-------WDTCON Bits -
#define		SWDTEN			WDTCON,0
#define		WDTPS0			WDTCON,1
#define		WDTPS1			WDTCON,2
#define		WDTPS2			WDTCON,3
#define		WDTPS3			WDTCON,4

#define		PWMB1CP			WDTCON,6
#define		PWMB0CP			WDTCON,7

;-------ADC0CN Bits -
#define		CM0					ADC0CN,0
#define		CM1					ADC0CN,1
#define		BUSY				ADC0CN,2
#define		ADC_EN			ADC0CN,3
#define		SC0					ADC0CN,4
#define		SC1					ADC0CN,5
#define		ADFM				ADC0CN,6
;-------ADS0 Bits ---
#define		VREFSEL0		ADS0,0
#define		VREFSEL1		ADS0,1
#define		REFSEL0			ADS0,2
#define		REFSEL1			ADS0,3
#define		CHNSEL0			ADS0,4
#define		CHNSEL1			ADS0,5
#define		CHNSEL2			ADS0,6
#define		CHNSEL3			ADS0,7


;----------------------bank1
;-------OPT_REG Bits---
#define		PS0					OPT_REG,0
#define		PS1					OPT_REG,1
#define		PS2					OPT_REG,2
#define		PSC					OPT_REG,3
#define		TCE					OPT_REG,4
#define		TCS					OPT_REG,5
#define		TMR0EN			OPT_REG,6
;-------CPIOA Bits --
#define		CPIOA0			CPIOA,0
#define		CPIOA1			CPIOA,1
#define		CPIOA2			CPIOA,2
#define		CPIOA3			CPIOA,3
#define		CPIOA4			CPIOA,4
#define		CPIOA5			CPIOA,5
;-------CPIOC Bits --
#define		CPIOC0			CPIOC,0
#define		CPIOC1			CPIOC,1
#define		CPIOC2			CPIOC,2
#define		CPIOC3			CPIOC,3
#define		CPIOC4			CPIOC,4
#define		CPIOC5			CPIOC,5
#define		CPIOC6			CPIOC,6
#define		CPIOC7			CPIOC,7
;-------PSTA Bits ---
#define		LVR					PSTA,0
#define		POR					PSTA,1
#define		IER					PSTA,2
#define		MCR					PSTA,3
#define		SLVREN			PSTA,4
#define		ULPWUE			PSTA,5
;-------OSCCON Bits -
#define		SCS					OSCCON,0
#define		LTS					OSCCON,1
#define		HTS					OSCCON,2
#define		OSTS				OSCCON,3
#define		IRCF0				OSCCON,4
#define		IRCF1				OSCCON,5
#define		IRCF2				OSCCON,6
#define		FOSCEN			OSCCON,7
;-------ADINA Bits --
#define		AN0					ADINA,0
#define		AN1					ADINA,1
#define		AN2					ADINA,2
#define		AN3					ADINA,4
#define		AN4					ADINA,5
;-------PAPHR Bits --
#define		PAPHR0			PAPHR,0
#define		PAPHR1			PAPHR,1
#define		PAPHR2			PAPHR,2
#define		PAPHR3			PAPHR,3
#define		PAPHR4			PAPHR,4
#define		PAPHR5			PAPHR,5
;-------PAINTR Bits -
#define		PAINTR0			PAINTR,0
#define		PAINTR1			PAINTR,1
#define		PAINTR2			PAINTR,2
#define		PAINTR3			PAINTR,3
#define		PAINTR4			PAINTR,4
#define		PAINTR5			PAINTR,5
;-------PAPDR Bits --
#define		PAPDR0			PAPDR,0
#define		PAPDR1			PAPDR,1
#define		PAPDR2			PAPDR,2
#define		PAPDR4			PAPDR,4
#define		PAPDR5			PAPDR,5
;-------PCPHR Bits --
#define		PCPHR0			PCPHR,0
#define		PCPHR1			PCPHR,1
#define		PCPHR2			PCPHR,2
#define		PCPHR3			PCPHR,3
#define		PCPHR4			PCPHR,4
#define		PCPHR5			PCPHR,5
#define		PCPHR6			PCPHR,6
#define		PCPHR7			PCPHR,7
;-------PCPDR Bits --
#define		PCPDR0			PCPDR,0
#define		PCPDR1			PCPDR,1
#define		PCPDR2			PCPDR,2
#define		PCPDR3			PCPDR,3
#define		PCPDR4			PCPDR,4
#define		PCPDR5			PCPDR,5
#define		PCPDR6			PCPDR,6
#define		PCPDR7			PCPDR,7
;-------ADINC Bits --
#define		AN5					ADINC,0
#define		AN6					ADINC,1
#define		AN7					ADINC,2
#define		AN8					ADINC,3
#define		AN9					ADINC,4
#define		AN10				ADINC,5
#define		AN11				ADINC,6
#define		AN12				ADINC,7


;--------------------bank2
;-------PWMCON0 Bits-
#define		PWMA0EN			PWMCON0,0
#define		PWMA1EN			PWMCON0,1
#define		PWMB0EN			PWMCON0,2
#define		PWMB1EN			PWMCON0,3
#define		PWMA0ON			PWMCON0,4
#define		PWMA1ON			PWMCON0,5
#define		PWMB0ON			PWMCON0,6
#define		PWMB1ON			PWMCON0,7
;-------PWMCON1 Bits-
#define		PWMA0OL			PWMCON1,0
#define		PWMA1OL			PWMCON1,1
#define		PWMB0OL			PWMCON1,2
#define		PWMB1OL			PWMCON1,3
#define		PWMA0TR			PWMCON1,4
#define		PWMA1TR			PWMCON1,5
#define		PWMB0TR			PWMCON1,6
#define		PWMB1TR			PWMCON1,7