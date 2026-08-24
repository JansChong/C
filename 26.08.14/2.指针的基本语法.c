#include <stdio.h>

int main(int argc, char const *argv[])
{

    // 指针的定义和初始化

    // 定义: 数据类型 *指针变量名,  数据类型表示指针保存的数据的数据类型
    int *a1;       // 整型指针       int = 8;  return int;
    char *a2;      // 字符型指针     &char
    float *a3;     // 浮点型指针     &float
    // int (*arr)[5]; // 数组指针 
    // int *arr[5] // ？ 指针数组

    // 指针的初始化
    int num = 10;
    int *a4 = &num; // int类型的值的地址，  赋值给 int类型的指针， 类型不匹配则会有警告
    char *a22 = (char * )0x771123334; // 强制转换为 char*, 否则只是一个int类型的值

    char num2 = 'a';
    char *a5 = &num2;

    float num3 = 3.14;
    float *a6 = &num3;

    int arr[3] = {1, 2, 3};

    int *a7 = arr;  // arr指向数组首元素 的地址
    // int *a8 = &arr[0]; // 数组首元素 的地址

    // int *a9 = &arr; // 警告：数组本身的地址  这个要int类型的指针， 但是你给的是一个数组数据类型的地址
    int (*a10)[3] = &arr; // 正确 这里存了整个数组的地址

    printf("a7 = %p\n",  a7); // 结果一致
    printf("a10 = %p\n",  a10); // 结果一致
}