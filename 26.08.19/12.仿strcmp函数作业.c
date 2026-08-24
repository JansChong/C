#include <stdio.h>

// 【strcmp】
// 头文件 #include <string.h>
// 函数原型 int strcmp(const char *s1, const char *s2);
// 说明：strcmp() 用来比较参数 s1 和 s2 字符串。字符串大小的比较是以 ASCII 码表上的顺序来决定，此顺序亦为字符的值。
// strcmp() 首先将 s1 第一个字符值减去 s2 第一个字符的值，若差为 0 则再继续比较下个字符，若差值不为 0 则将差值返回。
// 例如，字符串 “Ac” 和 “ba” 比较则会返回字符 ‘A’(65) 和 ‘b’(98) 的差值 (-33)。
// 返回值：若参数 s1 和 s2 字符串相同则返回 0，s1 若大于 s2 则返回大于 0 的值，s1 若小于 s2 则返回小于 0 的值。

int myStrcmp(const char *s1, const char *s2)
{
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0' ; i++)
    {
        int calc = s1[i] - s2[i];

        // 如果不相等
        if(calc != 0) return calc;
    }

    // 跑完for循环  没有不相等
    return 0;
    
}

int main(int argc, char const *argv[])
{
    char *str1 = "hello";
    char *str2 = "iello";

    int val = myStrcmp(str1, str2); // -1

    if(val == 0) printf("两个字符串相等\n");
    else printf("%d 两个字符串不相等\n", val);  // -1 两个字符不想等
}