#include <stdio.h>

struct student
{
    int num;
    char name[20];
    float score;
};

int main(int argc, char const *argv[])
{

    // 结构体数组 (类似于对象数组)
    // 语法 =>  数据类型(结构体就是数据类型) 标识符[] = { };


    // 列表初始化, 只能在定义时初始化
    // struct student myclass[] = {1,"张三", 60,  2, "李四", 80};  // 里面存储了两个结构体, 里面的 {} 可以省略
    struct student myclass1[] = {{1, "张三", 60}, {2, "李四", 80}};

    // 不在定义时初始化, 就只能逐个初始化
    struct student myclass2[2];
    
    // myclass2[0] = { 1, "张三", 60}; // 报错 列表初始化只能在定义时初始化,,  赋值语句中不能直接用 {...}
    // {...} 初始化列表只能在变量定义（声明）时使用‌，用于给变量赋初值。
    // 变量定义完成后，单独的赋值语句 myclass2[0] = { ... }; 是‌非法语法‌，编译器会报错


    // 只能逐个初始化
    myclass2[0].num1 = 1;
    strcpy(class2[0].name, "张三");
    myclass2[0].score = 60;

    myclass2[1].num1 = 2;
    strcpy(class2[1].name, "李四");
    myclass2[1].score = 65;


    printf("学生1: %d %s %f\n", myclass2[0].num1, class2[0].name, myclass2[0].score);
    printf("学生2: %d %s %f\n", myclass2[0].num1, class2[0].name, myclass2[0].score);
}