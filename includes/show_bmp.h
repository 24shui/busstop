#ifndef _SHOW_BMP_H_
#define _SHOW_BMP_H_
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#pragma pack(1) // 设置最大对齐数可以为n，n可以取(1, 2, 4, 8, 16)
typedef struct
{
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserverd1;
	unsigned short bfReserverd2;
	unsigned int bfOffBits;
} bmpfile_head_t; // bmp文件信息头

typedef struct
{
	unsigned int biSize;
	unsigned int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrmportant;
} bmpbit_head_t; // bmp位图信息头
#pragma pack()	 // / 取消设置的对齐数，还原为默认

int show_24bmp(char *bmppath, unsigned int *lcdp);
int show_any24bmp_anywhere(char *bmppath, unsigned int *lcdp, int sx, int sy);
int show_24bmp_reduce(char *bmppath, unsigned int *lcdp, int reducex);

#endif 