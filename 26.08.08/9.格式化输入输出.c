#include <stdio.h>

int main(int argc, char const *argv[])
{

    // stdin: 标准输入
    // stdout: 标准输出
    // stderr: 标准出错

    printf("hello world"); // printf 会先保存在"输出行缓冲区", 等到满足一定条件时, 才会输出到标准输出
    // fflush(stdout);
    // while (1)
    // { // 上面的hello world不会输出,因为没有满足以下五个条件
    // };

    // 刷出缓冲区的条件
    // 1. 整个程序结束的时候
    // 2. 缓冲区满的时候 一般超过或等于1024就会立即输出, 但不绝对
    // 3. 后面加上scanf
    // 4. 加上\n
    // 5. fflush函数,   语法: fflush(stdout),    用途: 刷出缓冲区

    

    // 输入：scanf
    // 功能：在输入行缓冲中获取数据。
    // int scanf(const char *format, ...);
    // 例如：scanf("%d", &a);    //通过%d的一个格式进行输入一个整数，通过&去地址找到a的地址，存放到a里面
    // scanf("") 要按照里面的格式进行输入吗


    // while (getchar() != '\n'); // 清空输入缓冲区里面的数据
    // 用途：去掉上一次输入遗留的垃圾字符（最常见就是残留的回车\n），防止干扰下一次字符输入。


}