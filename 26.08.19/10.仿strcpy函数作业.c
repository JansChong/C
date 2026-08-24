#include <stdio.h>

// 【strcpy】 字符串拷贝
// 头文件 <string.h>
// 函数原型 char *strcpy(char *dest, const char *str);
// 说明：strcpy() 会将参数 str 字符串拷贝至参数 dest 所指的地址。
// 返回值：返回参数 dest 的字符串起始地址。
// 附加说明：如果参数 dest 所指的内存空间不够大，可能会造成缓冲溢出（buffer Overflow）的错误情况，在编写程序时请特别留意，或者用 strncpy() 来取代。


// 函数接收一个目标字符串，一个要拷贝的字符串， 返回拼接完成后的目标字符串基地址
char *myStrcpy(char *dest, const char *str)
{
    // 直接赋值的话，会修改 dest的指向
    // dest = str;

    // 逐字拷贝
    for (int i = 0;; i++)
    {
        // 逐字拷贝
        dest[i] = str[i];

        // 包括队尾得\0也得拷贝， 然后再退出
        if (str[i] == '\0')  return dest; // 函数返回 dest 的字符串起始地址
    }
}

int main(int argc, char const *argv[])
{

    // 字符串拷贝 不可以 拿字符指针常量来做为strcpy函数的第一个参数    常量数据的地址不可以被写入其他内容
    char first_str[99] = "aaaaaaaaaa";
    char *last_str = "hello";

    // 拷贝函数
    char *result_str = myStrcpy(first_str, last_str);


    
    // 验证：
    printf("字符串拷贝函数返回值: %s\n字符串拷贝函数返回的地址：%p\n", result_str, result_str); // %s读取到\0就结束了， 所以得用 %c逐个查看， 否则只能读取到 "hello\0"
    printf("原目标字符串的值: %s\n原目标字符串的地址：%p\n", first_str, first_str);             // %s读取到\0就结束了， 所以得用 %c逐个查看， 否则只能读取到 "hello\0"


    // 成功拷贝到 \0
    for (int i = 0; i < 10; i++)
    {
        printf("%c: %d\n", first_str[i], first_str[i]); // 第6位读取到 \0 空字符串
        printf("%c: %d\n", result_str[i], result_str[i]);         // 第6位读取到 \0 空字符串
    }
}