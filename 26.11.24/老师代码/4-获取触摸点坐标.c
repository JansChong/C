#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <linux/input.h>

int main()
{
    // 1.打开触摸屏设备文件
    int touch_fd = open("/dev/input/event6", O_RDONLY);
    if (touch_fd == -1)
    {
        perror("open event6 failed");
        return -1;
    }

    // 读取数据
    struct input_event ev;
    while (1)
    {
        read(touch_fd, &ev, sizeof(ev));

        int ts_x, ts_y;
        if (ev.type == EV_ABS) // 绝对位移时间
        {
            if (ev.code == ABS_X)
            {
                ts_x = ev.value;
            }
            if (ev.code == ABS_Y)
            {
                ts_y = ev.value;
            }
        }

        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) // 松手检测
        {
            printf("x = %d  y = %d\n", ts_x, ts_y);
        }
    }

    close(touch_fd);
    return 0;
}