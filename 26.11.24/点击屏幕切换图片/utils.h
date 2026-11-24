#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h> // open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // read. close

#include <linux/input.h> // 导入 输入设备 的头文件

/* 触摸事件监听返回的结构体 */
typedef struct
{
      int pressed;     // 是否按下:   1=按下中, 0=没按下
      int released;    // 是否松开:   1=本次刚松开(一次性标志), 0=否
      int swipe_left;  // 左滑:       1=检测到左滑
      int swipe_right; // 右滑:       1=检测到右滑
      int x;           // 当前 x 坐标
      int y;           // 当前 y 坐标
} touch_event_t;

/* 触摸事件容差: 横向移动超过这个数才算滑动, 小于等于它就当作普通点击 */
#define SWIPE_TOLERANCE 50

// 导入函数，输入图片路径，返回图片缓冲区数据 【ARGB】    任意图片尺寸都可以
int *read_bmp_func(char *img_src);
// 显示图片到指定位置
void show_image_to_location(int *img_buf, int x, int y);
// LCD 初始化, 整个程序只调用一次 (open fb0 + mmap)
int lcd_init(void);
// 程序退出时调用一次, 解除映射并关闭 fb0
void lcd_close(void);

// 打开触摸屏
int touch_open(const char *dev_path);
// 触摸事件监听
touch_event_t get_touch_event(void);
// 关闭触摸屏
void touch_close(void);

#endif // !_UTILS_H
