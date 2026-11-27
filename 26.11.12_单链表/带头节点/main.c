#include "linked.h"


int main(int argc, char const *argv[])
{

// 初始化链表
node_type_p head = init_list();

// 测试无元素头删
remove_head(head); // 链表中没有元素, 头删失败

// 尾插
insert_tail(head,70);
insert_tail(head,80);
insert_tail(head,90);

// 头插
insert_head(head, 60);
insert_head(head, 50);
insert_head(head, 40);

// 显示所有数据
show_list(head); // 40 50 60 70 80 90 

// 头删
remove_head(head);
show_list(head); // 50 60 70 80 90 

// 尾删
remove_tail(head);
// 显示所有数据
show_list(head); // 50 60 70 80

// 查找数据
search_data(head, 70);
}