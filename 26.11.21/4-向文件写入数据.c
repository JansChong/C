#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close  read
#include <string.h> // strerror
#include <errno.h>  // 全局错误码声明所在的头文件

int main(int argc, char const *argv[])
{

    // 打开文件
    int fd = open("test3.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open error\n");
        return -1;
    }

    // 设置要存入文件的内容  (缓冲区)
    char buf[15] = "0123456789"; // 这里存入10个字节, 剩下的5个字节初始化为 \0

    // 写入
    // write(fd, buf, 20); // 实际写入的数据大于 buf的数据, 有可能会写入乱码, 另外 10-15 填入的是\n
    write(fd, buf, 10); 

    // 多次写入会在后面追加
    // write(fd, buf, 20); // 实际写入的数据大于 buf的数据, 有可能会写入乱码, 另外 10-15 填入的是\n
    write(fd, buf, 10); 

    // char buf2[100];
    // bzero(buf2, 100);
    // 从键盘输入数据
    // fgets(buf2, 100, stdin);
    // 将输入的数据写入文件
    // write(fd, buf2, strlen(buf));

    // 关闭文件
    close(fd);


    // 每次open() 时， 文件读写指针会重新移动到头部， 此时再写会被覆盖
}