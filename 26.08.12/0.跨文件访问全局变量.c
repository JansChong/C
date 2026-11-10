#include <stdio.h>

// 全局变量默认的功能：
// 1. 默认支持跨文件使用， 在需要导入的文件， 使用extern声明外部变量， 即可使用， （在编译时， 需要编译两个文件： gcc 4.静态变量修饰全局变量的作用.c 0.跨文件访问全局变量.c -o 文件名）
int num1 = 10;
// int num2 = 666; //  可以跨文件读取到 0.文件名.c 的全局变量  num2 = 666;

static int num2 = 666; // static修饰的全局变量, 不能进行跨文件使用
static int num3 = 888;

// static全局变量的 目的是什么? 
// 避免跨文件的同名变量 造成污染

// 函数默认可以跨文件调用
void func(void)
{
    printf("num3 = %d\n", num3); //  static修饰的全局变量, 不能进行跨文件使用，只能在本文件使用
}

// 静态函数无法被跨函数调用, 详见 文件5
static void func2(void)
{
}