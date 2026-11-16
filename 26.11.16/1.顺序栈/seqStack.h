#ifndef _SEQSTACK_H
#define _SEQSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 顺序栈 管理结构体
typedef struct
{
    int *data; // 数组首地址
    int size;  // 数组可存储的最大元素个数
    int top;   // 栈顶元素下标，空栈-1
} seqStack_type, *seqStack_type_p;

// 初始化管理结构体
seqStack_type_p init_stack(int size);
bool push(seqStack_type_p manager, int value);
bool pop(seqStack_type_p manager);
void forEach(seqStack_type_p manager);
bool destroy(seqStack_type_p manager);

#endif // !_SEQSTACK_H