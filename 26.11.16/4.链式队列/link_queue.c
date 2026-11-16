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


