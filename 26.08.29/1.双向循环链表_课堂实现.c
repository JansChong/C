#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ele_type;

typedef struct node_{
      ele_type data;
      struct node_ *next; // 后继指针
      struct node_ *prev; // 前驱指针
} node_type, *node_type_p;


/**
 * 创建链表
 * @return boolean
 */
node_type_p create_list(void){
      // 实例化

      // 初始化

      // 记录
}
上一个。
prev
/**
 * 新建结点
 */



int main(int argc, char const *argv[])
{
     
      
      // 删除首结点
      



      /* 删除尾结点 */ 
      // 要删除的结点
      node_type_p delnode = head -> next -> prev;  // 要删除的结点

      delnode->prev->next = delnode->next; // 要删除元素的上一个元素的next 指向 删除元素的next

      head->next->prev = delnode-> prev;  // 第一个元素的上一个元素 指向 删除元素的上一个元素
      // delnode =  delnode-> prev; 

      free(delnode);

      


      /* 删除指定位置结点 */
      // 要删除的结点
      node_type_p delnode = head->next;
      for (int i = 0; i < loc-1; i++)
      {
            delnode = delnode -> next; // 要删除的元素
      }

      // 上一个元素的next指向 删除元素的next
      delnode->prev->next = delnode -> next;
      // 下一个元素的prev指向 删除元素的prev
      delnode->next->prev = delnode -> prev;

      free(delnode);




      // 从后往前输出

      // head   node1 
      // head   node1  node2
      // head   node1  node2  node3


      node_type_p temp = head;
      
      do{

      }while()
      


}

