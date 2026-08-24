#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 头文件 <string.h>
    // 函数原型： size_t strlen (const char *s);
    // 说明：strlen() 用来计算指定的字符串 s 的长度，不包括结束字符 ‘\0’。
    // 返回值：返回字符串 s 的字符数。

    
    char str[] = "hello world";
    // size_t  strlen(const char *s)  函数原型,   作用是获取字符串长度,   需要导入头文件<string.h>
    int size = strlen(str);                            // 获取有效字符串的长度 
    int size2 = sizeof(str);                           // 获取所占内存的空间
    printf("字符串长度: %d字节\n", size);              // 11   strlen() 不包含 \0
    printf("字符串所占内存空间大小: %d字节\n", size2); // 12   sizeof() 包含 \0



    char *str = "hello world";
    // size_t  strlen(const char *s)  函数原型,   作用是获取字符串长度,   需要导入头文件<string.h>
    int size = strlen(str);                            // 获取有效字符串的长度
    int size2 = sizeof(str);                           // 获取所占内存的空间
    printf("字符串长度: %d字节\n", size);              // 11   strlen() 不包含 \0
    printf("字符串所占内存空间大小: %d字节\n", size2); // 8   char * 在64位机 占8字节


    int size3 = strlen("asdf");
    
}
