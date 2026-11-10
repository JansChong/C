#include <stdio.h>
#include <string.h>

// 基本语法
// struct 结构体标签 { 成员1; 成员2; }

// 定义结构体
struct student
{
    int year;
    char name[10];  //  这个name不可以直接赋值, 因为 name是一个数组,  只能在初始化时可以直接列表初始化赋值,   后面要用下标或者strcpy赋值
    // char *name;  //   这个 name可以直接赋值,  指向其他字符串的地址， 但是不能用scanf输入， 也不能用 strcpy 拷贝， 因为 没有初始化 或者 也不能修改常量数据的地址
    float score;
};
// 相当于定义了一个自定义数据类型， 类似于 interface 接口

// 定义结构体 + 定义变量
struct teacher
{
    int year;
    char name;
    float score;
} c, d; // c, d 是全局变量

// 定义匿名结构体 + 定义变量
struct
{
    int year;
    char name;
    float score;
} e, f; //  只有e和f变量可以使用这个匿名结构体

int main(int argc, char const *argv[])
{
    // 由于结构体内部拥有多个不同类型的成员，因此初始化采用与数组类似的列表方式
    // 结构体的初始化有两种方式，1普通初始化，(列表形式)2、指定成员初始化
    // 为了能适应结构体类型的升级迭代，一般建议采用指定成员初始化

    // 结构体变量的定义 和 普通初始化  (列表形式)
    struct student a = {18, "M", 88.6}; // 不可以交换位置  (数据类型要一一对应, 否则会尝试隐式转换 或者 报警告,   没有初始化数据与其对应则初始化为0)

    // 结构体变量的定义 和 指定成员初始化  (建议采用指定成员初始化)
    struct student b = {.year = 18, .name = "N", .score = 90}; // 可以交换位置 (没有初始化数据与其对应则初始化为0)

    // 用现成的结构体变量初始化
    struct student c = b;


    // 通过scanf赋值给结构体
    // scanf("%d %s %f", &a.year, a.name, &a.score); // 可以赋值

    // printf("年龄: %d\n", a.year);  // 输入的值
    // printf("名字: %s\n", a.name);  // 输入的值
    // printf("成绩: %f\n", a.score); // 输入的值


    // 结构体成员访问
    a.year = 19;
    // b.name = "ww"; //  字符串被数组保存时, 不可以对数组直接赋值,   可以用下标 赋值 或者 strcpy
    strcpy(b.name, "小王");
    c.score = 100;

    printf("年龄: %d\n", a.year);  // 19
    printf("名字: %s\n", b.name);  // 小王
    printf("成绩: %f\n", c.score); // 100.000000
}