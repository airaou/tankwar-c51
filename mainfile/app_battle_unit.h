#ifndef __APP_BATTLE_UNIT__
#define __APP_BATTLE_UNIT__

typedef struct app_battle_unit_struct
{
	unsigned char life3Wclass5;//������������λΪlife������λΪclass
}app_battle_unit_struct;

typedef enum app_battle_unit_class
{
	app_battle_unit_class_Default,		//0	Ĭ��
	app_battle_unit_class_Floor,		//1	��
	app_battle_unit_class_Grass,		//2	��
	app_battle_unit_class_Wall,			//3	ǽ
	app_battle_unit_class_Box,			//4	��
	app_battle_unit_class_Bird,			//5	ӥ
	app_battle_unit_class_Rattan,		//6	��
	app_battle_unit_class_Water,		//7	ˮ
	app_battle_unit_class_Tool,			//8	��
	app_battle_unit_class_Tool_life,	//9	��Ѫ
	app_battle_unit_class_Tool_power,	//a	�ӻ�
	app_battle_unit_class_Tool_speed	//b	����
}app_battle_unit_class;
typedef enum app_battle_unit_event
{
	app_battle_unit_event_Create,		//����
	app_battle_unit_event_Repaint,		//�ػ�
	app_battle_unit_event_Refresh,		//ˢ��
	app_battle_unit_event_Beattack,		//�ܻ�
	app_battle_unit_event_Bestand		//��վ
}app_battle_unit_event;
#define app_battle_unit_event_Quantity 5

extern code void (code *(app_battle_unit_handle[/*class*/][app_battle_unit_event_Quantity/*event*/]))(unsigned char *,unsigned char);
extern xdata app_battle_unit_struct app_battle_unit_memory[][8];				  
#endif