#ifndef _LCD_MMAP_H_
#define _LCD_MMAP_H_

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>

/**
 * @brief	LCD屏幕文件内存映射
 *
 * @param fd 文件描述符
 * @return unsigned int*
 */
unsigned int *lcdmmap(int *fd);

/**
 * @brief	将整个LCD帧缓冲区设置为黑色
 *
 * @param lcdp	内存映射
 */
void clear_lcd_screen(unsigned int *lcdp);

/**
 * @brief 取消内存映射,释放空间,关闭显示屏
 *
 * @param fd	文件描述符
 * @param lcdp	内存映射
 */
void unlcd_mmap(int fd, unsigned int *lcdp);

#endif