#include "showfont.h"

/**
 * @brief 在显示屏上显示文字
 *
 * @param lcd_mmap 内存映射
 * @param txt 字符串
 * @param info 字体信息
 * @param n 字体大小
 * @return int
 */
int show_font(unsigned int *lcd_mmap, char *txt, font_t *info, int n)
{
	// 打开字体文件
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");

	// 字体大小的设置
	fontSetSize(f, n);

	// 创建一个画板（点阵图）
	bitmap *bm = createBitmapWithInit(info->mapw, info->maph, 4, info->map_c); // 也可使用createBitmapWithInit函数，改变画板颜色

	// 将字体写到点阵图上
	fontPrint(f, bm, info->font_x, info->font_y, txt, info->font_c, info->maxWidth);

	// 把字体框输出到LCD屏幕上
	show_font_to_lcd(lcd_mmap, info->map_x, info->map_y, bm);

	// 关闭字体，关闭画板
	fontUnload(f);
	destroyBitmap(bm);
	return 0;
}

// font_t font_info =
// 	{
// 		300,						// 画板宽
// 		48,							// 画板的高
// 		getColor(0, 255, 255, 255), // 画板颜色getColor(0, 0, 0, 255)
// 		50,							// 画板显示位置
// 		70,							// 画板显示位置

// 		0,						// 字体位置x
// 		0,						// 字体位置y
// 		getColor(0, 255, 0, 0), // 字体getColor(0, 0, 0, 255)
// 		300,					// 一行显示字体的最大宽度
// };
// show_font(lcdp, "helloworld", &font_info);