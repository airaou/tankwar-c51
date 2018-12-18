#ifndef __APP_BATTLE__
#define __APP_BATTLE__
typedef enum app_battle_state
{
	app_battle_state_Over,
	app_battle_state_1P,
	app_battle_state_2P
}app_battle_state;
extern unsigned char winner;
extern unsigned int historytime_0;
extern unsigned int historytime_1; 
extern int app_battle_main();
#endif