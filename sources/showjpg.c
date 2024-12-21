#include "showjpg.h"

/**
 * @brief 显示一张jpg图片
 *
 * @param jpgpath jpg图片路径
 * @param lcdp lcd映射后的内存
 * @return int
 */
int show_800x480jpg(char *jpgpath, unsigned int *lcdp)
{
	int x, y;
	FILE *jpgp;

	// 定义解压缩结构体变量和处理错误的结构体变量
	struct jpeg_decompress_struct mydem;
	struct jpeg_error_mgr myerr;
	mydem.err = jpeg_std_error(&myerr);
	jpeg_create_decompress(&mydem);

	// 打开你要显示的jpg
	jpgp = fopen(jpgpath, "r");
	if (jpgp == NULL)
	{
		printf("open %s: %s\r\n", jpgpath, strerror(errno));
		return -1;
	}
	// 获取数据源
	jpeg_stdio_src(&mydem, jpgp);
	// 读取jpg的头信息
	jpeg_read_header(&mydem, 1);
	printf("jpeg width: %d\n", mydem.image_width);
	printf("jpeg height: %d\n", mydem.image_height);
	// 开始解压缩
	jpeg_start_decompress(&mydem);
	// 定义一个指针存放一行RGB数值
	unsigned char *rgbbuf = calloc(1, mydem.image_width * 3);
	// 解压缩成功后得到的就是jpg图片的原始RGB数值--》读取并填充到lcd上
	for (y = 0; y < mydem.image_height; y++)
	{
		// 每次循环读取一行RGB
		jpeg_read_scanlines(&mydem, (JSAMPARRAY)&rgbbuf, 1);
		// 填充(写入)到开发板的液晶屏中
		// 将一行RGB--》转化成ARGB
		for (x = 0; x < mydem.image_width; x++)
		{
			*(lcdp + y * 800 + x) = rgbbuf[3 * x] << 16 |
									rgbbuf[3 * x + 1] << 8 |
									rgbbuf[3 * x + 2];
		}
	}
	// 收尾工作
	jpeg_finish_decompress(&mydem);
	jpeg_destroy_decompress(&mydem);
	fclose(jpgp);
	free(rgbbuf);

	return 0;
}

/**
 * @brief 在指定位置显示一张jpg图片
 *
 * @param jpgpath jpg图片路径
 * @param lcdp lcd映射后的内存
 * @param sx x坐标
 * @param sy y坐标
 * @return int
 */
int show_anyjpg_anywhere(char *jpgpath, unsigned int *lcdp, int sx, int sy)
{
	int x, y;
	FILE *jpgp;

	if (sx >= 800 || sy >= 480)
		return -1;
	sx = sx > 0 ? sx : 0;
	sy = sy > 0 ? sy : 0;

	// 定义解压缩结构体变量和处理错误的结构体变量
	struct jpeg_decompress_struct mydem;
	struct jpeg_error_mgr myerr;
	mydem.err = jpeg_std_error(&myerr);
	jpeg_create_decompress(&mydem);

	// 打开你要显示的jpg
	jpgp = fopen(jpgpath, "r");
	if (jpgp == NULL)
	{
		printf("open %s: %s\r\n", jpgpath, strerror(errno));
		return -1;
	}

	// 获取数据源
	jpeg_stdio_src(&mydem, jpgp);
	// 读取jpg的头信息
	jpeg_read_header(&mydem, 1);
	printf("jpeg width: %d\n", mydem.image_width);
	printf("jpeg height: %d\n", mydem.image_height);
	// 开始解压缩
	jpeg_start_decompress(&mydem);
	// 定义一个指针存放一行RGB数值
	unsigned char *rgbbuf = calloc(1, mydem.image_width * 3);
	// 解压缩成功后得到的就是jpg图片的原始RGB数值--》读取并填充到lcd上
	for (y = 0; y < mydem.image_height; y++)
	{
		// 每次循环读取一行RGB
		jpeg_read_scanlines(&mydem, (JSAMPARRAY)&rgbbuf, 1);
		// 填充(写入)到开发板的液晶屏中
		// 将一行RGB--》转化成ARGB
		for (x = 0; x < mydem.image_width; x++)
		{
			if (sy + y < 480 && sx + x < 800)
			{
				*(lcdp + (sy + y) * 800 + sx + x) = rgbbuf[3 * x] << 16 |
													rgbbuf[3 * x + 1] << 8 |
													rgbbuf[3 * x + 2];
			}
		}
	}
	// 收尾工作
	jpeg_finish_decompress(&mydem);
	jpeg_destroy_decompress(&mydem);
	fclose(jpgp);
	free(rgbbuf);

	return 0;
}

// // show_24bmp("./kunkun.bmp", lcdp);
// // show_24bmp_reduce("./kunkun.bmp", lcdp, 4);
// show_any24bmp_anywhere("./kunkun.bmp", lcdp, 200, 100);
// show_800x480jpg(argv[1], lcdp); // 显示jpeg
// show_anyjpg_anywhere(argv[1], lcdp, 40, 20);