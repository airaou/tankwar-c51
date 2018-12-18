#ifndef __ISPDOWNLOAD__
#define __ISPDOWNLOAD__
sfr IAP_CONTR=0xE7;
void ISPdownload(void)
{
	TMOD = 0x20;
	SM0=0;
	SM1=1;
	REN=1;
	TH1 = 0xFd;
	TL1 = 0xFd;
	TR1 = 1;
	EA=1;
	ES=1;
}
void UART_Interrupt_Receive (void) interrupt 4
{
	if(RI==1)
	{
		RI=0;
		IAP_CONTR = 0x60;
	}
	else TI=0;
}
#endif