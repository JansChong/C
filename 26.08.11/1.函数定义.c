#include <stdio.h>

// 在调用函数时，调用之前必须要有函数声明或者函数定义， 否则会报警告
// 函数的声明:
int max(int n, int m);
void fn(void);
void myprintf(char *str);
float perimeter(int r);
char Atoa(char C);
void year(int year, int mon, int day);
void printf_temp(float temp, float rh, char *weather, int wind_speed);
void calc();

int main(int argc, char const *argv[])
{
    int a, b;
    // scanf("%d %d", &a, &b);
    // printf("最大值是 %d\n", max(a, b)); // 调用max函数获取两个数中较大的数

    // 调用 fn函数, 无需参数, 无返回值
    fn();

    // 接收半径求周长
    float res = perimeter(2);    // 函数调用
    printf("a的值为 %f\n", res); // 12.56

    // 大写转小写
    char str = Atoa('B');                 // 函数调用
    printf("%c 转成小写 %c\n", 'B', str); // %c输出字符: b

    year(2001, 1, 1);                                 // 函数调用  岁数： 2025年 7月 10日
    printf_temp(31.5, 78.21425, "多云转晴", 15.6789); // 多类型参数 温度 湿度 天气 风速(float会隐式转换为int 15)

    calc();


    // while 一直获取缓存区的char, 没有获取到'\n', 循环一直执行, 获取到'\n'退出循环
    /* while (getchar() != '\n') { } */
    
}

// 以下是函数定义：

// 函数返回值  函数名称(函数参数列表)
int max(int n, int m)
{
    int val = m > n ? m : n;
    return val; // int 返回值
}

// 无返回值, 函数名(无需参数)
void fn(void)
{
    // return;  可以省略return
    return; // 或者 return 空;
}

// 接受一个字符串参数 无返回值
void myprintf(char *str)
{
    // 输出一个字符串
    printf("%s\n", str);
    return;
}

// 接收半径参数， 求圆的周长， float返回值
float perimeter(int r)
{
    float val = 2 * 3.14 * r;
    return val; // float返回值
}

// 大小写转换， char返回值
char Atoa(char C)
{
    char str = C + 32;
    return str; // char返回值
}

// 多个参数 计算年龄
void year(int year, int mon, int day)
{
    int des_year = 2026;
    int des_mon = 8;
    int des_day = 11;

    printf("岁数：%d年，%d月, %d日\n", des_year - year, des_mon - mon, des_day - day);
    return; // void不需返回值
}

// 多类型参数 温度 湿度 天气 风速
void printf_temp(float temp, float rh, char *weather, int wind_speed)
{
    printf("温度： %.1f\n", temp);
    printf("湿度： %.3f\n", rh);
    printf("天气   %s\n", weather);
    printf("风速： %d\n", wind_speed);
}

// 函数的返回值，要和函数定义时定义的返回值类型一致
// 函数的返回值，在返回时如果和函数定义时定义的返回值类型不一致， 允许隐式转换的会进行隐式转换， 不允许的(比如指针)则会报警告
// 函数的参数： 在函数传参时，如果传递的参数类型和定义的参数类型不一致， 允许隐式转换的会进行隐式转换， 不允许的(比如指针)则会报警告
// 实参形参在进行传递时， 参数的类型必须一致， 顺序、数量也要一致
// 函数调用的时候， 参数的数据传送是单向的，不可逆的。 形参的初始化顺序是从右往左的

// 定义一个简易计算器，
void calc()
{
start:
    int num1, num2;
    char operators;
    scanf("%d %c %d", &num1, &operators, &num2);

    int res;
    switch (operators)
    {
    case '+':
        res = num1 + num2;
        break;
    case '-':
        res = num1 - num2;
        break;
    case '*':
        res = num1 * num2;
        break;
    case '/':
        // 有余数
        if (num1 % num2 != 0)
        {
            float result = (float)num1 / num2;
            printf("结果是%f\n", result);
            goto start;
        }
        res = num1 / num2;
        break;
    default:
        break;
    }

    printf("结果是%d\n", res);

    goto start;
}