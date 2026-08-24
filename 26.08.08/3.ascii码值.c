#include <stdio.h>

int main()
{
    int a = 'a'; // 单字符这里只能用单引号

    printf("%d\n", a); // %d 按十进制输出 97
    printf("%c\n", a); // %c 按ascii码对应的字符输出 a
}