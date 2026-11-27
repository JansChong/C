#include <stdbool.h>

// 头文件中所存放的内容，就是各个源码文件的彼此可见的公共资源，包括：
// 全局变量的声明。
// 普通函数的声明。
// 静态函数的定义。
// 宏定义。
// 结构体、联合体的定义。
// 枚举常量列表的定义。
// 其他头文件。

#ifndef _SEQUENTIAL_H
#define _SEQUENTIAL_H

typedef struct Seq
{
    int length;
    int last;
    int * data;
} Seq_type, *Seq_type_p;


// 全局变量、普通函数的定义一般出现在某个源文件（*.c *.cpp）中，其他的源文件想要使用都需要进行声明，因此一般放在头文件中更方便。
// 静态函数、宏定义、结构体、联合体的定义都只能在其所在的文件可见，因此如果多个源文件都需要使用的话，放到头文件中定义是最方便，也是最安全的选择。

// 函数声明
// 初始化
Seq_type_p init_list(int length); 
// 头插
bool insert_head(Seq_type_p list, int value);
// 尾插
bool insert_tail(Seq_type_p list, int value);
// 删除头部
bool delete_head(Seq_type_p list);
// 尾部删除
bool delete_tail(Seq_type_p list);
// 在顺序表中查找指定元素
int find_value(Seq_type_p list, int value);
// 指定位置插入
bool insert_pos(Seq_type_p list, int value, int pos);
// 指定位置删除
bool delete_pos(Seq_type_p list, int pos);
// 显示顺序表
void show_list(Seq_type_p list);
// 销毁顺序表
void destroy_list(Seq_type_p list);

#endif // !_SEQUENTIAL_H