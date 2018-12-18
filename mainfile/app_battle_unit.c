#include<mainfile\app_battle_unit.h>
#include<mainfile\app_battle_stream.h>
#include<mainfile\app_battle_bomb.h>
#include<mainfile\app_battle_car.h>
#include<mainfile\app_battle.h>
#include<common\timeget.h>

xdata app_battle_unit_struct app_battle_unit_memory[12][8]={0};

//****************************************************  default

void app_battle_unit_default_create(unsigned char*info,unsigned char msg)
//msg:life[0,7]	info:in:placex,placey,class[0,31]
{		
	app_battle_unit_memory[info[0]][info[1]].life3Wclass5=(msg<<5)|info[2];
	app_battle_unit_handle[info[2]][app_battle_unit_event_Repaint](info,0);	
}									  	
void app_battle_unit_default_refresh(unsigned char*info,unsigned char msg)
//msg:passtime	info:in:placex,placey
{
	info=info;
	msg=msg;	
}
void app_battle_unit_default_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{			
	info=info;
	msg=msg;	
}	
void app_battle_unit_default_beattack(unsigned char*info,unsigned char msg)
//msg:bombnum	info:in:placex,placey out:能否穿越(-1:Y/-2:N)
{	 
	app_battle_unit_handle[app_battle_unit_memory[info[0]][info[1]].life3Wclass5&0x1f][app_battle_unit_event_Repaint](info,0);
	info[0]=-1;
	msg=msg;	
}
void app_battle_unit_default_bestand(unsigned char*info,unsigned char msg)
//msg:carnum	info:in:placex,placey out:能否站立(-1:Y/-2:N)
{
	info[0]=-1;	
	msg=msg;	
}
//*******************************************************  Floor
//*******************************************************  Grass
void app_battle_unit_grass_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Grass],1);
	msg=msg;	
}	
//*******************************************************  Wall	
void app_battle_unit_wall_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Wall],1);
	msg=msg;	
}			
//void delay_t(unsigned int t){while(t--);}
unsigned char dirofbomb,powerofbomb;		   	
void app_battle_unit_wall_beattack(unsigned char*info,unsigned char msg)
//msg:bombnum	info:in:placex,placey out:能否穿越(-1:Y/-2:N)
{	 			  
	app_battle_unit_handle[app_battle_unit_memory[info[0]][info[1]].life3Wclass5&0x1f]
							[app_battle_unit_event_Repaint](info,0);
	dirofbomb=app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3>>6;
	powerofbomb=(app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3>>3)&0x7;	 	
	if(powerofbomb--==0)
	{
		app_battle_bomb_default_move_arr[0]=-2;
		return;
	}
	switch(dirofbomb)
	{
	case app_battle_bomb_direction_U:
		dirofbomb=app_battle_bomb_direction_D;
		break;				 
	case app_battle_bomb_direction_D:
		dirofbomb=app_battle_bomb_direction_U;
		break;
	case app_battle_bomb_direction_L:
		dirofbomb=app_battle_bomb_direction_R;
		break;
	case app_battle_bomb_direction_R:
		dirofbomb=app_battle_bomb_direction_L;
		break;
	}
	app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3=1;
	app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3|=dirofbomb<<6;
	app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3|=powerofbomb<<3;
	app_battle_bomb_default_move_arr[0]=-1;
	msg=msg;
	//此处不知为何使用info[0]不能回馈信息到调用函数，因其调用函数只有一个，故而直接对其变量回馈
}
void app_battle_unit_wall_bestand(unsigned char*info,unsigned char msg)
//msg:carnum	info:in:placex,placey out:能否站立(-1:Y/-2:N)
{
	info[0]=-2;	
	msg=msg;	
}
//*******************************************************  Box	 
void app_battle_unit_box_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Box],1);
	msg=msg;	
}							   
void app_battle_unit_box_beattack(unsigned char*info,unsigned char msg)
//msg:bombnum	info:in:placex,placey out:能否穿越(-1:Y/-2:N)
{	 
	if((app_battle_unit_memory[info[0]][info[1]].life3Wclass5>>5)!=0)
	{
		app_battle_unit_memory[info[0]][info[1]].life3Wclass5-=0x20;
		app_battle_bomb_default_move_arr[0]=-2;
		return;
	}
	switch(time%16)
	{
	case 7:
		app_battle_unit_memory[info[0]][info[1]].life3Wclass5=app_battle_unit_class_Tool_life;
		break;	
	case 6:
		app_battle_unit_memory[info[0]][info[1]].life3Wclass5=app_battle_unit_class_Tool_power;
		break;						   
	case 5:
		app_battle_unit_memory[info[0]][info[1]].life3Wclass5=app_battle_unit_class_Tool_speed;
		break;
	default:					
		app_battle_unit_memory[info[0]][info[1]].life3Wclass5=app_battle_unit_class_Floor;
		break;
	} //*/
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[0],0);
	app_battle_unit_handle[app_battle_unit_memory[info[0]][info[1]].life3Wclass5&0x1f][app_battle_unit_event_Repaint](info,0);
	app_battle_bomb_default_move_arr[0]=-2;
	msg=msg;	
}
//*******************************************************  Bird	 
void app_battle_unit_bird_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Bird],1);
	msg=msg;	
}										
void app_battle_unit_bird_bestand(unsigned char*info,unsigned char msg)
//msg:carnum	info:in:placex,placey out:能否站立(-1:Y/-2:N)
{
	info[0]=-1;	
	winner=msg;
	msg=msg;	
}
//*******************************************************  Rattan 
void app_battle_unit_rattan_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Rattan],1);
	msg=msg;	
}	
//*******************************************************  Water   
void app_battle_unit_water_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey	重绘此unit
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Water],1);
	msg=msg;	
}	
//*******************************************************  Tool	
void app_battle_unit_tool_beattack(unsigned char*info,unsigned char msg)
//msg:bombnum	info:in:placex,placey out:能否穿越(-1:Y/-2:N)
{	 
	app_battle_unit_memory[info[0]][info[1]].life3Wclass5=app_battle_unit_class_Floor; 
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[0],0);
	app_battle_unit_handle[app_battle_unit_class_Floor][app_battle_unit_event_Repaint](info,0);
	app_battle_bomb_default_move_arr[0]=-2;
	msg=msg;	
}
//*******************************************************  Tool_life  
void app_battle_unit_tool_life_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Tool_life],1);
	msg=msg;	
}											 
void app_battle_unit_tool_life_bestand(unsigned char*info,unsigned char msg)
//msg:carnum	info:in:placex,placey out:能否站立(-1:Y/-2:N)
{												   
	app_battle_unit_memory[info[0]][info[1]].life3Wclass5=app_battle_unit_class_Floor; 
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[0],0);
	app_battle_unit_handle[app_battle_unit_class_Floor][app_battle_unit_event_Repaint](info,0);
	info[0]=app_battle_car_updata_Life;
	app_battle_car_handle[0][app_battle_car_event_Updata](info,msg);
	info[0]=-1;	
	msg=msg;	
}
//*******************************************************  Tool_power  
void app_battle_unit_tool_power_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Tool_power],1);
	msg=msg;	
}									 
void app_battle_unit_tool_power_bestand(unsigned char*info,unsigned char msg)
//msg:carnum	info:in:placex,placey out:能否站立(-1:Y/-2:N)
{												   
	app_battle_unit_memory[info[0]][info[1]].life3Wclass5=app_battle_unit_class_Floor; 
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[0],0);
	app_battle_unit_handle[app_battle_unit_class_Floor][app_battle_unit_event_Repaint](info,0);
	info[0]=app_battle_car_updata_Power;
	app_battle_car_handle[0][app_battle_car_event_Updata](info,msg);
	info[0]=-1;	
	msg=msg;	
}
//*******************************************************  Tool_speed  
void app_battle_unit_tool_speed_repaint(unsigned char*info,unsigned char msg)
//msg:0			info:in:placex,placey
{
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[app_battle_stream_picnum_Tool_speed],1);
	msg=msg;	
}		 			 
void app_battle_unit_tool_speed_bestand(unsigned char*info,unsigned char msg)
//msg:carnum	info:in:placex,placey out:能否站立(-1:Y/-2:N)
{												   
	app_battle_unit_memory[info[0]][info[1]].life3Wclass5=app_battle_unit_class_Floor; 
	app_battle_stream_pic(info[0],info[1],app_battle_stream_picture[0],0);
	app_battle_unit_handle[app_battle_unit_class_Floor][app_battle_unit_event_Repaint](info,0);
	info[0]=app_battle_car_updata_Speed;
	app_battle_car_handle[0][app_battle_car_event_Updata](info,msg);
	info[0]=-1;	
	msg=msg;	
}


				
code void (code *(app_battle_unit_handle[/*class*/][app_battle_unit_event_Quantity/*event*/]))(unsigned char*,unsigned char)=
{
	{
		app_battle_unit_default_create,
		app_battle_unit_default_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_default_beattack,
		app_battle_unit_default_bestand
	},//default
	{
		app_battle_unit_default_create,
		app_battle_unit_default_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_default_beattack,
		app_battle_unit_default_bestand
	},//floor
	{
		app_battle_unit_default_create,
		app_battle_unit_grass_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_default_beattack,
		app_battle_unit_default_bestand
	},//grass
	{
		app_battle_unit_default_create,
		app_battle_unit_wall_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_wall_beattack,
		app_battle_unit_wall_bestand
	},//wall
	{
		app_battle_unit_default_create,
		app_battle_unit_box_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_box_beattack,
		app_battle_unit_wall_bestand
	},//box
	{
		app_battle_unit_default_create,
		app_battle_unit_bird_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_default_beattack,
		app_battle_unit_bird_bestand
	},//bird
	{
		app_battle_unit_default_create,
		app_battle_unit_rattan_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_box_beattack,
		app_battle_unit_default_bestand
	},//rattan
	
	{
		app_battle_unit_default_create,
		app_battle_unit_water_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_default_beattack,
		app_battle_unit_wall_bestand
	},//water 
	{
		app_battle_unit_default_create,
		app_battle_unit_default_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_default_beattack,
		app_battle_unit_default_bestand
	},//tool
	{
		app_battle_unit_default_create,
		app_battle_unit_tool_life_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_tool_beattack,
		app_battle_unit_tool_life_bestand
	},//tool_life
	{
		app_battle_unit_default_create,
		app_battle_unit_tool_power_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_tool_beattack,
		app_battle_unit_tool_power_bestand
	},//tool_power
	{
		app_battle_unit_default_create,
		app_battle_unit_tool_speed_repaint,
		app_battle_unit_default_refresh,
		app_battle_unit_tool_beattack,
		app_battle_unit_tool_speed_bestand
	},//tool_speed	
};