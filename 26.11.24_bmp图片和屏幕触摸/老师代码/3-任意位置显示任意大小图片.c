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
    map_p = (int *)mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
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

int show_bmp(char *pathname, int star_x, int star_y)
{
    // 打开图片
    int bmp_fd = open(pathname, O_RDWR);
    if (bmp_fd == -1)
    {
        perror("open bmp failed\n");
        return -1;
    }

    // 2.读取bmp文件的数据
    char bmp_head[54];
    read(bmp_fd, bmp_head, 54);
    int *width = (int *)(bmp_head + 18);
    int *high = (int *)(bmp_head + 22);
    int w = *width;
    int h = *high;
    printf("w = %d\n", w);
    printf("h = %d\n", h);

    char bmp_buf[w * h * 3];

    read(bmp_fd, bmp_buf, w * h * 3);

    // 数据处理  BGR->ARGB
    int lcd_buf[w * h];
    int x, y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            lcd_buf[w * (h - 1 - y) + x] = bmp_buf[3 * (w * y + x)] | bmp_buf[3 * (w * y + x) + 1] << 8 | bmp_buf[3 * (w * y + x) + 2] << 16 | 0x00 << 24;
        }
    }

    int *p = map_p + 1024 * star_y + star_x;

    for (y = 0; y < h; y++)
    {

        for (x = 0; x < w; x++)
        {
            p[1024 * y + x] = lcd_buf[w * y + x];
        }
    }

    // 4.关闭文件
    close(bmp_fd);
    return 0;
}

int main()
{
    lcd_int();

    show_bmp("./2.bmp", 200, 200);
    lcd_close();

    return 0;
}