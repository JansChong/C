#include "chain_stack.h"

int main(int argc, char const *argv[])
{

    // 初始化
    link_stack_type_p managar = init_stack();

    // 打印行号，查找错误
    // printf("%d\n", __LINE__);

    // 入栈
    push(managar, 10);
    push(managar, 20);
    push(managar, 30);
    push(managar, 40);
    push(managar, 50);

    // 遍历
    forEach(managar); // 50 40 30 20 10 
    // printf("%d\n", __LINE__);

    // 出栈
    pop(managar);
    pop(managar);
    pop(managar);
    // printf("%d\n", __LINE__);

    // 遍历
    forEach(managar); // 20 10 
    // printf("%d\n", __LINE__);

    // 销毁
    destroy(managar);
}