#include "localweather.h"

font_t weather_info =
    {
        480,                     // 画板宽
        80,                      // 画板的高
        getColor(0, 85, 85, 85), // 画板颜色getColor(0, 0, 0, 255)
        80,                      // 画板显示位置X
        0,                       // 画板显示位置Y

        0,                          // 字体位置x
        10,                         // 字体位置y
        getColor(0, 255, 255, 255), // 字体getColor(0, 0, 0, 255)
        460,                        // 一行显示字体的最大宽度
};

/**
 * @brief 从文件中获取天气数据
 *
 * @return char* 指向天气数据字符串的指针
 */
char *get_weather()
{
    char read_buf[1024] = {0}; // 保存从文件中读取的数据
    int fd = open("./txt/weather.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("查询天气出错");
        return NULL;
    }

    ssize_t read_size = read(fd, read_buf, sizeof(read_buf) - 1); // 实际读到的数据
    if (read_size > 0)
    {
        read_buf[read_size] = '\0'; // 确保字符串以NULL结尾
    }
    else if (read_size < 0)
    {
        perror("读取天气数据失败");
        close(fd);
        return NULL;
    }

    close(fd); // 关闭文件描述符

    // 为天气数据分配内存
    char *weather_data = (char *)malloc(strlen(read_buf) + 1);
    if (weather_data == NULL)
    {
        perror("内存分配失败");
        return NULL;
    }
    strcpy(weather_data, read_buf);

    return weather_data;
}

/**
 * @brief LCD显示天气数据
 *
 * @param f 字体
 * @param lcd_mmap 内存映射
 * @return int
 */
int show_weather(unsigned int *lcdp)
{
    char buf[100]; // 写入的内容

    // 获取天气数据
    char *weather_data = get_weather();
    if (weather_data == NULL)
    {
        perror("获取天气数据失败");
        return -1;
    }

    // 将天气数据复制到buf中
    strncpy(buf, weather_data, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0'; // 确保字符串以NULL结尾

    // // 将字体写到点阵图上
    // fontPrint(f, bm, 0, 0, buf, getColor(0, 255, 0, 0), 800);

    // // 把字体框输出到LCD屏幕上
    // show_font_to_lcd(lcd_mmap, 0, 0, bm);

    // 显示天气
    show_font(lcdp, buf, &weather_info, 24);

    return 0;
}