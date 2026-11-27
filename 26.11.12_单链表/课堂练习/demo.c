#include "demo.h"

// 初始化链表

// 带头结点 -> 先初始化
// 不带头结点 -> 存入数据时初始化
node_type_p init_list(void)
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

/**
 * @description: 创建新节点的学生节点 -- 然后才可以插入节点
 * @param: {} value 学生信息结构体
 * @param: {}
 * @return
 */
node_type_p create_node(struct student_info value)
{
    // 申请空间
    node_type_p node = (node_type_p)malloc(sizeof(node_type));

    // 如果申请成功
    if (node != NULL)
    {
        // 把传入的学生结构体信息 赋值到 管理结构体(创建的节点)的data
        node->data.id = value.id;

        // node->data.name = value.name;  字符串不可以直接赋值
        strcpy(node->data.name, value.name);

        node->data.score = value.score;
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
bool insert_head(node_type_p head, struct student_info value)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return false;
    }

    // 创建节点()
    node_type_p node = create_node(value);
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
bool insert_tail(node_type_p head, struct student_info value)
{

    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return false;
    }

    // 创建节点()
    node_type_p node = create_node(value);
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

    printf("############## 所有学生数据如下 ################\n");
    // 首节点无数据， 不输出
    node_type_p temp = head->next;

    // 只要下一个节点不为空
    while (temp != NULL)
    {
        printf("%d %s %.2lf分\n", temp->data.id, temp->data.name, temp->data.score);
        // 就让下一个节点赋值并输出
        temp = temp->next;
    }

    printf("############## 学生信息输出结束 ################\n\n");
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
// (为了适配"按学号删除信息功能",
// 本查找函数返回查找到的元素的上一个元素,
// 输出时记得next
// 删除时通过id调用本函数,
// 拿到返回值直接处理next指针并删除下一元素即可)
node_type_p search_data(node_type_p head, int id)
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

    // 有可能找到第一个节点, 需要返回head
    node_type_p temp = head;

    // 0  1  2  NULL
    while (temp->next != NULL)
    {
        // 如果找得到数据
        if (temp->next->data.id == id)
        {
            // printf("查找到数据 %d\n", temp->data.id);
            // 返回这个节点
            return temp;
        }
        // 否则指针后移
        temp = temp->next;
    }

    printf("******该学号没有数据\n\n");
    return NULL;
}

// 按学号移除数据
node_type_p remove_data(node_type_p head, int id)
{
    // 调用查找函数, 会返回查找到的元素的上一个元素
    node_type_p prev = search_data(head, id);

    // 如果返回null说明要删除的数据不存在 
    // 如果要删除的数据不存在
    if(!prev){
        printf("******删除失败\n");
    }
    
    // 存储要删除的元素
    node_type_p delnode = prev->next;

    // 0 1 2 3
    // 改变上一个元素的指向
    prev->next = delnode->next;

    // 避免用这个元素访问到后续节点，因为要返回
    delnode->next = NULL;
    return delnode;
}