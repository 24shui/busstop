#ifndef _TOUCH_H_
#define _TOUCH_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdlib.h>

#define LCD_WIDTH 800
#define LCD_HIGH 480
#define BLACK_PCB 0 // 1：黑屏， 0：蓝屏

typedef enum
{
    SLIDE_UP = 0,      // 向上滑屏
    SLIDE_DOWN,        // 向下滑屏
    SLIDE_LEFT,        // 向左滑屏
    SLIDE_RIGHT,       // 向右滑屏
    SLIDE_TOUCH,       // 点击事件
    SLIDE_NONE = 0xFF, // 没有滑屏
} e_slide;

/**
 * @brief 打开触摸屏
 *
 * @return int
 */
int open_touchscreen(void);

/**
 * @brief 滑屏判断
 *
 * @param x 点击事件时，获取x轴坐标
 * @param y 点击事件时，获取y轴坐标
 * @return e_slide 返回滑屏动作的方向
 */
e_slide sliding_screen(int *x, int *y);

/**
 * @brief 关闭触摸屏
 *
 * @return int
 */
int close_touchscreen(void);
#endif