#include <stdio.h>
#include "../26.08.24/project/include/if.h"  // 在头文件使用条件编译


int main(int argc, char const *argv[])
{




// #idndef判断宏是否未定义，  如果宏未定义，则条件为真


// 以头文件举例子：
#ifndef IF_H  // 判断宏 (文件名)是否未定义
#define IF_H  // 如果未定义， 则定义宏 (文件名)



#endif // !IF_H

// 这样在多次导入头文件时， 不会重复拷贝头文件中的文件内容

}