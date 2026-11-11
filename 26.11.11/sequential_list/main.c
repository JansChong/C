#include <stdio.h>
#include "sequential.h"

// 函数声明放在头文件中

// gcc *.c -o 1 && ./1 && rm 1;
int main(int argc, char const *argv[])
{

    // 初始化
    Seq_type_p list = init_list(10);

    // 尾插
    insert_tail(list, 20);
    insert_tail(list, 30);

    // 头插
    insert_head(list, 10);
    insert_head(list, 0);

    // TODO.. 指定位置插入
    // TODO.. 指定位置删除

    // 显示元素
    show_list(list); // 0 10 20 30

    // 头部删除
    delete_head(list);
    // delete_head(list);
    // delete_head(list);
    // delete_head(list);
    // delete_head(list);

    // 尾部删除
    delete_tail(list);
    // delete_tail(list);
    // delete_tail(list);
    // delete_tail(list);
    // delete_tail(list);

    // 显示元素
    show_list(list); // 0 10 20 30

    // 在顺序表中查找指定元素
    find_value(list, 10);
    find_value(list, 20);
    find_value(list, 0);
    find_value(list, 100);

    // 销毁顺序表
    destroy_list(list);
}