#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    
    // int strcmp(const char *src,   const char *src);   比较两个字符串是否相同, 如果相等返回0, 不相等返回非0的值
    char *str1 = "aacd";
    char *str2 = "aacda";

    int flag = strcmp(str1, str2);
    printf("%s\n", flag == 0 ? "一样" : "不一样");

    // strcmp本质是单个字符做减法, 如果结果为0则表示相等,  如果不为0则返回相减的差值
    printf("%d\n", flag); // -2




    
    // int strncmp(const char *src,  const char *src,  size_t n);   只比较前面n个字符是否相同

    
}