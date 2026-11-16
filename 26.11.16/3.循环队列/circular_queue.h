#ifndef _CIRCULAR_QUEUE_H
#define _CIRCULAR_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// 队列是一种非常常见的数据结构，类似于日常生活中的排队场景。队列的本质是一种特殊的线性表，其特点如下：
// - 只能在固定的两端进行操作
// - 满足“先进先出”（FIFO, First In First Out）的逻辑

// 关键术语：
// - 队头（Front）：允许删除/出队的一端
// - 队尾（Rear）：允许插入/入队的一端
// - 入队（enQueue）：插入元素到队尾
// - 出队（outQueue）：移除队头元素
// - 取队头（front）：仅获取队头元素，不移除

// 这是课堂实现 笔记实现会更优雅
// 循环队列(数组实现) 管理结构体定义
typedef struct
{
    int *data;
    int front; // 队头指针（指向队头元素）
    int rear;  // 队尾指针（指向队尾元素的下一个空位）

    int max_size; // 最大元素个数, 也用于判满 (取模)
} circular_queue_type, *circular_queue_type_p;

circular_queue_type_p init_queue(int length);
static bool isEmpty(circular_queue_type_p manager);
static bool isFull(circular_queue_type_p manager);
bool enQueue(circular_queue_type_p manager, int value);
bool outQueue(circular_queue_type_p manager);
void forEach(circular_queue_type_p manager);

#endif // !_CIRCULAR_QUEUE_H
