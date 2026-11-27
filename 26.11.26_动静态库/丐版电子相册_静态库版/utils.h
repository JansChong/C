#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h> // open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // read. close

#include <linux/input.h> // 导入 输入设备 的头文件
#include <dirent.h>
#include "link.h"

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

extern node_type_p banner_list;
extern int *map;

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

// 读取路径下的文件, 存入双向循环链表中
bool get_dir_designated_file(char *path, char *file_extension);

// 图片特效
int show_1152000bmp(char *pathname, int *show_1152000bmp_fd);
int show_location_bmp(char *pathname, int lcd_x_coordinates, int lcd_y_coordinates, int wide, int height, int *show_bmp_lcd_mmap);

int pic_circular_spread(char *pathname, int *pic_circular_spread_fd);
int pic_circular_shrink(char *pathname, int *pic_circular_shrink_fd);
int pic_down(char *pathname, int *pic_down_fd);
int pic_up(char *pathname, int *pic_up_fd);
int pic_left(char *pathname, int *pic_left_fd);
int pic_right(char *pathname, int *pic_right_fd);
int pic_transverse_blinds(char *pathname, int *pic_transverse_blinds_fd);
int pic_vertical_blinds(char *pathname, int *pic_vertical_blinds_fd);
int pic_left_right_coincidence(char *pathname, int *pic_left_right_coincidence_fd);
int pic_mid_spread(char *pathname, int *pic_mid_spread_fd);
int pic_oblique_block(char *pathname, int *pic_oblique_block_fd);


// ===== 函数指针数组 =====
// 所有动画函数的签名都是：int 函数名(char *pathname, int *lcd_mmap)
// 所以函数指针类型是：int (*)(char *, int *)
extern int (*effects[])(char *, int *);
// 特效总数
#define EFFECTS_NUM  (sizeof(effects) / sizeof(effects[0]))

// int main()
// {
//     int lcd_fd = open("/dev/fb0", O_RDWR);
//     int *map = mmap(NULL, LCD_TOTAL * 4, PROT_WRITE, MAP_SHARED, lcd_fd, 0);

//     char *images[] = {
//         "./1.bmp", "./2.bmp", "./3.bmp",
//         "./4.bmp", "./5.bmp", "./6.bmp",
//         "./7.bmp", "./8.bmp", "./9.bmp",
//         "./10.bmp", "./11.bmp"
//     };

//     while (1)
//     {
//         // 依次播放 11 种特效
//         for (int i = 0; i < EFFECTS_NUM; i++)
//         {
//             effects[i](images[i], map);   // 调用第 i 个特效
//             sleep(2);
//         }
//     }

//     munmap(map, LCD_TOTAL * 4);
//     close(lcd_fd);
//     return 0;
// }

#endif // !_UTILS_H
