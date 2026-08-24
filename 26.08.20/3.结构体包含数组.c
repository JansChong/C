#include <stdio.h>

// 结构体包含特殊成员
struct goods
{
    int num;
    float price;
    int arr[3];
    char name[10];
}

main(int argc, char const *argv[])
{

    // 定义结构体变量和 普通初始化 (列表形式)
    // struct goods ice = {1, 2.0, {5, 6, 7}, "冰块"}; // 可行
    struct goods ice = {1, 2.0, 5, 6, 7, "冰块"};   // 可行
    
    printf("%d\n", ice.num);
    printf("%s", ice.name);
    printf("%f\n", ice.price);
    printf("%d %d %d\n", ice.arr[0], ice.arr[1], ice.arr[3]);



    // 定义结构体变量和 指定成员初始化
    struct goods wather = {
        .num = 2,
        .name = "哇哈哈", // char*字符串 和 char str[]  字符串初始化时, 可以直接字符串赋值1次,   {}列表初始化这种只能在定义时初始化
        .arr = {1,2,3},
        .price = 5.0
    };

    printf("%d\n", wather.num);
    printf("%s", wather.name);
    printf("%f\n", wather.price);
    printf("%d %d %d\n", wather.arr[0], wather.arr[1], wather.arr[2]);
    
}