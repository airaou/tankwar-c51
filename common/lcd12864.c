#include "HARD.H"
#include "lcd12864.h"

//µ»√¶
#ifdef __WAIT_BUSY__
void wait_busy(void)
{
	EN=0;
	IO=0xFF;
	RS=0;RW=1;EN=1;EN=1;
	while(BUSY);LED1=0;LED1=1;
	EN=0;
}
#endif

#ifdef __WRITE_CMD__
void write_cmd(unsigned char cmd)
{
	wait_busy();
	IO=cmd;
	RS=0;RW=0;
	EN=1;EN=1;EN=1;
	EN=0;
}
#endif
 
#ifdef __WRITE_DAT__
void write_dat (unsigned char dat)
{
	wait_busy();
	IO=dat;		
	RS=1;RW=0;	
	EN=1;EN=1;EN=1;
	EN=0;
}
#endif
	
#ifdef __READ_DAT__
unsigned char read_dat (void)
{
	data unsigned char out;
	wait_busy ();
	IO=0xFF;
	RS=1;RW=1;
	EN=1;EN=1;EN=1;
	out=IO;
	EN=0;
	return out;
}
#endif