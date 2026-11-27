#ifndef _SEQSTACK_H
#define _SEQSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// LIFO(last in first out, 后进先出)
// 栈：先进后出，后进先出 （即只需尾插尾删）
// 顺序栈 管理结构体
typedef struct
{
    int *data; // 数组首地址
    int size;  // 数组可存储的最大元素个数
    int top;   // 栈顶元素下标，空栈-1
} seqStack_type, *seqStack_type_p;

// 初始化管理结构体
seqStack_type_p init_stack(int size);
// 入栈、压栈 (尾插)
bool push(seqStack_type_p manager, int value);
// 出栈、弹栈 (尾删)
bool pop(seqStack_type_p manager);
// 遍历打印
void forEach(seqStack_type_p manager);
// 销毁
bool destroy(seqStack_type_p manager);

#endif // !_SEQSTACK_H