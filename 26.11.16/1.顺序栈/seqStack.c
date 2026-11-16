#include "seqStack.h"

// 初始化管理结构体
seqStack_type_p init_stack(int size)
{

    // 结构体申请空间
    seqStack_type_p manager = (seqStack_type_p)malloc(sizeof(seqStack_type));

    // 如果申请失败
    if (manager == NULL)
    {
        return NULL;
    }

    // 设置 可存储的最大元素个数
    manager->size = size;

    // calloc函数：
    // 原型:   void *calloc(size_t n, size_t size);
    // 功能: 在堆中中请一个具有n个元素的匿名数组，每个元素大小为size（字节）
    // 返回值
    // 成功 新申请的内存基地址
    // 失败 NULL
    // 备注：该函数申请的内存将被初始化为0
    manager->data = (int *)calloc(manager->size, sizeof(int));

    // 如果申请失败
    if (manager->data == NULL)
    {
        printf("内存分配失败\n");
        // 释放管理结构体申请的空间
        free(manager);
        return NULL;
    }
    // 栈顶指针初始化
    manager->top = -1;

    // 返回管理结构体
    return manager;
}

// 判满
static bool isFull(seqStack_type_p manager)
{
    // printf("%s\n", manager->top == manager->size - 1 ? "栈已满" : "栈未满");
    return manager->top == manager->size - 1;
};

// 判空
static bool isEmpty(seqStack_type_p manager)
{
    // printf("%s\n", manager->top == -1 ? "栈为空" : "栈不为空");
    return manager->top == -1;
}

// 判有效
static bool isWorng(seqStack_type_p manager)
{
    // printf("%s\n", manager == NULL ? "管理结构体参数错误：未初始化" : "管理结构体正常");
    return manager == NULL;
}

// 入栈、压栈
bool push(seqStack_type_p manager, int value)
{
    // 判满
    if (isFull(manager))
    {
        printf("栈已满，无法入栈\n");
        return false;
    }

    manager->data[++manager->top] = value;
    return true;
}

// 出栈、弹栈
bool pop(seqStack_type_p manager)
{
    // 判空
    if (isEmpty(manager))
    {
        printf("栈为空，无法出栈\n");
        return false;
    }

    // 获取栈顶元素
    int value = manager->data[manager->top];
    manager->top--;
    return true;
}

// 遍历打印
void forEach(seqStack_type_p manager)
{
    // 判空
    if (isEmpty(manager))
    {
        printf("栈为空, 无需遍历\n");
        return;
    }

    for (int i = 0; i <= manager->top; i++)
    {
        printf("%d ", manager->data[i]);
    }
    printf("\n");
}

// 销毁
bool destroy(seqStack_type_p manager)
{
    // 如果参数无效
    if (isWorng(manager))
    {
        printf("管理结构体未初始化，无需销毁\n");
        return false;
    };

    // 释放数据
    free(manager->data);
    // 指向NULL, 避免使用时访问野指针
    manager->data = NULL;
    manager->size = 0;
    manager->top = -1;

    // 释放管理结构体
    free(manager);

    printf("销毁结构体成功\n");
    return true;
}
