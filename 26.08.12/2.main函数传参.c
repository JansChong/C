#include <stdio.h>
#include <stdlib.h>

// main 函数的返回值， 返回给系统 或 启动程序

int main(int argc, char *argv[])
{

    printf("argc = %d\n", argc);       // 执行这个程序时， 传递的参数个数
    printf("argv[0] = %s\n", argv[0]); // 执行这个程序时， 传递的参数列表: Array<string>,  第0个: "./2"  即执行的文件名，规定运行程序的命令一定是argv的第一个参数
    printf("argv[1] = %s\n", argv[1]); // 执行这个程序时， 传递的参数列表: Array<string>   第1个:  运行命令后 携带的其他字符串参数 1
    printf("argv[2] = %s\n", argv[2]); // 执行这个程序时， 传递的参数列表: Array<string>   第2个:  运行命令后 携带的其他字符串参数 2

    
    // atoi, atol, atoll - 将字符串转换为整数
    /*   
        #include <stdlib.h>
        int atoi(const char *nptr);
        long atol(const char *nptr);
        long long atoll(const char *nptr); 
    */

    // 传递进来的是字符串，可以将字符串转成其他类型：
    // int atoi (CONST char * nptr);   只能使用数字字符，会跳过开头的非数字字符串，转换数字字符串， 遇到非数字字符就停止转换

    int num1 = atoi(argv[1]);      // 将 argv[1] 参数 “123”  转成int整数 123
    int num2 = atoi("456");        // 将"456" 转为int整数 456
    int num2 = atoi("aa 456");     // 将"aa 456" 转为int整数 456
    int num2 = atoi("aa 456.333"); // 将"aa 456.333" 转为int整数 456

   
}

// 回调函数 和 函数指针， 没有讲


// 查看man手册  man -f 函数名;  // (比如输入：man -f itoa;   输出：atoi (3)  - convert a string to an integer）
// 打开man手册  man 3 atoi;    // 这里是打开上面查到的函数名atoi 和 序列3

