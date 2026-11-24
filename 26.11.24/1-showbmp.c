#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 1. 打开文件 (液晶屏和图片)
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open fail");
        return -1;
    }

    // 判断打开失败
    // 2. 打开图片
    int bmp_fd = open("./成都熊猫基地.bmp", O_RDONLY);
    if (bmp_fd == -1)
    {
        perror("open fail");
        return -1;
    }

#if 0
    // 读取文件头 14
    // struct tagBITMAPFILEHEADER bfh;
    // read(bmp_fd, &bfh, sizeof(bfh));

    // //读取文件信息头  40
    // struct tagBITMAPINFOHEADER bih;
    // read(bmp_fd, &bih, sizeof(bih));

    // printf("宽度:%d, 高度:%d, 位深:%d\n", bih.biWidth, bih.biHeight, bih.biBitCount);
    // printf("文件大小:%d\n", bih.biSizeImage+54);
#endif

    // 2. 读取文件 (图片)
    // 保存图片时，选择的是 bmp格式_24位图(3字节 rgb)_1024*600
    char bmp_buf[1024 * 600 * 3] = {0}; // char型数组(每个元素1字节), 需要乘3才是完整图片， 因为一个像素点 【BGR】 3个字节，有1024*600像素点

    // 读取图片要跳过文件头
    lseek(bmp_fd, 54, SEEK_SET);
    // 一次读取全部数据 到 缓冲区
    read(bmp_fd, bmp_buf, 1024 * 600 * 3);

    // bmp读取到的数据是【BGR】3字节， LCD显示【ARGB】4字节
    // 定义一个int数组, 每个元素4字节
    int temp_buf[1024 * 600] = {0}; // 不用乘4, int数组一个元素有4字节

    // temp_buf 和 bmp_buf的对应关系: 【ARGB】 -> 【BGR】
    // temp_buf[0] -> bmp_buf[0] bmp_buf[1] bmp_buf[2] 0x00
    // temp_buf[1] -> bmp_buf[3] bmp_buf[4] bmp_buf[5] 0x00
    // temp_buf[2] -> bmp_buf[6] bmp_buf[7] bmp_buf[8] 0x00
    // temp_buf[n] -> bmp_buf[3n] bmp_buf[3n+1] bmp_buf[3n+2] 0x00

    // 把【BGR】转成 【ARGB】, 用移位， 写循环 1024*600
    // temp_buf[n] = bmp_buf[3*n] | bmp_buf[3*n+1]<<8 |bmp_buf[3*n+2]<<16 | 0x00<<24;
    // 考虑到屏幕的规律，屏幕中的每一个像素点的位置为： 1024*i+j
    // temp_buf[1024*i+j] = bmp_buf[3*(1024*i+j)] | bmp_buf[3*(1024*i+j)+1]<<8 |bmp_buf[3*(1024*i+j)+2]<<16 | 0x00<<24;

    for (int i = 0; i < 600; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            // bmp位图上下颠倒，所以 用 (599 - 行数量) 纠正
            temp_buf[1024 * (599 - i) + j] = bmp_buf[3 * (1024 * i + j)] | bmp_buf[3 * (1024 * i + j) + 1] << 8 | bmp_buf[3 * (1024 * i + j) + 2] << 16 | 0x00 << 24;

            // 踩坑：将n换成(1024*i+j)时， 没有加(), 导致 3*1024*i + j,  j没有作为整体*3， 最后显示的图片只有1/3的列(宽度)
            //  temp_buf[n] = bmp_buf[3*n] | bmp_buf[3*n+1]<<8 |bmp_buf[3*n+2]<<16 | 0x00<<24;

        }
    }

    // 建立一个1024*600*4的内存映射
    int *map = mmap(NULL, 1024*600*4, PROT_WRITE, MAP_SHARED, lcd_fd, 0);

    // 3. 写入到液晶屏
    // 一次将读取到的数据写入屏幕
    // write(lcd_fd, temp_buf, 1024 * 600);

    // 写入虚拟内存
    memcpy(map, temp_buf, 1024*600*4);

    
    // 4. 关闭文件 -- (解除内存映射munmap)
    close(lcd_fd);
    close(bmp_fd);
    munmap(map, 1024*600*4); // 解除内存映射
    return 0;
}
