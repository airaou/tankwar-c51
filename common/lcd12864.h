#ifndef __LCD12864__
#define __LCD12864__

#include<common\hard.h>
#define IO P2
sbit RS = P0^7;
sbit RW = P0^6;
sbit EN = P0^5;
sbit RST = P0^3;
sbit BUSY = P2^7;

#define LCD_BASE_MODLE write_cmd(0x30) //用于突出表示lcd进入基本指令状态
#define LCD_PLUS_MODLE write_cmd(0x36) //用于突出表示lcd进入扩充指令状态、

extern void wait_busy();
		#define __WAIT_BUSY__
extern void write_cmd(unsigned char cmd);
		#define __WRITE_CMD__
extern void write_dat (unsigned char dat);
		#define __WRITE_DAT__
extern unsigned char read_dat ();
		#define __READ_DAT__
#endif