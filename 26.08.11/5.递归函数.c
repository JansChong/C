#include <stdio.h>

int factorial(int i);
int sequence(int i);
int fibonacci(int i);

int main(int argc, char const *argv[])
{

    // 递归函数必须具备两个要素： 结束条件和递推关系;
    // 递推关系： 当前问题与子问题之间的关系， 将问题逐步缩小

    // 阶乘
    int count;
    // scanf("%d", &count);
    // int res = factorial(count);
    // printf("%d的阶乘是: %d\n", count, res);

    // 等差数列
    int num;
    // scanf("%d", &num);
    // int res = sequence(num);
    // printf("等差数列之和是: %d\n", res);

    // 斐波那契数列
    int fibo;
    scanf("%d", &fibo);
    int res = fibonacci(fibo);
    printf("第%d位的斐波那契数是: %d\n", fibo, res);
}

// 阶乘
int factorial(int i)
{
    // 求 n的阶乘： n = 1 * 2 * 3 * 4 * 5 * ... * n;
    // n = 1：   1
    // n = 2：   1 * 2                =  （1!）* 2;
    // n = 2：   1 * 2 * 3            =  （2!）* 3;
    // ...
    // n = m ：  1 * 2 * 3 * ... * m  =  （<m-1>!）* m;

    if (i == 1 || i == 2)
    {
        return i; // 递归出口
    }
    else
    {
        return factorial(i - 1) * i;
    }
}

// 等差数列
int sequence(int i)
{
    // n + （n-1）
    // ....
    // 5 + 4 + 3 + 2 + 1   =  5 + （4）
    // 4 + 3 + 2 + 1  = 4 + (3)
    // ...
    // 2 + 1 =  2 + (1)
    // 1

    if (i == 1)
        return 1; // 递归出口
    else
        return i + sequence(i - 1);
}

// 斐波那契数列
int fibonacci(int i)
{
    // 斐波那契数列（Fibonacci sequence）是一个从第三项开始，每一项都等于前两项之和的数列‌，通常以 0 和 1 开始，即 0, 1, 1, 2, 3, 5, 8...

    // 1： '0'    f(1)
    // 2： '1'    f(2)
    // 3： '1'    f(3): f(2) + f(1)
    // 4： '2'    f(4): f(3) + f(2)
    // 5： '3'    f(5)：f(4) + f(3)
    // 6： '5'    f(6): f(5) + f(4)
    // ...
    // n:  f(n-1) + f(n-2)

    if (i == 1 || i == 2) return i - 1; // 递归出口
    
    else return fibonacci(i - 1) + fibonacci(i - 2);
}