#ifndef __MYPTHREAD_H__
#define __MYPTHREAD_H__

#include <pthread.h>
#include "showfont.h"
#include "localtime.h"
#include "showjpg.h"
#include "adverts.h"

/**
 * 暂停线程的函数。
 * 该函数通过锁定互斥锁来确保对paused变量的访问是线程安全的，然后设置paused为1，表示线程应该暂停。
 */
void pause_threads();

/**
 * 恢复线程的函数。
 * 该函数通过锁定互斥锁来确保对paused变量的访问是线程安全的，然后设置paused为0，表示线程可以恢复运行。
 * 接着使用条件变量广播通知所有等待的线程，最后解锁互斥锁。
 */
void resume_threads();

/**
 * @brief 以线程形式显示广告
 *
 * @param arg 线程的形参
 * @return void*
 */
void *show_adverts(void *arg);

/**
 * @brief 以线程形式显示时间
 *
 * @param arg 线程的形参
 * @return void*
 */
void *show_time(void *arg);

#endif