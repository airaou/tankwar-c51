#include<common\HARD.H>  
#include<common\lcd12864_draw.h>
#include<common\timeget.h>		
#include<common\ISPdownload.h>
//初始化
void set_lcd()
{				
	RST = 1;
	RST = 0;//复位 
	RST = 0;								   
	RST = 0;
	RST = 0;
	RST = 0;
	RST = 1;
	write_cmd(0x30);	//..11 ....		设置为基本指令集动作		
	write_cmd(0x30);	//..11 ....		设置为基本指令集动作		
	write_cmd(0x08);	//.... 1...		设置显示光标闪烁全关		
	write_cmd(0x01);	//.... ...1		清屏并且DDRAM数据指针清零	
	write_cmd(0x06);	//.... .11.		进入模式设置				
	write_cmd(0x0C);	//.... 11..		开显示					
}

#include<mainfile\app_battle.h>
void main()
{
	timeget();
	ISPdownload();
	set_lcd();
	LCD_PLUS_MODLE;
	draw_allclean();
	app_battle_main();
	LCD_BASE_MODLE;
	while(1);
}