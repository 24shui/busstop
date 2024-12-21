#ifndef _SHOWFONT_H_
#define _SHOWFONT_H_
#include "font.h"

typedef struct
{
	int mapw;	 // 画板宽
	int maph;	 // 画板的高
	color map_c; // 画板颜色getColor(0, 0, 0, 255)
	int map_x;	 // 画板显示位置x
	int map_y;	 // 画板显示位置y

	int font_x;	  // 字体位置x
	int font_y;	  // 字体位置y
	color font_c; // 字体颜色getColor(0, 0, 0, 255)
	s32 maxWidth; // 一行显示字体的最大宽度
} font_t;

/**
 * @brief 在显示屏上显示文字
 *
 * @param lcd_mmap 内存映射
 * @param txt 字符串
 * @param info 字体信息
 * @param n 字体大小
 * @return int
 */
int show_font(unsigned int *lcd_mmap, char *txt, font_t *info, int n);

#endif