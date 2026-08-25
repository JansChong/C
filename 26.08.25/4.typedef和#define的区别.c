
// typedef跟宏的区别：
// 1、宏主要用于定义常量及书写复杂的内容；typedef主要用于定义类型别名。
// 2、宏替换发生在编译阶段之前，属于文本插入替换；typedef是编译的一部分。
// 3、宏不检查类型；typedef会检查数据类型。
// 4、宏不是语句，不在最后加分号；typedef是语句，要加分号标识结束。
// 5、注意对指针的操作，typedef char * p_char和#define p_char char *区别巨大。

#include <stdio.h>

// 宏定义替换字串， 导致连续定义时， 后续变量不会配置为指针
#define p_char  char *

// typedef 起别名,  连续定义时， 后续变量也会被配置为指针
typedef char * pp_char;

int main(int argc, char const *argv[])
{


    // 连续定义时：
    int * p,  q;  // p 是 int *指针，   q 是 int 变量

    // 宏定义： 纯文本替换， 导致连续定义时， 后续变量不会配置为指针
    p_char p, q;   // 同上  p 是 char *指针，   q 是 char 变量

    // 取别名
    pp_char p, q;  // p和q都是 char* 指针



}