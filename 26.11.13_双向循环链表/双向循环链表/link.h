#ifndef _LINK_H
#define _LINK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 管理结构体
typedef struct node
{
      char *data;
      struct node *prev;
      struct node *next;
} node_type, *node_type_p;

// 初始化
node_type_p init_list(void);
// 创建节点
node_type_p create_node(char *value);

// 头插
bool insert_head(node_type_p head, char *value);
// 尾插
bool insert_tail(node_type_p head, char *value);
// 头删
node_type_p remove_head(node_type_p head);
// 尾删
node_type_p remove_tail(node_type_p head);
// 显示所有数据
void show_list(node_type_p head);

// 查找数据
node_type_p find_node(node_type_p head, char *value);
// 销毁链表
bool destroy(node_type_p head);

#endif