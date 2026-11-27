#include "linked.h"

// 初始化链表

// 带头结点 -> 先初始化
// 不带头结点 -> 存入数据时初始化
node_type_p init_list()
{
    // 为头结点申请空间 (堆内存)
    node_type_p head = (node_type_p)malloc(sizeof(node_type));

    // 如果申请成功
    if (head != NULL)
    {
        // 将头结点的next指针指向null
        head->next = NULL;
    }

    // 返回头结点 (失败返回null, 成功返回结构体指针head)
    return head;
}

// 创建新节点 -> 然后才可以插入节点
node_type_p new_node(int value)
{
    node_type_p node = (node_type_p)malloc(sizeof(node_type));

    // 如果申请成功
    if (node != NULL)
    {
        // 存入数据
        node->data = value;
        // 将头结点的next指针指向null (后续用)
        node->next = NULL;
    }

    return node;
}

// 判断链表节点head是否正常初始化 (true表示错误, false相反)
static bool iswrong(node_type_p head)
{
    return !head;
}

// 判断链表是否为空链表
static bool isEmpty(node_type_p head)
{
    return !(head->next);
}

// 头插
bool insert_head(node_type_p head, int value)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return false;
    }

    // 创建节点()
    node_type_p node = new_node(value);
    if (node != NULL)
    {
        // node 先存好 原本head指向的下一个节点
        node->next = head->next;
        // head的next 指向新创建的 node
        head->next = node;
        return true;
    }
    return false;
}

// 尾插
bool insert_tail(node_type_p head, int value)
{

    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return false;
    }

    // 创建节点()
    node_type_p node = new_node(value);
    if (node != NULL)
    {
        // 找到最后一个指向null的节点
        node_type_p temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        // 把node插入末尾
        temp->next = node;
        return true;
    }
    return false;
}

// 头删
node_type_p remove_head(node_type_p head)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化, 头删失败\n");
        return NULL;
    }

    // 如果链表为空
    if (isEmpty(head))
    {
        printf("链表中没有元素, 头删失败\n");
        return NULL;
    }

    // 需要存储要删除的节点 （因为要释放内存）
    node_type_p temp = head->next;
    // 把head的next指向要删除的元素的next
    head->next = temp->next;

    // 释放
    // free(temp);
    // return true;

    // 建议设计成 把删除的节点地址返回 而不是释放
    temp->next = NULL;
    return temp;
}

// 尾删
node_type_p remove_tail(node_type_p head)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化, 尾删失败\n");
        return NULL;
    }

    // 如果链表为空
    if (isEmpty(head))
    {
        printf("链表中没有元素, 尾删失败\n");
        return NULL;
    }

    // 获取到倒数第二个节点 (这里考虑到只有一个元素的情况，所以用head而不用head->next)
    node_type_p temp = head;

    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }

    // 临时保存要删除的数据
    node_type_p delnode = temp->next;
    // temp->next = delnode->next; // 即 NULL
    temp->next = NULL;

    // 释放
    // free(delnode);
    // return true;

    // 建议设计成 把删除的节点地址返回 而不是释放
    // delnode->next = NULL; // 尾删的最后一个元素，其next本来就是NULL
    return delnode;
}

// 显示所有数据
void show_list(node_type_p head)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return;
    }

    // 如果链表为空
    if (isEmpty(head))
    {
        printf("链表中没有元素，显示为空\n");
        return;
    }

    // 首节点无数据， 不输出
    node_type_p temp = head->next;

    // 只要下一个节点不为空
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        // 就让下一个节点赋值并输出
        temp = temp->next;
    }

    printf("\n");
}

// 销毁
bool destroy(node_type_p head)
{
    if (iswrong(head))
    {
        printf("head结点没有成功初始化, 无需销毁\n");
        return false;
    }

    // 临时存储
    node_type_p p = head->next;

    // 从head开始，只要head->next不为空，都要删除，直到head->next为空
    // head   1    2    3    NULL
    while (p != NULL)
    {
        // 记录要删除的节点
        node_type_p temp = p;
        // 头节点的next指向删除节点后一位
        p = p->next;
        // 销毁要删除的节点
        free(temp);
    }

    // 销毁head
    free(head);
    return true;
}

// 查找数据
node_type_p search_data(node_type_p head, int value)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return NULL;
    }

    // 如果链表为空
    if (isEmpty(head))
    {
        printf("链表中没有元素，查找失败\n");
        return NULL;
    }

    node_type_p temp = head->next;

    while (temp != NULL)
    {
        // 如果找得到数据
        if (temp->data == value)
        {
            printf("查找到数据 %d\n", temp->data);
            // 返回这个节点
            return temp;
        }
        // 否则指针后移
        temp = temp->next;
    }

    printf("找不到数据\n");
    return NULL;
}

