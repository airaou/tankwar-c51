#include<common\timeget.h>
#include<common\HARD.H>
data unsigned int time=0;
data unsigned char time_0=0;
void timeget (void)
{
	TH0=0x00;
	TL0=0x00;
	TMOD=0x01;	//������ʽΪ16 λ��ʱ��
	ET0=0x01;	//����T/C0 �ж�
	EA=1;		//ȫ���ж�����
	TR0=1;		//����T/C0 ����
}
void timeget_0 (void) interrupt 1	//�жϷ�����
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