#include "link.h"

int main(int argc, char const *argv[])
{

      // 初始化链表
      node_type_p head = init_list();
      if (!head)
      {
            printf("链表初始化失败\n");
            return 0;
      }

      // 插入测试数据 方便调试
      struct goods a = {.id = 100003, .name = "iphoneX", .price = 4099.00, .total = 9820};
      struct goods b = {.id = 100004, .name = "iphone11", .price = 6099.00, .total = 820};
      struct goods c = {.id = 100005, .name = "iphone12", .price = 8099.00, .total = 4120};
      struct goods d = {.id = 100006, .name = "iphone13", .price = 10099.00, .total = 20};
      struct goods e = {.id = 100007, .name = "iphone14", .price = 12099.00, .total = 9};
      // 尾插
      insert_tail(head, a);
      insert_tail(head, b);
      insert_tail(head, c);
      insert_tail(head, d);
      insert_tail(head, e);

      // 头插两条数据
      struct goods f = {.id = 100002, .name = "iphone8", .price = 2099.00, .total = 140};
      struct goods g = {.id = 100001, .name = "iphone7", .price = 1099.00, .total = 33};
      // 头插
      insert_head(head, f);
      insert_head(head, g);
      
      // 显示
      show_list(head, 0);

      int keycode;
      while (1)
      {
            // 实现功能
            // 1、商品入库：在尾部增加一条商品记录
            // 2、查找商品：根据商品编号查询商品：找到打印商品全部信息，找不到提示商品不存在
            // 3、商品下架：按商品编号删除商品
            // 4、修改指定商品的库存
            // 5、正向遍历
            // 6、反向遍历
            // 7、退出
            printf("可执行的指令\n 1.商品入库\n 2.查找商品\n 3.商品下架\n 4.修改商品库存\n 5.正向遍历\n 6.反向遍历\n 7.退出\n请输入:");
            scanf("%d", &keycode);
            printf("\n");

            struct goods new_data;

            switch (keycode)
            {
            case 1:
                  // 1、商品入库：在尾部增加一条商品记录
                  printf("输入商品id: ");
                  scanf("%d", &new_data.id);
                  printf("输入商品名称: ");
                  scanf("%s", new_data.name);
                  printf("输入商品单价: ");
                  scanf("%f", &new_data.price);
                  printf("输入商品库存: ");
                  scanf("%d", &new_data.total);
                  if (insert_tail(head, new_data))
                  {
                        printf("## 商品添加成功 ##\n\n");
                  }
                  break;
            case 2:
                  // 2、查找商品：根据商品编号查询商品：找到打印商品全部信息，找不到提示商品不存在
                  printf("请输入要查询的商品id:");
                  scanf("%d", &new_data.id);
                  printf("\n");
                  node_type_p find_result = find_node(head, new_data.id);

                  // 如果找到数据
                  if (find_result)
                  {
                        printf("查找到商品=> id:%d\t名称:%s\t单价:%.2f\t数量:%d\n\n", find_result->data.id, find_result->data.name, find_result->data.price, find_result->data.total);
                  }
                  break;
            case 3:
                  // 3、商品下架：按商品编号删除商品
                  printf("请输入要删除的商品id:");
                  scanf("%d", &new_data.id);
                  printf("\n");
                  // 调用删除函数
                  node_type_p del_node = remove_node(head, new_data.id);
                  // 如果找到数据
                  if (del_node)
                  {
                        free(del_node);
                        printf("删除商品成功\n\n");
                  }
                  break;

            case 4:
                  printf("请输入要修改的商品id:");
                  scanf("%d", &new_data.id);
                  printf("\n");
                  // 4、修改指定商品的库存

                  node_type_p change = find_node(head, new_data.id);
                  // 找到该商品
                  if (change)
                  {
                        printf("输入新库存:");
                        scanf("%d", &new_data.total);
                        // 修改库存
                        change->data.total = new_data.total;
                        printf("修改成功\n\n");
                  }
                  else
                  {
                        printf("找不到该商品\n\n");
                  }
                  break;
            case 5:
                  // 5、正向遍历
                  show_list(head, 0);
                  break;
            case 6:
                  // 6、反向遍历
                  // 把显示的 next 都换成 prev, 其他不变
                  show_list(head, 1);
                  break;
            case 7:
                  // 7、退出
                  // 销毁
                  if (destroy(head))
                  {
                        printf("内存已释放\n");
                        return 0;
                  }
                  else
                  {
                        printf("内存未释放\n");
                  }
                  break;
            }

            
      }
}