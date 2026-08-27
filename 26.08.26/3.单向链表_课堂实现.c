#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 链表中节点的数据类型
typedef struct node_
{
    int data;        // 要存储的数据
    struct node_ * next; // 指向下一个节点的指针
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
    node_type_p head =  malloc(sizeof(node_type));
    if (head == NULL)
    {
        printf("malloc head error\n");
        return NULL;
    }


    // 要存储的数据
    head->data = 0; // 这里头结点不保存数据
    head->next = NULL; // 只有一个头节点, 还没有其他节点
    return head;    
}


/**
 * @description: 新建节点 -- 链表尾插
 * @param: {int} data 新建节点的数据
 * @return 新建节点的指针 or NULL
 */
node_type_p new_node(int data){
    // 申请新节点空间
    node_type_p new = malloc(sizeof(node_type));
    if (new == NULL)
    {
        printf("malloc new error\n");
        return NULL;
    }

    new -> data = data; // 插入数据
    new -> next = NULL; // 指针指向空 (这里还没有链接)
    
    printf("新节点创建成功\n");
    return new;
}

/**
 * 在链表的尾部插入节点
 * @param: { } node 要插入的节点指针
 * @param: { } head 需要插入的目标链表的头节点指针
 * @return boolean
 */
bool Inser_Node_List_Tail(node_type_p node, node_type_p head){

    if (head == NULL || node==NULL)
    {
        char *s = (head == NULL ? "head节点没有被创建" : "node节点没有被创建");
        printf("%s\n",s);
        return false;
    }
    
    // 尾插: 遍历 找到最后一个节点 (某个节点的next为NULL)
    node_type_p temp = head;

    // 如果这个临时节点 不是最后一个节点 (next不为NULL)
    while (temp->next != NULL)
    {
        // 将下一个节点的地址 赋值给临时节点
        temp = temp->next;
    }

    // 找到最后一个节点(next为NULL), 指向新节点地址 
    temp -> next  = node;
    node -> next = NULL; // 这一步在创建new_node的时候 本来就是 NULL,  这里保留, 后续换到中间插入的时候 只需要改掉null指向即可

    printf("插入节点成功!\n");
    return true;
}

/**
* @description: 遍历输出
* @param: {} head:链表的头结点指针
* @return void
*/
void show_list(node_type_p head){
    if (head == NULL)
    {
        printf("链表没有创建\n");
        return ;
    }

    // 从头开始 遍历链表 
    node_type_p temp = head;

    // 不是最后一个头结点
    while (temp -> next != NULL)
    {
        temp = temp -> next; // 把后一个结点赋给变量， 直到最后一个结点，   （这里的头结点是0， 不输出）
        printf("%d ", temp->data); // 直到输出最后一个结点， 再进入循环条件 直接退出
    }
    
    return;
}

/**
* @description: 在head头结点后面插入 -- 头插
* @param: {} head: 头结点指针
* @param: {} node: 新结点指针
* @return boolean
*/
bool Insert_head(node_type_p head, node_type_p node){
    if (head ==NULL)
    {
        printf("链表没有创建\n");
        return false;
    }

    // 头插法， 一开始新节点先指向头结点的下一个节点， 再让头节点指向新节点
    // 头插：  新结点的next 指向 head的next,     head的next指向新结点，  （head结点数据是0，不是要记录的数据）
    node -> next = head -> next;
    head -> next = node;
    
    return true;
}

/**
* @description: 指定位置插入
* @param: {} head 头结点指针
* @param: {} position  要插入的位置， 例如： 5, 表示新结点会在顺序5的位置
* @param: {} node 新节点指针
* @return boolean
*/
bool Insert_pos(node_type_p head, int position ,node_type_p node){
    if (head ==NULL)
    {
        printf("链表没有创建\n");
        return false;
    }
    
    node_type_p temp = head;

    // 0  10   20    30   40    50     =>   插入位置3， 在20后面
    for (int i = 1; i < position ; i++)
    {
        temp = temp -> next;

        // 如果插入的位置在超出链表长度， 转尾插
        if(temp -> next == NULL)  // 如果后面没结点了
        {
            break;  // 跳出循环， 插到最后一个结点后面
        }
    }

    node -> next = temp -> next;
    temp -> next = node;
    
    return true;
    
}


/**
* @description: 指定结点位置 删除元素
* @param: {} head 头结点
* @param: {} pos 要删除的结点位置
* @return boolean
*/
bool Delete_pos_node(node_type_p head, int position){

    if (head == NULL)
    {   
        printf("链表没有被创建\n");
        return false;
    }
    

    node_type_p temp = head;

    // 0  [10  20  30  40]    删除下标2, 注意忽略0， 删除30
    // 循环到指定位置, (拿到要删除的元素)
    for (int i = 0; i < pos-1; i++)
    {
        temp = temp -> next;
    }

    // 临时保存要删除的数据
    node_type_p delnode = temp -> next; // 30,  temp为20
    temp -> next = temp ->next ->next;   // 把 30 的 next 赋值给 30 的上一个元素 的next

    // 释放
    free(delnode);
    return true;
    
}




int main(int argc, char const *argv[])
{

}