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
ssize_t read(int fd, void *buf, size_t count);

函数参数：
    fd:要读取的文件的文件描述符
    buf:存放读取到的数据的缓冲区（void * 通用类型指针）
    count:想要读取的数据的字节数（期望值）

返回值：
    读取成功：返回实际读取到的数据的字节数
    读取失败：返回-1，并设置errno

#endif

int main()
{
    int fd = open("./1.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("open error\n");
        return -1;
    }

    char buf[10] = {0};
    int ret = 0;
    while (1)
    {
        bzero(buf, 10);
        ret = read(fd, buf, 10);
        if (ret == 0)
        {
            break;
        }
        printf("ret = %d\n", ret);
        printf("%s\n", buf);
    }

    close(fd);
    return 0;
}