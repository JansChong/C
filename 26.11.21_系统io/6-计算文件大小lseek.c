#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

int main()
{
    int fd = open("./关于open创建的文件在windows和linux环境下权限的问题.png", O_RDWR | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("open error\n");
        return -1;
    }

    // 因为lseek函数移动指针成功时返回新的指针位置(距文件开头的字节数)  因此可以将指针挪移到文件末尾，此时返回的指针位置就是该文件的大小）
    int ret = lseek(fd, 0, SEEK_END);
    printf("读取到文件大小 = %d\n", ret); 

    return 0;
}