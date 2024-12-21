#include "localtime.h"

// font_t time_info =
//     {
//         240,                        // 画板宽
//         160,                        // 画板的高
//         getColor(0, 207, 235, 246), // 画板颜色getColor(0, 0, 0, 255)
//         560,                        // 画板显示位置X
//         80,                         // 画板显示位置Y

//         10,                     // 字体位置x
//         0,                      // 字体位置y
//         getColor(0, 255, 0, 0), // 字体getColor(0, 0, 0, 255)
//         240,                    // 一行显示字体的最大宽度
// };

/**
 * @brief 取得时间戳
 *
 * @param date date结构体指针
 * @return int
 */
int get_time(struct tm *date)
{
    time_t tloc;
    time(&tloc); // 获得时间戳
    if (tloc == -1)
    {
        perror("time");
        return 1;
    }
    *date = *gmtime(&tloc); // 转换为UTC时间并复制到date
    return 0;
}

// void *show_time(void *arg)
// {
//     char datetime_str[256];
//     struct tm date;
//     unsigned int *lcdp = (unsigned int *)arg;
//     while (1)
//     {
//         pthread_mutex_lock(&pause_mutex);
//         while (paused)
//         {
//             pthread_cond_wait(&pause_cond, &pause_mutex);
//         }
//         pthread_mutex_unlock(&pause_mutex);

//         // 获取当前时间
//         get_time(&date);

//         int year, month, day, hour, min, sec, wday;
//         // 年月日拼成字符串,格式为year/month/day
//         year = date.tm_year + 1900;
//         month = date.tm_mon + 1;
//         day = date.tm_mday;
//         // 时分秒拼成字符串,格式为hour/min/sec
//         hour = date.tm_hour;
//         min = date.tm_min;
//         sec = date.tm_sec;
//         wday = date.tm_wday;

//         // 将年月日时分秒拼成字符串
//         // 格式为 year/month/day hour:min:sec
//         snprintf(datetime_str, sizeof(datetime_str), "%d/%02d/%02d \n%02d:%02d:%02d\n星期%d", year, month, day, hour, min, sec, wday);

//         // 显示时间
//         show_font(lcdp, datetime_str, &time_info, 48);
//         // 一秒一秒刷新
//         sleep(1);
//     }
// }

// void *show_time(void *lcdp)
// {
//     char datetime_str[256];
//     struct tm date;
//     int fd = *((int *)lcdp);
//     while (1)
//     {
//         // 获取当前时间
//         get_time(&date);

//         int year, month, day, hour, min, sec, wday;
//         // 年月日拼成字符串,格式为year/month/day
//         year = date.tm_year + 1900;
//         month = date.tm_mon + 1;
//         day = date.tm_mday;
//         // 时分秒拼成字符串,格式为hour/min/sec
//         hour = date.tm_hour;
//         min = date.tm_min;
//         sec = date.tm_sec;
//         wday = date.tm_wday;

//         // 将年月日时分秒拼成字符串
//         // 格式为 year/month/day hour:min:sec
//         snprintf(datetime_str, sizeof(datetime_str), "%d/%02d/%02d \n%02d:%02d:%02d\n星期%d", year, month, day, hour, min, sec, wday);

//         // 显示时间
//         show_font(lcdp, datetime_str, &time_info, 48);
//         // 一秒一秒刷新
//         sleep(1);
//     }
// }