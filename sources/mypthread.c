#include "mypthread.h"

// 定义一个互斥锁（mutex）用于控制线程的暂停和恢复，初始化为PTHREAD_MUTEX_INITIALIZER。
pthread_mutex_t pause_mutex = PTHREAD_MUTEX_INITIALIZER;

// 定义一个条件变量（condition variable）用于线程间的同步，初始化为PTHREAD_COND_INITIALIZER。
pthread_cond_t pause_cond = PTHREAD_COND_INITIALIZER;

// 定义一个整型变量paused，用于表示线程是否应该暂停（1表示暂停，0表示运行）。
int paused = 0;

font_t time_info =
    {
        240,                        // 画板宽
        160,                        // 画板的高
        getColor(0, 207, 235, 246), // 画板颜色getColor(0, 0, 0, 255)
        560,                        // 画板显示位置X
        80,                         // 画板显示位置Y

        10,                     // 字体位置x
        0,                      // 字体位置y
        getColor(0, 255, 0, 0), // 字体getColor(0, 0, 0, 255)
        240,                    // 一行显示字体的最大宽度
};

/**
 * 暂停线程的函数。
 * 该函数通过锁定互斥锁来确保对paused变量的访问是线程安全的，然后设置paused为1，表示线程应该暂停。
 */
void pause_threads()
{
    // 锁定互斥锁，确保对paused变量的修改是原子操作。
    pthread_mutex_lock(&pause_mutex);
    // 设置paused为1，指示线程应该暂停。
    paused = 1;
    // 解锁互斥锁。
    pthread_mutex_unlock(&pause_mutex);
}

/**
 * 恢复线程的函数。
 * 该函数通过锁定互斥锁来确保对paused变量的访问是线程安全的，然后设置paused为0，表示线程可以恢复运行。
 * 接着使用条件变量广播通知所有等待的线程，最后解锁互斥锁。
 */
void resume_threads()
{
    // 锁定互斥锁，确保对paused变量的修改是原子操作。
    pthread_mutex_lock(&pause_mutex);
    // 设置paused为0，指示线程可以恢复运行。
    paused = 0;
    // 使用条件变量广播通知所有等待的线程，它们可以检查paused变量并继续执行。
    pthread_cond_broadcast(&pause_cond);
    // 解锁互斥锁。
    pthread_mutex_unlock(&pause_mutex);
}

/**
 * @brief 以线程形式显示广告
 *
 * @param arg 线程的形参
 * @return void*
 */
void *show_adverts(void *arg)
{
    char *adverts_path = malloc(256);
    unsigned int *lcdp = (unsigned int *)arg;

    int i = 0;
    do
    {
        pthread_mutex_lock(&pause_mutex);
        while (paused)
        {
            pthread_cond_wait(&pause_cond, &pause_mutex);
        }
        pthread_mutex_unlock(&pause_mutex);

        if (i == 3)
        {
            i = 0;
        }
        snprintf(adverts_path, 256, "./image/Advertisement/%d.jpg", i);
        show_anyjpg_anywhere(adverts_path, lcdp, 0, 120);
        sleep(2);
        i++;
    } while (i < 4);
    free(adverts_path);
}

/**
 * @brief 以线程形式显示时间
 *
 * @param arg 线程的形参
 * @return void*
 */
void *show_time(void *arg)
{
    char datetime_str[256];
    struct tm date;
    unsigned int *lcdp = (unsigned int *)arg;
    while (1)
    {
        pthread_mutex_lock(&pause_mutex);
        while (paused)
        {
            pthread_cond_wait(&pause_cond, &pause_mutex);
        }
        pthread_mutex_unlock(&pause_mutex);

        // 获取当前时间
        get_time(&date);

        int year, month, day, hour, min, sec, wday;
        // 年月日拼成字符串,格式为year/month/day
        year = date.tm_year + 1900;
        month = date.tm_mon + 1;
        day = date.tm_mday;
        // 时分秒拼成字符串,格式为hour/min/sec
        hour = date.tm_hour;
        min = date.tm_min;
        sec = date.tm_sec;
        wday = date.tm_wday;

        // 将年月日时分秒拼成字符串
        // 格式为 year/month/day hour:min:sec
        snprintf(datetime_str, sizeof(datetime_str), "%d/%02d/%02d \n%02d:%02d:%02d\n星期%d", year, month, day, hour, min, sec, wday);

        // 显示时间
        show_font(lcdp, datetime_str, &time_info, 48);
        // 一秒一秒刷新
        sleep(1);
    }
}