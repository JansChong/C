#include <stdio.h>
#include <unistd.h> // close  read
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> // strerror
#include <errno.h>  // 全局错误码声明所在的头文件
#include <sys/mman.h>

int main(int argc, char const *argv[])
{

    // 将4.色盲检测的代码改为内存映射模式
    
    
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
    int black = 0x0000ff00;
    int yellow = 0x00ffff00;

    // 先准备1024*600这么大的颜色数据
    int black_buf[1024 * 600] = {0};
    int red_buf[1024 * 600] = {0};
    int yellow_buf[1024 * 600] = {0};

    // 用循环把数据缓冲区存满
    for (int i = 0; i < 1024 * 600; i++)
    {
        black_buf[i] = black;
        red_buf[i] = red;
        yellow_buf[i] = yellow;
    }

    // 4. 建立内存映射, 返回映射的虚拟内存的基地址
    int *map_p = (int *)mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    // 报错处理
    if (map_p == MAP_FAILED)
    {
        perror("映射失败");
        return -1;
    }

    // 循环将颜色数组 写入 虚拟内存， 用strcpy
    while (1)
    {
        // 头文件
        // #include <string.h>
        // 函数原型
        // void *memcpy(void *dest, const void *src, size_t n);
        // memcpy() 用来拷贝 src 所指的内存内容前 n 个字节到 dest 所指的内存地址上。

        memcpy(map_p, black_buf, 1024 * 600 * 4);
        sleep(1);
        lseek(lcd_fd, 0, SEEK_SET);

        memcpy(map_p, red_buf, 1024 * 600 * 4);
        sleep(1);
        lseek(lcd_fd, 0, SEEK_SET);

        memcpy(map_p, yellow_buf, 1024 * 600 * 4);
        sleep(1);
        lseek(lcd_fd, 0, SEEK_SET);
    }

    // 解除内存映射
    munmap(map_p, 1024 * 600 * 4);
    close(lcd_fd);
    return 0;
}
