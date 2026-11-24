#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// 导入函数，输入图片路径，返回图片缓冲区数据 【ARGB】    任意图片尺寸都可以
int *read_bmp_func(char *img_src);

// 显示图片到指定位置
void show_image_to_location(int *img_buf, int x, int y);

// 关闭文件, 解除内存映射
void close_fun();

#endif // !_UTILS_H
