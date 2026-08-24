#include <stdio.h>

int main(int argc, char const *argv[])
{

    // 在c语言， 表示字符串的方式  （字符串是一个首字符地址）


    // 字符串定义
    "123 abc !#";               // 字符串常量
    char str[] = "hello world"; // 可以 用下标修改, 用strcpy替换
    char *str2 = "hello world"; // 可以直接替换整个字符串, 可以用下标读取, 不可以用下标赋值, 不可以用strcpy替换
    char str3[6] = {'a', 'b', 'c', '\0', 'e', 'f'};


    // 字符串输出
    printf("123 abc !#\n");
    printf("%s\n", str);  // hello world
    printf("%s\n", str2); // hello world
    printf("%s\n", str3); // abc
    // %s会依次往后遍历，直到遇到\0



    
    // 字符串输入
    char str[100] = {0};

    // scanf("%s", str); // 键盘输入的内容， 存储到数组地址中,   这里的scanf遇到空白字符会停止截取，所以不能用空格分隔两段字符串
    // printf("%s\n", str); // 输出

    // 集合匹配
    scanf("%[abc]", str); // 这里的scanf 只能输入集合[abc]中的字符， 遇到其他字符会停止截取

    //
    // scanf("%[^p]", str); // 这里的scanf 遇到集合[^p]中的字符 会停止截取
    scanf("%[^p\n]", str); // 这里的scanf 遇到集合[^p\n]中的字符 会停止截取


}