#include "link.h"

// 初始化
node_type_p init_list(void)
{
      node_type_p head = (node_type_p)malloc(sizeof(node_type));

      // 初始化失败
      if (!head)
      {
            printf("head初始化失败\n");
            return NULL;
      }

      // 初始化成功
      head->next = head;
      head->prev = head;

      return head;
}

// 创建节点
node_type_p create_node(struct goods data)
{
      // 管理结构体空间
      node_type_p node = (node_type_p)malloc(sizeof(node_type));

      // 创建失败
      if (!node)
      {
            printf("创建节点失败\n");
            return NULL;
      }

      // 商品结构体 赋值给 管理结构体data
      node->data.id = data.id;
      node->data.price = data.price;
      node->data.total = data.total;
      strcpy(node->data.name, data.name);

      // 节点的两侧先指向自己 或 NULL
      node->next = node;
      node->prev = node;

      return node;
}

// 判断head参数是否合法
static bool isWrong(node_type_p head)
{
      return !head;
}

// 判断链表是否为空 (只有一个head节点)
static bool isEmpty(node_type_p head)
{
      return head->next == head;
}

/**
 * 通用删除函数
 * param {} del 需要被删除的节点指针
 */
static node_type_p deleteNode(node_type_p del)
{
      // 删除节点的上一节点
      node_type_p prev = del->prev;
      // 删除节点的下一节点
      node_type_p next = del->next;

      prev->next = next; // 上一个的 next 指向删除节点的下一个
      next->prev = prev; // 下一个的 prev 指向删除节点的上一个

      del->next = del;
      del->prev = del;
      // free(del);
      return del;
}

// 尾插
bool insert_tail(node_type_p head, struct goods data)
{

      // 判断参数是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n");
            return false;
      }

      // 新建节点
      node_type_p new_node = create_node(data);

      // head (6)
      // head  2  4  (6)
      // 双向循环 尾插 不再需要循环去找最后一个元素

      // 新节点的下一个 = 原尾节点的下一个 (即头节点)
      new_node->next = head;
      // 新节点的上一个 = 原尾节点
      new_node->prev = head->prev;

      // 原尾节点的next = 新节点
      head->prev->next = new_node;
      // 头节点的上一个 = 新节点
      head->prev = new_node;

      return true;
}

#if 1
// 头插
bool insert_head(node_type_p head, struct goods data)
{
      // 判断参数是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n");
            return false;
      }

      // 新建节点
      node_type_p new_node = create_node(data);
      if (new_node == NULL)
      {
            printf("头插失败\n");
            return false;
      }

      // head 1  2
      // 插入到 head 之后 (只有一个head节点和多个节点)
      new_node->prev = head;
      new_node->next = head->next;

      head->next->prev = new_node;
      head->next = new_node;
      return true;
}
// 头删
node_type_p remove_head(node_type_p head)
{
      // 判断head是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n");
            return NULL;
      }

      // 判断是否只有一个head节点
      if (isEmpty(head))
      {
            printf("链表中没有数据, 删除失败\n");
            return NULL;
      }

      // head (6)
      // head (2)  4  6
      // 记录要删除的节点
      node_type_p temp = head->next;

      // head的下一个 = 删除节点的下一个
      head->next = temp->next;
      // 要删除节点的下一个节点的prev = 删除节点的prev(即head)
      temp->next->prev = head;

      // 避免要移除的元素还可以链接到 链表
      temp->next = temp;
      temp->prev = temp;
      // 返回要移除的元素
      return temp;
}
// 尾删
node_type_p remove_tail(node_type_p head)
{
      // 判断head是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n");
            return NULL;
      }

      // 判断是否只有一个head节点
      if (isEmpty(head))
      {
            printf("链表中没有数据, 删除失败\n");
            return NULL;
      }

      // head (6)
      // head  2  4  (6)

      // 双向循环 尾删 不再需要循环去找最后一个元素
      // head的前驱节点 就是 尾节点
      node_type_p temp = head->prev;

      // 要删除节点的上一个指向我的, 指向我的下一个
      temp->prev->next = head;
      // 要删除节点的下一个指向我的, 指向我的上一个
      head->prev = temp->prev;

      temp->next = temp;
      temp->prev = temp;
      // 返回被移除的节点
      return temp;
}
#endif

// 查找数据
node_type_p find_node(node_type_p head, int id)
{
      // 判断head是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n\n");
            return NULL;
      }

      // 判断是否只有一个head节点
      if (isEmpty(head))
      {
            printf("链表中没有数据, 查找失败\n\n");
            return NULL;
      }

      node_type_p temp = head->next;
      while (temp != head)
      {
            if (temp->data.id == id)
            {
                  // printf("查找到商品=> id:%d\n 名称:%s\n 单价:%.2f\n 数量:%d\n\n", temp->data.id, temp->data.name, temp->data.price, temp->data.total);
                  return temp;
            }
            temp = temp->next;
      }

      printf("该编号没有找到数据\n\n");
      return NULL;
}

// 删除指定的商品
node_type_p remove_node(node_type_p head, int id)
{
      // 判断head是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n\n");
            return NULL;
      }

      // 判断是否只有一个head节点
      if (isEmpty(head))
      {
            printf("链表中没有数据, 删除失败\n\n");
            return NULL;
      }

      if(!find_node(head, id)){
            printf("该id没有商品,删除失败\n");
            return NULL;
      }

      // 以下代码的简化
      return deleteNode(find_node(head, id));

      // // 在带头节点的双向循环链表中， 删除任意节点的逻辑都是一样的：不管头删还是尾删还是中间删除, 都是 上一节点指向删除节点的下一个节点, 下一节点指向删除节点的上一个节点
      // node_type_p del_node = find_node(head, id);
      // // 所以调用通过删除函数
      // deleteNode(del_node);
      // // 返回要删除的节点
      // return del_node;
};

// 显示所有数据
// 用status的0,1 控制(0)顺序打印 和 (1)逆序打印
void show_list(node_type_p head, int status)
{
      // 判断head是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n");
            return;
      }

      // 判断是否只有一个head节点
      if (isEmpty(head))
      {
            printf("链表中没有数据, 输出失败\n");
            return;
      }

      // head (6)
      // head  2  4  (6)
      node_type_p temp = status ? head->prev : head->next;
      

      printf("###### 所有商品数据 ######\n");
      while (temp != head)
      {
            printf("id:%d\t名称:%s\t单价:%.2f\t数量:%d\n", temp->data.id, temp->data.name, temp->data.price, temp->data.total);
            temp = status ? temp->prev : temp->next;
      }
      printf("###### 商品输出结束 ######\n\n");

      printf("\n");
      return;
}

// 销毁链表
bool destroy(node_type_p head)
{
      if (isWrong(head))
      {
            printf("head结点没有成功初始化, 无需销毁\n");
            return false;
      }

      // 就算没有数据节点, 以下逻辑也正常覆盖
      // 临时存储
      node_type_p p = head->next;

      // 从head开始，只要head->next不为空，都要删除，直到head->next为空
      // head   1    2    3    head
      while (p != head)
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
      printf("销毁链表成功\n");
      return true;
}
