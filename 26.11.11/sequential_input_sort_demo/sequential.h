#include <stdbool.h>

#ifndef _SEQUENTIAL_H
#define _SEQUENTIAL_H


// 创建一个顺序表，并从键盘接收数字输入，将输入的正整数按从小到大的顺序插入顺序表，并在输入负整数的时候将其绝对值数据删除。每次输入后，将顺序表的内容打印到屏幕上。

typedef struct Seq
{
    int length;
    int last;
    int* data;
} Seq_type, *Seq_type_p;

// 初始化
Seq_type_p init_list(int length);

// 输入和显示
void input_and_show_list(Seq_type_p list);

// 按从小到大的顺序插入顺序表
bool sort_insert(Seq_type_p list, int value);
// 显示顺序表
void show_list(Seq_type_p list);
#endif // !_SEQUENTIAL_H