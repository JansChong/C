#ifndef _CIRCULAR_QUEUE_H
#define _CIRCULAR_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// 问题: 为什么用数组实现 循环队列 会占用掉一个空间？

// 数组循环队列空出一个位置，是为了区分「队空」和「队满」两种状态，
// 不然 `front == rear` 既可以是空，也可以是满，判断不了。
// 还有别的方案（单独加一个 size 计数变量、加标记位）就不需要浪费一个位置，我们说的 “牺牲一个位置” 是最经典、不用额外变量的实现方式。

// 循环队列两个指针：
// - `front`：队头，指向队首元素
// - `rear`：队尾，指向下一个要插入的空位

// 1. 队空条件：`front == rear`
// 2. 如果不留空位：不断入队，直到 `rear` 绕一圈追上 `front`，此时也是 `front == rear` → 和队空条件一模一样，程序分不清是空还是满！

// ✅ 解决办法：禁止把数组填到完全满，留一格不存数据
// 此时：
// - 队空：`front == rear`
// - 队满：`(rear + 1) % capacity == front`
// 代价：能存放元素的最大数量 = `数组长度 - 1`，也就是看起来 “浪费了一个空间”。


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
// 入队
bool enQueue(circular_queue_type_p manager, int value);
// 出队
bool outQueue(circular_queue_type_p manager);
// 遍历
void forEach(circular_queue_type_p manager);
// 销毁
void destroy(circular_queue_type_p manager);

#endif // !_CIRCULAR_QUEUE_H
