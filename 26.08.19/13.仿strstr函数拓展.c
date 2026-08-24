#include <stdio.h>
#include <string.h>

// 头文件 <string.h>

// 函数原型 char *strstr(const char *haystack, const char *needle);
// 说明：strstr() 会从字符串 haystack 中搜寻字符串 needle，并将第一次出现的地址返回。
// 返回值：返回指定字符串第一次出现的地址，否则返回 0。

char *myStrstr(const char *haystack, const char *needle)
{

    // 思路 用 strncmp 比较 needle长度 的两个字符串，   比较的范围：在  haystack长度 - needle长度 的上 (等于),  比较needle的长度
    int boundary = strlen(haystack) - strlen(needle);
    int length = strlen(needle);

    // 这里如果第二个字符串比第一个长， 则长度相减的值为负数， 小于负数进不去循环， 直接输出0， 不是子串
    for (int i = 0; i <= boundary; i++)
    {
        // char arr[99] = haystack[3];  语法错误，
        // char *arr = haystack[3];  语法错误，

        char *arr = haystack + i; // 地址偏移， 每次循环取到后半截的字符
        // printf("%s\n", arr); // 这里可以查看  从 "hello world"  取到  "rld"  的过程
        // 这里也可以使用 strncpy 拷贝字符串可能会更简单

        // 比较两个字符串， 比较后一个子串的长度
        int count = strncmp(arr, needle, length);
        // 如果等于0, 两个字符串相等， 是子串， 返回下标
        if (count == 0)
        {
            printf("找到子串%s\n", arr);
            return (haystack + i);
        };
    }

    // 经过for循环仍没有return下标，表示比较完了但没有找到子串，  返回0, 不是子串
    return (char *)0;
}

int main(int argc, char const *argv[])
{
    // char *str1 = "hello world";
    // char *str2 = "rld";

    // char *res = myStrstr(str1, str2);

    // printf("原字符串地址%p\n", str1); // 小地址
    // printf("第一次匹配到子串的地址%p\n", res);   // 大地址

    // 两个地址相差8位， 正确！

    // if (res == 0)
    //     printf("不是子串\n");
    // else
    //     printf("%s 是 %s 的子串\n", str2, str1);


        

    // 验证
    char *str1 = "hello world";
    char *str2 = "rld";

    char *res = myStrstr(str1, str2);
        
   if (res != NULL) {
        printf("找到子串内容: %s\n", res);
        
        // 2. 验证地址关系
        printf("2. str1 的首地址:      %p\n", (void*)str1);
        printf("3. res (返回指针)地址: %p\n", (void*)res);
        
        // 计算偏移量
        long offset = res - str1;
        printf("4. 偏移量 (索引):      %ld\n", offset);
        
        // 验证偏移位置字符
        printf("5. str1[%ld] 是:       '%c'\n", offset, str1[offset]);
    } else {
        printf("未找到\n");
    }
}