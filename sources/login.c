#include "login.h"

char *sys_account = "123456"; // 系统账号
char *sys_passwd = "123456";  // 系统密码

// 账号画板
font_t accountfont_info =
	{
		180,						// 画板宽
		40,							// 画板的高
		getColor(0, 246, 250, 253), // 画板颜色getColor(0, 0, 0, 255)
		160,						// 画板显示位置x
		160,						// 画板显示位置y

		0,						// 字体位置x
		0,						// 字体位置y
		getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
		180,					// 一行显示字体的最大宽度
};

// 密码画板
font_t passwdfont_info =
	{
		180,						// 画板宽
		40,							// 画板的高
		getColor(0, 246, 250, 253), // 画板颜色getColor(0, 0, 0, 255)
		160,						// 画板显示位置x
		220,						// 画板显示位置y

		0,						// 字体位置x
		0,						// 字体位置y
		getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
		180,					// 一行显示字体的最大宽度
};

/**
 * @brief 取得键值
 *
 * @param x x坐标
 * @param y y坐标
 * @return int
 */
int get_key(int x, int y)
{
	if (x >= 445 && x < 620 && y >= 320 && y < 395) // 0
	{
		return 0;
	}

	else if (x >= 445 && x < 530 && y >= 80 && y < 155) // 1
	{
		return 1;
	}

	else if (x >= 535 && x < 620 && y >= 80 && y < 155) // 2
	{
		return 2;
	}
	else if (x >= 625 && x < 705 && y >= 80 && y < 155) // 3
	{
		return 3;
	}
	else if (x >= 445 && x < 530 && y >= 160 && y < 235) // 4
	{
		return 4;
	}
	else if (x >= 535 && x < 620 && y >= 160 && y < 235) // 5
	{
		return 5;
	}
	else if (x >= 625 && x < 705 && y >= 160 && y < 235) // 6
	{
		return 6;
	}
	else if (x >= 445 && x < 530 && y >= 240 && y < 315) // 7
	{
		return 7;
	}
	else if (x >= 535 && x < 620 && y >= 240 && y < 315) // 8
	{
		return 8;
	}
	else if (x >= 625 && x < 705 && y >= 240 && y < 315) // 9
	{
		return 9;
	}

	else if (x >= 625 && x < 705 && y >= 320 && y < 395) // 删除
	{
		return 10;
	}
	else if (x >= 80 && x < 360 && y >= 275 && y < 325) // 确认
	{
		return 11;
	}
	else
	{
		return -1;
	}
}

/**
 * @brief 登录
 *
 * @param lcdp 内存映射
 */
void login(unsigned int *lcdp)
{
	int flag = 0; // 0:从键盘获取的是账号的信息，1：从键盘获取的是密码的信息
	// 登录主页面
	show_800x480jpg("./image/UI/login.jpg", lcdp);

	// 处理输入信息
	char account[10] = {0};
	int account_index = -1;

	char passwd[10] = {0};
	int passwd_index = -1;

	char password[10] = {0}; // 存*

	e_slide mode;
	int x, y;
	int key = -1;
	while (1)
	{
		mode = sliding_screen(&x, &y);
		if (mode == SLIDE_TOUCH) // 点了触摸屏
		{
			if (x > 130 && x < 360 && y > 155 && y < 205) // 获取的是账号
			{
				flag = 0;
			}
			if (x > 155 && x < 360 && y > 215 && y < 260) // 获取的是密码
			{
				flag = 1;
			}

			key = get_key(x, y);
			if (key >= 0 && key <= 9) // 键盘输入
			{
				if (flag == 0 && account_index < (int)(sizeof(account) - 2)) // account_index < sizeof(account) - 2不能越界
				{
					account[++account_index] = key + '0';
					show_font(lcdp, account, &accountfont_info, 48);
				}
				else if (flag == 1 && passwd_index < (int)(sizeof(passwd) - 2))
				{
					passwd[++passwd_index] = key + '0';
					password[passwd_index] = '*';
					show_font(lcdp, password, &passwdfont_info, 48);
				}
			}

			if (key == 10) // 键盘删除
			{
				if (flag == 0 && account_index >= 0)
				{
					account[account_index] = '\0';
					account_index--;
					show_font(lcdp, account, &accountfont_info, 48);
				}
				else if (flag == 1 && passwd_index >= 0)
				{
					passwd[passwd_index] = '\0';
					password[passwd_index] = '\0';
					passwd_index--;
					show_font(lcdp, password, &passwdfont_info, 48);
				}
			}

			if (key == 11) // 键盘确认
			{
				if (strcmp(sys_account, account) == 0 && strcmp(sys_passwd, passwd) == 0)
				{
					printf("===========登录成功============\r\n");
					break;
				}
			}
		}
	}
}