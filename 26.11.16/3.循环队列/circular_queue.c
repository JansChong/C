#include "circular_queue.h"

// 这是课堂实现 笔记实现会更优雅
// 初始化结构体
circular_queue_type_p init_queue(int length)
{
    // 为管理结构体 申请空间
    circular_queue_type_p managar = (circular_queue_type_p)malloc(sizeof(circular_queue_type));

    if (managar == NULL)
    {
        printf("内存申请失败\n");
        return NULL;
    }

    // 初始化数据
    managar->data = (int *)calloc(length, sizeof(int));
    // 如果申请失败
    if (managar->data == NULL)
    {
        printf("内存申请失败\n");
        free(managar);
        return NULL;
    }

    // 队头指针 队尾指针 初始化
    managar->front = 0;
    managar->rear = 0;
    // 最大元素个数, 也用于判满 (取模)
    managar->max_size = length;

    return managar;
}

// 判空
static bool isEmpty(circular_queue_type_p manager)
{
    // 队头等于队尾, 空队列
    return manager->front == manager->rear;
}

// 判满
static bool isFull(circular_queue_type_p manager)
{
    // 取模判定队列是否为空
    return (manager->rear + 1) % manager->max_size == manager->front;
}

// 入队
bool enQueue(circular_queue_type_p manager, int value)
{
    // 判满
    if (isFull(manager))
    {
        printf("队列已满, 无法入队\n");
        return false;
    }

    // 入队
    manager->data[manager->rear] = value;

    // rear会加到很大, 超过int *data的下标, 可能会越界访问其他地址
    // manager->rear++

    // 取余, 循环队尾指针, 避免上面的情况
    manager->rear = (manager->rear + 1) % manager->max_size;

    printf("%d ", manager->front);
    printf("%d \n", manager->rear);
    return true;
}

// 出队
bool outQueue(circular_queue_type_p manager)
{
    // 判空
    if (isEmpty(manager))
    {
        printf("空队列, 无法出队\n");
        return false;
    }

    // 定义变量, 存放要出队的数据 (如有必要可以返回)
    int value = manager->data[manager->front];

    // front会加到很大, 超过int *data的下标, 可能会越界访问其他地址
    // manager->front++

    // 取余, 循环队头指针, 避免上面的情况
    manager->front = (manager->front + 1) % manager->max_size;

    return true;
}

// 遍历队列  TODO..
void forEach(circular_queue_type_p manager)
{
    // 判空
    if (isEmpty(manager))
    {
        printf("空队列, 无需遍历\n");
        return;
    }

    // TODO..  队头可能再后面, 队尾可能再前面, 所以只要队头不等于队尾, 让队头往后加即可
    for (int i = manager->front; i != manager->rear; i = (i + 1) % manager->max_size)
    {
        printf("%d ", manager->data[i]);
    }

    printf("\n");
}


// 销毁队列
void destroy(circular_queue_type_p manager){
    free(manager->data); 
    free(manager);
    printf("循环队列已销毁\n");
}