#include <stdio.h>

int main(int argc, char const *argv[])
{

    FILE *fp = fopen("./6.txt", "a+"); // 追加 读写

    if (fp == NULL)
    {
        perror("file open fail");
        return -1;
    }

    char name[10] = "王五";
    int age = 24;
    float score = 100;

    // 写入两次
    for (int i = 0; i < 2; i++)
    {

        // fprintf() 会根据参数格式化数据，输出到文件流指定的文件中，直到出现字符串结束(’\0’)为止
        // 成功则返回实际写入的字符数，失败则返回-1，错误原因存于errno中。
        int ret = fprintf(fp, "\n%s %d %.2f", name, age, score); // 读取文件的内容, 按指定格式指定位置
    }

    return 0;
}