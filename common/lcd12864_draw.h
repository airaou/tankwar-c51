#ifndef __LCD12864_DRAW__
#define __LCD12864_DRAW__
#include<common\lcd12864.h>
/*
12864��ͼ����

����PLUS_COMMANDģʽ��ʹ��
*/

//���价�������GDRAM(3)
extern void draw_allclean();
		#define __DRAW_ALLCLEAN__

//���价�������㣬x��[0,127],y��[0,64]
extern void draw_dot(unsigned char x,unsigned char y,bit z);
		#define __DRAW_DOT__

//���价���������ص�
extern bit draw_readdot(unsigned char x,unsigned char y);
	//	#define __DRAW_READDOT__

//���价���������ͼ
extern void draw_picture(unsigned char x,unsigned char y,unsigned char *pic);
	//	#define __DRAW_PICTURE__

//���价������λ��ͼ,x��[0,15],y��[0,7],227B
extern void draw_areapic(unsigned char x,unsigned char y,unsigned char *pic,bit transparent);
	//	#define __DRAW_AREAPIC__

//���价����������ͼ,400B
extern void draw_flashpic(unsigned char x,unsigned char y,unsigned char *pic,bit transparent);
		#define __DRAW_FLASHPIC__

//���价������Բ(Բ�ĺ�,Բ����,�뾶),225B
extern void draw_circle(unsigned char xc,unsigned char yc,unsigned char r);
	//	#define __DRAW_CIRCLE__

//���价��������(��A�����,��A������,��B�����,��B������),80B,1197B
extern void draw_line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit color);
	//	#define __DRAW_LINE__

//���价����������(��A�����,��A������,�Խ������,�Խ�������),116B
extern void draw_square(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);
	//	#define __DRAW_SQUARE__

#endif