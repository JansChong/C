#include "seqStack.h"

int main(int argc, char const *argv[])
{
    // 初始化
    seqStack_type_p manager = init_stack(10);

    // 入栈
    push(manager, 10);
    push(manager, 20);
    push(manager, 30);
    push(manager, 40);
    push(manager, 50);
    // 遍历
    forEach(manager); // 10 20 30 40 50 
    // 出栈
    pop(manager);
    pop(manager);

    // 遍历
    forEach(manager); // 10 20 30 
    // 销毁
    destroy(manager);
}