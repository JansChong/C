#include "user_link.h"
# include "all_airline_info.h" 


// 初始化
userinfo_type_p user_init_list()
{
      // 为头结点申请空间 (堆内存)
      userinfo_type_p head = (userinfo_type_p)malloc(sizeof(userinfo_type));

      // 如果申请成功
      if (head != NULL)
      {
            // 将头结点的next指针指向null
            head->next = NULL;
      }

      // 返回头结点 (失败返回null, 成功返回结构体指针head)
      return head;
}

// 判空
static bool user_isEmpty(userinfo_type_p head)
{
      return !(head->next);
}

// 创建 用户数据 节点  (注册、管理员添加)
static userinfo_type_p user_new_node(userinfo value)
{
      // 申请一个用户数据 管理结构体
      userinfo_type_p node = (userinfo_type_p)malloc(sizeof(userinfo_type));

      // 如果申请成功
      if (node != NULL)
      {
            //  userinfo data, 是每一个用户数据, 含名字 密码 行程记录(航班号、席位) 行程数量
            // 把用户数据 插入data中
            strcpy(node->data.u_name, value.u_name);
            strcpy(node->data.u_pass, value.u_pass);

            // 给行程记录申请空间, 方便后续插入行程
            node->data.itinerary = (ride_info_type *)malloc(sizeof(ride_info_type) * 16);
            node->data.itinerary_count = 0;

            // 将头结点的next指针指向null (后续用)
            node->next = NULL;
      }

      return node;
}

// 用户购买行程 =>
// 给某个用户添加行程信息  (用户表, 用户名, 航班信息, 席位);
bool add_itinerary(userinfo_type_p head, char *u_name, ride_info_type value)
{
      // 在用户表中 查找这个用户
      userinfo_type_p current = find_user_by_name(head, u_name);

      // 先判断是否为空(没找到)
      if (current != NULL)
      {
            // 再指向真正的用户
            current = current->next;
      }else{
            printf("找不到这个用户\n");
            return false;
      }

      // 给这个用户添加 行程记录[航班号, 席位]
      strcpy(current->data.itinerary[current->data.itinerary_count].flight_number, value.flight_number); // 航班号
      current->data.itinerary[current->data.itinerary_count].type = value.type;                          // 航班席位
      current->data.itinerary_count++;                                                                   // 当前用户行程+1

      // 把这个用户添加到航司的用户链表中
      push_user_to_airline(u_name, value);
      return true;
};

// 插入数据到链表
bool user_insert_head(userinfo_type_p head, userinfo value)
{
      // 创建节点()
      userinfo_type_p node = user_new_node(value);
      if (node != NULL)
      {
            // node 先存好 原本head指向的下一个节点
            node->next = head->next;
            // head的next 指向新创建的 node
            head->next = node;
            return true;
      }
      return false;
}

// 按名字 查找 用户数据
// (为了适配"按名字删除信息功能",
// 本查找函数返回查找到的元素的上一个元素,
// 输出时记得next
// 删除时通过id调用本函数,
// 拿到返回值直接处理next指针并删除下一元素即可)
userinfo_type_p find_user_by_name(userinfo_type_p head, char *u_name)
{
      // 如果链表为空
      if (user_isEmpty(head))
      {
            printf("链表中没有元素，查找失败\n");
            return NULL;
      }

      // 有可能找到第一个节点, 需要返回head
      userinfo_type_p temp = head;

      // 0  1  2  NULL
      while (temp->next != NULL)
      {
            // if (temp->next->data.flight_number == flight_number) 字符串要用 strcmp比较
            // strcmp 返回 0 才是相等！你这个是"不相等就返回"
            // 如果找得到数据
            if (strcmp(temp->next->data.u_name, u_name) == 0)
            {
                  // printf("查找到数据 %s\n", temp->next->data.u_name);
                  // 返回这个用户节点
                  return temp;
            }
            // 否则指针后移
            temp = temp->next;
      }

      printf("#############该用户不存在############### \n\n");
      return NULL;
}

// 用名字 删除用户 (超级管理员删除) (航司管理员不能删除用户, 但是可以在航司用户表中 将该航司指定用户的状态改成其他 )
// 如果坐了某航司的航班，就将该用户加入 该航司客户表中 （并给该用户设置：姓名、飞行次数、 用户状态：0拉黑、 1正常、 是否会员：0否、1是）
bool remove_user_data(userinfo_type_p head, char *u_name)
{
      // 调用查找函数, 会返回查找到的元素的上一个元素
      userinfo_type_p prev = find_user_by_name(head, u_name);

      // 如果返回null说明要删除的数据不存在
      // 如果要删除的数据不存在
      if (!prev)
      {
            printf("******删除失败\n");
            return false;
      }

      // 存储要删除的元素
      userinfo_type_p delnode = prev->next;

      // 0 1 2 3
      // 改变上一个元素的指向
      prev->next = delnode->next;

      // 避免用这个元素访问到后续节点，因为要返回
      delnode->next = NULL;

      // 释放
      free(delnode->data.itinerary);
      free(delnode);
      return true;
}

// 查看全部用户 (超级管理员)
// 显示所有数据
void user_show_list(userinfo_type_p head)
{
      // 如果链表为空
      if (user_isEmpty(head))
      {
            printf("链表中没有元素，显示为空\n");
            return;
      }

      // 首节点无数据， 不输出
      userinfo_type_p temp = head->next;

      printf("########## 所有用户信息begin ########\n");
      printf("用户名\t密码\t当前行程\n");
      // 只要下一个节点不为空
      while (temp != NULL)
      {
            // 用户名  密码  行程
            printf("%s\t%s\t", temp->data.u_name, temp->data.u_pass);

            // 遍历当前用户的全部行程
            for (int i = 0; i < temp->data.itinerary_count; i++)
            {
                  // 输出航班号
                  printf("%s/", temp->data.itinerary[i].flight_number);
                  // 输出席位
                  switch (temp->data.itinerary[i].type)
                  {
                  case 0:
                        printf("头等舱\t");
                        break;

                  case 1:
                        printf("公务舱\t");
                        break;

                  case 2:
                        printf("经济舱\t");
                        break;
                  }
            }
            printf("\n");
            // 就让下一个节点赋值并输出
            temp = temp->next;
      }
      printf("########## 所有用户信息end ########\n\n");
}

// 退出系统，释放所有用户
bool user_destroy(userinfo_type_p head)
{
      // 临时存储
      userinfo_type_p p = head->next;

      // 从head开始，只要head->next不为空，都要删除，直到head->next为空
      // head   1    2    3    NULL
      while (p != NULL)
      {
            // 记录要删除的节点
            userinfo_type_p temp = p;
            // 头节点的next指向删除节点后一位
            p = p->next;
            // 销毁要删除的节点
            free(temp->data.itinerary);
            free(temp);
      }

      // 销毁head
      free(head);
      return true;
}