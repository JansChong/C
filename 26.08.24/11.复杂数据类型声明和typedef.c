#include <stdio.h>

// 在C语言中有时候有些声明是比较复杂的：
// void *(*puppy[3])(void (*kitty)(int tiger, int monkey));
// //puppy是一个函数指针数组，数组总共3个元素，返回值void *
// //函数的参数是一个函数指针，返回值是void，参数是两个整型数据

// 对于复杂的声明，解读方式：
// 1、从左往右边找到第一个非关键字标识符
// 2、以标识符为中心，按照运算符优先级逐层解释

// 对于一些复杂的声明，我们可以用typedef关键字起别名
// 用法：
// typedef 数据类型 别名;    //数据类型可以是任意数据类型
// 比如: typedef  void *(*puppy[3])(void (*kitty)(int tiger, int monkey)) o;


// typedef 数据类型 别名;
typedef int uint32; // typedef 数据类型 取 别名
typedef char uint8;
typedef int *int_p;
// typedef 数据类型 别名;
typedef struct student
{
    int age;
    char sex;
} people  *people1; // 这里的 *people 查一下


#define int_pp int *  // 宏定义 数据类型


// 定义函数
int func(int a, int b) {return  a+b};

// 函数指针别名 就是 指针名func,  所以 数据类型 func_  就等价于  int (*func_) (int a, int b) 
typedef int (*func_) (int a, int b); // 这里的别名 就是 func_


int main(int argc, char const *argv[])
{


    uint32 a = 10; // uint32 a = 10;
    uint8 b = 'x'; // uint8 b = 'x';    typedef 在预处理阶段 是不会进行替换的， 是在编译阶段处理的
    int_p c = &a;  // int_p c = &a;
    int_pp d = &a; // int * d = &a;    宏替换数据类型， 实在预处理阶段替换的

    // int a = 10;
    struct student a = {18, "M"}; 
    people b = {17, "N"}; // 数据类型别名

    
    printf("%d\n", a);        // 10
    printf("%c\n", b);        // 'x'
    printf("%p %p\n", &a, d); // 'x'


    func_ p1 = func; // 这里的 p1 就是函数指针 (func的入口地址)


}





// typedef跟宏的区别：
// 1、宏主要用于定义常量及书写复杂的内容；typedef主要用于定义类型别名。
// 2、宏替换发生在编译阶段之前，属于文本插入替换；typedef是编译的一部分。
// 3、宏不检查类型；typedef会检查数据类型。
// 4、宏不是语句，不在最后加分号；typedef是语句，要加分号标识结束。
// 5、注意对指针的操作，typedef char * p_char和#define p_char char *区别巨大。

