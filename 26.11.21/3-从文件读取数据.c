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
    int fd = open("test.txt", O_RDWR); // test中: // a有30个  b有30个

    
    char buf[100]; // 数据缓冲区, 用来存储 读取到的数据
    bzero(buf, 100); // 把指针s指向的内存前n个字节全部置为0。
    // char buf[100] = {0}; // 声明数组且把元素初始化为0
  
    // 2. 读取文件  ssize_t read(int fd, void * buf, size_t count); 返回实际读取到的字节数
    read(fd, buf, 25); // 换行符也会被读取,占用1字节
    // 输出读取的文件
    printf("1: %s\n", buf); // 23个a + 2个换行符

    // 3. 继续读取文件, 看读取位置
    bzero(buf, 100); // 把指针s指向的内存前n个字节全部置为0。
    read(fd, buf, 25);
    printf("2: %s\n", buf); // 7个a + 16个b + 两个换行符

    close(fd);
}