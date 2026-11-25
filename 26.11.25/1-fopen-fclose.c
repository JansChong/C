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
    FILE *fp1 = fopen("./1_1.txt", "w");
    FILE *fp2 = fopen("./1_2.txt", "a");
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