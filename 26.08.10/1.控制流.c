#include <stdio.h>

int main()
{
    // 1. 顺序结构： 程序从上往下运行

    // 分支结构

    // 单分支   if (printf("1\n"))  // printf 函数 会返回 "输出字符串" 的长度
    if (1 < 2)
    {
        printf("条件成立\n");
    }

    // 双分支
    // if() else{}

    // 多分支
    // if(){} else if(){} else {}

    // 练习：
    // 输入三个整数，将这三个整数按照从大到小的顺序排列显示出来。
    int num1, num2, num3;
    printf("请输入三个整数: \n");
    scanf("%d %d %d", &num1, &num2, &num3);

    if (num1 > num2 && num1 > num3 && num2 > num3){
        printf("%d %d %d\n", num1, num2, num3);
    }else if (num1 > num2 && num1 > num3 && num3 > num2){
        printf("%d %d %d\n", num1, num3, num2);
    }else if (num1 > num2 && num3 > num1){
        printf("%d %d %d\n", num3, num1, num2);
    }else if (num2 > num1 && num2 > num3 && num1 > num3){
        printf("%d %d %d\n", num2, num1, num3);
    }else if (num2 > num1 && num2 > num3 && num3 > num1){
        printf("%d %d %d\n", num2, num3, num1);
    }else{
        printf("%d %d %d\n", num3, num2, num1);
    }
    

    if (num1 > num2){
        if (num1 > num3){
            if (num2 > num3){
                printf("%d %d %d\n", num1, num2, num3);
            }else{
                printf("%d %d %d\n", num1, num3, num2);
            }
        }else {
            printf("%d %d %d\n", num3, num1, num2);
        }
    }else{
        if (num2 > num3){
            if (num1 > num3){
                printf("%d %d %d\n", num2, num1, num3);
            }else {
                printf("%d %d %d\n", num2, num3, num1);
            }
        } else {
            printf("%d %d %d\n", num3, num2, num1);
        }
    }
}