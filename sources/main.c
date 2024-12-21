#include "lcd_mmap.h"
#include "showjpg.h"
#include "show_bmp.h"
#include "touch.h"
#include "showfont.h"
#include "login.h"
#include "adverts.h"
#include "localtime.h"
#include "localweather.h"
#include "notice.h"
#include "inquiries.h"
#include "mypthread.h"

int main()
{
	int fd;
	unsigned int *lcdp = lcdmmap(&fd); // LCD屏幕文件内存映射
	e_slide mode;
	int x, y;
	if (open_touchscreen()) // 打开触摸屏
	{
		unlcd_mmap(fd, lcdp);
		return -1;
	}

	char *poweron_path = malloc(256);
	// 0) 开机动画
	for (int i = 1; i < 32; i++)
	{
		snprintf(poweron_path, 256, "./image/PowerOn/%d.jpg", i);
		show_800x480jpg(poweron_path, lcdp);
		usleep(10000);
	}
	free(poweron_path);

	// 1) 登录
	// show_800x480jpg("./image/UI/login.jpg", lcdp);
	login(lcdp);

	show_800x480jpg("./image/UI/main.jpg", lcdp);

	pthread_t time_thread, adverts_thread; // 创建线程

	pthread_create(&time_thread, NULL, show_time, lcdp);	   // 显示时间
	pthread_create(&adverts_thread, NULL, show_adverts, lcdp); // 显示广告

	while (1)
	{
		// 2) 获取坐标
		// 2)主界面
		show_800x480jpg("./image/UI/main.jpg", lcdp);
		show_weather(lcdp); // 天气
		show_notice(lcdp);	// 公告

		// 3)判断坐标进入不同的功能
		mode = sliding_screen(&x, &y);
		if (mode == SLIDE_TOUCH)
		{
			if (x >= 625 && x < 730 && y >= 275 && y < 365)
			{
				// 公交查询
				pause_threads();
				bus_input(lcdp);
				resume_threads();
			}
			else if (x >= 720 && x < 800 && y >= 0 && y < 80)
			{
				// 退出
				clear_lcd_screen(lcdp);
				break;
			}
		}
	}
	unlcd_mmap(fd, lcdp);
	close_touchscreen(); // 关闭触摸屏
	return 0;
}