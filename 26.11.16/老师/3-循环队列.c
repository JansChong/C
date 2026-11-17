#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *data;
    int front; // 指向队头
    int rear;  // 指向队尾
    int maxsize;
} SeqQueue;

SeqQueue *initQueue(int size)
{
    // 为管理结构体申请空间
    SeqQueue *manager = (SeqQueue *)malloc(sizeof(SeqQueue));
    if (manager == NULL)
    {
        printf("分配内存失败\n");
        return NULL;
    }

    // 初始化
    manager->front = 0;
    manager->rear = 0;
    manager->maxsize = size;

    // 为数据申请空间
    manager->data = (int *)calloc(manager->maxsize, sizeof(int));
    if (manager->data == NULL)
    {
        printf("分配内存失败\n");
        free(manager);
        return NULL;
    }

    return manager;
}

bool isFull(SeqQueue *manager)
{
    // 判断队列是否满
    if ((manager->rear + 1) % manager->maxsize == manager->front)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int push(SeqQueue *manager, int value)
{
    // 判断队列是否满
    if (isFull(manager))
    {
        printf("队列已满，无法入队\n");
        return -1;
    }
    manager->data[manager->rear] = value;
    manager->rear = (manager->rear + 1) % manager->maxsize;
}

bool isEmpty(SeqQueue *manager)
{
    if (manager->front == manager->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int pop(SeqQueue *manager)
{
    if (isEmpty(manager))
    {
        printf("队列为空\n");
        return -1;
    }

    int val = manager->data[manager->front];
    manager->front = (manager->front + 1) % manager->maxsize;

    return 0;
}

// 遍历打印
int traversal_printf(SeqQueue *manager)
{
    if (isEmpty(manager))
    {
        printf("队列为空\n");
        return -1;
    }
    for (int i = manager->front; i != manager->rear; i = (i + 1) % manager->maxsize)
    {
        printf("%d ", manager->data[i]);
    }
    printf("\n");
}

void destroy(SeqQueue *s)
{
    free(s->data);
    free(s);
    printf("销毁完成\n");
}

int main()
{
    SeqQueue *s = initQueue(5);

    push(s, 10);
    push(s, 20);
    push(s, 30);
    push(s, 40);
    push(s, 50);
    traversal_printf(s);

    pop(s);
    pop(s);
    traversal_printf(s);
    push(s, 60);
    push(s, 70);
    push(s, 80);
    traversal_printf(s);
    // destroy(s);
}

单位名称无效 "ssh~" 逃跑了 "ssh\x7e" 也许你应该使用systemd escape?
找不到ssh\x7e.service单元.
