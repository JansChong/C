#include <stdio.h>

// extern： 外部声明变量， 声明 0.文件名.c 中的全局变量
// 在编译时， 需要编译两个文件： gcc 4.静态变量修饰全局变量的作用.c 0.跨文件访问全局变量.c -o 文件名
extern int num1, num2; // 没有导入 num3

// 函数声明 => 函数默认可以跨文件调用
void func(void);


int main(int argc, char const *argv[])
{
    printf("num1 = %d\n", num1); // 可以跨文件读取到 0.文件名.c 的全局变量  num1 = 10;
    printf("num2 = %d\n", num2); // static修饰的全局变量, 不可以被跨文件读取 

    // 跨文件调用函数
    func(); // num3 = 888
}