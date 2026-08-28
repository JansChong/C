#include <stdio.h>

// 要存储的数据的数据类型
type int elementType_t;

// 设计链表的数据结点 (结点结构体),    数据结点 = 数据域 + 指针域,
typedef struct node_
{
    // 要存储的数据
    elementType_t data; // 数据域
    // 指向下一个结点的地址
    struct node_ *next; // 指针域

} node_type, *node_type_p;
// node_type 是 struct node_ 的别名  (结点结构体数据类型的别名)
// node_type_p 是 struct node_ * 的别名  (结点结构体指针数据类型的别名)

// 存储单链表 头结点地址
node_type_p head = NULL;
// 存储单链表 尾结点地址
node_type_p tail = NULL;
// 存储单链表 的结点数量
node_type_p node_count = 0;

/**
 * @description: 初始化链表 -- 第一次新增结点数据(首结点)
 * @param: {} input_data 要存储的数据 (按第3个文件, 首结点也可以不用存放数据)
 * @return void 这里之所以返回void, 是因为全局变量存储了 首尾结点和结点数量
 */
void create_head_list(elementType_t input_data) // 创建的时候， 它就是首结点， 也是尾结点，  剩下的就是 头插、尾插、中间插、删除
{
    // 申请空间
    node_type_p new_node = malloc(sizeof(node_type));
    if (new_node == NULL)
    {
        printf("malloc new_node error\n");
        return;
    }

    // 初始化
    new_node->data = input_data;
    new_node->next = NULL;

    head = new_node; // 第一个结点 是头结点
    tail = new_node; // 第一个结点 也是尾结点

    // 记录
    node_count++; // 结点数量递增
    return;
}

/**
 * @description: 尾插新增结点
 * @param: {} input_data
 * @return void
 */
void insert_list_tail(elementType_t input_data)
{
    // 申请空间
    node_type_p add_node = malloc(sizeof(node_type));
    if (add_node == NULL)
    {
        printf("malloc add_node error\n");
        return;
    }

    // 初始化
    add_node->data = input_data;
    add_node->next = NULl;

    tail->next = add_node; // 往之前的尾结点的next中存入新增结点
    tail = add_node;       // 现在自己是尾结点

    // 记录
    node_count++; // 结点数量递增
    return;
}

/**
 * @description: 头插新增结点
 * @param: {} input_data
 * @return void
 */
void insert_list_head(elementType_t input_data)
{
    // 实例化
    node_type_p new_node = malloc(sizeof(node_type));

    // 初始化
    new_node->data = input_data;

    // 自身指针指向原来的 首元素地址
    new_node->next = head;
    // 修改全局变量， 自己作为首元素
    head = new_node;

    // 记录
    node_count++;
    return;
}

/**
 * @description: 在指定位置插入元素 （数字是几就作为第几个元素，非下标）
 * @param: {} loc
 * @param: {} input_data
 * @return void
 */
void insert_list_by_loc(int loc, elementType_t input_data)
{
    // 不能插入大于元素个数的位置， 比如 1,2,3,  插入4可以， 插入5不行
    if (loc > node_count + 1 && loc < 1)
    {
        printf("下标越界，链表之间不能有空格 且位置大于0\n");
        return;
    }

    // 插入头部
    if (loc == 1)
    {
        insert_list_head(input_data);
    }
    // 插入尾部
    else if (loc == node_count + 1)
    {
        insert_list_tail(input_data);
    }
    // 插入中间
    else
    {
        // 从头开始
        node_type_p temp = head; // 1
        // 1，2，3，4，  插入2， 拿到1即可，执行0次
        // 1，2，3，4，  插入3， 拿到2即可，执行1次
        // 1，2，3，4，  插入4， 拿到3即可，执行2次
        // 1，2，3，4，  插入n， 拿到n-1即可，执行n-2次

        // 找到插入位置的前一个结点
        for (int i = 0; i < loc - 2; i++)
        {
            temp = temp->next;
        }

        // 实例化
        node_type_p new_node = malloc(sizeof(node_type));
        // 初始化
        new_node->data = input_data;
        // 记录
        node_count++;

        // 自身指针指向原来的 首元素地址
        new_node->next = temp->next;
        // 修改全局变量， 自己作为首元素
        temp->next = new_node;
    }
}

/**
 * 删除指定位置的元素 （数字是几就作为第几个元素，非下标）
 * @param: {} loc 要删除的元素位置
 * @return void
 */
void insert_list_by_loc(int loc)
{

    // 存储头结点
    node_type_p temp = head;

    // 删除第一个元素
    if (loc == 1)
    {
        // 把第二个结点作为头结点;
        head = temp->next;
        // 删除头结点
        free(temp);
        temp = NULL;
    }
    // 删除最后一个元素
    else if (loc == node_count)
    {
        // 遍历到最后一个结点的上一个结点. (temp本来就是头结点)
        for (int i = 0; i < count - 2; i++)
        {
            temp = head->next;
        }

        // 删除掉 temp的下一个结点
        free(temp -> next); // 释放掉最后一个结点 (但是里面的data可能没有清空, 可以考虑将删除的这个结点=NULL)
        temp -> next = NULL; // 这里只是把NULL 指向 temp->next 属性, 不代表原本的被删除的尾结点等于NULL 

        tail = temp; // 重置尾结点
    }
    // 删除中间的元素
}

// 显示所有数据

int main(int argc, char const *argv[])
{
}