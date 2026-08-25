#include <stdio.h>
#include "../26.08.24/project/include/if.h"  // 在头文件使用条件编译

#if 5 // 条件成立

void func(struct student) // 参数类型是在头文件if.h中定义的条件编译
{
    printf("321\n");
}
// printf("321\n"); // ❌ 错误：printf 必须在函数内部调用

#endif

int main(int argc, char const *argv[])
{

    // 条件编译： 根据不同的条件， 决定编译不同的代码， 生成不同的目标文件
    // 表达式为真： 则预处理阶段不会删除里面的代码
    // 表达式为假： 则预处理阶段直接删除里面的代码

#if 1 > 2            // 条件为假， 常量表达式可以正常处理
    printf("123\n"); // 在预处理阶段处理
    printf("456\n"); // 条件不成立， 就不会编译里面的代码， 而是直接删除掉里面的代码
#endif

int a = 10;
#if a > 0            // 变量表达式无法正常处理， 预处理阶段变量默认设置为0， 尽量不要把变量作为条件编译的条件
    printf("000\n"); // 带变量的条件表达式直接为假，
    printf("000\n");
#endif

#if 5 // 条件成立
    printf("654\n");
    printf("321\n");
#endif

#if AA // #if后 携带环境变量AA,  需要在编译的时候， 携带环境变量， 里面的代码也可以被编译
    printf("AAA\n");
    printf("AAA\n");
#endif

#if 5 // #if 支持嵌套
    printf("654\n");
    printf("321\n");

#if 10
    printf("嵌套关系\n");
#endif
#endif

#if 1 > 2 // #if 支持 #elif
    printf("654\n");
    printf("321\n");
#elif 1 < 2 // else if,  和 其他 if 存在互斥关系
    printf("支持elif\n");
#elif 1 < 2 // else if,  和 其他 if 存在互斥关系
    printf("支持elif\n");
#else       // 支持 else
#endif

    // gcc main.c -E -DAA      // 预处理时： 大写D参数， 后面的AA即为环境变量
    // gcc main.c -o main -DAA   // 编译时
}