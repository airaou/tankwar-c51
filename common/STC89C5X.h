/*-------------------------------------------------------------------------- 
STC89C5X.H 
 
Header file for SST89E564RD/SST89V564RD/SST89E554RC/SST89V554RC microcontroller. 
Copyright (c) 1990-2003 SuZhou Splendid Success Industry Controlling Co.Ltd. 
All rights reserved. 
--------------------------------------------------------------------------*/ 
#ifndef __STC89C52X__
#define __STC89C52X__ 
 
/*Byte Registers*/ 
sfr P0		=0X80; 
sfr P1		=0X90; 
sfr P2		=0XA0; 
sfr P3		=0XB0; 
sfr P4		=0xE8; 
sfr PSW		=0XD0; 
sfr ACC		=0XE0; 
sfr B			=0XF0; 
sfr SP		=0X81; 
sfr DPL		=0X82; 
sfr DPH		=0X83; 
sfr PCON	=0X87; 
sfr TCON	=0X88; 
sfr TMOD	=0X89; 
sfr TL0		=0X8A; 
sfr TL1		=0X8B; 
sfr TH0		=0X8C; 
sfr TH1		=0X8D; 
sfr IE		=0XA8; 
sfr IP		=0XB8; 
sfr SCON	=0X98; 
sfr SBUF  = 0x99; 
 
sfr XICON=0XC0; 
 
/*8052 Extension*/ 
sfr T2CON	=0XC8; 
sfr RCAP2L	=0XCA; 
sfr RCAP2H	=0XCB; 
sfr TL2		=0XCC; 
sfr TH2		=0XCD; 
 
 
/*SST89C54/58 addedSFRS defined here*/ 
sfr T2MOD	=0XC9; 
sfr IEA		=0XE8; 
 
sfr AUXR	=0X8E; 
sfr AUXR1	=0XA2; 
 
sfr WDT_CONTR=0XE1; 
 
sfr SFCF	=0XB1; 
sfr SFCM	=0XB2; 
sfr SFAL	=0XB3; 
sfr SFAH	=0XB4; 
sfr SFDT	=0XB5; 
sfr SFST	=0XB6; 
 
sfr IPH		=0XB7; 
sfr IPA		=0XF8; 
sfr IPAH	=0XF7; 
 
 
sfr SADDR	=0XA9; 
sfr SADEN	=0XB9; 
sfr SPCR	=0XD5; 
sfr SPSR	=0XAA; 
sfr SPDR	=0X86; 
 
sfr CH		=0XF9; 
sfr CL		=0XE9; 
sfr CCON	=0XD8; 
sfr CMOD	=0XD9; 
 
sfr CCAP0H	=0XFA; 
sfr CCAP0L	=0XEA; 
sfr CCAP1H	=0XFB; 
sfr CCAP1L	=0XEB; 
sfr CCAP2H	=0XFC; 
sfr CCAP2L	=0XEC; 
sfr CCAP3H	=0XFD; 
sfr CCAP3L	=0XED; 
sfr CCAP4H	=0XFE; 
sfr CCAP4L	=0XEE; 
 
sfr CCAPM0	=0XDA; 
sfr CCAPM1	=0XDB; 
sfr CCAPM2	=0XDC; 
sfr CCAPM3	=0XDD; 
sfr CCAPM4	=0XDE; 
 
/*IAP*/ 
sfr ISP_DATA	=	0xe2; 
sfr ISP_ADDRH	=	0xe3;   
sfr ISP_ADDRL	=   0xe4;   
sfr ISP_CMD		=   0xe5; 
sfr ISP_TRIG		=   0xe6;    
sfr ISP_CONTR     =   0xe7;  
 
 
/*BIT Register*/ 
 
/*	PSW	*/ 
sbit CY	=PSW^7; 
sbit AC	=PSW^6; 
sbit F0	=PSW^5; 
sbit RS1=PSW^4; 
sbit RS0=PSW^3; 
sbit OV	=PSW^2; 
sbit F1	=PSW^1; 
sbit P	=PSW^0; 
 
/*	TCON	*/       //控制寄存器 
sbit TF1=TCON^7;    //定时器1溢出标志 
sbit TR1=TCON^6;   //定时器1运行控制位 
sbit TF0=TCON^5;   //定时器0溢出标志 
sbit TR0=TCON^4;   //定时器0运行控制位 
sbit IE1=TCON^3;   //外部沿促发中断1请求标邋志(硬件) 
sbit IT1=TCON^2;   //外部中断1类型控制位(软件)1下降沿 
sbit IE0=TCON^1;   //外部沿促发中断0请求标邋志 
sbit IT0=TCON^0;   //外部中断0类型控制位 
 
/*	IE	*/ 
sbit EA =IE^7;//总允许位 
sbit ES	=IE^4;//串行口中断允许位 
sbit ET1=IE^3;//定时器1中断允许位 
sbit EX1=IE^2;//外部中断1允许位 
sbit ET0=IE^1;//定时器0中断允许位 
sbit EX0=IE^0;//外部终端0允许位 
 
/*	XICON	*/ 
sbit IE2=XICON^1; 
sbit EX2=XICON^2; 
 
/*  IP  */ 
sbit PS  =IP^4;//串行口中断优先级设定位 
sbit PT1 =IP^3;//定时器中断优先级设定位 
sbit PX1 =IP^2;//外部中断1优先级设定位 
sbit PT0 =IP^1;//定时器0中断优先级设定位 
sbit PX0 =IP^0;//外部中断0优先级设定位 
 
/*  P3  */ 
sbit RD    =P3^7; 
sbit WR    =P3^6; 
sbit T1    =P3^5; 
sbit T0    =P3^4; 
sbit INT1  =P3^3; 
sbit INT0  =P3^2; 
sbit TXD   =P3^1; 
sbit RXD   =P3^0; 
 
/*  SCON  */       //串行口控制寄存器 
sbit SM0 =SCON^7;//串行口操作模式选择位 
sbit SM1 =SCON^6;// 
sbit SM2 =SCON^5;// 
sbit REN =SCON^4;//允许接受位 
sbit TB8 =SCON^3;//发送数据位 
sbit RB8 =SCON^2;//接收数据位 
sbit TI  =SCON^1;//发送终端标志 
sbit RI  =SCON^0;//接受中断标志 
 
 
/*8052 Extension*/ 
/* IE */ 
sbit ET2 =IE^5; 
 
/* IP */ 
sbit PT2 =IP^5; 
 
/* P1 */ 
sbit T2EX =P1^1;  
sbit T2   =P1^0;  
 
/* T2CON */ 
sbit TF2    =T2CON^7; 
sbit EXF2   =T2CON^6; 
sbit RCLK   =T2CON^5; 
sbit TCLK   =T2CON^4; 
sbit EXEN2  =T2CON^3; 
sbit TR2    =T2CON^2; 
sbit C_T2   =T2CON^1; 
sbit CP_RL2 =T2CON^0; 
 
/*SST89C54/58 addedSFRS defined here*/ 
/* IE */ 
sbit EC =IE^6; 
 
/* IP */ 
sbit PPC =IP^6; 
 
/*	IPA	*/ 
sbit PBO =IPA^3; 
 
/* IEA	*/ 
sbit EBO =IEA^3; 
 
/* CCON */ 
sbit CF    	=CCON^7; 
sbit CR    	=CCON^6; 
sbit CCF4  	=CCON^4; 
sbit CCF3  	=CCON^3; 
sbit CCF2  	=CCON^2; 
sbit CCF1  	=CCON^1; 
sbit CCF0  	=CCON^0; 
 
/* WDT_CONTR */ 
/*sbit EN_WDT 	=WDT_CONTR^5; 
sbit CLR_WDT =WDT_CONTR^4; 
sbit IDLE_WDT =WDT_CONTR^3; 
sbit PS2  	=WDT_CONTR^2; 
sbit PS1  	=WDT_CONTR^1; 
sbit PS0  	=WDT_CONTR^0;*/
#endif