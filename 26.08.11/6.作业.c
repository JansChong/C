// #include <stdio.h>

// void exchange_two_values();
// int a = 1, b = 2;

// int main(int argc, char const *argv[])
// {
//     printf("原值: a=%d, b=%d\n", a, b);
//     exchange_two_values();
//     printf("函数外成功互换: a=%d, b=%d\n", a, b); // 1 2
// }

// //  输入两个整数，设计一个函数， 通过调用这个函数， 实现两个值的交换， 并在函数体内和函数体外打印交换的结果，怎么让这个结果一致？
// void exchange_two_values()
// {
//     int temp = a;
//     a = b;
//     b = temp;

//     printf("函数内成功互换: a=%d, b=%d\n", a, b); // 2 1
// }

#include <stdio.h>
#include <stdbool.h>

void exchange_two_values(int a, int b);
void prime_number(void);
int sequence(int i);
int days(int year, int month, int date);

int main(int argc, char const *argv[])
{
    // 两数互换
    int a = 1, b = 2;
    // printf("原值: a=%d, b=%d\n", a, b);
    // exchange_two_values(a, b);
    // printf("函数外未互换: a=%d, b=%d\n", a, b);                                                                              // 1 2
    // printf("要让函数外也互换，需要把变量作为全局变量直接操作， 且不能以传参的方式传递值，否则只是在操作参数这个局部变量\n"); // 1 2

    // 求质数
    // prime_number();

    // 等差数列
    // int num;
    // scanf("%d", &num);
    // int res = sequence(num);
    // printf("等差数列之和是: %d\n", res);

    // 键盘输入 年月日, 函数递归实现 这个日期是这一年的第几天, 并返回
    printf("输入年月日\n");
    int year, month, date;
    scanf("%d-%d-%d", &year, &month, &date);
    int day = days(year, month, date);
    printf("这是%d的第%d天\n", year, day);
}

//  输入两个整数，设计一个函数， 通过调用这个函数， 实现两个值的交换， 并在函数体内和函数体外打印交换的结果，怎么让这个结果一致？
void exchange_two_values(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    printf("函数内互换: a=%d, b=%d\n", a, b); // 2 1
}

// 编写一个判断素数的函数， 传入一个大于1的自然数，判断是否是素数
void prime_number(void)
{
    printf("输入一个自然数: \n");
    int count;
    scanf("%d", &count);

    // 质数: 1 - 它只身之外， 没有别的数可以整除它
    // 证明一个数是质数， 用反证法， 只要证明 1 -> 它自身之外没有别的数可以整除它， 就是质数

    for (int i = 2; i <= count/2; i++)  //  数 / 一半 = 2，   不考虑比2小的因数， 即不考虑比一半大的数的存在因数；  如11，不考虑5以上的因数
    {
        if (count % i == 0) // 如果能被 1 -> 他之间的数 整除
        {
            printf("%d不是质数\n", count);
            return; // 只要找到一个因数, 直接判定不是质数, 直接退出函数
        }
    }

    // 经过for循环没有退出函数, 这个数是质数
    printf("%d是质数\n", count);
}

// 累加函数: 输入一个值, 实现  1+2+3+...+n 运算 并返回
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



// 输入一个日期 用函数递归判断这个日期是这一年的第几天
int days(int year, int month, int date)
{

    // 否则 每一个月份的日期 = 它前一个月的天数 + date
    if (month == 12 || month == 10 || month == 7 || month == 5)
    {
        return days(year, month - 1, date) + 30;  // 递归
    }
    else if (month == 11 || month == 9 || month == 8 || month == 6 || month == 4 || month == 2)
    {
        return days(year, month - 1, date) + 31;  // 递归
    }
    else if (month == 3)
    {
        int c = year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? 29 : 28;
        return days(year, month - 1, date) + c;  // 递归
    }
    // 如果是1月份, 日期就是天数
    else if (month == 1)
    {
        return date;  // 递归出口
    }
    
}