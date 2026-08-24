#include <stdio.h>


int main(int argc, char const *argv[])
{


    int num = 100; // num的地址 存储了 100
    int *p = &num; // 指针变量p 存储了 num的地址

    // 对地址 使用* 解引用, 可以获取到地址中的内容
    printf("*p = %d\n", *p); // 100
    printf("*&num = %d\n", *&num); // 100,   *和&互相抵消, 等于num

    // 解引用 也可以对 地址中的内容 进行修改
    *p = 200; // 等价于对a进行赋值,  字符串的时候不行 ???
    printf("*p = %d\n", *p);
    printf("a = %d\n", a);


 

}