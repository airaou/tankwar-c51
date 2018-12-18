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

̹�˴�ս battle	alpha 1 for STC89C52RC by aou 

������¼��
16��5��2��00:02 alpha 1 ���

ȫƷ4��25����ʼ��˼��4��29����ʼ��д
29����12KB��30����18KB��1����15KB
��ʹ���˺���ָ�������ں������ӵ��ã���keilĬ�ϻ����䲻ֱ�ӵ��õĺ�����������ռ�
�ʲ��ֺ��������ı���Ϊȫ�ֱ������ұ���ᾯ�溯��Ƕ��
����������������������
������Ϸģʽ 1P����ģʽ 2P����ģʽ
δ�������ai��ʵ�ָ�����Ϸģʽ��ð�ջ򴳹�

��ֲ������
״̬��ʾLED��P1(��hard.h�ļ�) 
	LED0��ʾlcdæ��
	LED1~7��ʾ������æ��
	Խæ�������LED�ı��Խ��
	��æ��������LED1
���̽ӿ�ΪP32~P36��P00��P01(��app_battle_stream_readkey����)
	P35Ϊ��P34Ϊ�ϣ�P33Ϊ�£�P32Ϊ�ң�P36Ϊ����
	P00Ϊ���1
	P01Ϊ���2
	��ɨ�跽ʽ���app_battle_stream_readkey����
lcd�ӿڼ�lcd12864.h�ļ�
	#define IO P2
	sbit RS = P0^7;
	sbit RW = P0^6;
	sbit EN = P0^5;
	sbit RST = P0^3;
	sbit BUSY = P2^7;
��ֲʱ����ʵ������ı�ӿ�

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
		if(historytime_1-historytime_0)//ˢ��
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

