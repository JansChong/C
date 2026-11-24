#include "utils.h"

int main(int argc, char const *argv[])
{

    int *images[3];

    int i = 0;
    while (1)
    {
        // 写入虚拟内存
        images[0] = read_bmp_func("./颜色.bmp");
        show_image_to_location(images[0], 0, 0); // 任意大小任意位置只需要 改写入的方式而已
        sleep(2.5);

        images[1] = read_bmp_func("./光轨.bmp");
        show_image_to_location(images[1], 0, 0); // 任意大小任意位置只需要 改写入的方式而已
        sleep(2.5);

        images[2] = read_bmp_func("./迷宫.bmp");
        show_image_to_location(images[2], 0, 0); // 任意大小任意位置只需要 改写入的方式而已
        sleep(2.5);
        i = (i + 1) % 3; // 循环i
    }

    // 释放 read_bmp_func 函数申请的空间
    for (int i = 0; i < 3; i++)
    {
        free(images[i]);
    }

    return 0;

#if 0
    // 调用函数, 兑换4个 img_buf
    int *images[4];
    images[0] = read_bmp_func("./成都熊猫基地.bmp");
    images[1] = read_bmp_func("./北京飞广州.bmp");
    images[2] = read_bmp_func("./重庆魁星楼.bmp");
    images[3] = read_bmp_func("./汕尾海丰.bmp");
    

    int i = 0;
    while (1)
    {
        // 写入虚拟内存
        show_image_to_location(images[i], 0, 0); // 任意大小任意位置只需要 改写入的方式而已
        sleep(2.5);
        i = (i + 1) % 4; // 循环i
    }

    // 释放 read_bmp_func 函数申请的空间
    for (int i = 0; i < 4; i++)
    {
        free(images[i]);
    }
    
    return 0;

#endif
}