#ifndef __NOTICE_H__
#define __NOTICE_H__

#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "showfont.h"

/**
 * @brief 从文件中获取公告数据
 *
 * @return char*    字符串指针，指向公告数据
 */
char *get_notice();

/**
 * @brief 在显示屏上显示公告
 *
 * @param lcdp  内存映射
 * @return int
 */
int show_notice(unsigned int *lcdp);

#endif