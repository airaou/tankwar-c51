#ifndef __APP_BATTLE_BOMB__
#define __APP_BATTLE_BOMB__
typedef struct app_battle_bomb_struct
{
	unsigned char	pointx,
					pointy,
					direction2Wpower3Wmoverest3;					
}app_battle_bomb_struct;
typedef enum app_battle_bomb_event
{
	app_battle_bomb_event_Create,
	app_battle_bomb_event_Delete,
	app_battle_bomb_event_Move,
	app_battle_bomb_event_Repaint,
	app_battle_bomb_event_Refresh
}app_battle_bomb_event;
typedef enum app_battle_bomb_direction
{
	app_battle_bomb_direction_U,
	app_battle_bomb_direction_L,
	app_battle_bomb_direction_R,
	app_battle_bomb_direction_D
}app_battle_bomb_direction;
typedef enum app_battle_bomb_class
{
	app_battle_bomb_class_Default	
}app_battle_bomb_class;			  
#define app_battle_bomb_event_Quantity 5
#define app_battle_bomb_Quantity 32
#define app_battle_bomb_Speed 7
#define app_battle_bomb_Movestep 2
extern unsigned char app_battle_bomb_default_move_arr[2];
extern idata app_battle_bomb_struct app_battle_bomb_memory[app_battle_bomb_Quantity];
extern code void (code *(app_battle_bomb_handle[/*class*/][app_battle_bomb_event_Quantity/*ÊÂ¼þÊý*/]))(unsigned char*,unsigned char);
#endif