#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//链表中节点的数据类型
typedef struct node_
{
    int data;
    struct node_ * next;    //后继指针
    struct node_ * prv;     //前驱指针
} node_type, *node_type_p;//node_type:节点结构体数据类型的别名
                          //node_type_p：节点结构体指针数据类型的别名

/*
 * 功能：创建链表
 * 参数：NULL
 * 返回值：成功：返回头节点指针；否则：NULL
*/
node_type * Creat_List(void)
{
    //申请头节点head空间
    node_type * head = malloc(sizeof(node_type));
    if(head == NULL) 
    {
        printf("创建链表失败\n");
        return NULL;
    }
    head->data = 0;
    head->next = NULL;
    head->prv  = NULL;
    printf("创建链表成功\n");
    return head;
}

/*
 * 功能：新建节点
 * 参数：data: 新建的节点的数据
 * 返回值：成功：新建节点的指针；失败：NULL
*/
node_type *New_Node(int data)
{
    //申请新节点空间
    node_type * new = malloc(sizeof(node_type));
    if(new == NULL)
    {
        printf("新节点空间申请失败\n");
        return NULL;
    }
    new -> data = data;
    new -> next = NULL;
    new ->prv   = NULL;
    printf("新节点创建成功\n");
    return new;
}

/*
 * 功能：在链表的尾部插入节点
 * 参数：head:链表的头节点指针
 *      node:要插入的节点指针
 * 返回值：成功：true; 失败：false
*/
bool Insert_Node_List_Tail(node_type *head, node_type * node)
{
    if(head == NULL) 
    {
        printf("链表没有创建\n");
        return false;
    }
    //遍历链表找到最后一个节点, temp指向的就是最后一个节点
    node_type * temp = NULL;
    if(head -> next == NULL)
    {
        temp = head;
    }
    else
    {
        temp = head -> next;
    }
    for(; temp->next != head -> next; )
    {
        temp = temp->next;
    }
    temp->next = node; //将最后一个节点的next指向新节点node
    node->next = head->next;
    printf("插入节点成功\n");
    return true;
}
/*
 * 功能：双向循环链表的头插
 * 参数：head:头节点指针
 *      node:新节点指针
 * 返回值：成功：true; 失败：false
*/
bool Insert_head(node_type * head, node_type * node)
{
    //判断头节点后面是否还有其他节点
    if(head->next == NULL && head->prv == NULL)
    {
        //链表中只有一个头节点
        head->next = node;
        head->prv = node;
        node->next = node;
        node->prv = node;
    }
    else
    {
        node->next = head->next;//新节点 ->next = 以前的节点1
        node->prv = head->next->prv;//新节点 ->prv = 以前的节点1的prv(以前的尾节点)
        head->next->prv->next = node;//以前的节点1的prv(以前的尾节点)->next = 新节点
        head->next->prv = node; //以前的节点1 -> prv = 新节点

        head->next = node;
        head->prv  = node;
    }

}
/*
 * 功能：双向循环链表的尾插
 * 参数：head:头节点指针
 *      node:新节点指针
 * 返回值：成功：true; 失败：false
*/

bool Insert_Tail(node_type * head, node_type * node)
{
    //判断头节点后面是否还有其他节点
    if(head->next == NULL && head->prv == NULL)
    {
        //链表中只有一个头节点
        head->next = node;
        head->prv = node;
        node->next = node;
        node->prv = node;
    }
    else
    {
        head->next->prv->next = node;//head->next=第一个节点
                                     //第一个节点的prv = 尾节点
                                     //即尾节点的next -> 新节点node
        node->prv = head->next->prv; //新节点的prv -> 尾节点
        node->next = head->next;     //新节点的next -> 第一个节点
        head->next->prv = node;      //第一个节点 -> prv = 新节点
    }
}

/*
 * 功能：指定节点删除
 * 参数：head:头节点指针
 *      pos：要删除的位置，例如：5，表示顺序5的位置节点会被删除
 * 返回值：成功：true; 失败：false
 *      
*/
bool Delete_node(node_type * head, int pos)
{
    if(head -> next == NULL)
    {
        printf("链表中没有节点，删除失败\n");
        return false;
    }
    node_type * delnode = NULL;
    //删除第一个节点的情况
    if(pos == 1)
    {
        delnode = head->next;//暂存节点1，等下释放。
        head->next->next->prv = head->next->prv;//第二个节点的prv -> 尾节点
        head->next->prv->next = head->next->next;//尾节点的next -> 第二个节点
        head->next = head->next->next;//head->next -> 第二个节点
        head->prv = head->next;//head->prv -> 第二个节点
        free(delnode);
        return true;
    }
    node_type * temp = head ->next;
    int pos_ = 1;//保存当前temp指向的节点
    //循环的作用：找到要删除的节点并暂存在delnode，且temp -> 最后一个节点
    //也将节点总数保存在了pos_
    for(; temp->next != head ->next;)
    {
        temp = temp ->next;
        pos_ ++;
        if(pos_ == pos) //说米链表中找到了该节点
        {
            delnode = temp;
        }
    }
    temp = delnode;
    if(pos <= pos_)
    {
        temp ->prv ->next = temp->next; //将要删除节点的上一个节点的next指针
                                    //指向要删除节点的下一个
        temp ->next ->prv = temp->prv; //将要删除节点的下一个节点的prv指针
                                   //指向要删除节点的上一个
        free(delnode);       
        return true;                
    }
    // else if(pos == pos_)
    // {
    //     //删除尾节点的情况
    //     delnode = head->next->prv;//暂存要删除节点，等下释放。
    //     head->next->prv->prv->next = head->next;//将尾节点前面的节点的next
    //                                             //指向节点1
    //     head->next->prv = head->next->prv->prv; //将向节点1的prv指向尾节
    //                                             //点前面的节点
    //     free(delnode);
    //     return true;
    // }
    else
    {
        printf("没有这个节点\n");
        return false;
    } 
}





/*
 * 功能：遍历输出从前往后
 * 参数：head:链表的头节点指针
 * 返回值：NULL
*/
void Show(node_type * head)
{
    if(head == NULL) 
    {
        printf("链表没有创建\n");
        return ;
    }
#if 1   //从前往后输出
    //遍历链表找到最后一个节点, temp指向的就是最后一个节点
    node_type * temp = head -> next;
    for(; temp->next != head -> next; )
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d \n", temp->data);
#else  //从后往前输出
    //找到链表最后一个节点
    node_type * temp = head -> next ->prv;
    for(; temp->prv != head -> next ->prv; )
    {
        printf("%d ", temp->data);
        temp = temp->prv;
    }
    printf("%d \n", temp->prv -> data);
#endif

    return ;
}


void Show_(node_type * head)
{
    if(head == NULL) 
    {
        printf("链表没有创建\n");
        return ;
    }
#if 0   //从前往后输出
    //遍历链表找到最后一个节点, temp指向的就是最后一个节点
    node_type * temp = head -> next;
    for(; temp->next != head -> next; )
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d \n", temp->data);
#else  //从后往前输出
    node_type * temp = head -> next ->prv;
    int i = 0;
    for(; temp->prv != head -> next ->prv;)
    {
        
        printf("%d ", temp -> data);
        temp = temp->prv;
    }
    printf("%d \n", temp -> data);

#endif

    return ;
}



int main()
{
    //创建链表
    node_type * head = Creat_List(); 
    //创建节点
    node_type * new = New_Node(10);
    //头插
    Insert_head(head, new);
    Show(head);
    Show_(head);

    new = New_Node(40);
    Insert_head(head, new);
    Show(head);
    Show_(head);

    new = New_Node(50);
    Insert_head(head, new);
    Show(head);
    Show_(head);

    new = New_Node(-2);
    Insert_Tail(head, new);
    Show(head);
    Show_(head);

    new = New_Node(100);
    Insert_Tail(head, new);
    Show(head);
    Show_(head);

    new = New_Node(222);
    Insert_Tail(head, new);
    Show(head);


    Delete_node(head, 1);
    Show(head);

    Delete_node(head, 5);
    Show(head);

    Delete_node(head, 20);
    Show(head);


}






























