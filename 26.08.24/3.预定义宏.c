#include <stdio.h>


// 系统自己已经定义好的宏，要用不需要自己定义，直接拿来使用即可
// __LINE__        当前行号，int
// __DATE__    预处理日期，格式“MM DD YYYY”的字符串
// __TIME__    预处理时间，格式“HH MM SS”的字符串
// __FILE__        当前文件名
// __FUNCTION__    当前函数名

int main(int argc, char const *argv[])
{

    printf("当前行：%d\n", __LINE__); // 14
    printf("当前日期：%s\n", __DATE__); //  Aug 24 2026
    printf("当前时间：%s\n", __TIME__); // 15:00:33
    printf("当前文件名：%s\n", __FILE__); // 3.预定义宏.c
    printf("当前函数名：%s\n", __FUNCTION__); // 3.预定义宏.c

    // 当前行：14
    // 当前日期：Aug 24 2026
    // 当前时间：15:01:31
    // 当前文件名：3.预定义宏.c
    // 当前函数名：main

    
}