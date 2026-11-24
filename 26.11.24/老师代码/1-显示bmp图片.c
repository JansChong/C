#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
    // 1.打开fb0、bmp图片
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open fb0 failed\n");
        return -1;
    }
    int bmp_fd = open("./1.bmp", O_RDWR);
    if (bmp_fd == -1)
    {
        perror("open bmp failed\n");
        return -1;
    }

    // 内存映射
    int *map_p = (int *)mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (map_p == MAP_FAILED)
    {
        perror("映射失败");
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
    // int n;
    // for (n = 0; n < 1024 * 600; n++)
    // {
    //     lcd_buf[n] = bmp_buf[3 * n] | bmp_buf[3 * n + 1] << 8 | bmp_buf[3 * n + 2] << 16 | 0x00 << 24;
    // }

    /*
     ARGB                  B            G           R          A
    lcd_buf[0]  --->   bmp_buf[0]   bmp_buf[1]  bmp_buf[2]     0x00
    lcd_buf[1]  --->   bmp_buf[3]   bmp_buf[4]  bmp_buf[5]     0x00
    lcd_buf[2]  --->   bmp_buf[6]   bmp_buf[7]  bmp_buf[8]     0x00
    ...
    lcd_buf[n]  =  bmp_buf[3n] | bmp_buf[3n+1]<<8 | bmp_buf[3n+2]<<16 | 0x00<<24;

    */

    // 3.将数据写入映射空间
    // int i;
    // for (i = 0; i < 1024 * 600; i++)
    // {
    //     map_p[i] = lcd_buf[i]
    // }

    memcpy(map_p, lcd_buf, 1024 * 600 * 4);

    // 4.关闭文件
    close(bmp_fd);
    close(lcd_fd);

    return 0;
}