#ifndef __LCD12864_DRAW__
#define __LCD12864_DRAW__
#include<common\lcd12864.h>
/*
12864绘图驱动

进入PLUS_COMMAND模式后使用
*/

//扩充环境，清除GDRAM(3)
extern void draw_allclean();
		#define __DRAW_ALLCLEAN__

//扩充环境，画点，x∈[0,127],y∈[0,64]
extern void draw_dot(unsigned char x,unsigned char y,bit z);
		#define __DRAW_DOT__

//扩充环境，读像素点
extern bit draw_readdot(unsigned char x,unsigned char y);
	//	#define __DRAW_READDOT__

//扩充环境，描点贴图
extern void draw_picture(unsigned char x,unsigned char y,unsigned char *pic);
	//	#define __DRAW_PICTURE__

//扩充环境，区位贴图,x∈[0,15],y∈[0,7],227B
extern void draw_areapic(unsigned char x,unsigned char y,unsigned char *pic,bit transparent);
	//	#define __DRAW_AREAPIC__

//扩充环境，快速贴图,400B
extern void draw_flashpic(unsigned char x,unsigned char y,unsigned char *pic,bit transparent);
		#define __DRAW_FLASHPIC__

//扩充环境，画圆(圆心横,圆心纵,半径),225B
extern void draw_circle(unsigned char xc,unsigned char yc,unsigned char r);
	//	#define __DRAW_CIRCLE__

//扩充环境，画线(点A坐标横,点A坐标纵,点B坐标横,点B坐标纵),80B,1197B
extern void draw_line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit color);
	//	#define __DRAW_LINE__

//扩充环境，画矩形(∠A座标横,∠A座标纵,对角座标横,对角座标纵),116B
extern void draw_square(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);
	//	#define __DRAW_SQUARE__

#endif