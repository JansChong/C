#include <strings.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close  read lseek
#include <string.h> // strerror
#include <errno.h>  // 全局错误码声明所在的头文件

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


int main(int argc, char const *argv[])
{


      // 打开文件
      int fd = open("./test4.txt", O_RDWR | O_CREAT, 0777);

      if (fd == -1)
      {
            perror("open error\n");
            return -1;
      }

      // 数据缓冲区
      char wr_buf[15] = "hello world";
      write(fd, wr_buf, 11); // 写入test4.txt 11个字节

      // 数据缓冲区
      char rd_buf[6] = {0};
      int ret = lseek(fd, 20, SEEK_SET); // 移动文件读写指针位置, 从文件起始位置, 往后移动20字节
      printf("ret = %d\n", ret);         // lseek函数的返回值: 成功时返回新的指针位置（距文件开头的字节数），失败返回 -1 并设置错误码。‌‌‌

      read(fd, rd_buf, 5);    // 在[20]的位置 读取test4.txt  => 5字节. => 存入rd_buf缓冲区
      printf("%s\n", rd_buf); // 输出读取到的5个字节, 这里的数据缓冲区长度为6目的是存一个\0, 避免输出%s时找不到\0读取后续内存区的内容

      write(fd, wr_buf, 11); // 在[20+5]的位置再次写入 wr_buf 11个字节 (写入、读取、都会移动 “文件读写指针” 位置)

      // 这两个指针是用来看 rd_buf[5] 时, %s读取不到\0继续输出后续地址的内容用的, 下面两个输出经过验证是相邻地址
      // printf("%p\n", wr_buf);
      // printf("%p\n", rd_buf);

      return 0;
}

// 文件偏移量：
// 1. 可以在文件尾部继续向后偏移， 照成空洞， 可以在空洞后继续写入 （多线程写入同一个文件）
// 2. 因为lseek函数移动指针成功时返回新的指针位置(距文件开头的字节数)  因此可以将指针挪移到文件末尾，此时返回的指针位置就是该文件的大小）
