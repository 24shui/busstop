#ifndef __LOCALWEATHER_H__
#define __LOCALWEATHER_H__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "showfont.h"

/**
 * @brief 从文件中获取天气数据
 *
 * @return char* 指向天气数据字符串的指针
 */
char *get_weather();

/**
 * @brief LCD显示天气数据
 *
 * @param f 字体
 * @param lcd_mmap 内存映射
 * @return int
 */
int show_weather(unsigned int *lcdp);

#endif