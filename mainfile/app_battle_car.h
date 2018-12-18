#ifndef __APP_BATTLE_CAR__
#define __APP_BATTLE_CAR__

typedef struct app_battle_car_struct
{
	unsigned char	pointx,pointy,
					speed4Wmoverest4,
					power3Wfirerest5,
					life3Wdirection2;
}app_battle_car_struct;

typedef enum app_battle_car_class
{
	app_battle_car_class_Default
}app_battle_car_class;
typedef enum app_battle_car_direction
{
	app_battle_car_direction_U,
	app_battle_car_direction_L,
	app_battle_car_direction_R,
	app_battle_car_direction_D
}app_battle_car_direction;
typedef enum app_battle_car_event
{
	app_battle_car_event_Create,	//建立
	app_battle_car_event_Repaint,	//重绘
	app_battle_car_event_Refresh, 	//刷新
	app_battle_car_event_Move,		//移动
	app_battle_car_event_Fire,		//开火
	app_battle_car_event_Beattack,	//受击
	app_battle_car_event_Updata,	//升级
	app_battle_car_event_Delete		//销毁
}app_battle_car_event;
typedef enum app_battle_car_updata
{
	app_battle_car_updata_Life,
	app_battle_car_updata_Power,
	app_battle_car_updata_Speed
}app_battle_car_updata;	
#define app_battle_car_event_Quantity 8
#define app_battle_car_Quantity 8
#define app_battle_car_Fireresttime 30
#define app_battle_car_Movestep 2			

extern idata app_battle_car_struct app_battle_car_memory[app_battle_car_Quantity/*车数量*/];
extern code void (code *(app_battle_car_handle[/*class*/][app_battle_car_event_Quantity/*event*/]))(unsigned char *,unsigned char);
				  
#endif