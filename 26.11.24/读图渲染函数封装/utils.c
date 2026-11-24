#include "utils.h"

int w;
int h;
int lcd_fd;
int *map; // 内存映射

#define SCREEN_SIZE (1024 * 600) // 显示屏大小

/**
 * @description: 读取任意大小的 bmp图片，返回 file_buf
 * @param: 要读取的文件
 * @return int * file_buf
 */
int *read_bmp_func(char *img_src)
{

    // 2. 打开图片
    int bmp_fd = open(img_src, O_RDONLY);
    if (bmp_fd == -1)
    {
        perror("open fail");
        return NULL;
    }

    // 添加: 通过bmp_head,获取图片尺寸
    char bmp_head[55] = {0};
    read(bmp_fd, bmp_head, 54);
    // printf("%s\n", bmp_head);

    // 获取图片宽高
    int *width = (int *)(bmp_head + 18);
    int *height = (int *)(bmp_head + 22);
    w = *width;
    h = *height;
    // printf("图片尺寸为 %d * %d\n", w, h); // 成功

    // 2. 读取文件 (图片)
    // 保存图片时，选择的是 bmp格式_24位图(3字节 rgb)_1024*600
    char bmp_buf[w * h * 3];       // char型数组(每个元素1字节), 需要乘3才是完整图片， 因为一个像素点 【BGR】 3个字节，有1024*600像素点
    memset(bmp_buf, 0, w * h * 3); // 用 memset 清零

    // 读取图片要跳过文件头
    // lseek(bmp_fd, 54, SEEK_SET);

    // 一次读取全部数据 到 缓冲区
    read(bmp_fd, bmp_buf, w * h * 3);

    // 定义一个int数组, 每个元素4字节
    int *temp_buf = (int *)malloc(sizeof(int) * w * h); // 不用乘4, int数组一个元素有4字节

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // bmp位图上下颠倒，所以 用 (599 - 行数量) 纠正
            temp_buf[w * (h - 1 - i) + j] = bmp_buf[3 * (w * i + j)] | bmp_buf[3 * (w * i + j) + 1] << 8 | bmp_buf[3 * (w * i + j) + 2] << 16 | 0x00 << 24;
        }
    }

    close(bmp_fd);
    return temp_buf;
}

/**
 * @description: 显示图片到指定位置
 * @param: {} x 指定x坐标
 * @param: {} y 指定y坐标
 * @return void
 */
void show_image_to_location(int *img_buf, int x, int y)
{
    // 1. 打开文件 (液晶屏和图片)
    lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open fail");
    }

    // 因为图片的buf, 和lcd显示屏要渲染的1024*600的buf大小不一致, 所以要想办法把图片的buf 在 指定 x,y 写入 1024*600的buf中
    // 2个方法,
    // 1. 用 26.11.23的 6.center_box_demo 方法, 用边界交替写入, 这样屏幕的其他位置需要写入数据
    // 2. 在指定的x y, 开始写入图片buf的行, 并在 x加屏幕宽度的像素可以移动到下一行x
    // 不写入屏幕的其他像素, 只在屏幕的某个位置写入小图片

    // 2. 建立一个1024*600*4的内存映射, 返回其基地址
    map = mmap(NULL, SCREEN_SIZE * 4, PROT_WRITE, MAP_SHARED, lcd_fd, 0);

    // 3. 定义一个新的指针, 指向要开始写入的位置
    int *p = map + 1024 * y + x; // 移动指针p, 一行有 1024个像素点 * y行 + x列;  指针在map中指向要写入的坐标
    // 在内存映射的指定位置开始写入小图片
    // 循环遍历小图片的buf, 即位要写入的次数, 每一次写入一行, 结束跨下一行
    for (int i = 0; i < h; i++) // 行, 即图片的高度
    {
        for (int j = 0; j < w; j++) // 列, 即图片的宽度
        {
            // lcd一行有1024个像素, image一行有w个像素
            p[1024 * i + j] = img_buf[w * i + j];
        }
    }
}

void close_fun()
{
    close(lcd_fd); // 关闭文件
    munmap(map, 1024 * 600 * 4); // 解除内存映射
    return ;
}