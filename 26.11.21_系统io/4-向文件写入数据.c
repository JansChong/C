#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close  read
#include <string.h> // strerror
#include <errno.h>  // 全局错误码声明所在的头文件

int main(int argc, char const *argv[])
{

    // 1. 注释掉2, 先写入两次 0-9
    // // 打开文件, 不存在就创建
    // int fd = open("test3.txt", O_RDWR | O_CREAT, 0777);
    // if (fd == -1)
    // {
    //     perror("open error\n");
    //     return -1;
    // }

    // // 设置要存入文件的内容  (缓冲区)
    // char buf[15] = "0123456789"; // 这里存入10个字节, 剩下的5个字节初始化为 \0
    // // 写入
    // // write(fd, buf, 20); // 实际写入的数据大于 buf的数据, 有可能会写入乱码, 另外 10-15 填入的是\n
    // write(fd, buf, 10);
    // // 多次写入会在后面追加
    // // write(fd, buf, 20); // 实际写入的数据大于 buf的数据, 有可能会写入乱码, 另外 10-15 填入的是\n
    // write(fd, buf, 10); // 写入两次 0-9
    // // 关闭文件
    // close(fd);

    // =======

    // 2. 注释掉1, 再次open & 写入文件

    // 每次open() 时， 文件读写指针会重新移动到头部，此时写入会覆盖文件头部的内容
    // int fd = open("test3.txt", O_RDWR );

    // 除非用O_APPEND 把文件读写指针移动到文件尾部, 就可以从尾部写入
    int fd = open("test3.txt", O_RDWR | O_APPEND); 

    if (fd == -1)
    {
        perror("open error\n");
        return -1;
    }

    char buf2[100] = {0};

    // 从键盘输入数据到 数据缓冲区 buf2
    fgets(buf2, 100, stdin);

    // 将输入的数据写入文件, strlen(buf2) 查看字符串的长度
    int fet = write(fd, buf2, strlen(buf2) - 1); // -1的目的是为了不让fgets输入的回车写入文件
    // write成功则返回写入的字节数(可能小于,比如磁盘满), 失败则返回-1
    printf("%d\n", fet); // 写入 qwer12345, 返回9


    
    close(fd);
}