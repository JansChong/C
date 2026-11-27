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
    insert_tail(list, 40);
    insert_tail(list, 50);

    // 头插
    insert_head(list, 10);
    insert_head(list, 9);
    insert_head(list, 8);
    insert_head(list, 0);

    // 显示元素
    show_list(list); // 0 8 9 10 20 30 40 50

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
    show_list(list); // 8 9 10 20 30 40

    // 在顺序表中查找指定元素
    find_value(list, 10);  //  2
    find_value(list, 20);  //  3
    find_value(list, 0);   // -1
    find_value(list, 100); // -1

    show_list(list); // 8 9 10 20 30 40

    // 指定位置插入
    insert_pos(list, 7, 0); // 头插
    show_list(list); // 7 8 9 10 20 30 40

    insert_pos(list, 15, 4); // 中间插
    show_list(list); // 7 8 9 10 15 20 30 40

    insert_pos(list, 50, 8); // 尾插
    show_list(list); // 7 8 9 10 15 20 30 40 50

    insert_pos(list, 45, 8); // 中间插
    show_list(list); // 7 8 9 10 15 20 30 40 45 50

    // 指定位置删除
    delete_pos(list, 8); // 删除下标8的45
    show_list(list);     // 7 8 9 10 15 20 30 40 50

    delete_pos(list, 0); // 头删
    show_list(list);     // 8 9 10 15 20 30 40 50

    delete_pos(list, 8); // 尾删
    show_list(list);     // 8 9 10 15 20 30 40

    delete_pos(list, 1); // 删除下标1的9
    show_list(list);     // 8 10 15 20 30 40 

    // 销毁顺序表
    destroy_list(list);
}