#if 0

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

     //读取文件头 14
    struct tagBITMAPFILEHEADER bfh;
    read(bmp_fd, &bfh, sizeof(bfh));

    //读取文件信息头  40
    struct tagBITMAPINFOHEADER bih;
    read(bmp_fd, &bih, sizeof(bih));

    printf("宽度:%d, 高度:%d, 位深:%d\n", bih.biWidth, bih.biHeight, bih.biBitCount);
    printf("文件大小:%d\n", bih.biSizeImage+54);
    
    

    // 2. 读取文件 (图片)
    // 保存图片时，选择的是 bmp格式_24位图(3字节 rgb)_1024*600
    int bmp_buf[1024 * 600 * 3];
    // 一次读取全部数据 到 缓冲区
    read(bmp_fd, bmp_buf, 1024 * 600 * 3);

    // 3. 写入到液晶屏 --  (用或不用内存映射两套方案)
    // 一次将读取到的数据写入屏幕
    write(lcd_fd, bmp_buf, 1024 * 600 * 3);

    // 4. 关闭文件 -- (解除内存映射munmap)
    close(lcd_fd);
    close(bmp_fd);

    return 0;
}

#endif



#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define UINT  unsigned short
#define DWORD unsigned  int
#define LONG unsigned  int
#define WORD unsigned short

 struct tagBITMAPFILEHEADER
{
    WORD bfType; // 位图文件的类型，必须为BM(1-2字节）
    DWORD bfSize; // 位图文件的大小，以字节为单位（3-6字节）
    WORD bfReserved1; // 位图文件保留字，必须为0(7-8字节）
    WORD bfReserved2; // 位图文件保留字，必须为0(9-10字节）
    DWORD bfOffBits; // 位图数据的起始位置，以相对于位图（11-14字节）
    // 文件头的偏移量表示，以字节为单位
} __attribute__((packed));

 struct tagBITMAPINFOHEADER{
    DWORD biSize; // 本结构所占用字节数（15-18字节）
    LONG biWidth; // 位图的宽度，以像素为单位（19-22字节）    ------图片的宽度
    LONG biHeight; // 位图的高度，以像素为单位（23-26字节）   ------图片的高度
    WORD biPlanes; // 目标设备的级别，必须为1(27-28字节）
    WORD biBitCount;// 每个像素所需的位数，必须是1（双色），（29-30字节）  ---位深
    // 4(16色），8(256色）或24（真彩色）之一
    DWORD biCompression; // 位图压缩类型，必须是 0（不压缩），（31-34字节）
    // 1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
    DWORD biSizeImage; // 位图的大小，以字节为单位（35-38字节）   ---图片颜色数据的大小
    LONG biXPelsPerMeter; // 位图水平分辨率，每米像素数（39-42字节） 
    LONG biYPelsPerMeter; // 位图垂直分辨率，每米像素数（43-46字节)
    DWORD biClrUsed;// 位图实际使用的颜色表中的颜色数（47-50字节）
    DWORD biClrImportant;// 位图显示过程中重要的颜色数（51-54字节）
} __attribute__((packed));


int main() {
    //1、打开液晶屏文件
    int lcdFd = open("/dev/fb0", O_RDWR);
    if(lcdFd == -1)
    {
        perror("open lcd  error");
        return -1;
    }
    //2、打开图片文件
    int bmpFd = open("成都熊猫基地.bmp", O_RDONLY);
    if(bmpFd == -1)
    {
        perror("open bmp error");
        return -1;
    }
    //读取文件头 14
    struct tagBITMAPFILEHEADER bfh;
    read(bmpFd, &bfh, sizeof(bfh));

    //读取文件信息头  40
    struct tagBITMAPINFOHEADER bih;
    read(bmpFd, &bih, sizeof(bih));

    printf("宽度:%d, 高度:%d, 位深:%d\n", bih.biWidth, bih.biHeight, bih.biBitCount);
    printf("文件大小:%d\n", bih.biSizeImage+54);


    //3、读取图片颜色数据 
    char bmpbuf[1024*600*3] = {0}; //一共是1024*600个像素点，每个像素点3个字节
    int  lineByte = 1024*3;//一行的字节数

    read(bmpFd, bmpbuf, sizeof(bmpbuf));

    // for(int j=479; j>=0; j--)
    // {
    //     //让文件光标偏移到最后一行的起始地址
    //     lseek(bmpFd,54+j*lineByte,SEEK_SET);

    //     read(bmpFd, bmpbuf + (479-j) * lineByte,lineByte);
    // }
    

    //将图像中的每个像素点 BGR 转换为 ARGB
    int tempbuf[1024*600] = {0};//存储转换之后的颜色数据
    for(int i=0,j=0; i<1024*600; i++,j+=3)
    {
        tempbuf[i] =0x00<<24 | bmpbuf[j+2]<<16 |  bmpbuf[j+1]<<8 |  bmpbuf[j] ;
    }

    //将图片进行上下颠倒
    int lcdbuf[600][1024] = {0};
    for(int j=0; j<600; j++)
    {
        for(int i=0; i<1024; i++)
        {
            lcdbuf[j][i] = tempbuf[(479-j) * 1024 + i];
        }
    }

    //4、将读取到的图片数据写入液晶屏文件
    write(lcdFd,lcdbuf,sizeof(lcdbuf));

    //5、关闭液晶屏文件
    close(lcdFd);

    //6、关闭图片文件
    close(bmpFd);
}