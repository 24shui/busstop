#ifndef _SHOWJPG_H_
#define _SHOWJPG_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <errno.h>
#include "jpeglib.h" //jpg库的头文件

/**
 * @brief 显示一张jpg图片
 *
 * @param jpgpath jpg图片路径
 * @param lcdp lcd映射后的内存
 * @return int
 */
int show_800x480jpg(char *jpgpath, unsigned int *lcdp);

/**
 * @brief 在指定位置显示一张jpg图片
 *
 * @param jpgpath jpg图片路径
 * @param lcdp lcd映射后的内存
 * @param sx x坐标
 * @param sy y坐标
 * @return int
 */
int show_anyjpg_anywhere(char *jpgpath, unsigned int *lcdp, int sx, int sy);

#endif