#include "lcd_mmap.h"

/**
 * @brief	LCD屏幕文件内存映射
 *
 * @param fd 文件描述符
 * @return unsigned int*
 */
unsigned int *lcdmmap(int *fd)
{
	*fd = open("/dev/fb0", O_RDWR); // 打开屏幕文件
	if (*fd < 0)
	{
		perror("open fail");
		return NULL;
	}
	// 系统自动寻找合适的内存映射后的起始地址
	// 映射的内存大小
	// 映射内存的权限可读可写
	// 映射的内存进程共享
	// 要映射的文件描述符
	// 映射后文件偏移量
	unsigned int *p = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
	if (p == (void *)-1)
	{
		perror("mmap fail");
		close(*fd);
		return NULL;
	}
	return p;
}

/**
 * @brief	将整个LCD帧缓冲区设置为黑色
 *
 * @param lcdp	内存映射
 */
void clear_lcd_screen(unsigned int *lcdp)
{
	// 计算LCD帧缓冲区的大小（以像素为单位）
	size_t bufferSize = 800 * 480;

	// 将整个LCD帧缓冲区设置为黑色
	for (size_t i = 0; i < bufferSize; i++)
	{
		*(lcdp + i) = 0xFF000000; // ARGB: Alpha, Red, Green, Blue
	}
}

/**
 * @brief 取消内存映射,释放空间,关闭显示屏
 *
 * @param fd	文件描述符
 * @param lcdp	内存映射
 */
void unlcd_mmap(int fd, unsigned int *lcdp)
{
	// 资源回收
	munmap(lcdp, 800 * 480 * 4); // 取消映射
	close(fd);					 // 关闭文件
}