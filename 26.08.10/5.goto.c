#include <stdio.h>

int main(int argc, char const *argv[])
{

    // 无条件跳转 goto

    printf("1\n");
    goto label; // label 只是一个标识符（变量名）， 这里表示无条件跳转到下面定义的 label 位置 开始执行
    printf("2\n");
    printf("3\n");
    printf("4\n");
label: // label 可以在 goto之上， 这样会死循环
    printf("5\n");
    printf("6\n");

    // goto只能在本函数使用， 不能跨函数跳转
    // goto不利于程序可读性，一般不建议使用

    // start:
    // 初始化流程1
    // 初始化流程2
    // 初始化流程3
    // 初始化流程4
    // 初始化流程5
    // if(未初始化) goto start; // 重新初始化流程  
}
