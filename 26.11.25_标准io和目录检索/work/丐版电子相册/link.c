#include "link.h"
#include <string.h>

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
node_type_p create_node(char *value)
{
      node_type_p node = (node_type_p)malloc(sizeof(node_type));

      // 创建失败
      if (!node)
      {
            printf("创建节点失败\n");
            return NULL;
      }

      // node->data = value;
      strcpy(node->data, value);
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

// 头插
bool insert_head(node_type_p head, char *value)
{
      // 判断参数是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n");
            return false;
      }

      // 新建节点
      node_type_p new_node = create_node(value);
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
// 尾插
bool insert_tail(node_type_p head, char *value)
{

      // 判断参数是否合法
      if (isWrong(head))
      {
            printf("head参数不合法\n");
            return false;
      }

      // 新建节点
      node_type_p new_node = create_node(value);

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

// 查找数据
node_type_p find_node(node_type_p head, char *value)
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
            printf("链表中没有数据, 查找失败\n");
            return NULL;
      }

      node_type_p temp = head->next;
      while (temp != head)
      {
            if (strcmp(temp->data, value) == 0)
            {
                  printf("查找到数据=> %s\n", temp->data);
                  return temp;
            }
            temp = temp->next;
      }

      printf("没有找到数据\n");
      return NULL;
}

// 显示所有数据
void show_list(node_type_p head)
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
      node_type_p temp = head->next;

      while (temp != head)
      {
            printf("%s ", temp->data);
            temp = temp->next;
      }

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
