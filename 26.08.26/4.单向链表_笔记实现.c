#include <stdio.h>

// 要存储的数据的数据类型
type int elementType_t;

// 设计链表的数据结点 (结点结构体),    数据结点 = 数据域 + 指针域,
typedef struct node_
{
    // 要存储的数据
    elementType_t data; // 数据域
    // 指向下一个结点的地址
    struct node_ *next; // 指针域

} node_type, *node_type_p;
// node_type 是 struct node_ 的别名  (结点结构体数据类型的别名)
// node_type_p 是 struct node_ * 的别名  (结点结构体指针数据类型的别名)

// 存储单链表 头结点地址
node_type_p head = NULL;
// 存储单链表 尾结点地址
node_type_p tail = NULL;
// 存储单链表 的结点数量
node_type_p node_count = 0;

/**
 * @description: 初始化链表 -- 第一次新增结点数据(首结点)
 * @param: {} input_data 要存储的数据 (按第3个文件, 首结点也可以不用存放数据)
 * @return void 这里之所以返回void, 是因为全局变量存储了 首尾结点和结点数量
 */
void create_head_list(elementType_t input_data)
{
    // 申请空间
    node_type_p new_node = malloc(sizeof(node_type));
    if (new_node == NULL)
    {
        printf("malloc new_node error\n");
        return;
    }

    // 初始化
    new_node->data = input_data;
    new_node->next = NULL;

    // 记录
    node_count ++;   // 结点数量递增
    head = new_node; // 第一个结点 是头结点
    tail = new_node; // 第一个结点 也是尾结点
    return;
}

/**
 * @description: 尾插新增结点
 * @param: {} input_data
 * @return void
 */
void insert_list_tail(elementType_t input_data)
{
    // 申请空间
    node_type_p add_node = malloc(sizeof(node_type));
    if (add_node == NULL)
    {
        printf("malloc add_node error\n");
        return;
    }
    
    // 初始化
    add_node -> data = input_data;
    add_node -> next = NULl;
    
    // 记录
    node_count ++;   // 结点数量递增
    tail -> next = add_node; // 往之前的尾结点的next中存入新增结点
    tail = add_node; // 现在自己是尾结点

    return;
}


int main(int argc, char const *argv[])
{
}