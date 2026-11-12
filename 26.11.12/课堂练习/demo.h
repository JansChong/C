#ifndef _LINKED_H
#define _LINKED_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// 学生信息
struct student_info
{
    int id;
    char name[20];
    double score;
};

// 链表节点设计
typedef struct node
{
    // 要处理的数据
    struct student_info data; // 结构体
    struct node *next;
} node_type, *node_type_p;

// 初始化头结点
node_type_p init_list();
// 创建新节点 -> 然后才可以插入节点
node_type_p create_node(struct student_info value);

// 头插
bool insert_head(node_type_p head, struct student_info value);
// 尾插
bool insert_tail(node_type_p head, struct student_info value);
// 头删
node_type_p remove_head(node_type_p head);
// 尾删
node_type_p remove_tail(node_type_p head);
// 查找数据
node_type_p search_data(node_type_p head, int id);
// 按学号移除数据
node_type_p remove_data(node_type_p head, int id);

// 显示所有数据
void show_list(node_type_p head);
// 销毁所有数据
bool destroy(node_type_p head);

#endif // !_LINKED_H

//