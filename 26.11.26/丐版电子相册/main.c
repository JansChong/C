#include "utils.h"

node_type_p banner_list;

int (*effects[])(char *, int *) = {
    pic_circular_spread,        // 0: 圆形扩散
    pic_circular_shrink,        // 1: 圆形收缩
    pic_down,                   // 2: 向下飞入
    pic_up,                     // 3: 向上飞入
    pic_left,                   // 4: 向左飞入
    pic_right,                  // 5: 向右飞入
    pic_transverse_blinds,      // 6: 横百叶窗
    pic_vertical_blinds,        // 7: 竖百叶窗
    pic_left_right_coincidence, // 8: 左右相合
    pic_mid_spread,             // 9: 中间展开
    pic_oblique_block           // 10: 斜方块
};

// 目录检索到系统指定目录下（子目录）所有的bmp图片，
// 并且存入到链表 （顺序表： last, length, data）
// 遍历链表把图片显示在lcd上 （电子相册）
int main()
{
    // 初始化链表
    banner_list = init_list();

    // 读取目录下的图片路径 并且 写入循环链表
    get_dir_designated_file("./images/", "bmp");
    // show_list(banner_list);

    // 要显示的图片路径 -- 任意大小
    // char *image_src[7] = {"./颜色.bmp", "./光轨.bmp", "./迷宫.bmp", "./成都熊猫基地.bmp", "./北京飞广州.bmp", "./重庆魁星楼.bmp", "./汕尾海丰.bmp"};

    // 要写入LCD显示屏的坐标
    // int location[7][2] = {{230, 100}, {450, 30}, {600, 100}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    // int i = 0;              // 数组下标 (读取图片 和 图片需要显示的位置)
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

    // 头节点 （无数据，记录头结点用于跳过）
    node_type_p head = banner_list;
    // 临时节点
    node_type_p temp = head->next;
    // 调用 自定义函数 返回 图片数据缓冲区
    // images_buf = read_bmp_func(temp->data);
    // 写入虚拟内存
    // show_image_to_location(images_buf, 0, 0); // 任意图片大小、任意屏幕位置

    // 特效刷图
    show_location_bmp(temp->data, 0, 0, 1024, 600, map);
    // pic_circular_spread(temp->data, map);
    int i = -1; // 切换特效

    while (1)
    {
        // 读新图之前, 先释放上一张的缓冲区(如果有)
        // 这样无论本次是左滑/右滑/普通点击, 旧图都只释放一次, 既不泄漏也不会重复free
        if (images_buf != NULL)
        {
            free(images_buf);
            images_buf = NULL;
        }

        // 触摸事件监听
        touch_event_t e = get_touch_event();

        // 如果松开触摸屏
        if (e.released)
        {

            // 换特效
            i++;
            i = i % 10;
            printf("%d\n", i);

            if (e.swipe_left)
            {
                printf("  <- \n");
                temp = temp->next;
                // 需要跳过head节点
                if (temp == head)
                {
                    temp = temp->next;
                }
            }
            if (e.swipe_right)
            {
                printf("  -> \n");
                // i--; // 上一张 循环i
                // if (i < 0)
                //     i = 6;
                temp = temp->prev;
                if (temp == head)
                {
                    temp = temp->prev;
                }
            }

            printf("%s\n", temp->data);
            // images_buf = read_bmp_func(temp->data);
            // 写入虚拟内存
            // show_image_to_location(images_buf, 0, 0); // 任意图片大小、任意屏幕位置
            // pic_circular_spread(temp->data, map);
            // pic_circular_shrink(temp->data, map);
            effects[i](temp->data, map); // 调用第 i 个特效  photo_album
        }
    }

    // 释放read_bmp_func申请的空间
    free(images_buf);
    lcd_close();          // 解除映射并关闭 fb0
    touch_close();        // 释放触摸监听
    destroy(banner_list); // 销毁
    return 0;
}
