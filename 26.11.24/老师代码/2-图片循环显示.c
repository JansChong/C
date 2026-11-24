#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/mman.h>
#include <string.h>

int *map_p;
int lcd_fd;
char *pathname[] = {
    "./1.bmp",
    "./2.bmp",
    "./3.bmp",
    "./4.bmp",
    "./5.bmp"};

int lcd_int()
{
    // 1.打开fb0图片
    lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open fb0 failed\n");
        return -1;
    }

    // 内存映射
    int *map_p = (int *)mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (map_p == MAP_FAILED)
    {
        perror("映射失败");
        return -1;
    }

    return 0;
}

void lcd_close()
{
    munmap(map_p, 1024 * 600 * 4);
    close(lcd_fd);
}

int show_bmp(char *pathname)
{
    // 打开图片
    int bmp_fd = open(pathname, O_RDWR);
    if (bmp_fd == -1)
    {
        perror("open bmp failed\n");
        return -1;
    }

    // 2.读取bmp文件的数据
    char bmp_buf[1024 * 600 * 3];
    lseek(bmp_fd, 54, SEEK_SET);
    read(bmp_fd, bmp_buf, 1024 * 600 * 3);

    // 数据处理  BGR->ARGB
    int lcd_buf[1024 * 600];

    int x, y;
    for (y = 0; y < 600; y++)
    {
        for (x = 0; x < 1024; x++)
        {
            lcd_buf[1024 * (599 - y) + x] = bmp_buf[3 * (1024 * y + x)] | bmp_buf[3 * (1024 * y + x) + 1] << 8 | bmp_buf[3 * (1024 * y + x) + 2] << 16 | 0x00 << 24;
        }
    }

    memcpy(map_p, lcd_buf, 1024 * 600 * 4);

    // 4.关闭文件
    close(bmp_fd);
    return 0;
}

int main()
{
    lcd_int();
    int bmp_num = 0;
    while (1)
    {
        show_bmp(pathname[bmp_num]);
        sleep(1);
        bmp_num++;
        if (bmp_num > 4)
        {
            bmp_num = 0;
        }
    }

    lcd_close();

    return 0;
}