#ifndef _LINK_H
#define _LINK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 场景：线上仓库商品台账，采用带头节点的双向循环链表存储商品信息，商品编号，名称，单价，库存。
// 实现功能
// 1、商品入库：在尾部增加一条商品记录
// 2、查找商品：根据商品编号查询商品：找到打印商品全部信息，找不到提示商品不存在
// 3、商品下架：按商品编号删除商品
// 4、修改指定商品的库存
// 5、正向遍历
// 6、反向遍历
// 7、退出

// 商品信息: 商品编号，名称，单价，库存。
struct goods
{
      int id;
      char name[30];
      float price;
      int total;
};

// 管理结构体
typedef struct node
{
      // 要存醋的商品信息 结构体
      struct goods data;

      struct node *prev;
      struct node *next;
} node_type, *node_type_p;

// 初始化
node_type_p init_list(void);
// 创建节点
node_type_p create_node(struct goods data);

// 头插
bool insert_head(node_type_p head, struct goods data);
// 尾插
bool insert_tail(node_type_p head, struct goods data);

// 头删
node_type_p remove_head(node_type_p head);
// 尾删
node_type_p remove_tail(node_type_p head);
// 删除指定的商品
node_type_p remove_node(node_type_p head, int id);

// 显示所有数据
void show_list(node_type_p head,int status);

// 查找数据
node_type_p find_node(node_type_p head, int id);

// 销毁链表
bool destroy(node_type_p head);

#endif