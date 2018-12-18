#ifndef __APP_BATTLE_STREAM__
#define __APP_BATTLE_STREAM__	
#include<common\lcd12864_draw.h>
typedef enum app_battle_stream_key
{
	app_battle_stream_key_None,
	app_battle_stream_key_P1_U,
	app_battle_stream_key_P1_L,
	app_battle_stream_key_P1_R,
	app_battle_stream_key_P1_D,
	app_battle_stream_key_P1_Fire,
	app_battle_stream_key_P2_U,
	app_battle_stream_key_P2_L,
	app_battle_stream_key_P2_R,
	app_battle_stream_key_P2_D,
	app_battle_stream_key_P2_Fire
}app_battle_stream_key;		
typedef enum app_battle_stream_picnum
{
	app_battle_stream_picnum_None,
	app_battle_stream_picnum_Tank1_U, 
	app_battle_stream_picnum_Tank1_L,
	app_battle_stream_picnum_Tank1_R,
	app_battle_stream_picnum_Tank1_D,
	app_battle_stream_picnum_Tank2_U,	 
	app_battle_stream_picnum_Tank2_L,
	app_battle_stream_picnum_Tank2_R,
	app_battle_stream_picnum_Tank2_D, 
	app_battle_stream_picnum_Wall,
	app_battle_stream_picnum_Box,
	app_battle_stream_picnum_Water,
	app_battle_stream_picnum_Grass,
	app_battle_stream_picnum_Rattan,
	app_battle_stream_picnum_Bird,
	app_battle_stream_picnum_Tool_life,
	app_battle_stream_picnum_Tool_power,
	app_battle_stream_picnum_Tool_speed,
	app_battle_stream_picnum_bomb	 
}app_battle_stream_picnum;

//app_battle_stream_pic »æÖÆÌùÍ¼	
		#define app_battle_stream_pic(x,y,picnum,transparent) draw_flashpic((x)*8,(y)*8,(picnum),(transparent))	 
//app_battle_stream_picture	ÌùÍ¼´¢´æ
		extern code unsigned char app_battle_stream_picture[17][8];			
//app_battle_stream_readkey ¶ÁÈ¡¼üÅÌ
		extern app_battle_stream_key app_battle_stream_readkey();
//app_battle_stream_word	Êä³ö×ÖÄ¸
		extern void app_battle_stream_char(unsigned char x,unsigned char y,unsigned char *word);
#endif