#include <stdio.h>

// 【strlen】
// 头文件 <string.h>
// 函数原型： size_t strlen (const char *s);
// 说明：strlen() 用来计算指定的字符串 s 的长度，不包括结束字符 ‘\0’。
// 返回值：返回字符串 s 的字符数。

int myStrlen(const char *s)
{
    // 计数
    int count = 0;

    // 循环到字符串尾
    while (s[count] != '\0')
    {
        /* code */
        count++;
    }
    
    // 返回
    return count;
    
}



int main(int argc, char const *argv[])
{

    char *str1 = "hello world";
    char str2[] = "When you translate this sentence, you will find that it is nonsense";


    int len1 = myStrlen(str1); // 11 正确
    int len2 = myStrlen(str2); // 67 正确

    printf("len1: %d, len2: %d\n", len1, len2);
}