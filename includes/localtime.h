#ifndef __LOCALTIME_H__
#define __LOCALTIME_H__

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "showfont.h"
#include "mypthread.h"

/**
 * @brief 取得时间戳
 *
 * @param date date结构体指针
 * @return int
 */
int get_time(struct tm *date);

void *show_time(void *arg);
// void *show_time(void *lcdp);

#endif