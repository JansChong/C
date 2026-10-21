#include <stdio.h>

int main(int argc, char const *argv[])
{

    // 在c语言， 表示字符串的方式  （字符串是一个首字符地址）


    // 字符串定义
    "123 abc !#";               // 字符串常量
    char str[] = "hello world"; // 可以 用下标修改, 用strcpy替换
    // 数组名是地址常量‌：str 代表数组首元素的地址，是一个常量，不能被放在赋值运算符左侧修改。这和 5 = 10; 一样不合法。
    // ‌数组不能整体赋值‌：C语言只允许在‌声明时‌用字符串字面量初始化数组，声明之后就不能再直接 str = "..." 或 str[] = "..." 来整体赋值了。‌‌
    // str[] = "hello world"; // 错误

    char *str2 = "hello world"; // 可以直接替换整个字符串, 可以用下标读取, 不可以用下标赋值, 不可以用strcpy替换
    str2 = "你好世界"; // 编译通过
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