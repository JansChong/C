#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close
#include <string.h> // strerror
#include <errno.h> // 全局错误码声明所在的头文件

int main(int argc, char const *argv[])
{

    int fd = open("a.txt", O_RDWR); // O_RDWR 以可读写方式打开文件

    // 文件找不到， 文件描述符返回-1
    if(fd == -1){
        
        // 以下两条语句效果完全一致，输出函数错误的原因
        perror("打开a.txt失败");
        
        // strerror(errnum) 
        // 依参数errnum的错误代码来查询其错误原因的描述字符串
        // 头文件： #include <string.h>
        // 返回值：返回描述错误原因的字符串指针
        printf("打开a.txt失败: %s\n", strerror(errno)); 
    }

    close(fd);
    return 0;
}