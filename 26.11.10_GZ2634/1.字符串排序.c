#include <stdio.h>
#include <string.h>



int main(int argc, char const *argv[])
{

    // 输入10个字符串，然后排序输出

    char str[10][30]; // 最大不超过30个字符的子数组 char[30] 


    // 输入
    for (int i = 0; i < 10; i++)
    {
        scanf("%s", str[i]); // 输入一个 char[30]的数组的首元素地址
    }

    // 循环 排序比较
    // 【strcmp】
    // 头文件 #include <string.h>
    // 函数原型 int strcmp(const char *s1, const char *s2);
    // 说明：strcmp() 用来比较参数 s1 和 s2 字符串。字符串大小的比较是以 ASCII 码表上的顺序来决定，此顺序亦为字符的值。
    // strcmp() 首先将 s1 第一个字符值减去 s2 第一个字符的值，若差为 0 则再继续比较下个字符，若差值不为 0 则将差值返回。
    // 例如，字符串 “Ac” 和 “ba” 比较则会返回字符 ‘A’(65) 和 ‘b’(98) 的差值 (-33)。
    // 返回值：若参数 s1 和 s2 字符串相同则返回 0，s1 若大于 s2 则返回大于 0 的值，s1 若小于 s2 则返回小于 0 的值。

    // 小的往前 大的往后
    for (int i = 0; i < 10-1; i++)
    {
        for (int j = 0; j < 10 - 1 - i; j++)
        {
            // 只要大于0， 就把大的往后放
            if( strcmp(str[j], str[j+1]) > 0) // -1, 0, 1
            {
                char temp[30];
                strcpy(temp, str[j]); // char str[] => 可以用下标修改单个元素，或者strcpy替换整个数组
                strcpy(str[j], str[j+1]);
                strcpy(str[j+1], temp);
            }
        }
    }


    for (int i = 0; i < 10; i++)
    {
        printf("%s ", str[i]);
    }
    printf("\n");

    
    // 输入 aa bb cc dd ee ab ac ad bd ca
    // 输出 aa ab ac ad bb bd ca cc dd ee 

     
    // C C++ Java PHP Python Perl Ruby R JavaScript PHP
    // C C++ Java JavaScript PHP PHP Perl Python R Ruby 

    return 0;

}