#include<mainfile\app_battle_bomb.h>
#include<mainfile\app_battle_unit.h>
#include<mainfile\app_battle_car.h>
#include<common\lcd12864_draw.h>

idata app_battle_bomb_struct app_battle_bomb_memory[app_battle_bomb_Quantity]={0};
			   
void app_battle_bomb_default_create(unsigned char *info,unsigned char msg)
//msg:power	info:in:pointx,pointy,direction out:�Ƿ񴴽��ɹ�(-1:Y/-2:N)
{
	unsigned char n;
	for(n=0;n<app_battle_bomb_Quantity;n++)
	{
		if(app_battle_bomb_memory[n].direction2Wpower3Wmoverest3==0)
		{
			app_battle_bomb_memory[n].pointx=info[0];
			app_battle_bomb_memory[n].pointy=info[1];
			app_battle_bomb_memory[n].direction2Wpower3Wmoverest3=(info[2]<<6)|(msg<<3);
			app_battle_bomb_handle[0][app_battle_bomb_event_Repaint](info,n);
			info[0]=-1;
		 	return;
		}
	}
	info[0]=-2;
}
void app_battle_bomb_default_delete(unsigned char *info,unsigned char msg)
//msg:bombnum	info:in:
{								  
	unsigned char arr[2];
	arr[0]=app_battle_bomb_memory[msg].pointx/8;
	arr[1]=app_battle_bomb_memory[msg].pointy/8;

	app_battle_unit_handle[app_battle_unit_memory[arr[0]][arr[1]].life3Wclass5&0x1f]
					[app_battle_unit_event_Repaint](arr,msg);
	app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3=0;	
	app_battle_bomb_memory[msg].pointx=0;
	app_battle_bomb_memory[msg].pointy=0;
	info=info;
}

//���жϣ����ƶ����ʻ���bomb��ǽ��ŷ�������
unsigned char app_battle_bomb_default_move_arr[2]={0};
void app_battle_bomb_default_move(unsigned char *info,unsigned char msg)
//msg:bombnum	info:in:
{
	if(app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3==0)
		if(app_battle_bomb_memory[msg].pointy==0)return;
	if((app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3&0x7)!=0)return;
	app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3+=app_battle_bomb_Speed;
												
	draw_dot(app_battle_bomb_memory[msg].pointx  ,app_battle_bomb_memory[msg].pointy  ,0);
	draw_dot(app_battle_bomb_memory[msg].pointx+1,app_battle_bomb_memory[msg].pointy  ,0);
	draw_dot(app_battle_bomb_memory[msg].pointx  ,app_battle_bomb_memory[msg].pointy+1,0);
	draw_dot(app_battle_bomb_memory[msg].pointx+1,app_battle_bomb_memory[msg].pointy+1,0);//�����ͼ

	app_battle_bomb_default_move_arr[0]=app_battle_bomb_memory[msg].pointx/8;
	app_battle_bomb_default_move_arr[1]=app_battle_bomb_memory[msg].pointy/8;		 
	app_battle_unit_handle[app_battle_unit_memory[app_battle_bomb_default_move_arr[0]]
					[app_battle_bomb_default_move_arr[1]].life3Wclass5&0x1f]
					[app_battle_unit_event_Beattack](app_battle_bomb_default_move_arr,msg);//��������unit��beattack�¼�
	if(app_battle_bomb_default_move_arr[0]==-2)
	{
		app_battle_bomb_handle[0][app_battle_bomb_event_Delete](0,msg);
		return;
	}//�����ɴ�Խ�������� �����ٿ�ת�Ƶ�unit��bestand�¼��ڽ���	

	app_battle_bomb_default_move_arr[0]=app_battle_bomb_memory[msg].pointx;
	app_battle_bomb_default_move_arr[1]=app_battle_bomb_memory[msg].pointy;	
	app_battle_car_handle[0][app_battle_car_event_Beattack](app_battle_bomb_default_move_arr,(app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3>>3)&0x07);//����car��beattack�¼�			  
	if(app_battle_bomb_default_move_arr[0]==-2)
	{
		app_battle_bomb_handle[0][app_battle_bomb_event_Delete](0,msg);
		return;
	}//�������ɹ��������� �����ٿ�ת�Ƶ�unit��bestand�¼��ڽ���	
											

	switch(app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3>>6)//��ȡ�ƶ�������
	{
	case app_battle_bomb_direction_U:
		if(app_battle_bomb_memory[msg].pointy>=app_battle_bomb_Movestep)
			app_battle_bomb_memory[msg].pointy-=app_battle_bomb_Movestep;
		else
			app_battle_bomb_memory[msg].pointy=0;
		break;
	case app_battle_bomb_direction_D:
		if(app_battle_bomb_memory[msg].pointy<=62-app_battle_bomb_Movestep)
			app_battle_bomb_memory[msg].pointy+=app_battle_bomb_Movestep;
		else
			app_battle_bomb_memory[msg].pointy=62;
		break;
	case app_battle_bomb_direction_L:
		if(app_battle_bomb_memory[msg].pointx>=app_battle_bomb_Movestep)
			app_battle_bomb_memory[msg].pointx-=app_battle_bomb_Movestep;
		else
			app_battle_bomb_memory[msg].pointx=0;
		break;
	case app_battle_bomb_direction_R: 
		if(app_battle_bomb_memory[msg].pointx<=94-app_battle_bomb_Movestep)
			app_battle_bomb_memory[msg].pointx+=app_battle_bomb_Movestep;
		else
			app_battle_bomb_memory[msg].pointx=94;
		break;			
	}
	app_battle_bomb_handle[0][app_battle_bomb_event_Repaint](0,msg);//�ػ��ƶ�����ͼ
	info=info;
}
void app_battle_bomb_default_repaint(unsigned char *info,unsigned char msg)
//msg:bombnum	info:in:
{
	draw_dot(app_battle_bomb_memory[msg].pointx  ,app_battle_bomb_memory[msg].pointy  ,1);
	draw_dot(app_battle_bomb_memory[msg].pointx+1,app_battle_bomb_memory[msg].pointy  ,1);
	draw_dot(app_battle_bomb_memory[msg].pointx  ,app_battle_bomb_memory[msg].pointy+1,1);
	draw_dot(app_battle_bomb_memory[msg].pointx+1,app_battle_bomb_memory[msg].pointy+1,1);
	info=info;
}							
void app_battle_bomb_default_refresh(unsigned char *info,unsigned char msg)
//msg:bombnum	info:in:passtime
{
	unsigned char *p=&(app_battle_bomb_memory[msg].direction2Wpower3Wmoverest3);
	if(*p)
		if((*p&0x7)<=info[0])
		{
			*p&=0xf8;
		}
		else
		{
			*p-=info[0];
		}
}								

code void (code *(app_battle_bomb_handle[/*class*/][app_battle_bomb_event_Quantity/*�¼���*/]))(unsigned char*,unsigned char)=
{
  	{
		app_battle_bomb_default_create,
		app_battle_bomb_default_delete,
		app_battle_bomb_default_move,
		app_battle_bomb_default_repaint,
		app_battle_bomb_default_refresh
	}
};