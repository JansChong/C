#ifndef _CHAIN_STACK_H
#define _CHAIN_STACK_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// 栈：先进后出，后进先出

// 链式栈的底层是链表，栈顶在链表头部，操作全是 O(1)。

// 利用单链表实现。为了操作高效（O(1)），我们将链表的头部作为栈顶。
// - 入栈 = 链表头插法
// - 出栈 = 链表头删法

// 数据节点 结构体
typedef struct node
{
    int data;          // 数据域
    struct node *next; // 指针域
} node_type, *node_type_p;

// 栈 结构体
typedef struct 
{
    node_type_p top; // 栈顶指针
} link_stack_type, *link_stack_type_p;


// 初始化管理结构体
link_stack_type_p init_stack();
// - 入栈 = 链表头插法
bool push(link_stack_type_p manager, int value);
// - 出栈 = 链表头删法
bool pop(link_stack_type_p manager);
// 遍历
bool forEach(link_stack_type_p manager);
// 销毁
void destroy(link_stack_type_p manager);


#endif // !_CHAIN_STACK_H