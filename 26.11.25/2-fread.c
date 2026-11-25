#include <stdio.h>

int main()
{

    // 打开文件
    // FILE * 是一个文件流指针
    FILE *fp = fopen("./2.txt", "w");
    if (fp == NULL)
    {
        perror("file open fail");
        return -1;
    }
    printf("%d\n", fp->_fileno); // 文件描述符 3

    // 数据缓冲区
    char buf[100] = {0};

    // size_t fread(void * ptr, size_t size, size_t nmemb, FILE * stream);
    size_t ret = fread(buf, 5, 5, fp); // 返回实际读取到的 nmemb 数目。 当剩余的数据不足一块nmemb,则不会计入

    // fread() 会返回实际读取到的 nmemb 数目，如果此值比参数 nmemb 来得小，则代表可能读到了文件尾或有错误发生，这时必须用 feof() 或 ferror() 来决定发生什么情况。
    if (ret <= 5)
    {
        if (feof(fp) != 0)
        {
            printf("文件读取完毕\n");
        }

        if (ferror(fp) != 0)
        {
            printf("读取出错\n");
            return -1;
        }
    }

    printf("ret=%ld\n", ret); // 3
    printf("%s\n", buf);      // 读取到的内容

    fclose(fp);
    return 0;
}