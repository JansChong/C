#include <stdio.h>

int main(int argc, char const *argv[])
{

    // 打开文件
    FILE *fp = fopen("./3.txt", "a+"); // 追加 读写
    if (fp == NULL)
    {
        perror("file open fail");
        return -1;
    }

    // fseek() 移动文件流的读写位置， 同lseek，但是返回值不一样， 成功时则返回 0，若有错误则返回 -1，errno 会存放错误代码
    fseek(fp, 0, SEEK_SET);
    // 由于 fseek() 不像 lseek() 会return读写位置，因此必须使用 ftell() 来取得目前读写的位置。

    // long ftell(FILE * stream); 取得文件流的读取位置
    // 当调用成功时则返回目前的读写位置，若有错误则返回 -1，errno 会存放错误代码。
    long fp_idx = ftell(fp);
    printf("当前文件的读写位置%ld\n", fp_idx); // 当前文件的读写位置0

    // 如果用这个获取文件的大小， 需要先记录当前文件指针的位置， 然后挪动指针到末尾获取文件大小， 最后记得恢复文件指针到原来的位置，避免破坏性读取
    fseek(fp, 0, SEEK_END);                                  // 移动指针到文件末尾
    long file_size = ftell(fp);                              // 读取当前的文件读写指针
    printf("文件\"./3.txt\"的大小有: %ld字节\n", file_size); // 文件"./3.txt"的大小有: 22字节
    fseek(fp, fp_idx, SEEK_SET);                             // 移动指针到原先位置
}

// 文件描述符默认前3个 fd=0、1、2
// 文件流指针默认前3个 pd=0、1、2  stdin stdout stderr

// char str1[100] = {0};
// char * p= fgets(str1, 100, stdin); // 在标准输入 欲读取100字节 放到数组str
// fputs("hello world\n", stdout); // 把字符输出到 标准输出