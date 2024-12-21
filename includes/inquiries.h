#ifndef __INQUIRIES_H__
#define __QUIRIES_H__

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "showfont.h"
#include "showjpg.h"
#include "touch.h"

#define MAX_NAME_LENGTH 1024
#define MAX_STOPS 50

typedef struct
{
    char name[MAX_NAME_LENGTH];
} BusStop;

typedef struct
{
    char vehicle_number[MAX_NAME_LENGTH];   // 车辆编号
    char current_position[MAX_NAME_LENGTH]; // 当前位置
    char first_departure[MAX_NAME_LENGTH];  // 首发时间
    char last_departure[MAX_NAME_LENGTH];   // 末班时间
    BusStop stops[MAX_STOPS];               // 站点数组
    int num_stops;                          // 实际站点数量
} Bus;

/**
 * @brief 获取点击事件并赋予标志位
 *
 * @param x x轴坐标
 * @param y y轴坐标
 * @return int
 */

int pick_key(int x, int y);
/**
 * @brief 屏幕虚拟键盘输入公交线路号
 *
 * @param lcdp 内存映射
 */
void bus_input(unsigned int *lcdp);

/**
 * @brief   根据线路号从文件中读取内容查找
 *
 * @param filename  文件路径
 * @param bus   指向包含公交线路信息的结构体的指针
 * @param line_number   线路号
 * @param lcdp  内存映射
 * @return int
 */
int read_bus_info_from_file(const char *filename, Bus *bus, const char *line_number, unsigned int *lcdp);

/**
 * @brief   在LCD上显示查询到的公交线路信息
 *
 * @param bus   指向包含公交线路信息的结构体的指针
 * @param lcdp  内存映射
 */
void show_bus_info(const Bus *bus, unsigned int *lcdp);

/**
 * @brief 查询线路信息
 *
 * @param number 线路号
 * @param lcdp 内存映射
 * @return int
 */
int bus_quiries(char number[], unsigned int *lcdp);

#endif