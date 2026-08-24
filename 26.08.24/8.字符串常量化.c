#include <stdio.h>

// #define STR1 "abc";

// #define STR3(a) printf("#a\n"); 带引号无效，表示字符串 "#a\n" 了
#define STR2(a) printf(#a\n); // 没有加引号，表示 #a,  #在宏当中表示将a转成字符串


// #define STR3 #"xyz" // 如果 #直接修饰字面量，功能失效， 不能转成字符串


// 连续字符串是会默认拼接的
#define STR4(a,b) printf(#a " and " #b " : we are family\n")



int main(int argc, char const *argv[])
{

STR2(123);  // 把 123 转成字符串 "123"
STR2("abc"); // 把 "abc" 转成字符串 "\"abc\"";
    
// STR3; // 会替换成 #"xyz" 而不是  "\"xyz\""   如果 #直接修饰字面量，功能失效， 不能转成字符串

STR4(xiaoming, xiaohong); // 编译为  printf("xiaoming" " and " "xiaohong" " : we are family\n");

}