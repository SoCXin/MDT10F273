/***********************************************************************************
;Company : Yspring ------�����л㴺�Ƽ��ɷ����޹�˾
;File Name :10F273
;Description :  MDT10F273_AD_��������
;
;������˵��������PA2�ĵ�ѹ��ͨ��UART����ڷ��͵�PC����ʾ
;
;		MCU������ѹ2.2~5.5V
;
;		PA2��ΪAD�������ѹ������ѹ��Χ0 ~ 2.048V 
;
;		PA4�ӿ���S1����ѡ��UART�����ʣ�S1�Ͽ�ѡ��9600 bps��S1�պ�ѡ��19200 bps
;
;		PA5��ΪUART����ڣ�����AD���ݣ�12λAD���ת��Ϊʮ������ʽ���͵�PC��ʾ����ֵ��Χ 0 ~ 4095��
;		
;		ע�⣺PC�˴������ֽ��ջ�������ѡ��"�ı�ģʽ"
;
***********************************************************************************/

#include "mdt10F273.h"	//�á���������ͷ�ļ����ȵ�����Ŀ¼�²��ң��Ҳ������ٵ�IDE��װĿ¼ȥ���ң�
#include "273cfg.h"

//-----------------------------------���������ض���--------------------------------

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

//------------------------------------��������-------------------------------------

void Init_Timer0_WDT(void);           //��ʼ��tmr0��WDT
void Init_Timer1(void);               //��ʼ��timer1
void Init_Timer2(void);               //��ʼ��timer2
void Init_GPIO(void);                 //��ʼ��IO
void Init_INT(void);                  //��ʼ��INT
void Init_ADC(void);                  //��ʼ��ADC
void delay(unsigned char i);          //��ʱ����

void Uart_Tx_Deal(void);              //���ڷ�������
u16 Get_ADC_Result(u8 CHx ,u8 REFx);  //AD�ɼ�����

//-------------------------�궨��---------------------------------------

#define	UART_IO_OUT_L()		(PA5 = 0) //��������͵�ƽ
#define	UART_IO_OUT_H()		(PA5 = 1) //��������ߵ�ƽ

#define CHAR_SPACE	32	//ASIIֵ 32�� ��ӡ "�ո�"�ַ�
#define CHAR_CR		13	//ASIIֵ 13�� ��ӡ�����ַ�  "�س�"
#define CHAR_LF		10	//ASIIֵ 10�� ��ӡ�����ַ�  "����"
//#define CHAR_CR		'\r'	//ASIIֵ 13�� ��ӡ�����ַ�  "�س�"
//#define CHAR_LF		'\n'	//ASIIֵ 10�� ��ӡ�����ַ�  "����"

const u8 table_char[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'}; 


//#define DEBUG_UART_0X55_0XAA		1	//   ����ģʽ ����Ϊ"1"
#define DEBUG_UART_0X55_0XAA		0	//�ǵ���ģʽ ����Ϊ"0"


//-----------------------------------��������-------------------------------------
u8 uart_10bit_temp;	    //���ڼ�����
u8 uart_data_temp;      //�������ݻ���
u8 delay_ctr_1;         //

u8 i;

u16 adc_temp;           //AD��ʱ����

u8 adc_HH;              //ADֵǧλ������
u8 adc_HL;              //ADֵ��λ������
u8 adc_LH;              //ADֵʮλ������
u8 adc_LL;              //ADֵ��λ������
//-----------------------------------λ����---------------------------------------
bit flag_t0=0;

/*********************************************************************************
;
;������: main 
;
;����˵��:  ���������
;
*********************************************************************************/
void main(void)         
{
	CLRWDT();

	SET_HIRC(IRCF_8M);       //�ڲ�����Ƶ��ѡ��4MHz

	Init_GPIO();             //��ʼ��IO
	Init_Timer0_WDT();       //��ʼ��timer0��WDT
	Init_Timer1();           //��ʼ��timer1
//	Init_Timer2();
	Init_INT();              //��ʼ��INT
	Init_ADC();              //��ʼ��ADC
	

//==========================================��ѭ��
	while(1)
	{
		CLRWDT();	//��� ���Ź� 
				
		if(TMR1IF == 1)
		{
			TMR1ON = 0; 	//Timer1 ��ʱ 50ms���
			TMR1H = 0x3c;   //���� ��ʼֵ 0x3cb0	(15536 = 65536 - 50000) 	(50ms = 50,000us =	50000 * 1us)
			TMR1L = 0xb0;	
			TMR1ON = 1;     //ʹ��TMR1
			
			TMR1IF = 0;     //TMR1�жϱ�־��0

			//ÿ�� 50ms ��ȡһ��ADֵ ��ͨ�� UART ���� PC ����ʾ (Timer0��ʱ�ж� ʵ�� ���UART����)
			
			adc_temp = Get_ADC_Result(ANCHSEL_AN2,VREFSEL_4096MV) - Get_ADC_Result(ANCHSEL_VSS,VREFSEL_4096MV);	//12λ AD ֵ ʮ���� �� 0 ~ 4095

			adc_HH = (adc_temp / 1000);			//ǧ
			adc_HL = ((adc_temp % 1000) / 100);	//��
			adc_LH = ((adc_temp % 100) / 10);	//ʮ
			adc_LL = (adc_temp % 10);			//��
			

#if	DEBUG_UART_0X55_0XAA

			uart_data_temp = 0x55;                      //ʮ������ 0x55 ͨ�� UART���͵� PC����������ѡ��"HEXģʽ"������ʾ
			Uart_Tx_Deal();                             //��������
			
			uart_data_temp = 0xaa;                      //ʮ������ 0xaa ͨ�� UART���͵� PC����������ѡ��"HEXģʽ"������ʾ
			Uart_Tx_Deal();                             //��������
			
#else

			if(adc_temp >= 1000)                        //ȡǧλ��
				uart_data_temp = table_char[adc_HH];	//AD���ת��Ϊʮ���ƽ����ͨ��UART���͵� PC����������ѡ��"�ı�ģʽ"������ʾ
			else
				uart_data_temp = CHAR_SPACE;            //��ӡ "�ո�"
			Uart_Tx_Deal();                             //��������

			
			if(adc_temp >= 100)                         //ȡ��λ��
				uart_data_temp = table_char[adc_HL];
			else
				uart_data_temp = CHAR_SPACE;
			Uart_Tx_Deal();                             //��������
			
			if(adc_temp >= 10)                          //ȡʮλ��
				uart_data_temp = table_char[adc_LH];
			else
				uart_data_temp = CHAR_SPACE;
			Uart_Tx_Deal();                             //��������
			
			uart_data_temp = table_char[adc_LL];        //ȡ��λ�� 
			Uart_Tx_Deal();                             //��������
			
			uart_data_temp = CHAR_CR;	//"�س�"	
			Uart_Tx_Deal();                             //��������
			
			uart_data_temp = CHAR_LF;	//"����"	___��������ѡ��"�ı�ģʽ"������ʾ���ܻ��У�ѡ��"HEXģʽ"���ỻ��
			Uart_Tx_Deal();                             //��������

	
#endif
		}	
	}
}
/*******************************************************************
;
;������: Init_ADC

;����˵��:	��ʼ��AD
;
********************************************************************/
void Init_ADC(void)
{
	ADCHSET_PA2AN2();	//ADͨ������

	ADFM = 1;			//AD��� �Ҷ��룬��λ����
	ADSCKDIV_16();		//ADʱ��Ԥ��Ƶѡ��
	ADSTASEL_BUZY();	//AD����ת��ģʽѡ��


	//ע��: �ϵ��ʼ�� ����˯�߻��Ѻ���ر�ADģ�� �� ���� ����ֹĳЩ����Ӧ�õ���ADģ���쳣
	ADC_EN = 0;			//�ر� ADģ��
}
/**************************************************************************************************
;������: Get_ADC_Result
;
;����˵��: ��ȡAD���������12λAD���(0~4095)
;				
;��ڲ���:  ѡ��ͨ�� CHx ,ѡ��ο���ѹ REFx
;
;����ֵ: 	adc_res
;
***************************************************************************************************/
u16 Get_ADC_Result(u8 CHx ,u8 REFx)
{
	u8 i = 0;
	u16 temp =0,adsum=0;

	ADS0 = 0;
	
	ADS0 = ADS0 | CHx | REFx;	//ģ��ͨ��ѡ��

	ADC_EN = 1;			//���� ADģ�� 	
	
	delay(50);			//��ʱ200us		//�ı�ο���ѹ���� ����ADģ��  ����ʱ200us����

	adsum =0;	
	
	for(i=0;i<8;i++)
	{
		BUSY = 1;			//����AD ��ʼת��
		while(BUSY);		//�ȴ�AD ת�����  
		temp = ADRESH;	//(0000 xxxx)��ȡ12λAD ������ֽڼĴ���(��4λΪ0����4 λֵ��Ч)   //AD����Ҷ���	
		temp <<= 8;		//(0000 xxxx 0000 0000)
		temp += ADRESL;	//(0000 xxxx xxxx xxxx)��ȡ12λAD ������ֽڼĴ�����ֵ�������adc_res ��
		
		adsum+=temp;
	}

	adsum >>=3;

	ADC_EN = 0;				//�ر�ADģ�� ʡ��
	
	return(adsum);
}

/*******************************************************************
;
;������: Uart_Tx_Deal 
;
;����˵��:	UART���ͺ���----Ƕ�������ʵ��UART����ͨѶ
;
;		PA4�ӿ���S1����ѡ��UART�����ʣ�S1�Ͽ�ѡ��9600 bps��S1�պ�ѡ��19200 bps
;
;		PA5��ΪUART����ڣ�����AD���ݣ�12λAD���ת��Ϊʮ������ʽ���͵�PC��ʾ����ֵ��Χ 0 ~ 4095��
;		
;		ע�⣺PC�˴������ֽ��ջ�������ѡ��"�ı�ģʽ"
;
********************************************************************/

void Uart_Tx_Deal(void)
{
	
#asm	;//��ʼǶ����		ʹ�� PICC C������ ����ʱ����ҪǶ�� PIC ���ָ������ PICC Ƕ���� ���˵���ĵ�
	
	UART_TX_LOOP:

		;//Ƕ������룬��ע�� �õ��ı����������BANK�������´����õ��ı�������BANK0���򣬲���Ҫ�л�BANK
		

		BTFSS 	_PORTA,4			;//PA4����״̬ѡ�� UART ������ 
		GOTO	DELAY_19200BPS_LOOP
		GOTO	DELAY_9600BPS_LOOP
			
END_DELAY_19200BPS_LOOP:

END_DELAY_9600BPS_LOOP:
									
;//		BANKSEL _uart_10bit_temp		;//�л����üĴ��������BANK���򣬼Ĵ�����(���߱�����) ǰ������»��� "_"
	
		MOVF	_uart_10bit_temp,W	;//(Ŀ�ļĴ���ֻ���� w�� f ,�� 0���� 1�ᱨ��)
		BTFSS	_STATUS,2			;//Z��־
		GOTO	UART_TX_LOOP_1
	
	UART_TX_STAT_BIT:
		GOTO	$+1 				;//�ȴ�ָ��ռ�� 2��ָ������
		GOTO	$+1
		GOTO	$+1
		GOTO	$+1
		NOP
		BCF 	_PORTA,5			;//������λ "0"
		GOTO	$+1
		NOP
		GOTO	UART_TX_1BIT_END
			
	UART_TX_LOOP_1:
		MOVLW	9
		SUBWF	_uart_10bit_temp,W
		BTFSC	_STATUS,2			;//Z��־
		GOTO	UART_TX_STOP_BIT	
			
	UART_TX_8BIT_DATA:
		BTFSS	_uart_data_temp,0	;//�ȷ��͵�λ b0�����͸�λ (���� )	
		GOTO	UART_TX_DATA_BIT_0
		
	UART_TX_DATA_BIT_1:
		NOP
		BSF 	_PORTA,5			;//������λ "1"
		GOTO	UART_TX_DATA_BIT_END
		
	UART_TX_DATA_BIT_0:
		BCF 	_PORTA,5			;//������λ "0"
		GOTO	UART_TX_DATA_BIT_END
	
	
	UART_TX_DATA_BIT_END:
		RRF 	_uart_data_temp,F	;//����һλ		
		GOTO	UART_TX_1BIT_END	
	
					
	UART_TX_STOP_BIT:
		GOTO	$+1
//		NOP
		BSF 	_PORTA,5			;//��ֹͣλ "1"
		GOTO	UART_TX_1BIT_END
	
	
		
	UART_TX_1BIT_END:
		INCF	_uart_10bit_temp,F
		MOVLW	10
		SUBWF	_uart_10bit_temp,W
		BTFSS	_STATUS,2			;//Z��־
		GOTO	UART_TX_LOOP
		CLRF	_uart_10bit_temp
		GOTO	END_UART_TX

		
	DELAY_9600BPS_LOOP:		;//(0.000104s = 1/9600) UART������ 9600(104us)
		MOVLW	22
		MOVWF	_delay_ctr_1
		GOTO	$+1
//		NOP
		
	DELAY_9600BPS_LOOP_1:		;//176 = 22 * 8	
		GOTO	$+1 
		GOTO	$+1
		NOP
		DECFSZ	_delay_ctr_1,F
		GOTO	DELAY_9600BPS_LOOP_1
		GOTO	END_DELAY_9600BPS_LOOP


		
	DELAY_19200BPS_LOOP:	;//(0.000052s = 1/19200) UART������ 19200(52us)
		MOVLW	9
		MOVWF	_delay_ctr_1
		GOTO	$+1
		NOP
		
	DELAY_19200BPS_LOOP_1:		;//72 = 9 * 8
		GOTO	$+1 
		GOTO	$+1
		NOP
		DECFSZ	_delay_ctr_1,F
		GOTO	DELAY_19200BPS_LOOP_1
		GOTO	END_DELAY_19200BPS_LOOP
		
	
	END_UART_TX:
	
		
#endasm	//Ƕ���� ����

}

/*******************************************************************
;
;������: delay 
;
;����˵��:	��ʱ�ӳ���
;
********************************************************************/

void delay(unsigned char i)
{
	while(i--);
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

	CPIOA = 0b00010000;	//PA�������������		1:����		0:���
	CPIOC = 0b00000000;	//PC�������������		1:����		0:���
	
	PAPHR = 0b00010000;	//PA����������λ			1:ʹ��		0:��ֹ
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
	TCS = 0;		//TMR0ʱ��Դѡ��λ		1:PA2/T0CKI�������źŵ�����		0:�ڲ�ָ������ʱ�ӣ� Fcpu = Fosc/4��
	T0PSDIV_2();	//Timer0Ԥ��Ƶ��ѡ��1:2 	��Tiemr0������������Ϊ ����1us	(Fosc = 8MHz)  (Fcpu = Fosc/4 = 2MHz)
	
	TMR0 = 152;		//152 = 256 - 104		104us = 104 * 1us	(0.000104s = 1/9600) UART������9600(104us)
	
//	TMR0 = 204;		//204 = 256 - 52		52us = 52 * 1us	(0.000052s = 1/19200) UART������19200(52us)

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

	T1GINV = 0; //Timer1�ſط�תλ					0: Timer1�ſ�Ϊ�͵�ƽ��Ч���ſ�Ϊ�͵�ƽʱTimer1������
//	T1GINV = 1; 	//Timer1�ſط�תλ				1: Timer1�ſ�Ϊ�ߵ�ƽ��Ч���ſ�Ϊ�ߵ�ƽʱTimer1������

	TMR1GE = 0; //Timer1�ſ�ʹ��λ					0: Timer1��
//	TMR1GE = 1; 	//Timer1�ſ�ʹ��λ				1: Timer1��Timer1�ſز��ʱ��

	T1SCKSEL_FOSC();		//Fosc = 8MHz
	T1PSDIV_8();			//Timer1������������Ϊ 1us ( 1MHz = 8MHz  / 8 )

	T1SYNC = 0; 	//Timer1�ⲿʱ������ͬ������λ		0: ͬ���ⲿʱ������
//	T1SYNC = 1; 	//Timer1�ⲿʱ������ͬ������λ		1: ��ͬ���ⲿʱ������

	TMR1H = 0x3c;	//0x3cb0		(15536 = 65536 - 50000) 	(50ms = 50,000us =	50000 * 1us)
	TMR1L = 0xb0;	//Timer1 ��ʱ 50ms���
	
	TMR1IF = 0;
	TMR1ON = 1; 	//Timer1����/ֹͣλ 	1: ���� Timer1		0: ֹͣTimer1

}


/*******************************************************************
;
;������: Init_Timer2

;����˵��:	��ʼ��Timer2
;
********************************************************************/
void Init_Timer2(void)
{

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
	//TIS = 1;		//ʹ�� T0�ж�
	
	//GIE = 1;		//ʹ��  ���ж�
}

//*******************************************************************




