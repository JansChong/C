#include <stdio.h>
#include "../26.08.24/project/include/if.h"  // 在头文件使用条件编译

#define ABC 0


// 函数外部也可以使用 #ifdef
#ifdef ABC
void add(boid){
    printf("123\n");
}
#endif


int main(int argc, char const *argv[])
{
    // #ifdef 严格匹配宏是否定义， 不管宏替换的字段是什么

#ifdef ABC // 宏ABC 是否定义， 只判断有没有这个宏，不匹配它的值
    printf("123\n");
    printf("456\n");

#else // 支持 else ,  和 #ifdef 存在互斥关系
    printf("789\n");
    printf("987\n");
#endif

    // 没有 #elifdef ??
}