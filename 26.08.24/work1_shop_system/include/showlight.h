#ifndef SHOWLIGHT
#define SHOWLIGHT

#include <stdio.h>

// 商品定义
typedef struct product
{
    // 序号，
    int num;
    // 商品名字
    char *name;
    // 价格
    float price;
    // 剩余数量
    int count;
} product;


// 显示招牌 - 函数声明
void showLight();
// 购买 并 计算金额
void buy(product goods[]);
// 显示菜单
void showMenu(product goods[]);


#endif