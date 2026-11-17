#ifndef _LINK_QUEUE_H
#define _LINK_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// 链式  +  队列
// 队列: FIFO(first in first out) 先进先出
// - 队头（Front）：允许删除/出队的一端
// - 队尾（Rear）：允许插入/入队的一端
// - 入队（enQueue）：插入元素到队尾
// - 出队（outQueue）：移除队头元素
// - 取队头（front）：仅获取队头元素，不移除

// 数据节点 结构体定义 (链式)
typedef struct Node
{
      int data;          // 数据域
      struct Node *next; // 指针域名
} node_type, *node_type_p;

// 队列管理 结构体定义 (队列)
typedef struct
{
      node_type_p front; // 队头
      node_type_p rear;  // 队尾
} link_queue_type, *link_queue_type_p;

// 入队
bool enQueue(link_queue_type_p manager, int value);
// 出队
bool outQueue(link_queue_type_p manager);
// 遍历
void forEach(link_queue_type_p manager);
// 销毁
void destroy(link_queue_type_p manager);


#endif // !_LINK_QUEUE_H