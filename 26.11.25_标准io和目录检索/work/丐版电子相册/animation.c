#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <strings.h>


/*
    显示屏尺寸：1024 * 600
*/
#define LCD_WIDTH   1024
#define LCD_HEIGHT  600
#define LCD_TOTAL   (LCD_WIDTH * LCD_HEIGHT)

/*
图片特效：
    1）"圆形扩散"    2）"圆形收缩"
    3）"向下飞入"    4）"向上飞入"   5）"向左飞入"   6）"向右飞入"
    7）"横百叶窗"    8）"竖百叶窗"    9）"左右相合"   10）"中间展开"
    11）"斜方块"
*/

/*
    功能：显示1024*600大小的bmp图片。
    参数：
        char *pathname：要显示图片的名字。
        int *show_bmp_fd：被映射区的指针。
    返回值：成功  0
           失败  -1
*/
int show_bmp(char *pathname, int *show_bmp_fd)
{
    //1、打开BMP格式图片和lcd显示屏
    int fd_bmp = open(pathname,  O_RDWR);
    if(fd_bmp == -1)
    {
        printf("show_bmp(), open bmp fail!\n");
        return -1;
    }

    //2、去掉54个字节
    int ret = lseek(fd_bmp, 54, SEEK_SET);
    if(ret == -1)
    {
        printf("show_bmp(), lseek bmp fail!\n");
        return -1;
    }

    //3、读取BMP数据到lcd屏幕中
    char bmp_buf[LCD_TOTAL * 3];
    int lcd_buf[LCD_TOTAL];
    bzero(bmp_buf, LCD_TOTAL * 3);
    bzero(lcd_buf, LCD_TOTAL);

    ret = read(fd_bmp, bmp_buf, LCD_TOTAL * 3);//BMP数据放到了bmp_buf中
    if(ret == -1)
    {
        printf("show_bmp(), read bmp fail!\n");
        return -1;
    }

    //4、关闭文件，回收资源
    close(fd_bmp);

    //5、1024*600个A像素变成1024*600个B像素算法。
    int i;
    for(i=0; i<LCD_TOTAL; i++)
    {
        lcd_buf[i] = bmp_buf[i*3]<<0 | bmp_buf[i*3+1]<<8 | bmp_buf[i*3+2]<<16;
    }

    //6、lcd_buf数据（DDR2中的数据）通过mmap显示到LCD屏幕中。
    int x, y;
    for(y=0; y<LCD_HEIGHT; y++)//优化算法，解决图片颠倒问题
    {
        for(x=0; x<LCD_WIDTH; x++)
        {
            *(show_bmp_fd + LCD_WIDTH * (LCD_HEIGHT - 1 - y) + x) = lcd_buf[LCD_WIDTH * y + x];
        }
    }

    return 0;
}

/*
    功能：（不超过1024*600显示屏大小）显示任意位置任意大小的bmp图片
    形参：
        char *pathname：要显示图片的名字
        int lcd_x_coordinates：lcd屏的x轴坐标
        int lcd_y_coordinates：lcd屏的y轴坐标（通过x、y轴坐标确定显示图片起始显示坐标）
        int wide：所显示图片的宽度
        int height：所显示图片的高度
        int *show_bmp_lcd_mmap：被映射区的指针
    返回值：成功  0
            失败  -1

*/
int show_location_bmp(char *pathname,int lcd_x_coordinates, int lcd_y_coordinates, int wide, int height,int *show_bmp_lcd_mmap)
{
    int i;
    int ret;
    int x, y;

    char bmp_buf[wide*height*3];
    int  new_buf[wide*height];
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(new_buf, sizeof(new_buf));

    int bmp_fd = open(pathname, O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("show_location_bmp(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd,54,SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        printf("show_location_bmp(), lseek bmp failed\n");
        return -1;
    }

    int *new_p = show_bmp_lcd_mmap + LCD_WIDTH * lcd_y_coordinates + lcd_x_coordinates;//3、重新确定映射位置。

    ret = read(bmp_fd, bmp_buf, wide*height*3);//4、取读图片像素
    if(ret == -1)
    {
        printf("show_location_bmp(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0; i<wide*height; i++)//6、24bits 转 32bits控制变量
    {
            new_buf[i] = bmp_buf[i*3]<<0  |  bmp_buf[(i*3)+1]<<8 | bmp_buf[(i*3)+2]<<16;
    }

    for(y=0;y<height;y++)//7、解决图片上下颠倒问题
    {
        for(x=0;x<wide;x++)
        {
            *(new_p + (LCD_WIDTH * ((height-1)-y)) + x) = new_buf[wide*y+x];
        }
    }

    return 0;
}

/*
    功能：切换BMP图片特效"圆形扩散"。
    参数：
        char *pathname：图片的路径。
        int *pic_circular_spread_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_circular_spread(char *pathname, int* pic_circular_spread_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname, O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_circular_spread(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_circular_spread(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_circular_spread(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"圆形扩散"效果算法
    // 圆心 (512, 300)，最大半径约 593
    for(k=0; k<593; k+=3)
    {
        for(i=0; i<LCD_HEIGHT; i++)
        {
            for(j=0; j<LCD_WIDTH; j++)
            {
                if((j - LCD_WIDTH/2)*(j - LCD_WIDTH/2) + (i - LCD_HEIGHT/2)*(i - LCD_HEIGHT/2) <= k*k)
                {
                    pic_circular_spread_fd[LCD_WIDTH * i + j] = mi_buf[LCD_WIDTH * i + j];
                }
            }
        }
    }

    return 0;
}

/*
    功能：切换BMP图片特效"圆形收缩"。
    参数：
        char *pathname：图片的路径。
        int *pic_circular_shrink_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_circular_shrink(char *pathname, int* pic_circular_shrink_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_circular_shrink(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_circular_shrink(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_circular_shrink(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"圆形收缩"效果算法
    for(k=593; k>=0; k-=3)
    {
        for(i=0; i<LCD_HEIGHT; i++)
        {
            for(j=0; j<LCD_WIDTH; j++)
            {
                if((j - LCD_WIDTH/2)*(j - LCD_WIDTH/2) + (i - LCD_HEIGHT/2)*(i - LCD_HEIGHT/2) >= k*k)
                    pic_circular_shrink_fd[LCD_WIDTH * i + j] = mi_buf[LCD_WIDTH * i + j];
            }
        }
    }

    return 0;
}

/*
    功能：切换BMP图片特效"向下飞入"。
    参数：
        char *pathname：图片的路径。
        int *pic_down_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_down(char *pathname, int* pic_down_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_down(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_down(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_down(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"向下飞入"效果算法
    for(i=0; i<LCD_HEIGHT; i++)
    {
        for(j=0; j<LCD_WIDTH; j++)
        {
            pic_down_fd[LCD_WIDTH * i + j] = mi_buf[LCD_WIDTH * i + j];
        }
        usleep(1000);
    }

    return 0;
}

/*
    功能：切换BMP图片特效"向上飞入"。
    参数：
        char *pathname：图片的路径。
        int *pic_up_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_up(char *pathname, int* pic_up_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_up(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_up(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_up(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"向上飞入"效果算法
    for(i = LCD_HEIGHT - 1; i >= 0; i--)
    {
        for(j=0; j<LCD_WIDTH; j++)
        {
            pic_up_fd[LCD_WIDTH * i + j] = mi_buf[LCD_WIDTH * i + j];
        }
        usleep(500);
    }

    return 0;
}

/*
    功能：切换BMP图片特效"向左飞入"。
    参数：
        char *pathname：图片的路径。
        int *pic_left_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_left(char *pathname, int* pic_left_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_left(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_left(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_left(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"向左飞入"效果算法
    for(j = LCD_WIDTH - 1; j >= 0; j--)
    {
        for(i=0; i<LCD_HEIGHT; i++)
        {
            pic_left_fd[LCD_WIDTH * i + j] = mi_buf[LCD_WIDTH * i + j];
        }
        usleep(500);
    }

    return 0;
}

/*
    功能：切换BMP图片特效"向右飞入"。
    参数：
        char *pathname：图片的路径。
        int *pic_right_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_right(char *pathname, int* pic_right_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_right(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_right(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_right(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"向右飞入"效果算法
    for(j=0; j<LCD_WIDTH; j++)
    {
        for(i=0; i<LCD_HEIGHT; i++)
        {
            pic_right_fd[LCD_WIDTH * i + j] = mi_buf[LCD_WIDTH * i + j];
        }
        usleep(500);
    }

    return 0;
}

/*
    功能：切换BMP图片特效"横百叶窗"。
    参数：
        char *pathname：图片的路径。
        int *pic_transverse_blinds_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_transverse_blinds(char *pathname, int* pic_transverse_blinds_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_transverse_blinds(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_transverse_blinds(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_transverse_blinds(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"横百叶窗"效果算法 （分成8条）
    #define BLINDS_NUM 8
    for(j=0; j < LCD_WIDTH / BLINDS_NUM; j++)
    {
        for(i=0; i<LCD_HEIGHT; i++)
        {
            for(k=0; k<BLINDS_NUM; k++)
            {
                pic_transverse_blinds_fd[LCD_WIDTH * i + j + k * LCD_WIDTH / BLINDS_NUM] =
                    mi_buf[LCD_WIDTH * i + j + k * LCD_WIDTH / BLINDS_NUM];
            }
        }
        usleep(500);
    }

    return 0;
}

/*
    功能：切换BMP图片特效"竖百叶窗"。
    参数：
        char *pathname：图片的路径。
        int *pic_vertical_blinds_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_vertical_blinds(char *pathname, int* pic_vertical_blinds_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_vertical_blinds(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_vertical_blinds(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_vertical_blinds(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"竖百叶窗"效果算法（分成8条）
    for(i=0; i < LCD_HEIGHT / BLINDS_NUM; i++)
    {
        for(j=0; j<LCD_WIDTH; j++)
        {
            for(k=0; k<BLINDS_NUM; k++)
            {
                pic_vertical_blinds_fd[LCD_WIDTH * (i + k * LCD_HEIGHT / BLINDS_NUM) + j] =
                    mi_buf[LCD_WIDTH * (i + k * LCD_HEIGHT / BLINDS_NUM) + j];
            }
        }
        usleep(500);
    }

    return 0;
}

/*
    功能：切换BMP图片特效"左右相合"。
    参数：
        char *pathname：图片的路径。
        int *pic_left_right_coincidence_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_left_right_coincidence(char *pathname, int* pic_left_right_coincidence_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_left_right_coincidence(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_left_right_coincidence(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_left_right_coincidence(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"左右相合"效果算法
    // 1024 / 2 = 512 每边，分成 8 块，每块 64 像素
    #define COINCIDENCE_BLOCKS  8
    #define COINCIDENCE_STEP    (LCD_WIDTH / 2 / COINCIDENCE_BLOCKS)  // = 64
    for(block=0; block < COINCIDENCE_BLOCKS; block++)
    {
        for(i = COINCIDENCE_STEP * block; i < (block + 1) * COINCIDENCE_STEP; i++)//刷左部分矩形
        {
            for(j=0; j<LCD_HEIGHT; j++)
            pic_left_right_coincidence_fd[j * LCD_WIDTH + i] = mi_buf[j * LCD_WIDTH + i];
        }
        for(line = LCD_WIDTH - 1 - block * COINCIDENCE_STEP; line > LCD_WIDTH - 1 - (block+1) * COINCIDENCE_STEP; line--) //刷右部分矩形
        {
            for(j=0; j<LCD_HEIGHT; j++)
            pic_left_right_coincidence_fd[j * LCD_WIDTH + line] = mi_buf[j * LCD_WIDTH + line];
        }
        usleep(100000);
    }

    return 0;
}

/*
    功能：切换BMP图片特效"中间展开"。
    参数：
        char *pathname：图片的路径。
        int *pic_mid_spread_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_mid_spread(char *pathname, int *pic_mid_spread_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_mid_spread(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_mid_spread(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_mid_spread(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"中间展开"效果算法
    for(i=0; i < LCD_WIDTH / 2; i++)
    {
        for(j=0; j<LCD_HEIGHT; j++)
        {
            pic_mid_spread_fd[LCD_WIDTH/2 + LCD_WIDTH * j + i] = mi_buf[LCD_WIDTH/2 + LCD_WIDTH * j + i];
            pic_mid_spread_fd[LCD_WIDTH/2 + LCD_WIDTH * j - i] = mi_buf[LCD_WIDTH/2 + LCD_WIDTH * j - i];
        }
        usleep(500);
    }

    return 0;
}

/*
    功能：切换BMP图片特效"斜方块"。
    参数：
        char *pathname：图片的路径。
        int *pic_oblique_block_fd：被映射区的指针。
    返回值：成功  0
            失败  -1
*/
int pic_oblique_block(char *pathname, int *pic_oblique_block_fd)
{
    int ret=0;
    int line=0;
    int block=0;
    int i=0, j=0, k=0;
    int m=0, n=0;
    int bmp_fd=0;

    char bmp_buf[LCD_TOTAL * 3];
    int mi_buf[LCD_TOTAL];
    int temp_buf[LCD_TOTAL];
    bzero(mi_buf, sizeof(mi_buf));
    bzero(bmp_buf, sizeof(bmp_buf));
    bzero(temp_buf, sizeof(temp_buf));

    bmp_fd = open(pathname , O_RDONLY);//1、打开BMP格式图片
    if(bmp_fd == -1)
    {
        printf("pic_oblique_block(), open bmp failed\n");
        return -1;
    }

    ret = lseek(bmp_fd, 54 , SEEK_SET);//2、跳过bmp图片的前54个位置
    if(ret == -1)
    {
        perror("pic_oblique_block(), lseek bmp failed\n");
        return -1;
    }

    ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4、取读图片像素
    if(ret == -1)
    {
        printf("pic_oblique_block(), read bmp failed\n");
        return -1;
    }

    close(bmp_fd);//5、关闭图片

    for(i=0, j=0 ; i<LCD_TOTAL ; i++, j+=3)//6、24bits 转 32bits控制变量
    {
        temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
    }

    for(line=0 ; line < LCD_HEIGHT ; line++)//7、解决图片上下颠倒问题
    {
        for(i=0; i<LCD_WIDTH ; i++)
        mi_buf[LCD_WIDTH * line + i] = temp_buf[ (LCD_HEIGHT - 1 - line) * LCD_WIDTH + i ];
    }

    //8、特殊动画"斜方块"效果算法
    // 8x8 个方块，每个方块 128 x 75 像素 (1024/8=128, 600/8=75)
    #define OBLIQUE_COLS  8
    #define OBLIQUE_ROWS  8
    #define OBLIQUE_W     (LCD_WIDTH / OBLIQUE_COLS)   // 128
    #define OBLIQUE_H     (LCD_HEIGHT / OBLIQUE_ROWS)  // 75
    for(k=0; k <= OBLIQUE_COLS + OBLIQUE_ROWS - 2; k++)
    {
        for(i=0; i<OBLIQUE_ROWS; i++)
        {
            for(j=0; j<OBLIQUE_COLS; j++)
            {
                if(i + j <= k)
                {
                    for(m = OBLIQUE_W * i; m < OBLIQUE_W * (i+1); m++)
                    {
                        for(n = OBLIQUE_H * j; n < OBLIQUE_H * (j+1); n++)
                        {
                            pic_oblique_block_fd[n * LCD_WIDTH + m] = mi_buf[n * LCD_WIDTH + m];
                        }
                    }
                    usleep(200);
                }
            }
        }
    }

    return 0;
}

/*
    功能：显示任意位置任意大小的lcd屏
    参数：
        int color：要显示的颜色（RGB表示的十六进制）
        int lcd_x_coordinates：lcd屏幕的x轴坐标
        int lcd_y_coordinates：lcd屏幕的y轴坐标（通过x、y轴坐标确定起始显示颜色的坐标）
        int wide：所显示颜色的宽度
        int height：所显示颜色的高度（通过wide、height确定所显示颜色的面积）
        int *lcd_mmap：被映射区的指针
    返回值：成功  0
            失败  -1
*/
int clear_lcd_screen(int color, int lcd_x_coordinates, int lcd_y_coordinates, int wide, int height,int *lcd_mmap)
{
    int x, y;
    int *new_p = lcd_mmap + LCD_WIDTH * lcd_y_coordinates + lcd_x_coordinates;
    for(y=0; y<height; y++)
    {
        for(x=0; x<wide; x++)
        {
            *(new_p + LCD_WIDTH * y + x) = color;
        }
    }
    return 0;
}
