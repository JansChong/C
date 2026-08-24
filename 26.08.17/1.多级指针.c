#include <stdio.h>
    
int main(int argc, char const *argv[])
{

    // 多级指针: 把一个指向指针变量的指针, 称为多级指针变量

    int a = 10;
    int *p = &a;   // 一级指针: 指向一个数据的地址的指针
    int **p1 = &p; // 二级指针: 指向一个一级指针地址的指针
    int ***p2 = &p1;

    printf("%d\n", ***p2); // 10

}