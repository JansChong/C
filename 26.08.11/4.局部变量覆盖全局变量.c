#include <stdio.h>

int val = 10;

int main(int argc, char const *argv[])
{
    int val = 8;
    printf("val = %d\n", val); // 局部变量会覆盖全局变量
}


// 关于 内存管理，  全局变量和局部变量的初始化还没有讲