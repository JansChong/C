#include <stdio.h>


int main(int argc, char const *argv[])
{


        // sscanf(要分割的字符串, 指定格式字符串, 变量... );  格式分割字符串, 把分割出来的内容 赋值给变量    

        // char c[10] = {};
        // int a = 0;
        // float b = 0;

        // char * str1 = "abc 123 3.14";
        // sscanf(str1, "%s %d %f", c, &a, &b);


        char a[10] = {0};
        char b[10] = {0};
        
        char * str1 = "helloworld";
        sscanf(str1, "%[^w]%s", a, b);
        printf("a:%s\n", a); // hello
        printf("b:%s\n", b); // world




}