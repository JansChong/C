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
      // 队头或队尾 等于 空 即可
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
      if (isEmpty(manager))
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

      // printf("入队成功 %d\n", value);
      return true;
}
// 出队 （头删）
bool outQueue(link_queue_type_p manager)
{
      // 判空
      if (isEmpty(manager))
      {
            printf("空队列, 无法出队\n");
            return false;
      }

      // 1 NULL
      // 存储要出队的元素， 必要时可以返回
      node_type_p temp = manager->front;

      // 头节点后移
      manager->front = temp->next;

      // 释放队头节点
      free(temp);

      // 因为只有一个元素的时候, 队头和队尾都指向了这个元素
      // 这种情况下, 出队了一个元素, 原队尾还指向这个元素, 会有bug
      if (manager->front == NULL)
      {
            manager->rear == NULL;
      }

      // 出队成功
      return true;
}

// 遍历
void forEach(link_queue_type_p manager)
{
      // 判空
      if (isEmpty(manager))
      {
            printf("队列为空, 无需遍历\n");
            return;
      }

      // 从队头遍历到队尾, 需要临时变量, 否则会破坏队头指针
      node_type_p temp = manager->front;

      // 只要不为空, 就一直输出
      while (temp != NULL)
      {
            // 输出当前数据
            printf("%d ", temp->data);
            // 指针后移
            temp = temp->next;
      }
      printf("\n"); // 遍历结束
      return;
}

// 销毁
void destroy(link_queue_type_p manager)
{

      // 数据节点 和 管理结构体都是 申请的空间, 都要销毁

      // 只要当前的数据节点不为空 (有数据)
      while (manager->front != NULL)
      {
            // 需要临时节点, 否则会破坏队头指针
            node_type_p del_node = manager->front;

            // 移动指针到下一个数据节点
            manager->front = del_node->next;

            // 释放当前空间
            free(del_node);
      }

      // 这里队尾也指向了一个数据节点的地址， 被释放以后会指向野指针，所以要改指向
      // 不过这里也无所谓了， 下面会直接释放 manager
      manager->rear = NULL;

      // 直到没有数据节点, 只要清除管理结构体
      free(manager);
      printf("队列销毁成功\n");
      return;
}
