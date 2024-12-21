#ifndef __font_h__
#define __font_h__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#define color u32
#define getColor(A, R, G, B)   (A | B << 8 | G << 16 | R << 24)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

typedef struct stbtt_fontinfo
{
	void *userdata;
	unsigned char *data; // pointer to .ttf file
	int fontstart;		 // offset of start of font

	int numGlyphs; // number of glyphs, needed for range checking

	int loca, head, glyf, hhea, hmtx, kern; // table locations as offset from start of .ttf
	int index_map;							// a cmap mapping for our chosen character encoding
	int indexToLocFormat;					// format needed to map from glyph index to glyph
} stbtt_fontinfo;

typedef struct
{
	u32 height;
	u32 width;
	u32 byteperpixel;
	u8 *map;
} bitmap;

typedef struct
{
	stbtt_fontinfo *info;
	u8 *buffer;
	float scale;
} font;

// lcd设备结构体
struct LcdDevice
{
	int fd;
	unsigned int *mp; // 保存映射首地址
};


/**
 * @brief 初始化字库
 *
 * @param fontPath 字库的路径 开发板自带字库/usr/share/fonts/DroidSansFallback.ttf
 * @return font* 操作字库的句柄
 */
font *fontLoad(char *fontPath);

/**
 * @brief 设置字体的大小
 *
 * @param f 操作字库的句柄
 * @param pixels 字号大小 24、32、64等常见字号
 */
void fontSetSize(font *f, s32 pixels);

/**
 * @brief 设置字体输出框的大小
 *
 * @param width 输出框的宽
 * @param height 输出框的高
 * @param byteperpixel 当前屏幕一个像素的数据大小4个字节（32位色深）
 * @return bitmap* 字体输出框句柄
 */
bitmap *createBitmap(u32 width, u32 height, u32 byteperpixel);

// 可以指定输出框的颜色

/**
 * @brief 设置字体输出框的大小，可以指定输出框的颜色
 *
 * @param width 输出框的宽
 * @param height 输出框的高
 * @param byteperpixel 当前屏幕一个像素的数据大小4个字节（32位色深）
 * @param c	输出框颜色值	getColor(A, R, G, B)
 * @return bitmap* 字体输出框句柄
 */
bitmap *createBitmapWithInit(u32 width, u32 height, u32 byteperpixel, color c);

/**
 * @brief 把字体输出到输出框中
 * 
 * @param f 操作字库的句柄
 * @param screen 字体输出框句柄
 * @param x 字体的位置    X轴 
 * @param y 字体的位置    Y轴
 * @param text 字体文本 
 * @param c 字体颜色 getColor(A, R, G, B)
 * @param maxWidth 一行显示字体的最大宽度  （例如：字体大小为32，假设设置为64则一行显示两个字体，超过就换行显示）
 */
void fontPrint(font *f, bitmap *screen, s32 x, s32 y, char *text, color c, s32 maxWidth);


/**
 * @brief 把输出框的所有信息显示到LCD屏幕中
 * 
 * @param p LCD映射后的首地址
 * @param px 字体的位置 X轴
 * @param py 字体的位置 y轴
 * @param bm 字体输出框句柄
 */
void show_font_to_lcd(unsigned int *p, int px, int py, bitmap *bm);

// 关闭字体库
void fontUnload(font *f);

// 关闭字体输出框
void destroyBitmap(bitmap *bm);

#endif