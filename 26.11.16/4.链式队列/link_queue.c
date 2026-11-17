#include "link_queue.h"

// 初始化 -- 返回管理结构体
link_queue_type_p init_link_queue()
{
      // 管理结构体申请空间
      link_queue_type_p manager = (link_queue_type_p)malloc(sizeof(link_queue_type));

      // (也可以不申请, 但是需要把 管理结构体指针 传参进来)
      // 因为要初始化 队头和队尾
      manager->front = NULL;
      manager->rear = NULL;

      printf("链式队列已初始化\n");
      // 返回初始化后的管理结构体
      return manager;
}

// 判空
static bool isEmpty(link_queue_type_p manager)
{
      return manager->front == NULL;
}

// 入队 (尾插)
bool enQueue(link_queue_type_p manager, int value)
{
      // 新建数据节点
      node_type_p new_node = (node_type_p)malloc(sizeof(node_type));
      if (!new_node)
      {
            printf("新建节点失败, 入队失败\n");
            return false;
      }

      new_node->data = value;
      new_node->next = NULL;

      // 如果原队列没有元素
      if (!isEmpty(manager))
      {
            // 队头和队尾都指向新节点
            manager->front = new_node;
            manager->rear = new_node;
      }
      // 如果原队列有元素
      else
      {
            // 原队尾的next指向新节点
            manager->rear->next = new_node;
            // 把新节点作为队尾
            manager->rear = new_node;
      }

      printf("入队成功\n");
      return true;
}
// 出队
bool outQueue(link_queue_type_p manager)
{
      // 判空
      if (!isEmpty(manager))
      {
            printf("空队列, 无法出队\n");
      }

      
      
}
// 遍历
void forEach(link_queue_type_p manager)
{
}
// 销毁
void destroy(link_queue_type_p manager)
{
}
