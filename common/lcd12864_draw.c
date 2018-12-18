#include "LCD12864_DRAW.H"

#ifdef __DRAW_ALLCLEAN__
void draw_allclean ()
{
	data unsigned char x=0,y=0;
	for (y=0;y<32;y++)
	{
		write_cmd (0x80+y);
		write_cmd (0x80);
		for (x=0;x<32;x++)
		{
			write_dat (0x00);
		}
	}
	return;
}
#endif

#ifdef __DRAW_DOT__
void draw_dot (unsigned char x,unsigned char y,bit z)
{
	data unsigned char left=0,right=0;
	if (x>127) return;
	if (y>63)  return;
	//读取
	write_cmd (0x80+y-((y>=32)?32:0));
	write_cmd (0x80+x/16+((y>=32)?8:0));

	read_dat ();
	left=read_dat ();
	right=read_dat ();

	if ((x%16)>=8)
		if (z==1) right=right|(1<<(15-x%16));
		else right=right&(~(1<<(15-x%16)));
	else
		if (z==1) left=left|(1<<(7-x%16));
		else left=left&(~(1<<(7-x%16)));

	//写入
	write_cmd (0x80+y-((y>=32)?32:0));
	write_cmd (0x80+x/16+((y>=32)?8:0));

	write_dat (left);
	write_dat (right);

	return;//*/
}
#endif

#ifdef __DRAW_READDOT__
bit draw_readdot (unsigned char x,unsigned char y)
{
	data unsigned char left=0,right=0;
	if (x>127) return 0;
	if (y>63)  return 0;
	//读取
	write_cmd (0x80+y-((y>=32)?32:0));
	write_cmd (0x80+x/16+((y>=32)?8:0));

	read_dat ();
	left=read_dat ();
	right=read_dat ();

	if ((x%16)>=8)
	{
		return (1&(right>>(15-x%16)));
	}
	else
	{
		return (1&(left>>(7-x%16)));
	}
}
#endif

#ifdef __DRAW_PICTURE__
void draw_picture (unsigned char x,unsigned char y,unsigned char *pic)
{
	data unsigned char m=0,n=0;
	if(x>127 || y>63)return;
	for(n=0;n<7;n++)for(m=0;m<7;m++)
			draw_dot(x+m,y+n,(pic[n]>>(6-m))&1);
	return;
}
#endif

#ifdef __DRAW_AREAPIC__
void draw_areapic(
	unsigned char x,
	unsigned char y,
	unsigned char *pic,
	bit transparent)
{
	data unsigned char left,right,n,*p=(x%2)?&right:&left;
	x=0x80|(x>>1)+((y>3)?8:0);
	y=0x80|(y%4<<3);
	for(n=0;n<8;n++)
	{
		write_cmd(y+n);
		write_cmd(x);
		read_dat();
		left=read_dat();
		right=read_dat();

		*p=pic[n]|((transparent)?*p:0);
		write_cmd(y+n);
		write_cmd(x);
		write_dat(left);
		write_dat(right);
	}
}
#endif

#ifdef __DRAW_FLASHPIC__ 
void draw_flashpic(
	unsigned char x,
	unsigned char y,
	unsigned char *pic,
	bit transparent)
{ 
	data unsigned char r1,r2,r3,n,aimx,aimy,temp=x%16;
	data bit twotimes=(temp<16&&temp>8);
	for(n=0;n<8;n++,pic++)
	{
		aimy=(y+n)%32;		
		aimx=x/16+((y+n>=32)?8:0);

		write_cmd(0x80|aimy);
		write_cmd(0x80|aimx);
		read_dat();
		r1=read_dat();
		r2=read_dat();
		if(twotimes)r3=read_dat();

		if(temp<8)
		{
			if(!transparent)r1&=~(0xff>>temp);
			r1|=*pic>>temp;
		}
		if(temp!=0)
		{
			if(temp<8)
			{
				if(!transparent)r2&=~(0xff<<(8-temp));
				r2|=*pic<<(8-temp);
			}
			else
			{
				if(!transparent)r2&=~(0xff>>(temp-8));
				r2|=*pic>>(temp-8);
			}
		}
		if(temp>8)
		{
			if(!transparent)r3&=~(0xff<<(16-temp));
			r3|=*pic<<(16-temp);
		}		
		write_cmd(0x80|aimy);
		write_cmd(0x80|aimx);
		write_dat(r1);
		write_dat(r2);
		if(twotimes)write_dat(r3);
	}//*/
}
#endif	

#ifdef __DRAW_CIRCLE__
void draw_circle (unsigned char xc,unsigned char yc,unsigned char r)
{
	unsigned char x=0,y=r;
	int d;
	d=3-r-r;
	draw_dot(xc+y,yc+x,1);
	draw_dot(xc+x,yc+y,1);
	draw_dot(xc-x,yc+y,1);
	draw_dot(xc-y,yc+x,1);
	draw_dot(xc-y,yc-x,1);
	draw_dot(xc-x,yc-y,1);
	draw_dot(xc+x,yc-y,1);
	draw_dot(xc+y,yc-x,1);
	while(x<y)
	{
		if(d<0)
		{
			d=d+4*x+6;
		}
		else
		{
			d=d+4*(x-(y--))+10;
		}
		x++;
		draw_dot(xc+y,yc+x,1);
		draw_dot(xc+x,yc+y,1);
		draw_dot(xc-x,yc+y,1);
		draw_dot(xc-y,yc+x,1);
		draw_dot(xc-y,yc-x,1);
		draw_dot(xc-x,yc-y,1);
		draw_dot(xc+x,yc-y,1);
		draw_dot(xc+y,yc-x,1);
	}
}
void draw_circle_dot(unsigned char xc,unsigned char yc,unsigned char x,unsigned char y)
{		 	
	draw_dot(xc+y,yc+x,1);
	draw_dot(xc+x,yc+y,1);
	draw_dot(xc-x,yc+y,1);
	draw_dot(xc-y,yc+x,1);
	draw_dot(xc-y,yc-x,1);
	draw_dot(xc-x,yc-y,1);
	draw_dot(xc+x,yc-y,1);
	draw_dot(xc+y,yc-x,1);	
}
#endif

#ifdef __DRAW_LINE__
void draw_line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit color)  
{
	unsigned char a,b,d1,d2,d,x,y; 						 
	a=y0-y1;
	b=x1-x0;
	d=2*a+b; 					 
	d1=2*a;
	d2=2*(a+b); 					    
	x=x0;
	y=y0; 								    
	draw_dot(x,y,color); 				   
	while(x<x1)
	{ 							   
		if(d<0)
		{
			x++;
			y++;
			d+=d2;
		} 			   
		else
		{
			x++;
			d+=d1;
		} 			   
		draw_dot(x,y,color); 			   
	}
}
#endif

/*
#ifdef __DRAW_LINE__
void draw_line (unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
	unsigned char n=0;
	long l=0;	
	char m=0;
	if (x1>127||x2>127||y1>63||y2>63) return;//数据异常则直接返回

	//若两点连线段无斜率
	if (x1==x2)
	{
		m=((y1<y2)?1:-1);
		for (n=y1;n!=y2;n+=m)
		{
			draw_dot (x1,n,1);
		}
		draw_dot (x2,y2,1);
		return;
	}

	//斜率在(-1,1)之间
	if ((y2-y1)*(y2-y1)<(x2-x1)*(x2-x1))
	{	  
		m=((x1<x2)?1:-1);
		for (n=x1;n!=x2;n+=m)
		{
			//通过直线的方程来计算
			//此处数据类型极为重要
			//作者在此处曾纠结好久
			l=((long)((long)n*(long)y2-(long)n*(long)y1-(long)x1*(long)y2+(long)x2*(long)y1)*10/((long)x2-(long)x1)); 
			if (l%10>=5) l=l/10+1; else l=l/10;//四舍五入	
			draw_dot (n,l,1);
		}
	}
	//斜率在(-∞,-1]∪[1,+∞)之间
	else
	{
		m=((y1<y2)?1:-1);
		for (n=y1;n!=y2;n+=m)
		{	
			l=((long)((long)n*(long)x2-(long)n*(long)x1-(long)y1*(long)x2+(long)y2*(long)x1)*10/((long)y2-(long)y1));
			if (l%10>=5) l=l/10+1; else l=l/10;	 
			draw_dot (l,n,1);
		}
	}		
	draw_dot (x2,y2,1);
	return;
}
#endif
*/

#ifdef __DRAW_SQUARE__
void draw_square (unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
	char m=0;
	unsigned char n=0;

	m=((y1<y2)?1:-1);
	for (n=y1;n!=y2;n+=m)
	{
		draw_dot (x1,n,1);
		draw_dot (x2,n,1);
	}

	m=((x1<x2)?1:-1);
	for (n=x1;n!=x2;n+=m)
	{
		draw_dot (n,y1,1);
		draw_dot (n,y2,1);
	}
	draw_dot (x2,y2,1);
	return;
}
#endif