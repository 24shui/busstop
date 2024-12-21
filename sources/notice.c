#include "notice.h"

font_t notice_info =
    {
        640,                        // 画板宽
        80,                         // 画板的高
        getColor(0, 253, 250, 231), // 画板颜色getColor(0, 0, 0, 255)
        60,                         // 画板显示位置X
        400,                        // 画板显示位置Y

        0,                      // 字体位置x
        10,                     // 字体位置y
        getColor(0, 255, 0, 0), // 字体getColor(0, 0, 0, 255)
        1280,                   // 一行显示字体的最大宽度
};

/**
 * @brief 从文件中获取公告数据
 *
 * @return char*    字符串指针，指向公告数据
 */
char *get_notice()
{
    char read_buf[1024] = {0}; // 保存从文件中读取的数据
    int fd = open("./txt/notice.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("查询公告出错");
        return NULL;
    }

    ssize_t read_size = read(fd, read_buf, sizeof(read_buf) - 1); // 实际读到的数据
    if (read_size > 0)
    {
        read_buf[read_size] = '\0'; // 确保字符串以NULL结尾
    }
    else if (read_size < 0)
    {
        perror("读取公告数据失败");
        close(fd);
        return NULL;
    }

    close(fd); // 关闭文件描述符

    // 为公告数据分配内存
    char *notice_data = (char *)malloc(strlen(read_buf) + 1);
    if (notice_data == NULL)
    {
        perror("内存分配失败");
        return NULL;
    }
    strcpy(notice_data, read_buf);

    return notice_data;
}

/**
 * @brief 在显示屏上显示公告
 *
 * @param lcdp  内存映射
 * @return int
 */
int show_notice(unsigned int *lcdp)
{
    char buf[1024]; // 写入的内容

    // 获取公告数据
    char *notice_data = get_notice();
    if (notice_data == NULL)
    {
        perror("获取公告数据失败");
        return -1;
    }

    // 将公告数据复制到buf中
    strncpy(buf, notice_data, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0'; // 确保字符串以NULL结尾

    // 显示公告
    show_font(lcdp, buf, &notice_info, 16);

    // 释放公告数据内存
    free(notice_data);

    return 0;
}