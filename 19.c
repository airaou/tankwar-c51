#include<common\HARD.H>  
#include<common\lcd12864_draw.h>
#include<common\timeget.h>		
#include<common\ISPdownload.h>
//��ʼ��
void set_lcd()
{				
	RST = 1;
	RST = 0;//��λ 
	RST = 0;								   
	RST = 0;
	RST = 0;
	RST = 0;
	RST = 1;
	write_cmd(0x30);	//..11 ....		����Ϊ����ָ�����		
	write_cmd(0x30);	//..11 ....		����Ϊ����ָ�����		
	write_cmd(0x08);	//.... 1...		������ʾ�����˸ȫ��		
	write_cmd(0x01);	//.... ...1		��������DDRAM����ָ������	
	write_cmd(0x06);	//.... .11.		����ģʽ����				
	write_cmd(0x0C);	//.... 11..		����ʾ					
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