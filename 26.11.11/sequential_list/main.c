#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sequential.h"

// 函数声明放在头文件中

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

    // 显示元素
    show_list(list); // 0 10 20 30

    // 头部删除
    delete_head(list);
    delete_head(list);
    delete_head(list);
    delete_head(list);
    delete_head(list);
    // 尾部删除

    // 查找数据

    // 显示元素
    show_list(list); // 0 10 20 30
}