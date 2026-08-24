#include <stdio.h>

// 结构体是一种数据类型
struct student
{
    int num;
    char name[20];
    float score;
};

// 结构体 传参:  这里是值传递, 函数内的修改不会影响外部的结构体变量
void func1(struct student people)
{
    people.score = 100;
    printf("值传递, 函数内修改成绩: %d %s %f\n", people.num, people.name, people.score);
}

// 结构体指针 传参: 这里是地址传递, 函数内的修改会影响外部的结构体变量
void func2(struct student *people)
{
    people->score = 120;
    printf("地址传递, 函数内修改成绩:%d %s %f\n", people->num, people->name, people->score);
}


int main(int argc, char const *argv[])
{

    // 结构体变量a
    struct student a = {1, "张三", 90};

    // 结构体指针,  p指向a的地址
    struct student *p = &a;

    // 访问 结构体指针 成员 的值,   使用  -> 语法
    printf("%d %s %f\n", p->num, p->name, p->score); // 输出
    // printf("%d %s %f\n", (*p).num, (*p).name, (*p).score);  // 也可以输出

    // 修改 结构体指针 成员 的值
    p->score = 99;
    printf("%d %s %f\n", p->num, p->name, p->score); // 修改成功



    // 结构体传参 => 这里是值传递, 函数内的修改不会影响外部的结构体的值
    func1(a);
    printf("值传递 函数外打印原结构体, 发现没有被函数修改: %d %s %f\n", a.num, a.name, a.score);
    

    // 结构体指针传参 => 这里是地址传递, 函数内的修改会影响外部的结构体的值
    func2(p);
    printf("地址传递 函数外打印原结构体, 发现被函数修改: %d %s %f\n", a.num, a.name, a.score);

}
