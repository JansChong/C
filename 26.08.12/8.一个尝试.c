#include <stdio.h>

int main(int argc, char const *argv[])
{

    char *a = "hello";
    printf("%s\n", a);  // hello,  a是字符串"hello"的地址
    printf("%p\n", a);  // 地址1
    // printf("%p\n", &a); // 指针变量a自己在内存中的地址

    a = "你好"; // 这里为什么不带*号 ？   a 是char *类型，存储的是字符串的首字符地址，这里替换成了"你好"的地址
    printf("%s\n", a);  // 你好
    printf("%p\n", a);  // 地址2
    // printf("%p\n", &a); // 指针变量a自己在内存中的地址


    // *a = "你好"; // 警告：从'char*'向'char'赋值会使指针中的整数不经过强制转换[-Wint转换]

    // printf("%s\n", a);  // 你好
    // printf("%p\n", a);  // 地址1
    // printf("%p\n", &a); // 指针变量a自己在内存中的地址

    // &a = 'a'; // 报错




    int a = 10;
    int * b = &a;

    b = 30; 

    printf("%d", a);
    printf("%p", *b);
}