#ifndef __APP_BATTLE_UNIT__
#define __APP_BATTLE_UNIT__

typedef struct app_battle_unit_struct
{
	unsigned char life3Wclass5;//共用数，高三位为life，低五位为class
}app_battle_unit_struct;

typedef enum app_battle_unit_class
{
	app_battle_unit_class_Default,		//0	默认
	app_battle_unit_class_Floor,		//1	地
	app_battle_unit_class_Grass,		//2	草
	app_battle_unit_class_Wall,			//3	墙
	app_battle_unit_class_Box,			//4	箱
	app_battle_unit_class_Bird,			//5	鹰
	app_battle_unit_class_Rattan,		//6	藤
	app_battle_unit_class_Water,		//7	水
	app_battle_unit_class_Tool,			//8	具
	app_battle_unit_class_Tool_life,	//9	加血
	app_battle_unit_class_Tool_power,	//a	加火
	app_battle_unit_class_Tool_speed	//b	加速
}app_battle_unit_class;
typedef enum app_battle_unit_event
{
	app_battle_unit_event_Create,		//创建
	app_battle_unit_event_Repaint,		//重绘
	app_battle_unit_event_Refresh,		//刷新
	app_battle_unit_event_Beattack,		//受击
	app_battle_unit_event_Bestand		//受站
}app_battle_unit_event;
#define app_battle_unit_event_Quantity 5

extern code void (code *(app_battle_unit_handle[/*class*/][app_battle_unit_event_Quantity/*event*/]))(unsigned char *,unsigned char);
extern xdata app_battle_unit_struct app_battle_unit_memory[][8];				  
#endif