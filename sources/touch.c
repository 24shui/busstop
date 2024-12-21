#include "touch.h"

static int ts_fd;

/**
 * @brief 打开触摸屏
 *
 * @return int
 */
int open_touchscreen(void)
{
	ts_fd = open("/dev/input/event0", O_RDWR);
	if (ts_fd < 0)
	{
		perror("open /dev/input/event0 fail:");
		return -1;
	}
	return 0;
}

/**
 * @brief 滑屏判断
 *
 * @param x 点击事件时，获取x轴坐标
 * @param y 点击事件时，获取y轴坐标
 * @return e_slide 返回滑屏动作的方向
 */
e_slide sliding_screen(int *x, int *y)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int abs_x = 0; // 保存两次x轴坐标的绝对值
	int abs_y = 0; // 保存两次y轴坐标的绝对值
	int ret = 0;
	struct input_event ts; // 定义触控屏存储信息结构体，用于存储获取的触控屏信息。
	e_slide mode = SLIDE_NONE;
	while (1) // 获取刚开始点击屏幕未释放的坐标
	{

		ret = read(ts_fd, &ts, sizeof(struct input_event)); // 通过read函数存储获取的触控屏信息到ts
		if (ret == -1)
		{
			printf("read event0 data fail!\n");
			return SLIDE_NONE;
		}

#if BLACK_PCB																		  // 黑色边框
		if (ts.type == EV_ABS && ts.code == ABS_X && ts.value > 0 && ts.value < 1024) // 获取X轴坐标
		{
			x1 = ts.value * LCD_WIDTH / 1024;
		}
		if (ts.type == EV_ABS && ts.code == ABS_Y && ts.value > 0 && ts.value < 600) // 获取Y轴坐标
		{
			y1 = ts.value * LCD_HIGH / 600;
		}
#else
		if (ts.type == EV_ABS && ts.code == ABS_X && ts.value > 0 && ts.value < LCD_WIDTH) // 获取X轴坐标
		{
			x1 = ts.value;
		}
		if (ts.type == EV_ABS && ts.code == ABS_Y && ts.value > 0 && ts.value < LCD_HIGH) // 获取Y轴坐标
		{
			y1 = ts.value;
		}
#endif
		if (x1 > 0 && y1 > 0)
		{
			printf("(x1,y1) = (%d, %d)\r\n", x1, y1);
			break;
		}
	}

	while (1)
	{
		ret = read(ts_fd, &ts, sizeof(struct input_event)); // 通过read函数存储获取的触控屏信息到ts
		if (ret == -1)
		{
			printf("read event0 data fail!\n");
			return SLIDE_NONE;
		}
#if BLACK_PCB														  // 黑色边框
		if (ts.type == EV_ABS && ts.code == ABS_X && ts.value < 1024) // 获取X轴坐标
		{
			x2 = ts.value * LCD_WIDTH / 1024;
		}
		if (ts.type == EV_ABS && ts.code == ABS_Y && ts.value < 600) // 获取Y轴坐标
		{
			y2 = ts.value * LCD_HIGH / 600;
		}
#else
		if (ts.type == EV_ABS && ts.code == ABS_X && ts.value < LCD_WIDTH) // 获取X轴坐标
		{
			x2 = ts.value;
		}
		if (ts.type == EV_ABS && ts.code == ABS_Y && ts.value < LCD_HIGH) // 获取Y轴坐标
		{
			y2 = ts.value;
		}
#endif
		if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0) // 释放触摸屏动作
		{
			printf("(x2,y2) = (%d, %d)\r\n", x2, y2);
			break;
		}
	}

	printf("(x1,y1) = (%d, %d)\r\n", x1, y1);
	printf("(x2,y2) = (%d, %d)\r\n", x2, y2);
	abs_x = abs(x1 - x2);
	abs_y = abs(y1 - y2);
	if ((x2 <= 0 && y2 <= 0) || (abs_x <= 50 && abs_y <= 50))
	{
		printf("点击屏幕\n");
		mode = SLIDE_TOUCH;
		*x = x1;
		*y = y1;
	}
	else // 获取点击动作释放后的坐标。
	{
		if (abs_x > abs_y) // x轴变化最大，上下滑屏
		{
			if (x2 - x1 > 50) // 向右划屏
			{
				printf("向右滑屏\n");
				mode = SLIDE_RIGHT;
			}
			else if (x1 - x2 > 50) // 向左划屏
			{
				printf("向左滑屏\n");
				mode = SLIDE_LEFT;
			}
		}
		else // y轴变化最大，上下滑屏
		{
			if (y1 - y2 > 50) // 向上划屏
			{
				printf("向上滑屏\n");
				mode = SLIDE_UP;
			}
			else if (y2 - y1 > 50) // 向下划屏
			{
				printf("向下滑屏\n");
				mode = SLIDE_DOWN;
			}
		}
	}
	return mode;
}

/**
 * @brief 关闭触摸屏
 *
 * @return int
 */
int close_touchscreen(void)
{
	return close(ts_fd);
}

// e_slide mode;
// int x, y;
// while (1)
// {
// 	mode = sliding_screen(&x, &y);
// 	if (mode == SLIDE_DOWN)
// 		printf("下滑\r\n");
// 	printf("mode = %d, (%d, %d)\r\n", mode, x, y);
// }