#include "utils.h"

// 目录检索到系统指定目录下（子目录）所有的bmp图片，
// 并且存入到链表 （顺序表： last, length, data）
// 遍历链表把图片显示在lcd上 （电子相册）

int main(int argc, char const *argv[])
{

    // 要显示的图片路径 -- 任意大小
    char *image_src[7] = {"./颜色.bmp", "./光轨.bmp", "./迷宫.bmp", "./成都熊猫基地.bmp", "./北京飞广州.bmp", "./重庆魁星楼.bmp", "./汕尾海丰.bmp"};

    // 要写入LCD显示屏的坐标
    int location[7][2] = {{230, 100}, {450, 30}, {600, 100}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    int i = 0;              // 数组下标 (读取图片 和 图片需要显示的位置)
    int *images_buf = NULL; // 图片数据缓冲区

    // 打开触摸屏
    if (touch_open("/dev/input/event6") < 0)
    {
        return 1;
    }

    // LCD 只初始化一次, 之后切换图片共用, 不再反复 open/mmap
    if (lcd_init() < 0)
    {
        touch_close();
        return 1;
    }

    while (1)
    {
        // 读新图之前, 先释放上一张的缓冲区(如果有)
        // 这样无论本次是左滑/右滑/普通点击, 旧图都只释放一次, 既不泄漏也不会重复free
        if (images_buf != NULL)
        {
            free(images_buf);
            images_buf = NULL;
        }

        // 调用 自定义函数 返回 图片数据缓冲区
        images_buf = read_bmp_func(image_src[i]);
        // 写入虚拟内存
        show_image_to_location(images_buf, location[i][0], location[i][1]); // 任意图片大小、任意屏幕位置

        // 触摸事件监听
        touch_event_t e = get_touch_event();

        // 如果松开触摸屏
        if (e.released)
        {
            if (e.swipe_left)
            {
                // printf("  <- \n");
                i = (i + 1) % 7; // 下一张 循环i
            }
            if (e.swipe_right)
            {
                // printf("  -> \n");
                i--; // 上一张 循环i
                if (i < 0)
                    i = 6;
            }
        }
    }

    // 释放read_bmp_func申请的空间
    free(images_buf);
    lcd_close();   // 解除映射并关闭 fb0
    touch_close(); // 释放触摸监听
    return 0;
}
