#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int w;
int h;

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
