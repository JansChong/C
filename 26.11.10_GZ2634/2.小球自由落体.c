#include <stdio.h>

// 一球从100米高度自由落下，每次落地后反跳回原高度的一半；再落下，求它在第10次落地时，共经过多少米？第10次反弹多高？

// 宏定义
#define INITIAL_HEIGHT 100; // 初始高度
#define BOUNCE_COUNT 10;    // 弹跳次数

int main(int argc, char const *argv[])
{
    double decreasing_height = INITIAL_HEIGHT; // 递减高度
    double accumulated_height = INITIAL_HEIGHT; // 所经路径

    decreasing_height /= 2;

    for (int i = 2; i<=10; i++)
    {
      accumulated_height += decreasing_height * 2;
      decreasing_height /= 2;
    }

    // 经过for, s的高度为第10次反弹的高度
    // 第10次反弹的高度不需要加进去，只要第10次落地时经过的距离
    printf("%f %f\n", accumulated_height, decreasing_height);
}


// https://www.runoob.com/cprogramming/c-exercise-example20.html
