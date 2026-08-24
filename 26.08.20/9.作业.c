#include <stdio.h>



struct product
{
    // 序号，
    int num;
    // 商品名字
    char *name;
    // 价格
    float price;
    // 剩余数量
    int count;
};


void showLight();
void showMenu(struct product goods[]);
void buy(struct product goods[]);



int main(int argc, char const *argv[])
{

    // 练习3：
    // 设计一个购物程序

    // 用结构体表示商品信息（序号，商品名字、价格、剩余数量），程序开始运行的时候，初始化至少6种商品的信息。
    struct product goods[6] = {
        {1, "预知子", 16.99, 30},
        {2, "红芭乐", 18.99, 20},
        {3, "释迦果", 15.99, 24},
        {4, "妃子笑", 8.99, 32},
        {5, "嘉宝果", 14.99, 22},
        {6, "奇异果", 12.99, 10},
    }; // 结构体数组

    // (菜单显示设计成函数) 显示菜单：
    showMenu(goods);

    // 操作
    // 请选择要购买的商品：4
    // 请输入要购买的数量：2

    // 显示需要支付的金额（支付金额计算设计成函数 打印出来）

    // 交易完成。（这个时候重新显示菜单）
}



// 购买 并 计算金额
void buy(struct product goods[])
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
void showMenu(struct product goods[])
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

// 显示招牌
void showLight()
{
    // printf("\033[5;30;40m 输出红色字符\033[0m\n")
    printf("\033[5;30;46m 牛 \033[0m");
    printf(" ");
    printf("\033[5;30;41m 来 \033[0m");
    printf(" ");
    printf("\033[5;30;42m 超 \033[0m");
    printf(" ");
    printf("\033[5;30;43m 市 \033[0m");
    printf("  ");
    printf("\033[5;30;44m 特 \033[0m");
    printf(" ");
    printf("\033[5;30;45m 价 \033[0m");
    printf(" ");
    printf("\033[5;37;40m 甩 \033[0m");
    printf(" ");
    printf("\033[5;30;47m 卖 \033[0m");
    printf("\n");
}