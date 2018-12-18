#include<mainfile\app_battle_ui.h>
#include<mainfile\app_battle_stream.h>
#include<mainfile\app_battle.h>

void delay(unsigned int t){while(t--);}

void app_battle_ui_modechoose(unsigned char *info,unsigned char msg)
//msg:	info:in:0	out:选择:(0:结束 1:1P重玩 2:2P重玩)
{												 
	app_battle_stream_char(0,0 ,"BATTLE ALPHA 1\0");
	app_battle_stream_char(0,9 ,"MADE BY AOU\0");
	app_battle_stream_char(0,18," P1U TO PLAY WITH 1P\0");	
	app_battle_stream_char(0,27," P1D TO PLAY WITH 2P\0");
	while(1)
	{
		switch(app_battle_stream_readkey())
		{
		case app_battle_stream_key_P1_L:
			info[0]=0;
			return;
		case app_battle_stream_key_P1_U:  
			info[0]=1;
			return;
		case app_battle_stream_key_P1_D: 
			info[0]=2;
			return;
		}
	}
	msg=msg;
}

void app_battle_ui_gameover(unsigned char *info,unsigned char msg)
//msg:winner	info:in:
{
	draw_allclean();
	switch(msg)
	{
	case 1:
		app_battle_stream_char(0,0,"P1 WIN!\0");
		break;				  
	case 2:
		app_battle_stream_char(0,0,"P2 WIN!\0");
		break;
	default:
		app_battle_stream_char(0,0,"PLAYER LOST\0");
	}									  
	app_battle_stream_char(0,9,"GAME OVER\0"); 
	app_battle_stream_char(0,18,"PRESS ANYKEY TO\0"); 
	app_battle_stream_char(0,27,"REPLAY\0"); 
	delay(60000);
	while(!app_battle_stream_readkey());
	info=info;
}