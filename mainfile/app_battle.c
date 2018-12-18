#include<common\HARD.H>
#include<common\timeget.h>
#include<common\lcd12864_draw.h>
#include<mainfile\app_battle.h>
#include<mainfile\app_battle_car.h>
#include<mainfile\app_battle_stream.h>
#include<mainfile\app_battle_bomb.h>
#include<mainfile\app_battle_map.h>
#include<mainfile\app_battle_ui.h>

/*

坦克大战 battle	alpha 1 for STC89C52RC by aou 

开发记录：
16年5月2日00:02 alpha 1 完成

全品4月25日起始构思，4月29日起始编写
29日码12KB，30日码18KB，1日码15KB
因使用了函数指针数组在函数间间接调用，且keil默认会令互相间不直接调用的函数共享变量空间
故部分函数声明的变量为全局变量，且编译会警告函数嵌套
更多特性请自行下载游玩
现有游戏模式 1P调试模式 2P夺塔模式
未来会加入ai以实现更多游戏模式如冒险或闯关

移植帮助：
状态提示LED接P1(见hard.h文件) 
	LED0表示lcd忙绿
	LED1~7表示处理器忙绿
	越忙，亮起的LED的编号越大
	不忙，则亮起LED1
键盘接口为P32~P36和P00和P01(见app_battle_stream_readkey函数)
	P35为左，P34为上，P33为下，P32为右，P36为发射
	P00为玩家1
	P01为玩家2
	其扫描方式详见app_battle_stream_readkey函数
lcd接口见lcd12864.h文件
	#define IO P2
	sbit RS = P0^7;
	sbit RW = P0^6;
	sbit EN = P0^5;
	sbit RST = P0^3;
	sbit BUSY = P2^7;
移植时根据实际情况改变接口

*/

unsigned char winner=0;
unsigned int historytime_0,historytime_1;
						
void app_battle_main_play()
{							
	
	unsigned char temp_arr[2],temp_a,n;
	while(!winner)
	{
		historytime_0=historytime_1;
		historytime_1=time;
		switch(app_battle_stream_readkey())
		{
		case app_battle_stream_key_P1_U:
			temp_arr[0]=app_battle_car_direction_U;
			goto app_battle_page1;
		case app_battle_stream_key_P1_D:
			temp_arr[0]=app_battle_car_direction_D;
			goto app_battle_page1;
		case app_battle_stream_key_P1_L:
			temp_arr[0]=app_battle_car_direction_L;
			goto app_battle_page1;
		case app_battle_stream_key_P1_R:
			temp_arr[0]=app_battle_car_direction_R;
			goto app_battle_page1;
		app_battle_page1:
			app_battle_car_handle[0][app_battle_car_event_Move](temp_arr,1);
			break;		   
		case app_battle_stream_key_P2_U:
			temp_arr[0]=app_battle_car_direction_U;
			goto app_battle_page2;
		case app_battle_stream_key_P2_D:
			temp_arr[0]=app_battle_car_direction_D;
			goto app_battle_page2;
		case app_battle_stream_key_P2_L:
			temp_arr[0]=app_battle_car_direction_L;
			goto app_battle_page2;
		case app_battle_stream_key_P2_R:
			temp_arr[0]=app_battle_car_direction_R;
			goto app_battle_page2;
		app_battle_page2:
			app_battle_car_handle[0][app_battle_car_event_Move](temp_arr,2);
			break;
		case app_battle_stream_key_P1_Fire:
			app_battle_car_handle[0][app_battle_car_event_Fire](0,1);
			break;				
		case app_battle_stream_key_P2_Fire:
			app_battle_car_handle[0][app_battle_car_event_Fire](0,2);
			break;
		default:
			break;
		}

	
		P1=~(2<<(historytime_1-historytime_0));
		if(historytime_1-historytime_0)//刷新
		{						
			temp_a=historytime_1-historytime_0;
			for(n=0;n<app_battle_car_Quantity;n++)
			{
				app_battle_car_handle[0][app_battle_car_event_Refresh](&temp_a,n);
			}
			for(n=0;n<app_battle_bomb_Quantity;n++)
			{
			 	app_battle_bomb_handle[0][app_battle_bomb_event_Refresh](&temp_a,n);
				app_battle_bomb_handle[0][app_battle_bomb_event_Move](0,n);
			}
		}
	}
}

int app_battle_main()
{
	unsigned char state=app_battle_state_1P;
	while(state)
	{			
		draw_allclean();
		app_battle_ui_modechoose(&state,0);
		winner=0;	 
		draw_allclean();
		switch(state)
		{					  
		unsigned char temp_arr[5];
		case app_battle_state_1P:
			app_battle_map_create(0);				
			temp_arr[0]=3;
			temp_arr[1]=5;
			temp_arr[2]=7;
			temp_arr[3]=1;
			temp_arr[4]=3;
			app_battle_car_handle[0][app_battle_car_event_Create](temp_arr,1);	 			
			break;
		case app_battle_state_2P:	
			app_battle_map_create(1);	
			temp_arr[0]=1;
			temp_arr[1]=1;
			temp_arr[2]=7;
			temp_arr[3]=1;
			temp_arr[4]=3;
			app_battle_car_handle[0][app_battle_car_event_Create](temp_arr,1);
			temp_arr[0]=10;
			temp_arr[1]=6;							 
			app_battle_car_handle[0][app_battle_car_event_Create](temp_arr,2);
			break;
		case app_battle_state_Over:
			return 0;
			break;
		default:  				  
			app_battle_map_create(0);	
			temp_arr[0]=3;
			temp_arr[1]=5;
			temp_arr[2]=7;
			temp_arr[3]=1;
			temp_arr[4]=3;
			app_battle_car_handle[0][app_battle_car_event_Create](temp_arr,1);
			break;
		}
		app_battle_main_play();
		app_battle_car_handle[0][app_battle_car_event_Delete](0,1);
		app_battle_car_handle[0][app_battle_car_event_Delete](0,2);
		app_battle_ui_gameover(0,winner);
	}
	return 0;
}

