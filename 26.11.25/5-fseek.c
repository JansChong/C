#include <stdio.h>

int main(int argc, char const *argv[])
{

    // 打开文件
    // FILE * 是一个文件流指针
    // FILE *fp = fopen("./3.txt", "r+"); // 覆盖 读写
    // FILE *fp = fopen("./3.txt", "w+"); // 清空 读写
    FILE *fp = fopen("./3.txt", "a+"); // 追加 读写

    if (fp == NULL)
    {
        perror("file open fail");
        return -1;
    }

    fseek(fp, 0, SEEK_SET); // 同lseek，但是返回值不一样， 成功时则返回 0，若有错误则返回 -1，errno 会存放错误代码
    // fseek() 不像 lseek() 会返回读写位置，因此必须使用 ftell() 来取得目前读写的位置。
    // TODO..

    
    
    printf("%d\n", fp->_fileno); // 文件描述符 3



    // 如果用这个获取文件的大小， 需要先记录当前文件指针的位置， 然后挪动指针到末尾获取文件大小， 最后记得恢复文件指针到原来的位置，避免破坏性读取
}


// 文件描述符 默认有3个  fd=0、1、2
// 文件流指针 默认也有3个 pd=0、1、2  stdin stdout stderr

    // char str1[100] = {0};
    // char * p= fgets(str1, 100, stdin); // 在标准输入 欲读取100字节 放到数组str
    // fputs("hello world\n", stdout); // 把字符输出到 标准输出