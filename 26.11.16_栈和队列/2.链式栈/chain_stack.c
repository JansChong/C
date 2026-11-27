#include "chain_stack.h"

// 栈：先进后出，后进先出 

// 初始化管理结构体
link_stack_type_p init_stack()
{

    // 老师这里用的是有头结点的写法， 初始化了一个 head的 node_type_p

    link_stack_type_p manager = (link_stack_type_p)malloc(sizeof(link_stack_type));
    if (manager == NULL)
    {
        printf("管理结构体初始化失败\n");
        return NULL;
    }
    manager->top = NULL;
    // 返回管理结构体
    return manager;
}

// 判空
static bool isEmpty(link_stack_type_p manager)
{
    return manager->top == NULL;
}

// 利用单链表实现。为了操作高效（O(1)），我们将链表的头部作为栈顶。
// - 入栈 = 链表头插法
bool push(link_stack_type_p manager, int value)
{
    // 初始化数据节点
    node_type_p new_node = (node_type_p)malloc(sizeof(node_type));

    if (new_node == NULL)
    {
        printf("数据节点创建失败, 入栈失败\n");
        return false;
    }

    // 数据节点赋值
    new_node->data = value;
    // 新数据节点的下一个节点，指向原有的栈顶结点(或NULL)
    new_node->next = manager->top;
    // 栈顶节点指向新入栈的这个数据节点
    manager->top = new_node;

    printf("入栈成功\n");
    return true;
}

// - 出栈 = 链表头删法
bool pop(link_stack_type_p manager)
{
    // 判空
    if (isEmpty(manager))
    {
        printf("空栈，无法出栈\n");
        return false;
    }

    // 记录要出栈的（栈顶）节点（用于释放内存）
    node_type_p temp = manager->top;
    // 存储要出栈的结点的数据 (如有必要可以用于返回)
    int value = temp->data;

    // 栈顶结点后移
    manager->top = temp->next;

    // 释放栈顶节点
    free(temp);

    printf("出栈成功\n");
    return true;
}

// 遍历
bool forEach(link_stack_type_p manager)
{
    // 判空
    if (isEmpty(manager))
    {
        printf("空栈，无法输出\n");
        return false;
    }

    // 需要临时变量  否则遍历会破坏栈顶指针
    node_type_p temp = manager->top;

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
    return true;
}

// 销毁
void destroy(link_stack_type_p manager)
{
    // 判空
    if (isEmpty(manager))
    {
        printf("空栈，无需销毁\n");
        return;
    }

    // 栈顶指针后移，且销毁
    while (manager->top != NULL)
    {
        // 临时存储栈顶节点
        node_type_p temp = manager->top;
        // 栈顶结点后移
        manager->top = temp->next;
        // 依次释放临时存储的栈顶节点
        free(temp);
    }

    // 销毁管理结构体
    free(manager);
    printf("销毁成功\n");
    return;
}