#include <stdio.h>

int *sum(int m, int n);

int main(int argc, char const *argv[])
{
    /* code */
    // return 0; // 对于main函数， return 0表示正常， return 其他值表示不正常

    int a = 10;
    int b = 20;
    int *m = sum(a, b); // 用指针 接收函数返回的地址
    
    printf("%p\n", m);  // 看看函数结束之后 是否还可以使用 m 的地址:  nil 拿不到地址， 函数结束后空间已经释放
    printf("%d\n", *m);  // 访问m中的数据： 段错误，非法访问内存
}


// 函数被调用时， 内存会给函数分配一个栈空间， 这个栈空间会给形参分配空间并用实参初始化， 当函数返回时，这个函数的栈空间会被释放，后续无法访问这个空间
int *sum(int m, int n)
{
    printf("m： %p\n", &m); // 这里可以 输出m的地址
    int sum = m + n; // 局部变量： 在函数的栈空间内会给 局部变量也分配用于计算和存储的空间， 当函数结束时，局部变量所在的内存会被系统收回，因此也叫局部变量
    return &m; // 以指针的形式 返回 m 的地址

    // return 之后不可再访问函数的局部变量， 因此返回一个局部变量的地址通常是错误的
}


