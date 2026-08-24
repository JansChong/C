#include <stdio.h>

int main()
{
    // 不同编译器、不同的系统， 编译出来的结果可能不一样

    // %ld 会接受后面参数的值(或返回值) 以 long int 输出

    // sizeof: 计算数据类型或变量的长度（即所占字节数Byte）

    // 不同数据类型 申请的 内存空间(字节数Byte)
    printf("'a' = %ld\n", sizeof('a')); // ASCII 90 占用 4 字节， 按int类型输出
    printf("56 = %ld\n", sizeof(56)); // 占用 4 字节， 按int类型输出

    printf("1. void = %ld\n", sizeof(void)); // 占用 1 字节
    printf("2. char = %ld\n", sizeof(char)); // 占用 1 字节, 1字节等于8比特， char是8位整型
    printf("3. int = %ld\n", sizeof(int)); // 占用 4 字节
    printf("4. long = %ld\n", sizeof(long)); // 占用 8 字节， 32位机占用4字节
    printf("5. float = %ld\n", sizeof(float)); // 占用 4 字节
    printf("6. double = %ld\n", sizeof(double)); // 占用 8 字节
    printf("7. long double = %ld\n", sizeof(long double)); // 占用 16 字节， 32位机占用12字节
    printf("8. long long = %ld\n", sizeof(long long)); // 占用 8 字节

    // 指针
    printf("char * = %ld\n", sizeof(char *)); // char类型的指针占用 8 字节,  32位机占用4字节
    printf("int * = %ld\n", sizeof(int *)); // int类型的指针占用 8 字节,  32位机占用4字节
}