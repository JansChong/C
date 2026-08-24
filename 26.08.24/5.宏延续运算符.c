#include <stdio.h>

// 宏延续运算符
// 当宏在一个单行上如果太长，可以考虑换行，可以使用 \ 这个运算符把字串分行表示

#define AREA(pi, r) ({         \
    float a = pi;              \
    float b = r;               \
    printf("%f\n", a * b * b); \
}) // 圆括号和花括号，可以省略， 但是一般加上， 防止优先级导致逻辑问题
// 如果不加圆括号，最后一行不要加 \ 否则会把后面一行当作宏定义的字串处理


int main(int argc, char const *argv[])
{
    // 带参宏的换行
    AREA(3.14, 2);

    // 预处理结果:  ({ int a = 3.14; int b = 2; printf("%d\n", a * b * b); });

    // 输出结果：12.560000
}