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

    // 3. 内存映射, 返回申请的虚拟空间首地址， 映射失败返回MAP_FAILED(-1),
    // 定义 int * 类型的地址， 地址一次偏移4字节， char *只能偏移1字节， 这里一个屏幕像素点4字节
    int *map_p = (int *)mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);

    // 报错处理
    if (map_p == MAP_FAILED)
    {
        perror("映射失败");
        return -1;
    }

    // 4.将数据放入映射空间
    int i;
    for (i = 0; i < 1024 * 600; i++)
    {
        // 让 int * map_p 偏移,  int * 刚好一次偏移4字节
        // *(map_p + i) = green;

        // 数组和指针可以互相转换
        map_p[i] = green;
    }
    // 使用内存映射和普通write写入相比，效率更高, 可以对比一下 文件5和文件1

    
    // 5. 解除内存映射
    munmap(map_p, 1024 * 600 * 4);
    return 0;
}