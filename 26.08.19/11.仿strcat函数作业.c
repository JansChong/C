#include <stdio.h>
#include <string.h>

// 【strcat】
// 头文件 <string.h>
// 函数原型 char *strcat(char *dest, const char *src);
// 说明：strcat() 会将参数 src 字符串拷贝到参数 dest 所指的字符串尾。第一个参数 dest 要有足够的空间来容纳要拷贝的字符串。
// 返回值：返回参数 dest 的字符串起始地址。

char *myStrcat(char *dest, const char *src)
{
    // 拿到长度
    int len1 = strlen(dest);
    int len2 = strlen(src);

    for (int i = 0; i < len2; i++)
    {
        // 拼接字符串到dest末尾
        dest[len1 + i] = src[i];
    }

    return dest;
}


int main(int argc, char const *argv[])
{

    // 必须保证前面字符串申请的地址空间要足够大, 必须能容纳两个字符串, 否则会越界

    char str1[20] = "hello";
    char str2[20] = " world";

    // 调用函数, 把str2 拼接到 str1 末尾
    char * resstr = myStrcat(str1, str2);

    printf("str1 = %s\n", str1); // hello world
    printf("str2 = %s\n", str2);  //  world
    printf("resstr = %s\n", resstr);  // hello world
}