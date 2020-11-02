/***********************************************************************************
;Company : Yspring ------深圳市汇春科技股份有限公司
;File Name :10F273
;Description :  MDT10F273_AD_范例程序
;
;程序功能说明：采样PA2的电压，通过UART输出口发送到PC端显示
;
;		MCU工作电压2.2~5.5V
;
;		PA2作为AD输入检测电压，检测电压范围0 ~ 2.048V 
;
;		PA4接开关S1用于选择UART波特率，S1断开选择9600 bps，S1闭合选择19200 bps
;
;		PA5作为UART输出口，发送AD数据（12位AD结果转化为十进制形式发送到PC显示，数值范围 0 ~ 4095）
;		
;		注意：PC端串口助手接收缓冲区需选择"文本模式"
;
***********************************************************************************/

#include "mdt10F273.h"	//用“”包含的头文件，先到工程目录下查找（找不到，再到IDE安装目录去查找）
#include "273cfg.h"

//-----------------------------------数据类型重定义--------------------------------

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

//------------------------------------函数声明-------------------------------------

void Init_Timer0_WDT(void);           //初始化tmr0和WDT
void Init_Timer1(void);               //初始化timer1
void Init_Timer2(void);               //初始化timer2
void Init_GPIO(void);                 //初始化IO
void Init_INT(void);                  //初始化INT
void Init_ADC(void);                  //初始化ADC
void delay(unsigned char i);          //延时函数

void Uart_Tx_Deal(void);              //串口发送数据
u16 Get_ADC_Result(u8 CHx ,u8 REFx);  //AD采集函数

//-------------------------宏定义---------------------------------------

#define	UART_IO_OUT_L()		(PA5 = 0) //串口输出低电平
#define	UART_IO_OUT_H()		(PA5 = 1) //串口输出高电平

#define CHAR_SPACE	32	//ASII值 32， 打印 "空格"字符
#define CHAR_CR		13	//ASII值 13， 打印控制字符  "回车"
#define CHAR_LF		10	//ASII值 10， 打印控制字符  "换行"
//#define CHAR_CR		'\r'	//ASII值 13， 打印控制字符  "回车"
//#define CHAR_LF		'\n'	//ASII值 10， 打印控制字符  "换行"

const u8 table_char[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'}; 


//#define DEBUG_UART_0X55_0XAA		1	//   调试模式 定义为"1"
#define DEBUG_UART_0X55_0XAA		0	//非调试模式 定义为"0"


//-----------------------------------变量定义-------------------------------------
u8 uart_10bit_temp;	    //串口计数器
u8 uart_data_temp;      //串口数据缓存
u8 delay_ctr_1;         //

u8 i;

u16 adc_temp;           //AD临时变量

u8 adc_HH;              //AD值千位数缓存
u8 adc_HL;              //AD值百位数缓存
u8 adc_LH;              //AD值十位数缓存
u8 adc_LL;              //AD值个位数缓存
//-----------------------------------位定义---------------------------------------
bit flag_t0=0;

/*********************************************************************************
;
;函数名: main 
;
;函数说明:  主函数入口
;
*********************************************************************************/
void main(void)         
{
	CLRWDT();

	SET_HIRC(IRCF_8M);       //内部振荡器频率选择4MHz

	Init_GPIO();             //初始化IO
	Init_Timer0_WDT();       //初始化timer0和WDT
	Init_Timer1();           //初始化timer1
//	Init_Timer2();
	Init_INT();              //初始化INT
	Init_ADC();              //初始化ADC
	

//==========================================主循环
	while(1)
	{
		CLRWDT();	//清除 看门狗 
				
		if(TMR1IF == 1)
		{
			TMR1ON = 0; 	//Timer1 定时 50ms溢出
			TMR1H = 0x3c;   //加载 初始值 0x3cb0	(15536 = 65536 - 50000) 	(50ms = 50,000us =	50000 * 1us)
			TMR1L = 0xb0;	
			TMR1ON = 1;     //使能TMR1
			
			TMR1IF = 0;     //TMR1中断标志清0

			//每隔 50ms 获取一次AD值 ，通过 UART 发到 PC 上显示 (Timer0定时中断 实现 软件UART功能)
			
			adc_temp = Get_ADC_Result(ANCHSEL_AN2,VREFSEL_4096MV) - Get_ADC_Result(ANCHSEL_VSS,VREFSEL_4096MV);	//12位 AD 值 十进制 数 0 ~ 4095

			adc_HH = (adc_temp / 1000);			//千
			adc_HL = ((adc_temp % 1000) / 100);	//百
			adc_LH = ((adc_temp % 100) / 10);	//十
			adc_LL = (adc_temp % 10);			//个
			

#if	DEBUG_UART_0X55_0XAA

			uart_data_temp = 0x55;                      //十六进制 0x55 通过 UART发送到 PC，串口助手选择"HEX模式"接收显示
			Uart_Tx_Deal();                             //发送数据
			
			uart_data_temp = 0xaa;                      //十六进制 0xaa 通过 UART发送到 PC，串口助手选择"HEX模式"接收显示
			Uart_Tx_Deal();                             //发送数据
			
#else

			if(adc_temp >= 1000)                        //取千位数
				uart_data_temp = table_char[adc_HH];	//AD结果转化为十进制结果，通过UART发送到 PC，串口助手选择"文本模式"接收显示
			else
				uart_data_temp = CHAR_SPACE;            //打印 "空格"
			Uart_Tx_Deal();                             //发送数据

			
			if(adc_temp >= 100)                         //取百位数
				uart_data_temp = table_char[adc_HL];
			else
				uart_data_temp = CHAR_SPACE;
			Uart_Tx_Deal();                             //发送数据
			
			if(adc_temp >= 10)                          //取十位数
				uart_data_temp = table_char[adc_LH];
			else
				uart_data_temp = CHAR_SPACE;
			Uart_Tx_Deal();                             //发送数据
			
			uart_data_temp = table_char[adc_LL];        //取个位数 
			Uart_Tx_Deal();                             //发送数据
			
			uart_data_temp = CHAR_CR;	//"回车"	
			Uart_Tx_Deal();                             //发送数据
			
			uart_data_temp = CHAR_LF;	//"换行"	___串口助手选择"文本模式"接收显示才能换行，选择"HEX模式"不会换行
			Uart_Tx_Deal();                             //发送数据

	
#endif
		}	
	}
}
/*******************************************************************
;
;函数名: Init_ADC

;函数说明:	初始化AD
;
********************************************************************/
void Init_ADC(void)
{
	ADCHSET_PA2AN2();	//AD通道设置

	ADFM = 1;			//AD结果 右对齐，高位补零
	ADSCKDIV_16();		//AD时钟预分频选择
	ADSTASEL_BUZY();	//AD启动转换模式选择


	//注意: 上电初始化 或者睡眠唤醒后，需关闭AD模块 再 启动 ，防止某些特殊应用导致AD模块异常
	ADC_EN = 0;			//关闭 AD模块
}
/**************************************************************************************************
;函数名: Get_ADC_Result
;
;函数说明: 获取AD采样结果，12位AD结果(0~4095)
;				
;入口参数:  选择通道 CHx ,选择参考电压 REFx
;
;返回值: 	adc_res
;
***************************************************************************************************/
u16 Get_ADC_Result(u8 CHx ,u8 REFx)
{
	u8 i = 0;
	u16 temp =0,adsum=0;

	ADS0 = 0;
	
	ADS0 = ADS0 | CHx | REFx;	//模拟通道选择

	ADC_EN = 1;			//启动 AD模块 	
	
	delay(50);			//延时200us		//改变参考电压或者 启动AD模块  需延时200us以上

	adsum =0;	
	
	for(i=0;i<8;i++)
	{
		BUSY = 1;			//启动AD 开始转换
		while(BUSY);		//等待AD 转换完成  
		temp = ADRESH;	//(0000 xxxx)读取12位AD 结果高字节寄存器(高4位为0，低4 位值有效)   //AD结果右对齐	
		temp <<= 8;		//(0000 xxxx 0000 0000)
		temp += ADRESL;	//(0000 xxxx xxxx xxxx)读取12位AD 结果低字节寄存器的值，存放在adc_res 中
		
		adsum+=temp;
	}

	adsum >>=3;

	ADC_EN = 0;				//关闭AD模块 省电
	
	return(adsum);
}

/*******************************************************************
;
;函数名: Uart_Tx_Deal 
;
;函数说明:	UART发送函数----嵌入汇编代码实现UART串口通讯
;
;		PA4接开关S1用于选择UART波特率，S1断开选择9600 bps，S1闭合选择19200 bps
;
;		PA5作为UART输出口，发送AD数据（12位AD结果转化为十进制形式发送到PC显示，数值范围 0 ~ 4095）
;		
;		注意：PC端串口助手接收缓冲区需选择"文本模式"
;
********************************************************************/

void Uart_Tx_Deal(void)
{
	
#asm	;//开始嵌入汇编		使用 PICC C编译器 编译时，需要嵌入 PIC 汇编指令，请参照 PICC 嵌入汇编 相关说明文档
	
	UART_TX_LOOP:

		;//嵌入汇编代码，需注意 用到的变量所定义的BANK区域，以下代码用到的变量都在BANK0区域，不需要切换BANK
		

		BTFSS 	_PORTA,4			;//PA4输入状态选择 UART 波特率 
		GOTO	DELAY_19200BPS_LOOP
		GOTO	DELAY_9600BPS_LOOP
			
END_DELAY_19200BPS_LOOP:

END_DELAY_9600BPS_LOOP:
									
;//		BANKSEL _uart_10bit_temp		;//切换到该寄存器定义的BANK区域，寄存器名(或者变量名) 前面需加下划线 "_"
	
		MOVF	_uart_10bit_temp,W	;//(目的寄存器只能用 w或 f ,用 0或者 1会报错)
		BTFSS	_STATUS,2			;//Z标志
		GOTO	UART_TX_LOOP_1
	
	UART_TX_STAT_BIT:
		GOTO	$+1 				;//等待指令占用 2个指令周期
		GOTO	$+1
		GOTO	$+1
		GOTO	$+1
		NOP
		BCF 	_PORTA,5			;//发启动位 "0"
		GOTO	$+1
		NOP
		GOTO	UART_TX_1BIT_END
			
	UART_TX_LOOP_1:
		MOVLW	9
		SUBWF	_uart_10bit_temp,W
		BTFSC	_STATUS,2			;//Z标志
		GOTO	UART_TX_STOP_BIT	
			
	UART_TX_8BIT_DATA:
		BTFSS	_uart_data_temp,0	;//先发送低位 b0，后发送高位 (右移 )	
		GOTO	UART_TX_DATA_BIT_0
		
	UART_TX_DATA_BIT_1:
		NOP
		BSF 	_PORTA,5			;//发数据位 "1"
		GOTO	UART_TX_DATA_BIT_END
		
	UART_TX_DATA_BIT_0:
		BCF 	_PORTA,5			;//发数据位 "0"
		GOTO	UART_TX_DATA_BIT_END
	
	
	UART_TX_DATA_BIT_END:
		RRF 	_uart_data_temp,F	;//右移一位		
		GOTO	UART_TX_1BIT_END	
	
					
	UART_TX_STOP_BIT:
		GOTO	$+1
//		NOP
		BSF 	_PORTA,5			;//发停止位 "1"
		GOTO	UART_TX_1BIT_END
	
	
		
	UART_TX_1BIT_END:
		INCF	_uart_10bit_temp,F
		MOVLW	10
		SUBWF	_uart_10bit_temp,W
		BTFSS	_STATUS,2			;//Z标志
		GOTO	UART_TX_LOOP
		CLRF	_uart_10bit_temp
		GOTO	END_UART_TX

		
	DELAY_9600BPS_LOOP:		;//(0.000104s = 1/9600) UART波特率 9600(104us)
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


		
	DELAY_19200BPS_LOOP:	;//(0.000052s = 1/19200) UART波特率 19200(52us)
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
	
		
#endasm	//嵌入汇编 结束

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
//void ISR(void) __interrupt 		//YSDCC 编译 中断函数定义
void interrupt ISR(void)		//PICC 编译 中断函数定义
{
	if(TIF == 1)
	{
		TIF = 0;		//T0 带自动重载功能 不需要重置初始值

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

	CPIOA = 0b00010000;	//PA口输入输出控制		1:输入		0:输出
	CPIOC = 0b00000000;	//PC口输入输出控制		1:输入		0:输出
	
	PAPHR = 0b00010000;	//PA弱上拉控制位			1:使能		0:禁止
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
	TCS = 0;		//TMR0时钟源选择位		1:PA2/T0CKI引脚上信号的跳变		0:内部指令周期时钟（ Fcpu = Fosc/4）
	T0PSDIV_2();	//Timer0预分频比选择1:2 	，Tiemr0单步计数周期为 单步1us	(Fosc = 8MHz)  (Fcpu = Fosc/4 = 2MHz)
	
	TMR0 = 152;		//152 = 256 - 104		104us = 104 * 1us	(0.000104s = 1/9600) UART波特率9600(104us)
	
//	TMR0 = 204;		//204 = 256 - 52		52us = 52 * 1us	(0.000052s = 1/19200) UART波特率19200(52us)

	TMR0EN = 1;		//Tiemr0 启动/停止位	1:启动Timer0		0:停止Timer0
	
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

	T1GINV = 0; //Timer1门控翻转位					0: Timer1门控为低电平有效（门控为低电平时Timer1计数）
//	T1GINV = 1; 	//Timer1门控翻转位				1: Timer1门控为高电平有效（门控为高电平时Timer1计数）

	TMR1GE = 0; //Timer1门控使能位					0: Timer1打开
//	TMR1GE = 1; 	//Timer1门控使能位				1: Timer1在Timer1门控不活动时打开

	T1SCKSEL_FOSC();		//Fosc = 8MHz
	T1PSDIV_8();			//Timer1单步计数周期为 1us ( 1MHz = 8MHz  / 8 )

	T1SYNC = 0; 	//Timer1外部时钟输入同步控制位		0: 同步外部时钟输入
//	T1SYNC = 1; 	//Timer1外部时钟输入同步控制位		1: 不同步外部时钟输入

	TMR1H = 0x3c;	//0x3cb0		(15536 = 65536 - 50000) 	(50ms = 50,000us =	50000 * 1us)
	TMR1L = 0xb0;	//Timer1 定时 50ms溢出
	
	TMR1IF = 0;
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
	
	TIF = 0;
	//TIS = 1;		//使能 T0中断
	
	//GIE = 1;		//使能  总中断
}

//*******************************************************************




