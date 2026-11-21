#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

#if 0
头文件：
#include <unistd.h>

函数原型：
ssize_t write(int fd, const void *buf, size_t count);

函数参数：
    fd:要写入的文件的文件描述符
    buf:存放要写入的数据的缓冲区（void * 通用类型指针）
    count:想要写入的数据的字节数（期望值）

返回值：
    写入成功：返回实际写入的数据的字节数
    读取失败：返回-1，并设置errno

#endif

int main()
{
    int fd = open("./1.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
    if (fd == -1)
    {
        perror("open error\n");
        return -1;
    }

    int ret = 0;
    // char buf[15] = "abcdefghijk";
    char buf2[15] = "hello world";

    // ret = write(fd, buf, 11);
    // printf("ret = %d\n", ret);
    ret = write(fd, buf2, 11);
    printf("ret = %d\n", ret);
    return 0;
}