#include <stdio.h>

// 自定义一个函数, 接收一个数组 和 一个数组处理函数,  
void foreach (int a[], void (*f)(int index, int item), int len)
{
    for (int i = 0; i < len; i++)
    {
        f(i, a[i]); // 调用回调函数fn
    }
}


// 在这个数组处理函数输出下标和值
void fn(int i, int v)
{
    printf("下标%d, 值%d\n", i, v); // 输出下标和对应的值

    // 这里也可以传入一个小写字符数组转换成大写字符数组 并返回这个数组  toUppercase()
    // 或者过滤出数组中满足某个条件的数组项, 并返回这个数组项组成的数组   filter()
    // 以及其他一些自定义功能
}



int main(int argc, char const *argv[])
{
    int arr[] = {10, 20, 30, 40, 50};
    foreach (arr, fn, 5); 
}