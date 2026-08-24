#include <stdio.h>

// 用循环封装带参宏的字段

#define S1(pi, r)                  \
    do                             \
    {                              \
        float a = pi;              \
        float b = r;               \
        printf("%f\n", a * b * b); \
    } while (0)

#define S2(pi, r)                  \
    while (0)                      \
    {                              \
        float a = pi;              \
        float b = r;               \
        printf("%f\n", a * b * b); \
    }

#define S3(pi, r)                  \
    for (int i = 0; i < 3; i++)    \
    {                              \
        float a = pi;              \
        float b = r;               \
        printf("%f\n", a * b * b); \
    }

int main(int argc, char const *argv[])
{
    S1(3.14, 2); // 编译为： do { float a = 3.14; float b = 2; printf("%f\n", a * b * b); } while (0);

    S2(3.14, 2); // 编译为：while (0) { float a = 3.14; float b = 2; printf("%f\n", a * b * b); };

    S3(3.14, 2); // 编译为：for (int i = 0; i < 3; i++) { float a = 3.14; float b = 2; printf("%f\n", a * b * b); };


    // 注意：这种宏定义的写法不带返回值
}