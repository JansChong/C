#include <stdio.h>


struct product
{
    int number;
    // char *name;
    char name[10];
    float price;
};


int main(int argc, char const *argv[])
{


    // 定义结构体变量 没有初始化
    struct  product  wather = {.name = "M"};

    printf("请输入序号, 名字, 价格: \n");
    scanf("%d %s %f", &a.number, a.name, &a.price);
    
    printf("商品序号: %d\n", a.number);
    printf("商品名称: %s\n", a.name);
    printf("商品价格: %f\n", a.price);
}
