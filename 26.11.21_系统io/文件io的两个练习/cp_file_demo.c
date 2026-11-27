#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close  read
#include <string.h> // strerror
#include <errno.h>  // 全局错误码声明所在的头文件

int main(int argc, char const *argv[])
{
#if 0
      // 练习1.将1.txt文件里面的内容读取出来，写入到2.txt中。 
      // 当文件有1024个字节的时候   1M  2M   10M

      // 打开要读取的文件
      int original_fd = open("./1.录制钉钉.MP4", O_RDONLY);

      // 打开要写入的文件 (读写|创建)
      // O_TRUNC‌是 Linux 文件打开标志，作用是：如果目标文件‌已经存在‌且以‌可写方式‌打开，就把它‌清空到 0 字节‌
      int target_fd = open("copy_录制钉钉.MP4", O_RDWR | O_CREAT | O_TRUNC, 0777);
#endif

#if 1
      // 2.编写代码实现类似cp指令的程序，(使用主函数传参)
      // cp 文件1 文件2 （如果文件2不存在，就创建）
      // ./cpfile 文件1 文件2
      // 打开要读取的文件
      int original_fd = open(argv[1], O_RDONLY);

      // 打开要写入的文件 (读写|创建)
      // O_TRUNC‌是 Linux 文件打开标志，作用是：如果目标文件‌已经存在‌且以‌可写方式‌打开，就把它‌清空到 0 字节‌
      int target_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0777);

      // 编译命令:
      // gcc cp_file_demo.c -o cpfile
      // ./cpfile 1.录制钉钉.MP4 2.拷贝钉钉录制.mp4
      // 获取编译时输入的参数:
      printf("[0]:%s\n", argv[0]); // ./cpfile
      printf("[1]%s\n", argv[1]);  // 1.录制钉钉.MP4
      printf("[2]%s\n", argv[2]);  // 2.拷贝钉钉录制.mp4
      // return 0;
#endif

      if (original_fd == -1 || target_fd == -1)
      {
            perror("文件打开失败\n");
            // 关闭文件
            close(original_fd);
            close(target_fd);
            return 0;
      }

      // 缓冲区
      char buf[64 * 1024] = {0};

      // 每次读取到的字节数
      // ‌ssize_t 是 POSIX 标准定义的有符号整数类型‌，专门用于系统调用返回值，既能表示读写字节数也能表达 -1 错误状态。‌‌‌
      ssize_t r_fet;
      ssize_t w_fet;

      while (1)
      {
            // 每次写入之前都清空一下 数据缓冲区, 避免有残留数据
            bzero(buf, 64 * 1024);

            // 读取文件到缓冲区, 返回读取到的字节数, 0则读取结束, -1则读取失败
            r_fet = read(original_fd, buf, 64 * 1024);

            if (r_fet <= 0)
            {
                  printf("读取结束, %zd\n", r_fet);
                  break;
            }

            // 每次读取到的内容写入文件 (返回实际写入的字节数, -1写入失败)
            w_fet = write(target_fd, buf, r_fet);

            if (w_fet == -1)
            {
                  printf("写入文件失败\n");
                  // 关闭文件
                  close(original_fd);
                  close(target_fd);
                  return 0;
            }
      }

      // 关闭文件
      close(original_fd);
      close(target_fd);
}