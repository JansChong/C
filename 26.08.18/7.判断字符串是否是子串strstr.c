#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{

    char *str1 = "abcde";

    // strstr(const char *str,  const char *str);   
    // 判断第二个字符串是否是第一个字符串的子串,

    // 如果是: 返回子串在大字符串中出现的位置,  (第二个字符串 在 第一个字符串中 第一次出现的地址)
    char *str2 = "bc";
    char *p = strstr(str1, str2);
    printf("p的地址: %p,  p的值: %s\n", p, p); // 返回第一次匹配到的地址,
                                               // 由于p是 子串在第一个字符串中匹配到的地址, (第一个字符串的地址)
                                               // 所以 %s 也可以把p当作字符串读取到\0 =>  "bcde"

                                               
    char *str3 = "zzz";
    char *k = strstr(str1, str2);                  
    // 如果不是: 返回NULL
    printf("k的地址: %p,  k的值: %s\n", k, k); //  nil  null





    // strrstr 
}