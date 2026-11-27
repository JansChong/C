#include <stdio.h>

int main(int argc, char const *argv[])
{

    // 完成使用标准IO拷贝文件

    // 1. 打开要拷贝的文件 只读  r （只读 文件必须存在）
    FILE *old_file = fopen("test1.txt", "r");
    // 2. 创建一个新文件，接收拷贝的文件  w+   （清空 读写 文件不存在则创建）
    FILE *new_file = fopen("test2.txt", "w+");

    // 读取到的数据的缓冲区
    char buf[1025] = {};

    // 3. 循环读取文件， 每次读取1字节，1024段  （每次1kb的读取），直到读取到的字节数等于0
    while (1)
    {

        int fet = fread(buf, 1, 1024, old_file); // 返回实际读取到的 nmemb 数目

        if (fet == 0)
        {
            printf("读取结束\n");
            break;
        }

        if (ferror(old_file) != 0)
        {
            perror("读取fp1出错\n");
            return -1;
        }

        // 写入数据, 每次写入读取到的字节数
        fwrite(buf, 1, fet, new_file);
    }
}