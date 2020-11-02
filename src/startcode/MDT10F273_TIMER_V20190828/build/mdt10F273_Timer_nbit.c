#include	"mdt10F273_Timer_bitname.h"
/***********************************************************************************
;Company : Yspring ------�����л㴺�Ƽ��ɷ����޹�˾
;File Name :10F272
;Author : Zhu_Chuan_rong
;Create Data : 2018-05
;Last Modified :2018-05
;Description :  MDT10F272_TIMER_��������
;Version : 1.0
************************************************************************************/


#include <mdt.h>		//�� <> ������ͷ�ļ���ֱ�ӵ�IDE��װĿ¼ȥ����
#include "mdt10F273.h"	//�á���������ͷ�ļ����ȵ�����Ŀ¼�²��ң��Ҳ������ٵ�IDE��װĿ¼ȥ���ң�
#include "273cfg.h"

//--------------------------------------------���������ض���

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;


//--------------------------------------------��������

void Init_IRCF(void);
void CLR_RAM(void);
void Init_Timer0_WDT(void);
void Init_Timer1(void);
void Init_Timer2(void);
void Init_GPIO(void);
void Init_INT(void);




//--------------------------------------------������(������) ����

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

FLAG FLAG0;		//�ṹ��������

//--------------------------------------------�ṹ���ͱ���λ��궨��
#define flag_t0		FLAG0.bit_type.b0 
#define flag_t1		FLAG0.bit_type.b1
#define flag_t2	 	FLAG0.bit_type.b2
#define flag_3		FLAG0.bit_type.b3
#define flag_4		FLAG0.bit_type.b4
#define flag_5		FLAG0.bit_type.b5
#define flag_6		FLAG0.bit_type.b6
#define flag_7		FLAG0.bit_type.b7


//--------------------------------------------�궨��


#define TRUE	1
#define FALSE	0

#define CLR_BYTE	0x00
#define CLR_WORD	0x0000
#define CLR_LONG	0x00000000


#define	T2S		20	//2s = 20 * 100ms
#define	T1S		100	//1s = 100 * 10ms
#define	T500MS	250	//500ms = 250 * 2ms

	
//--------------------------------------------��������



volatile u8 Timer_2ms_ctr;
volatile u8 Timer_10ms_ctr;
volatile u8 Timer_100ms_ctr;




/*******************************************************************
;
;������: main 
;
;����˵��:	���������
;
********************************************************************/
void main(void)         
{
	Init_IRCF();
	CLR_RAM();
	Init_Timer0_WDT();
	Init_Timer1();
	Init_Timer2();
	Init_GPIO();
	Init_INT();

//==========================================��ѭ��
	while(1)
	{
		CLRWDT();	//��� ���Ź� 
			
		if(flag_t0 == TRUE)
		{
			flag_t0 = FALSE;
			
			Timer_2ms_ctr ++ ;
			if(Timer_2ms_ctr >= T500MS)
			{
				Timer_2ms_ctr = CLR_BYTE;
				
				PORTC ^= 0x08;	//PC3 	500ms ȡ�����
			}
		}
		
		if(flag_t1 == TRUE)
		{
			flag_t1 = FALSE;
			
			Timer_10ms_ctr ++ ;
			if(Timer_10ms_ctr >= T1S)
			{
				Timer_10ms_ctr = CLR_BYTE;
				
				PORTC ^= 0x010;	//PC4 	1s ȡ�����
			}
		}

		
		if(flag_t2 == TRUE)
		{
			flag_t2 = FALSE;
			
			Timer_100ms_ctr ++ ;
			if(Timer_100ms_ctr >= T2S)
			{
				Timer_100ms_ctr = CLR_BYTE;
				
				PORTC ^= 0x20;	//PC5 	2s ȡ�����
			}
		}
			
	}
}


/*******************************************************************
;
;������: ISR 
;
;����˵��:	�жϷ������
;
********************************************************************/
//void ISR(void) __interrupt 		//YSDCC ���� �жϺ�������
void interrupt ISR(void)		//PICC ���� �жϺ�������
{
	
	if(TIF == 1)
	{
		TIF = 0;		//T0 ���Զ����ع��� ����Ҫ���ó�ʼֵ
		
		PORTC ^= 0x01;	//Timer0 ��ʱ 2ms�ж����	PC0 ȡ�����
		flag_t0 = TRUE;
	}
	
	if(TMR1IF == 1)
	{
		TMR1IF = 0;
		
		TMR1ON = 0;			//T1�����ó�ʼֵ
		TMR1H = 0x63;		//25536 = 65536 - 40000	(0x63c0 = 25536)
		TMR1L = 0xc0;		//10ms = 40000 * 0.25us	( Fosc = 4MHz  __ T = 0.25us)
		TMR1ON = 1;		
		
		PORTC ^= 0x02;		//Timer1 ��ʱ 10ms�ж����	PC1 ȡ�����
		flag_t1 = TRUE;
	}
	
	if(TMR2IF == 1)
	{
		TMR2IF = 0;
		
		TMR2ON = 0;			//T2�����ó�ʼֵ
		TMR2H = 0x3c;		//15536 = 65536 - 50000	(0x3cb0 = 15536)
		TMR2L = 0xb0;		//100ms = 50000 * 2us
		TMR2ON = 1;	
		
		PORTC ^= 0x04;		//Timer2 ��ʱ100ms�ж����	PC2 ȡ�����
		flag_t2 = TRUE;
	}
}




/*******************************************************************
;
;������: Init_GPIO

;����˵��:	��ʼ��IO��
;
********************************************************************/

void Init_GPIO(void)
{
	ADINA = 0x00;	//PAģ��/����IO���� 		1:ģ�⹦��		0:����I/O����
	ADINC = 0x00;	//PCģ��/����IO���� 		1:ģ�⹦��		0:����I/O����
	
	CPIOA = 0b00001000;	//PA�������������		1:����		0:���
	CPIOC = 0b00000000;	//PC�������������		1:����		0:���
	
	PAPHR = 0x00;	//PA����������λ			1:ʹ��		0:��ֹ
	PAPDR = 0x00;	//PA����������λ			1:ʹ��		0:��ֹ
	
	PCPHR = 0x00;	//PC����������λ			1:ʹ��		0:��ֹ
	PCPDR = 0x00;	//PC����������λ			1:ʹ��		0:��ֹ
		
	PAINTR = 0x00;	//PA��ƽ�仯�ж�����λ		1:ʹ��		0:��ֹ
	
	PORTA = 0x00;	//PAȫ���"L"
	PORTC = 0x00;	//PCȫ���"L"
}


/*******************************************************************
;
;������: Init_Timer0_WDT

;����˵��:	��ʼ��Timer0��WDT
;
********************************************************************/

void Init_Timer0_WDT(void)
{
	TCS = 0;		//TMR0ʱ��Դѡ��λ		1:PA2/T0CKI�������źŵ�����		0:�ڲ�ָ������ʱ�ӣ� Fosc/4��
	T0PSDIV_8();	//Timer0Ԥ��Ƶ��ѡ��1:8	����8us	(Fosc = 4MHz)  (Fcpu = Fosc/4 = 1MHz)
	TMR0 = 6;		//250 = 256 - 6		2ms = 250 * 8us	
	TMR0EN = 1;		//Tiemr0 ����/ֹͣλ	1:����Timer0		0:ֹͣTimer0
	
//	WDTDIV_512();
	WDTDIV_32768();
	SWDTEN = 1;	
}


/*******************************************************************
;
;������: Init_Timer1

;����˵��:	��ʼ��Timer1
;
********************************************************************/
void Init_Timer1(void)
{
	
	T1SELEN = 0;//Timer1 ʱ��Դѡ��λ				0: Timer1 ʱ��Դ��TMR1CSλȷ��
//	T1SELEN = 1;	//Timer1 ʱ��Դѡ��λ				1: Timer1 ʱ��Դ�� T1FOSCλȷ��

	T1FOSC = 0; //Timer1 ʱ��Դѡ���ڲ���ʱ��ʹ��λ 	0: Timer1 ʱ��Դѡ���ڲ� " ��ʱ�� " 	(�� T1SELEN = 1ʱ)
//	T1FOSC = 1; //Timer1 ʱ��Դѡ���ڲ���ʱ��ʹ��λ 	1: Timer1 ʱ��Դѡ���ڲ� " ��ʱ�� " (�� T1SELEN = 1ʱ)
		

	T1GINV = 0; //Timer1�ſط�תλ					0: Timer1�ſ�Ϊ�͵�ƽ��Ч���ſ�Ϊ�͵�ƽʱTimer1������
//	T1GINV = 1; 	//Timer1�ſط�תλ				1: Timer1�ſ�Ϊ�ߵ�ƽ��Ч���ſ�Ϊ�ߵ�ƽʱTimer1������

	TMR1GE = 0; //Timer1�ſ�ʹ��λ					0: Timer1��
//	TMR1GE = 1; 	//Timer1�ſ�ʹ��λ				1: Timer1��Timer1�ſز��ʱ��

	T1PSDIV_1();	//Timer1����ʱ��Ԥ��Ƶ��ѡ��1:1	( Fosc = 4MHz  __ T = 0.25us)	

	T1SYNC = 0; 	//Timer1�ⲿʱ������ͬ������λ		0: ͬ���ⲿʱ������
//	T1SYNC = 1; 	//Timer1�ⲿʱ������ͬ������λ		1: ��ͬ���ⲿʱ������

	TMR1CS = 0; 	//Timer1ʱ��Դѡ��λ			0: �ڲ�ʱ�ӣ�FOSC��
//	TMR1CS = 1; 	//Timer1ʱ��Դѡ��λ			1: ����T12CK1���ţ������أ����ⲿʱ��

	T1OSCEN = 0;	//LP����ʹ�ܿ���λ			0:	LP�����ر�
//	T1OSCEN = 1;	//LP����ʹ�ܿ���λ			1:	LP������ʹ������Timer1ʱ��	


	TMR1H = 0x63;		//25536 = 65536 - 40000	(0x63c0 = 25536)
	TMR1L = 0xc0;		//10ms = 40000 * 0.25us	( Fosc = 4MHz  __ T = 0.25us)

	TMR1ON = 1;		//Timer1����/ֹͣλ		1: ���� Timer1		0: ֹͣTimer1

}


/*******************************************************************
;
;������: Init_Timer2

;����˵��:	��ʼ��Timer2
;
********************************************************************/
void Init_Timer2(void)
{
	
	T2SELEN = 0;	//Timer2 ʱ��Դѡ��λ					0: Timer2 ʱ��Դ��TMR2CSλȷ��
//	T2SELEN = 1;	//Timer2 ʱ��Դѡ��λ					1: Timer2 ʱ��Դ�� T2FOSCλȷ��

	T2FOSC = 0; //Timer2 ʱ��Դѡ���ڲ���ʱ��ʹ��λ 		0: Timer2 ʱ��Դѡ���ڲ� " ��ʱ�� " 	(�� T2SELEN = 1ʱ)
//	T2FOSC = 1; //Timer2 ʱ��Դѡ���ڲ���ʱ��ʹ��λ 	1: Timer2 ʱ��Դѡ���ڲ� " ��ʱ�� " (�� T2SELEN = 1ʱ)
		

	T2GINV = 0;		//Timer2�ſط�תλ					0: Timer2�ſ�Ϊ�͵�ƽ��Ч���ſ�Ϊ�͵�ƽʱTimer2������
//	T2GINV = 1;		//Timer2�ſط�תλ				1: Timer2�ſ�Ϊ�ߵ�ƽ��Ч���ſ�Ϊ�ߵ�ƽʱTimer2������

	TMR2GE = 0;		//Timer2�ſ�ʹ��λ					0: Timer2��
//	TMR2GE = 1;		//Timer2�ſ�ʹ��λ				1: Timer2��Timer2�ſز��ʱ��

	T2PSDIV_8();	//Timer2����ʱ��Ԥ��Ƶ��ѡ��1:8	( Fosc = 4MHz  __ T = 2us)

	T2SYNC = 0;		//Timer2�ⲿʱ������ͬ������λ		0: ͬ���ⲿʱ������
//	T2SYNC = 1;		//Timer2�ⲿʱ������ͬ������λ		1: ��ͬ���ⲿʱ������

	TMR2CS = 0;		//Timer2ʱ��Դѡ��λ			0: �ڲ�ʱ�ӣ�SYS_CLK��
//	TMR2CS = 1;		//Timer2ʱ��Դѡ��λ			1: ����T12CK1���ţ������أ����ⲿʱ��

	T2OSCEN = 0;	//LP����ʹ�ܿ���λ			0:  LP�����ر�
//	T2OSCEN = 1;	//LP����ʹ�ܿ���λ			1:  LP������ʹ������Timer2ʱ��	

	
	TMR2H = 0x3c;		//15536 = 65536 - 50000	(0x3cb0 = 15536)
	TMR2L = 0xb0;		//100ms = 50000 * 2us
	
	TMR2ON = 1;		//Timer2����/ֹͣλ		1: ���� Timer2		0: ֹͣTimer2
}


/*******************************************************************
;
;������: Init_INT

;����˵��:	��ʼ�� �ж�
;
********************************************************************/

void Init_INT(void)
{
	INTS = 0x00;	//�ж���ؼĴ��� ����
	
	TIF = 0;
	TIS = 1;		//ʹ�� T0�ж�
	
	TMR1IF = 0;
	TMR1IE = 1;		//ʹ��  T1�ж�		�õ� T1�ж� ��ͬʱʹ�� T1�жϡ������жϡ����ж� 
	
	TMR2IF = 0;
	TMR2IE = 1;		//ʹ��  T2�ж�		�õ� T2�ж� ��ͬʱʹ�� T2�жϡ������жϡ����ж� 
	
	PEIE = 1;		//ʹ��  �����ж�
	GIE = 1;		//ʹ��  ���ж�
}



/*******************************************************************
;
;������: Init_IRCF 
;
;����˵��:	��ʼ�� �ڲ�ϵͳʱ��
;
********************************************************************/

void Init_IRCF(void)
{
	SCS = 1;		//ϵͳʱ��ѡ��λ		1:�ڲ���������ϵͳʱ��		0:ʱ��Դ��FOSC<2:0>����
	
	IRCF_16MHZ();	//�ڲ�����Ƶ��ѡ��16MHz
	asm("nop");		//�л��� Fosc ����ʱ ���� "nop" ָ�� �ȴ�ʱ���ȶ�
	asm("nop");
	while(HTS == 0)	//�ȴ��ڲ���ʱ���ȶ�
		asm("clrwdt");	

	IRCF_8MHZ();	//�ڲ�����Ƶ��ѡ��8MHz
	asm("nop");
	asm("nop");
	while(HTS == 0)			
		asm("clrwdt");	
	
	IRCF_4MHZ();	//�ڲ�����Ƶ��ѡ��4MHz
	asm("nop");
	asm("nop");
	while(HTS == 0)			
		asm("clrwdt");		
}




/*******************************************************************
;
;������: CLR_RAM 
;
;����˵��:	���ڴ�
;
********************************************************************/

void CLR_RAM(void)
{
	MSR = 0x20;
	while(MSR <= 0x7f)	//��0x20 ~ 0x7f  ��RAM ����
	{
		IAR = 0;
		MSR ++ ;
	}
	
	MSR = 0xa0;
	while(MSR <= 0xbf)	//��0xa0 ~ 0xbf  ��RAM ����
	{
		IAR = 0;
		MSR ++ ;
	}
}



