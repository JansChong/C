#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{

    // 打开文件
    // FILE *fopen(const char *path, const char *mode);
    // FILE * 是一个文件流指针(结构体)，存储了文件的一些信息， 包括文件描述符  fp->_fileno
    // 打开文件
    // FILE * 是一个文件流指针
    FILE *fp1 = fopen("./1_1.txt", "r"); // 打开只读文件，该文件必须存在。
    FILE *fp1 = fopen("./1_1.txt", "w"); // 打开只写文件，若文件存在则文件长度清为零，即该文件内容会消失；若文件不存在则建立该文件。
    FILE *fp2 = fopen("./1_2.txt", "a"); // 以附加的方式打开只写文件, 若文件不存在，则会建立该文件

    // FILE *fp = fopen("./3.txt", "r+"); // 覆盖 读写，该文件必须存在。
    // FILE *fp = fopen("./3.txt", "w+"); // 清空 读写，不存在则创建
    // FILE *fp = fopen("./3.txt", "a+"); // 追加 读写，不存在则创建

    if (fp1 == NULL || fp2 == NULL)
    {
        perror("file open fail");
        return -1;
    }

    printf("%d\n", fp1->_fileno); // 文件描述符 3
    printf("%d\n", fp2->_fileno); // 文件描述符 4

    int fd3 = open("1_3.txt", O_RDWR | O_CREAT, 0777);
    if (fd3 == -1)
    {
        perror("file open fail");
        return -1;
    }
    printf("%d\n", fd3); // 文件描述符 5

    fclose(fp1);
    fclose(fp2);
    close(fd3);
    return 0;
}