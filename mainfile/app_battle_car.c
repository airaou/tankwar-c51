#include<mainfile\app_battle_car.h>
#include<mainfile\app_battle_stream.h>
#include<mainfile\app_battle_unit.h>
#include<mainfile\app_battle_bomb.h>
#include<mainfile\app_battle.h>
#include<common\hard.h>

idata app_battle_car_struct app_battle_car_memory[app_battle_car_Quantity/*车数量*/]={0};

void app_battle_car_default_create(unsigned char *info,unsigned char msg)
//msg:carnum	info:in:placex,placey,speed,power,life
{
	app_battle_car_memory[msg].pointx=info[0]*=8;
	app_battle_car_memory[msg].pointy=info[1]*=8;
	app_battle_car_memory[msg].speed4Wmoverest4=info[2]<<4;
	app_battle_car_memory[msg].power3Wfirerest5=info[3]<<5;	
	app_battle_car_memory[msg].life3Wdirection2=(info[4]<<2)|app_battle_car_direction_D;
	app_battle_car_handle[0][app_battle_car_event_Repaint](info,0);
}				  					 
void app_battle_car_default_repaint(unsigned char *info,unsigned char msg)
//msg:0	info:in:pointx,pointy	若此位置有car则重绘之
{
	unsigned char n;
	app_battle_car_struct *car_p=app_battle_car_memory;
	for(n=0;n<app_battle_car_Quantity;n++,car_p++)
	{
		if(car_p->speed4Wmoverest4!=0)
		if((info[0]-car_p->pointx)<8)
		if((info[1]-car_p->pointy)<8)
		{
			draw_flashpic(	car_p->pointx,car_p->pointy,
							app_battle_stream_picture
							[
								((((car_p->life3Wdirection2>>2)&0x7)>3)?app_battle_stream_picnum_Tank2_U:app_battle_stream_picnum_Tank1_U)+
								(car_p->life3Wdirection2&0x03)   
							],1);
		}
	}		  
	msg=msg;
}				
void app_battle_car_default_refresh(unsigned char *info,unsigned char msg)
//msg:carnum	info:in:passtime
{				
	info[0]=historytime_1-historytime_0;
	if(app_battle_car_memory[msg].speed4Wmoverest4)
		if((app_battle_car_memory[msg].speed4Wmoverest4&0xf)<=info[0])
		{
			app_battle_car_memory[msg].speed4Wmoverest4&=0xf0;
		}
		else
		{
			app_battle_car_memory[msg].speed4Wmoverest4-=info[0];
		}
	if(app_battle_car_memory[msg].power3Wfirerest5)
		if((app_battle_car_memory[msg].power3Wfirerest5&0x1f)<=info[0])
		{
			app_battle_car_memory[msg].power3Wfirerest5&=0xe0;
		}
		else
		{
			app_battle_car_memory[msg].power3Wfirerest5-=info[0];
		}
}			


/*
	此函数与此文件他函数共用其内所声明的变量
	且此函数会调用此文件他函数
	因而为避数据丢失，此函数内不应声明变量
*/
unsigned char	default_move_n,
				temp_speed,
				temp_direction,
				temp_carnum;	   
app_battle_car_struct *default_move_car_p;
unsigned char temp_arr[2];
void app_battle_car_default_move(unsigned char *info,unsigned char msg)
//msg:carnum	info:in:direction,0
{ 						
	temp_direction=info[0];
	temp_carnum=msg;
	default_move_n=0;
	default_move_car_p=app_battle_car_memory+msg;//保存信息防止覆盖
	if(default_move_car_p->speed4Wmoverest4==0)return;
	if((default_move_car_p->speed4Wmoverest4&0xf)!=0)return;//不满足则不移动
	default_move_car_p->speed4Wmoverest4|=default_move_car_p->speed4Wmoverest4>>4;
	
	draw_flashpic(default_move_car_p->pointx,
		default_move_car_p->pointy,
		app_battle_stream_picture[app_battle_stream_picnum_None],
		0);//清除贴图

	temp_speed=default_move_car_p->speed4Wmoverest4;
	default_move_car_p->speed4Wmoverest4=0;//暂令车死亡			   
										
	temp_arr[0]=(default_move_car_p->pointx)/8;
	temp_arr[1]=(default_move_car_p->pointy)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]]
		[temp_arr[1]].life3Wclass5&0x1f]
		[app_battle_unit_event_Repaint](temp_arr,0);
	temp_arr[0]=(default_move_car_p->pointx+7)/8;
	temp_arr[1]=(default_move_car_p->pointy)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]]
		[temp_arr[1]].life3Wclass5&0x1f]
		[app_battle_unit_event_Repaint](temp_arr,0);
	temp_arr[0]=(default_move_car_p->pointx)/8;
	temp_arr[1]=(default_move_car_p->pointy+7)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]]
		[temp_arr[1]].life3Wclass5&0x1f]
		[app_battle_unit_event_Repaint](temp_arr,0);
	temp_arr[0]=(default_move_car_p->pointx+7)/8;
	temp_arr[1]=(default_move_car_p->pointy+7)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]]
		[temp_arr[1]].life3Wclass5&0x1f]
		[app_battle_unit_event_Repaint](temp_arr,0);//重绘附近地面								 

	temp_arr[0]=default_move_car_p->pointx;
	temp_arr[1]=default_move_car_p->pointy;	
	app_battle_car_handle[0][app_battle_car_event_Repaint](temp_arr,0);
	temp_arr[0]=default_move_car_p->pointx+7;
	temp_arr[1]=default_move_car_p->pointy;	
	app_battle_car_handle[0][app_battle_car_event_Repaint](temp_arr,0);
	temp_arr[0]=default_move_car_p->pointx;
	temp_arr[1]=default_move_car_p->pointy+7;
	app_battle_car_handle[0][app_battle_car_event_Repaint](temp_arr,0);
	temp_arr[0]=default_move_car_p->pointx+7;
	temp_arr[1]=default_move_car_p->pointy+7;  
	app_battle_car_handle[0][app_battle_car_event_Repaint](temp_arr,0);//重绘附近车
			   
	default_move_car_p->life3Wdirection2&=0xfc;//改变方向
	default_move_car_p->life3Wdirection2+=temp_direction;
	default_move_car_p->speed4Wmoverest4=temp_speed;
	
	temp_speed		=default_move_car_p->pointx;
	default_move_n	=default_move_car_p->pointy;//保存原坐标	
	switch(temp_direction)//获取移动后座标
	{
	case app_battle_car_direction_U:
		if(default_move_car_p->pointy>=app_battle_car_Movestep)
			default_move_car_p->pointy-=app_battle_car_Movestep;
		else
			default_move_car_p->pointy=0;
		break;
	case app_battle_car_direction_D:
		if(default_move_car_p->pointy<=56-app_battle_car_Movestep)
			default_move_car_p->pointy+=app_battle_car_Movestep;
		else
			default_move_car_p->pointy=56;
		break;
	case app_battle_car_direction_L:
		if(default_move_car_p->pointx>=app_battle_car_Movestep)
			default_move_car_p->pointx-=app_battle_car_Movestep;
		else
			default_move_car_p->pointx=0;
		break;
	case app_battle_car_direction_R: 
		if(default_move_car_p->pointx<=88-app_battle_car_Movestep)
			default_move_car_p->pointx+=app_battle_car_Movestep;
		else
			default_move_car_p->pointx=88;
		break;			
	}
	temp_arr[0]=(default_move_car_p->pointx)/8;
	temp_arr[1]=(default_move_car_p->pointy)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]][temp_arr[1]].life3Wclass5&0x1f]
					[app_battle_unit_event_Bestand](temp_arr,temp_carnum);
	if(temp_arr[0]==-2)
	{default_move_car_p->pointx=temp_speed;default_move_car_p->pointy=default_move_n;goto default_move_page1;}
	temp_arr[0]=(default_move_car_p->pointx+7)/8;
	temp_arr[1]=(default_move_car_p->pointy)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]][temp_arr[1]].life3Wclass5&0x1f]
					[app_battle_unit_event_Bestand](temp_arr,temp_carnum);
	if(temp_arr[0]==-2)
	{default_move_car_p->pointx=temp_speed;default_move_car_p->pointy=default_move_n;goto default_move_page1;}
	temp_arr[0]=(default_move_car_p->pointx)/8;
	temp_arr[1]=(default_move_car_p->pointy+7)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]][temp_arr[1]].life3Wclass5&0x1f]
					[app_battle_unit_event_Bestand](temp_arr,temp_carnum);  
	if(temp_arr[0]==-2)
	{default_move_car_p->pointx=temp_speed;default_move_car_p->pointy=default_move_n;goto default_move_page1;}
	temp_arr[0]=(default_move_car_p->pointx+7)/8;
	temp_arr[1]=(default_move_car_p->pointy+7)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]][temp_arr[1]].life3Wclass5&0x1f]
					[app_battle_unit_event_Bestand](temp_arr,temp_carnum); 
	if(temp_arr[0]==-2)
	{default_move_car_p->pointx=temp_speed;default_move_car_p->pointy=default_move_n;goto default_move_page1;}
default_move_page1:
	info[0]=default_move_car_p->pointx;
	info[1]=default_move_car_p->pointy;	
	app_battle_car_handle[0][app_battle_car_event_Repaint](info,0);//重绘车	
		  									   
}				  
void app_battle_car_default_fire(unsigned char *info,unsigned char msg)
//msg:carnum	info:in:
{
	unsigned char arr[3];
	if((app_battle_car_memory[msg].power3Wfirerest5&0x1f)!=0)return;
	arr[0]=app_battle_car_memory[msg].pointx+3;
	arr[1]=app_battle_car_memory[msg].pointy+3;
	arr[2]=app_battle_car_memory[msg].life3Wdirection2&0x3;
	switch(arr[2])
	{
	case app_battle_car_direction_U:
		arr[1]-=6;
		break;						
	case app_battle_car_direction_R: 
		arr[0]+=6;
		break;
	case app_battle_car_direction_L:
		arr[0]-=6;
		break;
	case app_battle_car_direction_D:
		arr[1]+=6;
		break;
	}
	app_battle_bomb_handle[0][app_battle_bomb_event_Create](arr,app_battle_car_memory[msg].power3Wfirerest5>>5);
	if(arr[0]==-1)
	{																 			
		app_battle_car_memory[msg].power3Wfirerest5&=0xe0;
		app_battle_car_memory[msg].power3Wfirerest5+=app_battle_car_Fireresttime;
	}
	info=info;
}							
void app_battle_car_default_beattack(unsigned char *info,unsigned char msg)
//msg:sublife	info:in:pointx,pointy	out:可穿越否(-1:Y/-2:N)	若此处有car则减血之
{
	unsigned char n;
	app_battle_car_struct *car_p=app_battle_car_memory;
	for(n=0;n<app_battle_car_Quantity;n++,car_p++)
	{
		if(car_p->speed4Wmoverest4!=0)
		if((info[0]-car_p->pointx)<8)
		if((info[1]-car_p->pointy)<8)
		{
			app_battle_bomb_default_move_arr[0]=-2;
			if(((car_p->life3Wdirection2>>2)&0x07)<=msg)
			{
				car_p->life3Wdirection2&=0xe3;
			}
			else
			{						
				car_p->life3Wdirection2-=0x04*msg;
			}
			if(((car_p->life3Wdirection2>>2)&0x07)==0)
			{
				void app_battle_car_default_delete(unsigned char*,unsigned char); 
				app_battle_car_default_delete(0,n);
			}
			return;
		}
	}
	app_battle_bomb_default_move_arr[0]=-1;
}							 
void app_battle_car_default_updata(unsigned char *info,unsigned char msg)
//msg:carnum	info:in:app_battle_car_updata
{
	switch(info[0])
	{
	case app_battle_car_updata_Life:
		if((app_battle_car_memory[msg].life3Wdirection2&0x1c)!=0x1c)
		{
			app_battle_car_memory[msg].life3Wdirection2+=0x04;
		}
		break;
	case app_battle_car_updata_Power: 
		if((app_battle_car_memory[msg].power3Wfirerest5&0xe0)!=0xe0)
		{
			app_battle_car_memory[msg].power3Wfirerest5+=0x20;
		}
		break;
	case app_battle_car_updata_Speed: 
		if((app_battle_car_memory[msg].speed4Wmoverest4&0xf0)!=0x30)
		{
			app_battle_car_memory[msg].speed4Wmoverest4-=0x10;
		}
		break;
	default:
		break;
	}
	info=info;
	msg=msg;
}					
void app_battle_car_default_delete(unsigned char *info,unsigned char msg)
//msg:carnum	info:in:
{			
	app_battle_car_struct *car_p=app_battle_car_memory+msg;	
	draw_flashpic(app_battle_car_memory[msg].pointx,app_battle_car_memory[msg].pointy,app_battle_stream_picture[0],0);

	temp_arr[0]=(car_p->pointx)/8;
	temp_arr[1]=(car_p->pointy)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]]
		[temp_arr[1]].life3Wclass5&0x1f]
		[app_battle_unit_event_Repaint](temp_arr,0);
	temp_arr[0]=(car_p->pointx+7)/8;
	temp_arr[1]=(car_p->pointy)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]]
		[temp_arr[1]].life3Wclass5&0x1f]
		[app_battle_unit_event_Repaint](temp_arr,0);
	temp_arr[0]=(car_p->pointx)/8;
	temp_arr[1]=(car_p->pointy+7)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]]
		[temp_arr[1]].life3Wclass5&0x1f]
		[app_battle_unit_event_Repaint](temp_arr,0);
	temp_arr[0]=(car_p->pointx+7)/8;
	temp_arr[1]=(car_p->pointy+7)/8;
	app_battle_unit_handle[app_battle_unit_memory[temp_arr[0]]
		[temp_arr[1]].life3Wclass5&0x1f]
		[app_battle_unit_event_Repaint](temp_arr,0);//重绘附近地面
	car_p->pointx=0;													 
	car_p->pointy=0;			
	car_p->speed4Wmoverest4=0;
	car_p->power3Wfirerest5=0;
	car_p->life3Wdirection2=0;
	info=info;
}



code void (code *(app_battle_car_handle[/*class*/][app_battle_car_event_Quantity/*event*/]))(unsigned char *,unsigned char)=
{
	{
		app_battle_car_default_create,
		app_battle_car_default_repaint,
		app_battle_car_default_refresh,
		app_battle_car_default_move,
		app_battle_car_default_fire,
		app_battle_car_default_beattack,
		app_battle_car_default_updata,
		app_battle_car_default_delete
	}
};