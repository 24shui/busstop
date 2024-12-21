#include "inquiries.h"

// 查询画板
font_t inquiries_font_info =
    {
        320,                        // 画板宽
        40,                         // 画板的高
        getColor(0, 197, 197, 197), // 画板颜色getColor(0, 0, 0, 255)
        200,                        // 画板显示位置x
        40,                         // 画板显示位置y

        0,                      // 字体位置x
        0,                      // 字体位置y
        getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
        320,                    // 一行显示字体的最大宽度
};

// 线路
font_t busline_font_info =
    {
        240,                        // 画板宽
        40,                         // 画板的高
        getColor(0, 206, 228, 179), // 画板颜色getColor(0, 0, 0, 255)
        40,                         // 画板显示位置x
        120,                        // 画板显示位置y

        0,                      // 字体位置x
        0,                      // 字体位置y
        getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
        240,                    // 一行显示字体的最大宽度
};

// 定位
font_t buslocate_font_info =
    {
        240,                        // 画板宽
        40,                         // 画板的高
        getColor(0, 206, 228, 179), // 画板颜色getColor(0, 0, 0, 255)
        40,                         // 画板显示位置x
        160,                        // 画板显示位置y

        0,                      // 字体位置x
        0,                      // 字体位置y
        getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
        240,                    // 一行显示字体的最大宽度
};

// 首发
font_t first_departure_font_info =
    {
        240,                        // 画板宽
        40,                         // 画板的高
        getColor(0, 206, 228, 179), // 画板颜色getColor(0, 0, 0, 255)
        40,                         // 画板显示位置x
        200,                        // 画板显示位置y

        0,                      // 字体位置x
        0,                      // 字体位置y
        getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
        240,                    // 一行显示字体的最大宽度
};

// 末班
font_t last_departure_font_info =
    {
        240,                        // 画板宽
        40,                         // 画板的高
        getColor(0, 206, 228, 179), // 画板颜色getColor(0, 0, 0, 255)
        40,                         // 画板显示位置x
        240,                        // 画板显示位置y

        0,                      // 字体位置x
        0,                      // 字体位置y
        getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
        240,                    // 一行显示字体的最大宽度
};

// 站点
font_t stationshead_font_info =
    {
        240,                        // 画板宽
        40,                         // 画板的高
        getColor(0, 206, 228, 179), // 画板颜色getColor(0, 0, 0, 255)
        360,                        // 画板显示位置x
        120,                        // 画板显示位置y

        0,                      // 字体位置x
        0,                      // 字体位置y
        getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
        240,                    // 一行显示字体的最大宽度
};

// 站点信息
font_t stationsMsg_font_info =
    {
        400,                        // 画板宽
        240,                        // 画板的高
        getColor(0, 206, 228, 179), // 画板颜色getColor(0, 0, 0, 255)
        360,                        // 画板显示位置x
        160,                        // 画板显示位置y

        0,                      // 字体位置x
        0,                      // 字体位置y
        getColor(255, 0, 0, 0), // 字体getColor(0, 0, 0, 255)
        400,                    // 一行显示字体的最大宽度
};

/**
 * @brief 获取点击事件并赋予标志位
 *
 * @param x x轴坐标
 * @param y y轴坐标
 * @return int
 */
int pick_key(int x, int y)
{
    if (x >= 80 && x < 160 && y >= 120 && y < 200) // 0
    {
        return 0;
    }

    else if (x >= 200 && x < 280 && y >= 120 && y < 200) // 1
    {
        return 1;
    }

    else if (x >= 320 && x < 400 && y >= 120 && y < 200) // 2
    {
        return 2;
    }
    else if (x >= 440 && x < 520 && y >= 120 && y < 200) // 3
    {
        return 3;
    }
    else if (x >= 200 && x < 280 && y >= 240 && y < 320) // 4
    {
        return 4;
    }
    else if (x >= 320 && x < 400 && y >= 240 && y < 320) // 5
    {
        return 5;
    }
    else if (x >= 440 && x < 520 && y >= 240 && y < 320) // 6
    {
        return 6;
    }
    else if (x >= 200 && x < 280 && y >= 360 && y < 440) // 7
    {
        return 7;
    }
    else if (x >= 320 && x < 400 && y >= 360 && y < 440) // 8
    {
        return 8;
    }
    else if (x >= 440 && x < 520 && y >= 360 && y < 440) // 9
    {
        return 9;
    }

    else if (x >= 560 && x < 640 && y >= 120 && y < 200) // 删除
    {
        return 10;
    }
    else if (x >= 560 && x < 640 && y >= 240 && y < 320) // 确认
    {
        return 11;
    }
    else if (x >= 680 && x < 800 && y >= 400 && y < 480) // 退出
    {
        return 12;
    }
    else if (x >= 0 && x < 120 && y >= 0 && y < 80) // 返回
    {
        return 13;
    }
    else
    {
        return -1;
    }
}

/**
 * @brief 屏幕虚拟键盘输入公交线路号
 *
 * @param lcdp 内存映射
 */
void bus_input(unsigned int *lcdp)
{
    int flag = 0; // 0:从键盘获取的是账号的信息，1：从键盘获取的是密码的信息
    // 登录主页面
    show_800x480jpg("./image/UI/businquiries.jpg", lcdp);

    // 处理输入信息
    char lines[10] = {0};
    char output[105];
    int lines_index = -1;

    e_slide mode;
    int x, y;
    int key = -1;
    while (1)
    {
        mode = sliding_screen(&x, &y);
        if (mode == SLIDE_TOUCH) // 点了触摸屏
        {
            if (x > 200 && x < 520 && y > 40 && y < 80) // 点击输入框
            {
                flag = 0;
            }

            key = pick_key(x, y);
            if (key >= 0 && key <= 9) // 键盘输入
            {
                if (flag == 0 && lines_index < (int)(sizeof(lines) - 2)) // lines_index < sizeof(lines) - 2不能越界
                {
                    lines[++lines_index] = key + '0';
                    show_font(lcdp, lines, &inquiries_font_info, 40);
                }
            }

            if (key == 10) // 键盘删除
            {
                if (flag == 0 && lines_index >= 0)
                {
                    lines[lines_index] = '\0';
                    lines_index--;
                    show_font(lcdp, lines, &inquiries_font_info, 40);
                }
            }
            else if (key == 11)
            {
                snprintf(output, sizeof(output), "从%s", lines);
                bus_quiries(output, lcdp);
                show_800x480jpg("./image/UI/buslinemsg_.jpg", lcdp);
            }
            if (key == 12) // 退出
            {
                break;
            }
            if (key == 13) // 返回
            {
                bus_input(lcdp);
            }
        }
    }
}

/**
 * @brief   根据线路号从文件中读取内容查找
 *
 * @param filename  文件路径
 * @param bus   指向包含公交线路信息的结构体的指针
 * @param line_number   线路号
 * @param lcdp  内存映射
 * @return int
 */
int read_bus_info_from_file(const char *filename, Bus *bus, const char *line_number, unsigned int *lcdp)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("打开文件失败");
        return 0;
    }

    char buffer[MAX_NAME_LENGTH];
    int found = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strncmp(buffer, "车辆信息:", 6) == 0)
        {
            // 检查这一行是否包含用户输入的线路号
            if (strstr(buffer, line_number) != NULL)
            {
                found = 1;
                // 提取车辆编号
                sscanf(buffer, "车辆信息:%s", bus->vehicle_number);
                continue;
            }
        }

        if (!found)
        {
            // show_800x480jpg("./image/UI/notfound.jpg", lcdp);
            continue;
        }
        else
        {
            show_800x480jpg("./image/UI/buslinemsg.jpg", lcdp);
            if (strncmp(buffer, "当前位置:", 6) == 0)
            {
                // 读取当前位置
                sscanf(buffer, "当前位置:%s", bus->current_position);
            }
            else if (strncmp(buffer, "首发:", 4) == 0)
            {
                // 读取首发时间
                sscanf(buffer, "首发:%s", bus->first_departure);
            }
            else if (strncmp(buffer, "末班:", 4) == 0)
            {
                // 读取末班时间
                sscanf(buffer, "末班:%s", bus->last_departure);
            }
            else if (strncmp(buffer, "站点:", 4) == 0)
            {
                // 读取站点信息
                char *token = strtok(buffer + 4, ",");
                bus->num_stops = 0;
                while (token != NULL && bus->num_stops < MAX_STOPS)
                {
                    strncpy(bus->stops[bus->num_stops].name, token, MAX_NAME_LENGTH - 1);
                    bus->stops[bus->num_stops].name[MAX_NAME_LENGTH - 1] = '\0'; // 确保字符串以NULL结尾
                    bus->num_stops++;
                    token = strtok(NULL, ",");
                }
                break; // 读取完站点信息后，跳出循环
            }
        }
    }

    fclose(file);
    return found;
}

/**
 * @brief   在LCD上显示查询到的公交线路信息
 *
 * @param bus   指向包含公交线路信息的结构体的指针
 * @param lcdp  内存映射
 */
void show_bus_info(const Bus *bus, unsigned int *lcdp)
{
    char busline_str[64];         // 线路
    char locate_str[64];          // 定位
    char first_departure_str[64]; // 首发
    char last_departure_str[64];  // 末班
    char stations_str[1024];      // 站点
    char all_stations[1024] = ""; // 假设所有站点名称的总长度不会超过1024字符

    snprintf(busline_str, sizeof(busline_str), "公交线路号: %s", bus->vehicle_number);
    show_font(lcdp, busline_str, &busline_font_info, 36);

    snprintf(locate_str, sizeof(locate_str), "当前位置: %s", bus->current_position);
    show_font(lcdp, locate_str, &buslocate_font_info, 36);

    snprintf(first_departure_str, sizeof(first_departure_str), "首发时间: %s", bus->first_departure);
    show_font(lcdp, first_departure_str, &first_departure_font_info, 36);

    snprintf(last_departure_str, sizeof(last_departure_str), "末班时间: %s", bus->last_departure);
    show_font(lcdp, last_departure_str, &last_departure_font_info, 36);

    printf("站点:\n");
    show_font(lcdp, "站点:", &stationshead_font_info, 36);

    for (int i = 0; i < bus->num_stops; ++i)
    {
        printf("%d. %s\n", i + 1, bus->stops[i].name); // 打印每个站点的名称
        strcat(all_stations, bus->stops[i].name);
        if (i < bus->num_stops - 1)
        {
            strcat(all_stations, "->"); // 在每个站点名称之间添加一个连字符
        }
    }

    show_font(lcdp, all_stations, &stationsMsg_font_info, 24);
}

/**
 * @brief 查询线路信息
 *
 * @param number 线路号
 * @param lcdp 内存映射
 * @return int
 */
int bus_quiries(char number[], unsigned int *lcdp)
{
    char line_number[MAX_NAME_LENGTH];
    Bus bus = {0}; // 初始化Bus结构体，确保所有字符串成员初始化为0

    strcpy(line_number, number);

    if (read_bus_info_from_file("./txt/Bus_information.txt", &bus, line_number, lcdp))
    {
        show_bus_info(&bus, lcdp);
    }
    else
    {
        printf("未找到线路号为 %s 的公交信息\n", line_number);
        show_800x480jpg("./image/UI/notfound.jpg", lcdp);
    }

    return 0;
}
