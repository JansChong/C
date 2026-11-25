#include <stdio.h>

int main()
{

    // 打开文件
    // FILE * 是一个文件流指针
    // FILE *fp = fopen("./3.txt", "r+"); // 覆盖
    // FILE *fp = fopen("./3.txt", "w+"); // 清空
    FILE *fp = fopen("./3.txt", "a+"); // 追加

    if (fp == NULL)
    {
        perror("file open fail");
        return -1;
    }
    printf("%d\n", fp->_fileno); // 文件描述符 3

    // 数据缓冲区
    char buf[11] = "1234567890";
    size_t ret = fwrite(buf, 5, 2, fp);
    // size_t ret = fwrite(buf, 5, 5, fp); // 越界也可以写入
    printf("ret = %ld\n", ret); // 如果返回值和要写入的块数不相等，则写入失败



    fclose(fp);
    return 0;
}