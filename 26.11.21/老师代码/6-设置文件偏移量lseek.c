#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

#if 0
头文件：
#include <sys/types.h>
#include <unistd.h>


函数原型：
off_t lseek(int fd, off_t offset, int whence);

函数参数：
    fd:要偏移的文件的文件描述符
    offset:要偏移的字节数
    whence:偏移的起始位置 
            SEEK_SET  //从开头开始偏移
            SEEK_CUR  //从当前所在位置开始偏移   
            SEEL_END  //从末尾开始偏移

返回值：
    偏移成功：返回成功偏移的字节数
    偏移失败：返回-1，并设置errno

#endif

int main()
{
    int fd = open("./1.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("open error\n");
        return -1;
    }

    char wr_buf[15] = "hello world";
    write(fd, wr_buf, 11);

    char rd_buf[6] = {0};
    int ret = lseek(fd, 20, SEEK_SET);
    read(fd, rd_buf, 5);
    printf("%s\n", rd_buf);
    printf("ret = %d\n", ret);
    write(fd, wr_buf, 11);
    // printf("%p\n", wr_buf);
    // printf("%p\n", rd_buf);
    return 0;
}