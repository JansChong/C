#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if 0
#include <sys/mman.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

#endif

int main(int argc, char const *argv[])
{

    // 在开发板屏幕的正中心显示一个边长100的红色正方形  tips: 晚上的练习：-450  +550

    // 1.打开lcd显示屏
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open fail");
        return -1;
    }

    // 2.准备颜色数据
    // 颜色数据： 0xARBG
    int red = 0x00ff0000;
    int green = 0x0000ff00;
    int yellow = 0x00ffff00;
    int black = 0x00000000;
    int white = 0x00ffffff;

    // 3. 内存映射, 返回申请的虚拟空间首地址， 映射失败返回MAP_FAILED(-1),
    // 定义 int * 类型的地址， 地址一次偏移4字节， char *只能偏移1字节， 这里一个屏幕像素点4字节
    int *map_p = (int *)mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);

    // 报错处理
    if (map_p == MAP_FAILED)
    {
        perror("映射失败");
        return -1;
    }

    // int 地址递增
    // int count;
    // 考虑到屏幕的规律，屏幕中的每一个像素点的位置为： 1024*i+j;  可以用来替换count

    // 水平起始地址： 1024/2 - 50  + 50
    // 垂直起始地址： 600/2 - 50 + 50
    for (int i = 0; i < 600; i++) // 行
    {
        for (int j = 0; j < 1024; j++) // 列
        {

            // 中间区域
            if (j >= 1024 / 2 - 50 && j <= 1024 / 2 + 50 && i >= 600 / 2 - 50 && i <= 600 / 2 + 50)
            {
                // map_p[count++] = red;
                map_p[1024*i+j] = red;
            }
            // 区域之外
            else
            {
                // 全白
                map_p[1024*i+j] = white;
            }
        }
    }

    // 5. 解除内存映射
    munmap(map_p, 1024 * 600 * 4);
    return 0;
}