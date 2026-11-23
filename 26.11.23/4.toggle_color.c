#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close  read
#include <string.h> // strerror
#include <errno.h>  // 全局错误码声明所在的头文件

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
    int black = 0x0000ff00;
    int yellow = 0x00ffff00;

#if 0
    // 3.将颜色数据写入fb0文件
    // lcd一个屏幕点像素占据4字节（ARGB）
    // write(写入的目标文件, 数据缓冲区(地址), 写入的字节数)
    // write(lcd_fd, &green, 4); // 只能把屏幕的第一个像素点变绿

    // 这个代码是循环， 每次点亮一个像素点， 看起来会从上往下刷新
    for (int i = 0; i < 1024 * 600; i++)
    {
        write(lcd_fd, &green, 4); // 只能把屏幕的第一个像素点变绿
    }
#endif

    // 3、先准备1024*600这么大的颜色数据
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

    // 4、一次性将准备好的满屏绿色数据 写入 液晶屏文件中

    while (1)
    {
        write(lcd_fd, black_buf, 1024 * 600 * 4);
        sleep(1);
        lseek(lcd_fd, 0, SEEK_SET);

        write(lcd_fd, red_buf, 1024 * 600 * 4);
        sleep(1);
        lseek(lcd_fd, 0, SEEK_SET);

        write(lcd_fd, yellow_buf, 1024 * 600 * 4);
        sleep(1);
        lseek(lcd_fd, 0, SEEK_SET);
    }

    close(lcd_fd);
    return 0;
}