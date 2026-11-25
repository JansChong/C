#include <stdio.h>

int main(int argc, char const *argv[])
{

    FILE *fp = fopen("./6.txt", "a+"); // 追加 读写

    if (fp == NULL)
    {
        perror("file open fail");
        return -1;
    }

    char name[10] = {0};
    int age;
    float score;

    for (int i = 0; i < 2; i++)
    {   
        // 成功则返回参数数目，失败则返回-1，错误原因存于errno中。
        int ret = fscanf(fp, "%s %d %f", name, &age, &score); // 读取文件的内容, 按指定格式指定位置

        // printf("ret = %d\n", ret); // 成功读取，返回参数个数
        printf("%s %d %.2f\n", name, age, score);
    }

    return 0;
}