#include "utils.h"

int main(int argc, char const *argv[])
{

    // 要显示的图片路径 -- 任意大小
    char *image_src[3] = {"./颜色.bmp", "./光轨.bmp", "./迷宫.bmp"};
    // 要写入LCD显示屏的坐标
    int location[3][2] = {{230, 100}, {450, 30}, {600, 100}};

    int i = 0;       // 数组下标 (读取图片 和 图片需要显示的位置)
    int *images_buf; // 图片数据缓冲区

    while (1)
    {
        // 调用 自定义函数 返回 图片数据缓冲区
        images_buf = read_bmp_func(image_src[i]);
        // 写入虚拟内存
        show_image_to_location(images_buf, location[i][0], location[i][1]); // 任意图片大小、任意屏幕位置
        sleep(2.5);
        i = (i + 1) % 3; // 循环i
    }

    // 释放 read_bmp_func 函数申请的空间
    for (int i = 0; i < 3; i++)
    {
        free(images_buf);
    }

    return 0;
}