#include <stdio.h>
// 结构体： 每一个成员都有一个空间， 所有成员都有效

// 联合体(共用体)：  共用体的尺寸，是其成员中最大的成员的尺寸决定的， 其成员间的基地址是共用的
// 也就是说， 给共用体的某个成员赋值， 会覆盖掉其他成员的值， 其他成员的值不一定等于赋值的这个成员的值
// 也就是说， 成员之间形成一种互斥的逻辑， 在某个时刻只有一个成员有效

union p
{
    char a;
};

union u
{
    int a; // 4
    // short b;    //
    short b[3]; // 40
    // char c; // 1

    // float c; //  整数的c会隐式转换成float类型的c,  按小数的二进制位的方式来存储
};

main(int argc, char const *argv[])
{

    // union u d = {10, {1, 2, 3}, 'A'}; // 联合体不可以通过 {} 普通初始化， 因为联合体同一时间只有一个成员有效
    // union u d = {.a = 10, .b = {1, 2, 3}, .c = 'A'}; // 联合体可以通过指定成员初始化， 但只有最后一个成员有效

    // 等价于 单独赋值
    // d.c = 'A';

    // 输出
    // printf("d.a = %d\n", d.a); // 最后一个成员是 char 'A'， 覆盖第一个成员的int, 所以 d.a 只有 'A'的 ascii 65
    // printf("d.b[0] = %d\n", d.b[0]); // 65
    // printf("d.b[1] = %d\n", d.b[1]); // 0
    // printf("d.b[2] = %d\n", d.b[2]); // 0
    // printf("d.c = %c\n", d.c); // 'A'

    union p a2;
    a2.a = 2;

    union u a1;
    a1.a = 2;

    printf("联合体的大小 %ld\n", sizeof(union u)); // 20
    printf("联合体的地址 %p\n", &a1.a);            // 30   00 

    printf("联合体的大小 %ld\n", sizeof(union p)); // 20
    printf("联合体的地址 %p\n", &a2.a);            //  2f   ff

    // printf("联合体的大小 %ld\n", sizeof(d));       // 20
}