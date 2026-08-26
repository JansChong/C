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

int main(int argc, char const *argv[])
{
}