#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5

// ========== 结构定义 ==========
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

// ========== 初始化 ==========
void initQueue(CircularQueue *q) {
    q->front = 0;
    q->rear = 0;
    printf(" 队列已初始化\n");
}

// ========== 判空 ==========
bool isEmpty(CircularQueue *q) {
    return q->front == q->rear;
}

// ========== 判满 ==========
bool isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// ========== 入队 ==========
bool enqueue(CircularQueue *q, int val) {
    if (isFull(q)) {
        printf(" 队列已满，入队失败: %d\n", val);
        return false;
    }
    q->data[q->rear] = val;
    q->rear = (q->rear + 1) % MAX_SIZE;
    printf(" 入队: %d\n", val);
    return true;
}

// ========== 出队 ==========
int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf(" 队列为空，出队失败\n");
        return -1;
    }
    int val = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    printf(" 出队: %d\n", val);
    return val;
}

// ========== 查看队头元素 ==========
int peek(CircularQueue *q) {
    if (isEmpty(q)) {
        printf(" 队列为空\n");
        return -1;
    }
    return q->data[q->front];
}

// ========== 遍历打印 ==========
void printQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf(" 队列为空\n");
        return;
    }
    printf(" 队列内容 (头 -> 尾): ");
    for (int i = q->front; i != q->rear; i = (i + 1) % MAX_SIZE) {
        printf("[%d] ", q->data[i]);
    }
    printf("\n");
}

// ========== 销毁 ==========
void destroy(CircularQueue *q) {
    q->front = 0;
    q->rear = 0;
    printf(" 循环队列已销毁\n");
}

// ========== 主函数测试 ==========
int main() {
    CircularQueue q;
    initQueue(&q);

    printf("\n--- 测试入队 ---\n");
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    printf("\n--- 测试遍历 ---\n");
    printQueue(&q);

    printf("\n--- 测试入队满 ---\n");
    enqueue(&q, 50);

    printf("\n--- 测试查看队头 ---\n");
    printf(" 当前队头: %d\n", peek(&q));

    printf("\n--- 测试出队 ---\n");
    dequeue(&q);
    dequeue(&q);

    printf("\n--- 再次入队（测试循环） ---\n");
    enqueue(&q, 60);
    enqueue(&q, 70);

    printf("\n--- 最终遍历 ---\n");
    printQueue(&q);

    destroy(&q);
    return 0;
}