#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 链表中节点的数据类型
typedef struct node_
{
    int data;           // 要存储的数据
    struct node_ *next; // 指向下一个节点的指针
} node_type, *node_type_p;
// node_type: 节点结构体数据类型的别名
// *node_type: 节点结构体指针数据类型的别名

/**
 * @description: 创建链表
 * @return 申请到的头结点指针 or NULL
 */
node_type_p create_head_list(void)
{

    // 申请头节点的空间
    node_type_p head = malloc(sizeof(node_type));
    if (head == NULL)
    {
        printf("malloc head error\n");
        return NULL;
    }

    // 要存储的数据
    head->data = 0;    // 这里头结点不保存数据
    head->next = NULL; // 只有一个头节点, 还没有其他节点
    return head;
}

/**
 * @description: 新建节点 -- 链表尾插
 * @param: {int} data 新建节点的数据
 * @return 新建节点的指针 or NULL
 */
node_type_p new_node(int data)
{
    // 申请新节点空间
    node_type_p new = malloc(sizeof(node_type));
    if (new == NULL)
    {
        printf("malloc new error\n");
        return NULL;
    }

    new->data = data; // 插入数据
    new->next = NULL; // 指针指向空 (这里还没有链接)

    printf("新节点创建成功\n");
    return new;
}

/**
 * @description: 尾插
 * @param: { } node 要插入的节点指针
 * @param: { } head 需要插入的目标链表的头节点指针
 * @return boolean
 */
bool Inser_Node_List_Tail(node_type_p node, node_type_p head)
{

    if (head == NULL || node == NULL)
    {
        char *s = (head == NULL ? "head节点没有被创建" : "node节点没有被创建");
        printf("%s\n", s);
        return false;
    }

    // 尾插: 定义一个临时结点
    node_type_p temp;

    // 如果只有一个 head 结点
    if (head->next == NULL)
    {
        temp = head; // 找到头结点
    }
    else
    {
        temp = head->next; // 找到头结点
    }

    // 如果这个临时节点 不是最后一个节点  (临时结点的next不等于头结点)
    while (temp->next != head->next)
    {
        // 将下一个节点的地址 赋值给临时节点
        temp = temp->next;
    }

    // 找到最后一个节点(next为头结点), next指向新节点地址
    temp->next = node;
    node->next = head->next; // 改成 head -> next , 单向循环链表， 最后一个结点的next 指向 第一个结点

    printf("插入节点成功!\n");
    return true;
}

/**
 * @description: 遍历输出
 * @param: {} head:链表的头结点指针
 * @return void
 */
void show_list(node_type_p head)
{
    if (head == NULL)
    {
        printf("链表没有创建\n");
        return;
    }
    else if (head->next == NULL)
    {
        printf("链表中还没有元素\n");
        return;
    }

    // 从第一个数据开始 遍历循环链表
    node_type_p temp = head->next;

    // 不是最后一个头结点
    while (temp->next != head->next)
    {
        printf("%d ", temp->data); // 这里要先输出

        temp = temp->next; // 把后一个结点赋给变量，（这里的头结点是0， 不输出）
    }

    printf("%d \n", temp->data); // 最后一个结点不满足循环条件，额外输出一次
    return;
}

/**
 * @description: 头插
 * @param: {} head: 头结点指针
 * @param: {} node: 新结点指针
 * @return boolean
 */
bool Insert_head(node_type_p head, node_type_p node)
{
    if (head == NULL)
    {
        printf("链表没有创建\n");
        return false;
    }

    // 头插法， 一开始新节点先指向头结点的下一个节点， 再让头节点指向新节点
    // 头插：  新结点的next 指向 head的next,     head的next指向新结点，  （head结点数据是0，不是要记录的数据）

    // 如果 head 后面没有结点
    if (head->next == NULL)
    {
        head->next = node;
        node->next = node;
    }

    // 如果 head 后面存在结点
    else
    {

        // 头插以后，要让原本的最后一个结点的next指向这个新的结点
        node_type_p temp = head->next;
        // 如果这个临时节点 不是最后一个节点  (临时结点的next不等于头结点)
        while (temp->next != head->next)
        {
            // 将下一个节点的地址 赋值给临时节点
            temp = temp->next;
        }
        temp->next = node;

        // 头插
        node->next = head->next;
        head->next = node;
    }

    return true;
}

/**
 * @description: 指定位置插入
 * @param: {} head 头结点指针
 * @param: {} position  要插入的位置， 例如： 5, 表示新结点会在顺序5的位置
 * @param: {} node 新节点指针
 * @return boolean
 */
bool Insert_pos(node_type_p head, int position, node_type_p node)
{
    if (head == NULL)
    {
        printf("链表没有创建\n");
        return false;
    }

    // 1则头插
    if (position == 1)
    {
        Insert_head(head, node);
        return true;
    }

    node_type_p temp = head;

    // 0  10   20    30   40    50     =>   插入位置3， 在20后面
    for (int i = 1; i < position; i++)
    {
        temp = temp->next;

        // 如果插入的位置在超出链表长度， 转尾插
        if (temp->next == head->next) // 如果后面没结点了
        {
            break; // 跳出循环， 插到最后一个结点后面
        }
    }

    node->next = temp->next;
    temp->next = node;

    return true;
}

/**
 * @description: 指定位置删除元素
 * @param: {} head 头结点
 * @param: {} pos 要删除的结点位置
 * @return boolean
 */
bool Delete_pos_node(node_type_p head, int pos)
{

    if (head == NULL)
    {
        printf("链表没有被创建\n");
        return false;
    }
    // jc补充代码：修复 没有元素时，删除第一个元素导致段错误的问题
    else if (head->next == NULL)
    {
        printf("链表中没有元素可以删除\n");
        return false;
    }

    node_type_p temp = head;

    // 如果删除的是第一个，则要把最后一个结点的next绑定到第二个
    if (pos == 1)
    {
        temp = head->next;

        // 只有一个删除第一个
        if (temp->next == head->next)
        {
            head->next = NULL;
            free(temp);
            return true;
        }

        // 有多个删除第一个
        while (temp->next != head->next)
        {
            // 找到最后一个结点
            temp = temp->next;
        }
        // 最后一个结点的next指向第二个结点
        temp->next = head->next->next;
        free(head->next);
        head->next = temp->next;
        return true;
    }

    // 0  [10  20  30  40]    删除下标2, 注意忽略0， 删除30
    // 循环到指定位置, (拿到要删除的元素)
    for (int i = 0; i < pos - 1; i++)
    {
        temp = temp->next;

        // jc补充代码：修复 要删除位置超出单向链表的元素个数导致段错误 的问题
        if (temp->next == head->next)
        {
            printf("下标越界，该位置没有可删除的元素\n");
            return false;
        }
    }

    // 临时保存要删除的数据
    node_type_p delnode = temp->next; // 30,  temp为20
    temp->next = temp->next->next;    // 把 30 的 next 赋值给 30 的上一个元素 的next

    // 释放
    free(delnode);
    return true;
}

/**
 * @description:  删除指定元素
 * @param: {} head 头结点
 * @param: {} val 要删除的元素的值
 * @return boolean
 */
bool Delete_specified_element(node_type_p head, int val)
{
    if (head == NULL)
    {
        printf("链表没有被创建\n");
        return false;
    }
    // jc补充代码：修复 没有元素时，删除第一个元素导致段错误的问题
    else if (head->next == NULL)
    {
        printf("空链表，没有元素可以删除\n");
        return false;
    }

    // 循环匹配
    node_type_p temp = head->next; // 第一个结点
    // 记录要删除的元素的上一个结点的信息
    node_type_p prev = head;
    // 假设不存在要删除的元素
    bool flag = false;

    // 0  [10  20  30  40]  30
    while (true)
    {
        // 找到要删除的元素
        if (temp->data == val)
        {
            // 存在要删除的元素
            flag = true;
            break;
        }
        // 找到的这个结点是最后一个结点，退出循环
        else if (temp->next == head->next)
        {
            break;
        }
        else
        {
            temp = temp->next;
            prev = prev->next;
        }
    }

    // 如果没有要删除的元素
    if (!flag)
    {
        printf("没有要删除的这个元素\n");
        return false;
    }

    // 如果链表中只有一个元素且是需要删除的元素
    else if (prev == head)
    {
        head->next = NULL;
        free(temp);
    }
    // 如果链表中不止有一个元素
    else
    {
        prev->next = temp->next;
        free(temp);
    }
}

int main(int argc, char const *argv[])
{

    // 创建链表
    node_type_p head = create_head_list();

    // 修复没有元素时，删除第一个元素的问题
    Delete_pos_node(head, 1);
    // 修复没有元素时，删除指定元素的问题
    Delete_specified_element(head, 10);

    // 新增结点
    node_type_p new_node1 = new_node(10);
    node_type_p new_node2 = new_node(20);
    node_type_p new_node3 = new_node(30);
    node_type_p new_node4 = new_node(40);

    // 遍历
    show_list(head);

    // 尾插
    Inser_Node_List_Tail(new_node1, head);
    show_list(head); // 10
    Delete_pos_node(head, 1); // 只有一个结点时删除一个结点
    show_list(head); // 链表中还没有元素

    Inser_Node_List_Tail(new_node2, head);
    Inser_Node_List_Tail(new_node3, head);
    Inser_Node_List_Tail(new_node4, head);
    // 遍历
    show_list(head); // 20 30 40

    // 删除指定结点位置的元素
    Delete_pos_node(head, 2);
    // 遍历输出
    show_list(head); // 20  40

    // 头插 -- 在参数中新建结点
    Insert_head(head, new_node(1));
    Insert_head(head, new_node(2));
    Insert_head(head, new_node(3));
    Insert_head(head, new_node(4));

    // 遍历输出
    show_list(head); // 4 3 2 1 20  40

    // 指定位置插入
    Insert_pos(head, 1, new_node(5));    // 插入第一个即头插
    show_list(head);                     // 5 4 3 2 1 20  40
    Insert_pos(head, 800, new_node(50)); // 超出范围则尾插
    show_list(head);                     // 5 4 3 2 1 20  40 50
    Insert_pos(head, 6, new_node(0));    // 插入第六个位置
    show_list(head);                     // 5 4 3 2 1 0 20 40 50 


    // 删除指定结点位置的元素
    Delete_pos_node(head, 200); // 下标越界，该位置没有可删除的元素

    Delete_pos_node(head, 10); // 下标越界，该位置没有可删除的元素
    show_list(head); // 5 4 3 2 1 0 20 40 50
    Delete_pos_node(head, 9); // 删掉最后一个结点，50
    show_list(head); // 5 4 3 2 1 0 20 40
    Delete_pos_node(head, 1); // 删掉第一个结点，5
    show_list(head); // 4 3 2 1 0 20 40 

    Delete_pos_node(head, 3); // 删掉第三个结点，2
    show_list(head); // 4 3 1 0 20 40 
}