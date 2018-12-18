#include<common\timeget.h>
#include<common\HARD.H>
data unsigned int time=0;
data unsigned char time_0=0;
void timeget (void)
{
	TH0=0x00;
	TL0=0x00;
	TMOD=0x01;	//工作方式为16 位定时器
	ET0=0x01;	//允许T/C0 中断
	EA=1;		//全部中断允许
	TR0=1;		//启动T/C0 运行
}
void timeget_0 (void) interrupt 1	//中断服务函数
{
	time_0++;
	if(time_0==2)
	{
		time++;
		time_0=0;
	}
	TH0=0x00;
	TL0=0x00;
}