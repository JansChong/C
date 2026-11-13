#include "link.h"

int main(int argc, char const *argv[])
{

      // 初始化链表
      node_type_p head = init_list();

      // 无元素 显示
      // show_list(head); // 逻辑通过
      // 无元素 头删
      // remove_head(head); // 逻辑通过
      // 无元素 尾删
      // remove_tail(head); // 逻辑通过

      // 3 6 9 12  30 60 90 120

      // 头插
      insert_head(head, 12);
      insert_head(head, 9);
      insert_head(head, 6);
      insert_head(head, 3);
      // 显示
      show_list(head); // 逻辑通过

      // 尾插
      insert_tail(head, 30);
      insert_tail(head, 60);
      insert_tail(head, 90);
      insert_tail(head, 120);
      // 显示
      show_list(head); // 逻辑通过

      // 头删
      remove_head(head);
      remove_head(head);
      // 显示
      show_list(head); // 逻辑通过

      // 尾删
      remove_tail(head);
      remove_tail(head);
      // 显示
      show_list(head); // 逻辑通过 9 12 30 60 

      // 查找数据
      find_node(head, 1130); // 找不到
      find_node(head, 30); // 找到数据

      // 销毁链表
      destroy(head); // 销毁链表成功

}