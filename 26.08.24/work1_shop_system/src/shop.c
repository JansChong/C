#include "../include/showlight.h"

// 购买 并 计算金额
void buy(product goods[])
{
      int number, count;
      // 请选择要购买的商品：4
      printf("\n请选择要购买的商品序号: ");
      scanf("%d", &number);

      // 请输入要购买的数量：2
      printf("请输入要购买的数量: ");
      scanf("%d", &count);

      // 计算金额: 您当前购买的商品:xxx, 数量:xxx, 总价:xxx;
      printf("\n\033[1;30;47m ******您当前购买的商品****** \033[0m\n");
      printf("名称\t\t单价\t\t购买数量\t\t总价\n");
      printf("%s\t\t%.2f\t\t%d\t\t\t￥%.2f\n\n", goods[number - 1].name, goods[number - 1].price, count, goods[number - 1].price * count);

      // 减去相应的水果数量, 重新显示菜单
      goods[number - 1].count = goods[number - 1].count - count;
      showMenu(goods);
}

// 显示菜单
void showMenu(product goods[])
{

      showLight(); // 招牌
      printf("序号\t\t名字\t\t价格\t\t数量\n");

      for (int i = 0; i < 6; i++)
      {
            printf("%d\t\t%s\t\t%.2f\t\t%d\n", goods[i].num, goods[i].name, goods[i].price, goods[i].count);
      }

      // 购买操作
      buy(goods);
      // 列表显示每种商品的 名字、价格、数量
      // 序号    名字        价格    数量
      // 1    zsan    22    3
      // 2    lisi        21    4
      // 3    wangwu    23    6
      // 4     zliu        22    10
      // 5     tianqi    21    7
      // 6    wangba    22    8
}
