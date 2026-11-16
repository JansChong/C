#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 节点结构体
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 管理结构体
typedef struct
{
    Node *front; // 队头指针
    Node *rear;  // 队尾指针
    int size;    // 队列元素个数
} LinkQueue;

Node *head;

LinkQueue *initQueue()
{
    LinkQueue *manager = (LinkQueue *)malloc(sizeof(LinkQueue));
    if (manager == NULL)
    {
        printf("分配内存失败\n");
        return NULL;
    }

    head = (Node *)malloc(sizeof(Node));
    if (head == NULL)
    {
        printf("分配内存失败\n");
        free(manager);
        return NULL;
    }

    head->next = NULL;

    manager->front = NULL;
    manager->rear = NULL;
    manager->size = 0;

    return manager;
}

// 入队
int JionQueue(LinkQueue *s, int value)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("分配内存失败\n");
        return -1;
    }

    newnode->data = value;
    newnode->next = NULL;

    if (s->rear == NULL) // 判断是否为空队列
    {
        s->front = newnode;
        s->rear = newnode;
        head->next = newnode;
        s->size++;
    }
    else
    {
        s->rear->next = newnode;
        s->rear = newnode;
        s->size++;
    }

    return 0;
}

// 出队
int LeaveQueue(LinkQueue *s)
{
    if (s->size == 0) // 判断队列是否为空
    {
        printf("空队列\n");
        return -1;
    }

    head->next = s->front->next;

    free(s->front);

    s->front = head->next;
    s->size--;

    return 0;
}

// 遍历打印
int traversal_printf(LinkQueue *s)
{
    if (s->size == 0) // 判断队列是否为空
    {
        printf("空队列\n");
        return -1;
    }
    Node *p = s->front;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}

// 销毁
void destroy(LinkQueue *s)
{
    while (s->front != NULL)
    {
        Node *p = s->front;
        s->front = p->next;
        free(p);
    }

    free(head);
    free(s);
    printf("销毁完成\n");
}

int main()
{
    LinkQueue *s = initQueue();

    JionQueue(s, 10);
    JionQueue(s, 20);
    JionQueue(s, 30);
    JionQueue(s, 40);
    JionQueue(s, 50);

    traversal_printf(s);

    LeaveQueue(s);
    LeaveQueue(s);
    traversal_printf(s);

    destroy(s);
    return 0;
}
