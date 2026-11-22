#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close  read
#include <string.h> // strerror
#include <errno.h>  // 全局错误码声明所在的头文件

int main(int argc, char const *argv[])
{
    // 练习3：重复读取一个文件，那么第二次读取的时候是在第一次基础上继续读，还是重新读？

    // 1. 打开文件
    int fd = open("test1.txt", O_RDWR); // test中: // a有30个  b有30个

    char buf[20];   // 数据缓冲区, 用来存储 读取到的数据
    bzero(buf, 20); // 把指针s指向的内存前n个字节全部置为0。
    // char buf[100] = {0}; // 声明数组且把元素初始化为0

    // 2. 读取文件  ssize_t read(int fd, void * buf, size_t count); 返回实际读取到的字节数
    read(fd, buf, 7); // 换行符也会被读取, linux占用1字节\n, windows占用2字节\r\n
    // 输出读取的文件
    printf("1: %s\n", buf);

    // 3. 继续读取文件, 看读取位置
    bzero(buf, 20); // 把指针s指向的内存前n个字节全部置为0。
    read(fd, buf, 7);
    printf("2: %s\n", buf);

    close(fd);
    // 结论, 每一次都是在上一次的位置继续向后读取
    // 如果在3之前重新open文件的话, 文件读取指针会重新挪回文件头部

    // ===========

    // 练习, 把test1.txt的内容完整输出到终端
    // 打开文件,
    int fd2 = open("test1.txt", O_RDWR);

    // 要考虑文件不存在的情况
    if (fd2 == -1)
    {
        perror("open");
        return -1;
    }
    // 定义 缓冲区数组并初始化
    // 踩坑: 设置的数组刚好和要写入的大小相等, 再%s输出读取到的内容时, 由于读取不到\0会继续读取相邻内存的内容,直到需要\0;
    //  (`%s` 会从`buf2[0]` 开始一直往后打， 越过数组末尾 ，继续读栈上的邻居内存，直到碰巧遇到一个 0 字节才停。那块栈内存里往往残留着上一次的输出缓冲、函数内部变量之类的内容 —— 看起来就像"重复读了一些东西"。)
    // 解决,多设置一个字节用于存储\0
    char buf2[11] = {0};

    // 存储 文件读取的字节数
    int fet;
    // 循环读取文件,直到文件读取字节数为0, 跳出循环
    printf("文件test1.txt的内容为:\n");
    while (1)
    {
        // 每次循环要将之前的缓冲区初始化为0, 避免最后一次读取的字节数不够无法完全重写buf2, 残留上一次的数据
        bzero(buf2, 10);

        // 读取文件(文件描述符, 存入的缓冲区, 每次读取多少字节)
        fet = read(fd2, buf2, 10); // 返回实际读取到的字节数

        // 如果读取到的字节数为0, 说明没有文件可以读取了
        // 如果读取到-1, 说明出错了, 也要跳出循环, 避免死循环
        if (fet <= 0)
        {
            break;
        }

        // 否则就是有读取到内容, 输出每次循环读取到的文件内容
        // 输出数据缓冲区
        // printf("aaaabbbb\n");
        printf("%s", buf2);

#if 0 
        `fet = read(fd2, buf2, 10);
        if (fet <= 0) break;
        write(STDOUT_FILENO, buf2, fet); // 写入道标准输出, 明确告诉它"只输出 fet 个字节"`
        `write` 按字节数输出，不依赖`'\0'` ，`char buf2[10]` 也不用改。做文件拷贝这类场景这是标准写法。
#endif
    }
    printf("\n");
    // 关闭文件
    close(fd2);
}