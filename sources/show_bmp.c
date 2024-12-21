#include "show_bmp.h"

int show_24bmp(char *bmppath, unsigned int *lcdp)
{
	bmpfile_head_t filehead;
	bmpbit_head_t bithead;
	FILE *bmpfp = fopen(bmppath, "r");
	if (bmpfp == NULL)
	{
		printf("open %s: %s\r\n", bmppath, strerror(errno));
		return -1;
	}
	fread(&filehead, sizeof(filehead), 1, bmpfp); // bmp文件信息头
	fread(&bithead, sizeof(bithead), 1, bmpfp);	  // bmp位图信息头
#if 0
	// bmp文件信息头
	printf("bfType:%#x\nbfSize:%d\nbfOffBitss:%d\n", filehead.bfType, filehead.bfSize, filehead.bfOffBits);

	// bmp位图信息头
	printf("biWidth:%d\nbiHeight:%d\nbiBitCount:%d\nbiSizeImage:%d\n",
		   bithead.biWidth, bithead.biHeight, bithead.biBitCount, bithead.biSizeImage);
#endif
	if (bithead.biBitCount / 8 != 3)
	{
		printf("The picture is not a 24-bit bmp!!!\r\n");
		fclose(bmpfp);
		return -1;
	}

	unsigned char *data = calloc(bithead.biWidth * 3, 1);
	// 扫描行补充字节数
	int pad = (4 - (bithead.biWidth * 3) % 4) % 4;

	// 读图片像素点的数据，并写入到屏幕文件
	// for (int y = 0; y < bithead.biHeight; y++)
	for (int y = bithead.biHeight - 1; y >= 0; y--) // 解决图片镜像翻转问题
	{
		fread(data, bithead.biWidth * 3, 1, bmpfp); // 读一行的数据
		fseek(bmpfp, pad, SEEK_CUR);				// 往后偏移补充字节数
		for (int x = 0; x < bithead.biWidth; x++)
		{
			// 屏幕内存            = 一个像素的数据
			*(lcdp + y * 800 + x) = (0 << 24) | (data[3 * x + 2] << 16) |
									(data[3 * x + 1] << 8) |
									(data[3 * x] << 0);
		}
	}
	free(data);
	fclose(bmpfp);
	return 0;
}

int show_any24bmp_anywhere(char *bmppath, unsigned int *lcdp, int sx, int sy)
{
	bmpfile_head_t filehead;
	bmpbit_head_t bithead;

	if (sx >= 800 || sy >= 480)
		return -1;
	sx = sx > 0 ? sx : 0;
	sy = sy > 0 ? sy : 0;

	FILE *bmpfp = fopen(bmppath, "r");
	if (bmpfp == NULL)
	{
		printf("open %s: %s\r\n", bmppath, strerror(errno));
		return -1;
	}
	fread(&filehead, sizeof(filehead), 1, bmpfp); // bmp文件信息头
	fread(&bithead, sizeof(bithead), 1, bmpfp);	  // bmp位图信息头
#if 0
	// bmp文件信息头
	printf("bfType:%#x\nbfSize:%d\nbfOffBitss:%d\n", filehead.bfType, filehead.bfSize, filehead.bfOffBits);

	// bmp位图信息头
	printf("biWidth:%d\nbiHeight:%d\nbiBitCount:%d\nbiSizeImage:%d\n",
		   bithead.biWidth, bithead.biHeight, bithead.biBitCount, bithead.biSizeImage);
#endif
	if (bithead.biBitCount / 8 != 3)
	{
		printf("The picture is not a 24-bit bmp!!!\r\n");
		fclose(bmpfp);
		return -1;
	}

	unsigned char *data = calloc(bithead.biWidth * 3, 1);
	// 扫描行补充字节数
	int pad = (4 - (bithead.biWidth * 3) % 4) % 4;

	// 读图片像素点的数据，并写入到屏幕文件
	// for (int y = 0; y < bithead.biHeight; y++)
	for (int y = bithead.biHeight - 1; y >= 0; y--) // 解决图片镜像翻转问题
	{
		fread(data, bithead.biWidth * 3, 1, bmpfp); // 读一行的数据
		fseek(bmpfp, pad, SEEK_CUR);				// 往后偏移补充字节数
		for (int x = 0; x < bithead.biWidth; x++)
		{
			if (sy + y < 480 && sx + x < 800)
			{
				// 屏幕内存            = 一个像素的数据
				*(lcdp + (sy + y) * 800 + (sx + x)) = (0 << 24) | (data[3 * x + 2] << 16) |
													  (data[3 * x + 1] << 8) |
													  (data[3 * x] << 0);
			}
		}
	}
	free(data);
	fclose(bmpfp);
	return 0;
}

// reducex 缩小倍数1 、 4 、 9 、 16
int show_24bmp_reduce(char *bmppath, unsigned int *lcdp, int reducex)
{
	bmpfile_head_t filehead;
	bmpbit_head_t bithead;
	int reduce = sqrt(reducex); // 缩小倍数4
	if (reduce <= 0)
		reduce = 1;
	FILE *bmpfp = fopen(bmppath, "r");
	if (bmpfp == NULL)
	{
		printf("open %s: %s\r\n", bmppath, strerror(errno));
		return -1;
	}
	fread(&filehead, sizeof(filehead), 1, bmpfp); // bmp文件信息头
	fread(&bithead, sizeof(bithead), 1, bmpfp);	  // bmp位图信息头

	if (bithead.biBitCount / 8 != 3)
	{
		printf("The picture is not a 24-bit bmp!!!\r\n");
		fclose(bmpfp);
		return -1;
	}

	unsigned char *data = calloc(bithead.biWidth * 3, 1);
	// 扫描行补充字节数
	int pad = (4 - (bithead.biWidth * 3) % 4) % 4;

	// 读图片像素点的数据，并写入到屏幕文件
	for (int y = bithead.biHeight - 1; y >= 0; y--) // 解决图片镜像翻转问题
	{
		fread(data, bithead.biWidth * 3, 1, bmpfp); // 读一行的数据
		fseek(bmpfp, pad, SEEK_CUR);				// 往后偏移补充字节数
		for (int x = 0; x < bithead.biWidth; x++)
		{
			if (x % reduce == 0 && y % reduce == 0)
			{
				// 屏幕内存            = 一个像素的数据
				*(lcdp + (y / reduce) * 800 + x / reduce) = (0 << 24) | (data[3 * x + 2] << 16) |
															(data[3 * x + 1] << 8) |
															(data[3 * x] << 0);
			}
		}
	}
	free(data);
	fclose(bmpfp);
	return 0;
}


