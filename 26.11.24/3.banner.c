#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

// 实现4张图片循环显示，本文件需要编译 2.read_bmp_func.c 和 3.banner.c

// #define img_src "./成都熊猫基地.bmp" // 要读取的图片路径
#define SCREEN_SIZE (1024 * 600) // 显示屏大小
// #define CONNECT(a, b) a##b       // 变量名递增, 后面换成数组了，这个变量名拼接不用了

int *map;     // 内存映射
extern int w; // 图片宽高
extern int h; // 图片宽高

// 导入函数，输入图片路径，返回图片缓冲区数据 【ARGB】    任意图片尺寸都可以
int *read_bmp_func(char *img_src);

// 显示图片到指定位置
void show_image_to_location(img_buf, x, y)
{
    // 1. 打开文件 (液晶屏和图片)
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open fail");
        return -1;
    }

    // 因为图片的buf, 和lcd显示屏要渲染的1024*600的buf大小不一致, 所以要想办法把图片的buf 在 指定 x,y 写入 1024*600的buf中
    // 2个方法,
    // 1. 用 26.11.23的 6.center_box_demo 方法, 用边界交替写入, 这样屏幕的其他位置需要写入数据
    // 2. 在指定的x y, 开始写入图片buf的行, 并在 x加屏幕宽度的像素可以移动到下一行x
    // 不写入屏幕的其他像素, 只在屏幕的某个位置写入小图片

    // 2. 建立一个1024*600*4的内存映射, 返回其基地址
    map = mmap(NULL, SCREEN_SIZE * 4, PROT_WRITE, MAP_SHARED, lcd_fd, 0);

    // 3. 定义一个新的指针, 指向要开始写入的位置
    int *p = map + 1024 * y + x; // 移动指针p, 一行有 1024个像素点 * y行 + x列;  指针在map中指向要写入的坐标
    // 在内存映射的指定位置开始写入小图片
    // 循环遍历小图片的buf, 即位要写入的次数, 每一次写入一行, 结束跨下一行
    for (int i = 0; i < h; i++) // 行, 即图片的高度
    {
        for (int j = 0; j < w; j++) // 列, 即图片的宽度
        {
            // lcd一行有1024个像素, image一行有w个像素
            p[1024 * i + j] = img_buf[w * i + j]
        }
    }
}

int main(int argc, char const *argv[])
{

    // 图片转file_buf, 用数组存储每一张图片的地址
    // int *images[4];
    // images[0] = read_bmp_func("./成都熊猫基地.bmp");
    // images[1] = read_bmp_func("./北京飞广州.bmp");
    // images[2] = read_bmp_func("./重庆魁星楼.bmp");
    // images[3] = read_bmp_func("./汕尾海丰.bmp");

    // int *image_buf = read_bmp_func("./成都熊猫基地.bmp");

    // int i = 0;
    // while (1)
    // {
    //     // 写入虚拟内存
    //     memcpy(map, images[i], SCREEN_SIZE * 4); // 任意大小任意位置只需要 改写入的方式而已
    //     sleep(2.5);
    //     i = (i + 1) % 4; // 循环i
    // }

    close(lcd_fd); // 关闭文件
    // 释放 read_bmp_func 函数申请的空间
    // for (int i = 0; i < 4; i++)
    // {
    //     free(images[i]);
    // }
    munmap(map, 1024 * 600 * 4); // 解除内存映射
    return 0;
}