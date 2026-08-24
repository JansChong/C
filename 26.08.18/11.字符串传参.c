#include <stdio.h>

// 字符串传参 本质是传递的首字符地址    (既然是地址传递，那么函数中的修改也会影响外面的变量)
// 字符串作为函数返回，返回首字符地址

char *func1(char *str)
{
    str[0] = 'A';
    return str;
}


char *func2(char str[])
{
    str[0] = 'A';
    return str;
}




int main(int argc, char const *argv[])
{

    char str2[] = "12345";

    // char *resstr = func1(str2);// A2345
    char *resstr = func2(str2);// A2345
    printf("%s\n", resstr); 
}