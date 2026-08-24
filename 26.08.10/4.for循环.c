#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    goto demo;

    // for(初始值; 判断条件; 变量修改)
    // for (int i = 0; i < 11; i++)
    // {
    //     /* code */
    // }

    // int i = 567;
    // // 第一个数
    // int a = i / 100;

    // // 第二个数
    // int b = i % 100 / 10;

    // // 第三个数
    // int c = i % 10;

    // printf("%d %d %d", a, b, c);

    // 4.3、输出100 ~999的所有的水仙花数，一个数的百位，十位，个位，每一位的立方和等于这个数本身，这个数就是水仙花数，比如：153
    // 1*1*1+5*5*5+3*3*3 == 153，就说明这个153是一个水仙花数。用for写
    for (int i = 100; i < 1000; i++)
    {

        // 第一个数
        int a = i / 100;
        // 第二个数
        int b = i % 100 / 10;
        // 第三个数
        int c = i % 10;

        if (a * a * a + b * b * b + c * c * c == i)
            printf("%d是水仙花数\n", i);
    }

    // 4.4、输入一个n，计算1+1/2-1/3+1/4-1/5+1/6....1/n；
    int n;
    double sum = 0.0;
    scanf("%d", &n);

    for (n; n > 0; n--)
    {
        // printf("执行了%d %f\n", n, 1.0 / n); // ok
        // sum = sum + 1 / n;

        if (n <= 2)
        {
            sum = sum + 1.0 / n;
        }
        else
        {
            // 奇数  偶数
            double temp = n % 2 == 0 ? 1.0 / n : -1.0 / n;
            sum = sum + temp;
        }
    }

    printf("%f\n", sum); // 4,  1.416667

demo:
    // 4.5 随机输入一个字符串， 计算 大写、小写、数字、其他字符的个数
    int capital = 0, lowercase = 0, number = 0, other = 0;
    char str[] = "aaZZu.2223"; // 编译器自动添加 '\0'
    // printf("%s", str); // 输出 "aaZZu.2223"

    for (int i = 0; str[i] != '\0'; i++)
    {
        // printf("%c ", str[i]); // 字符输出
        // printf("%d\n", str[i]); // 整型输出

        if (str[i] >= 'A' && str[i] <= 'Z') capital++;
        else if(str[i] >= 'a' && str[i] <= 'z') lowercase++;
        else if(str[i] >= '0' && str[i] <= '9') number++;
        else other++;
    }

    printf("字符串:%s\n大写: %d\n小写: %d\n数字: %d\n其他: %d\n", str, capital, lowercase, number, other);
}



// 遍历字符串的两种方式: 
/* 
#include <stdio.h>
int main() {
    // 定义字符数组，编译器自动添加 '\0'
    char str[] = "aaZZu.2223";

    // --- 遍历方法 1：下标法（最常用、直观）---
    printf("下标遍历: ");
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
    }
    printf("\n");

    return 0;
} */


/* 
#include <stdio.h>
int main() {
    // 定义字符指针指向字符串常量
    // 注意：建议加 const，因为字符串字面量通常存储在只读区
    const char *str = "aaZZu.2223";

    // --- 遍历方法 2：指针法（高效、C语言风格）---
    printf("指针遍历: ");
    char *p = str; // 创建临时指针进行遍历，保护原指针
    while (*p != '\0') {
        printf("%c", *p);
        p++; // 指针移向下一个字符
    }
    printf("\n");

    return 0;
} */
