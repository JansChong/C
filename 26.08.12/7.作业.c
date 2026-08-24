#include <stdio.h>

void work1();
void work2();
void work3();

int main(int argc, char const *argv[])



{

    // work1();
    // work2();

        // 两数互换
        int a = 1, b = 2;
        printf("原值: a=%d, b=%d\n", a, b);
        work3(a, b);
        printf("函数外未互换: a=%d, b=%d\n", a, b);                                                                              // 1 2
        printf("要让函数外也互换，需要把变量作为全局变量直接操作， 且不能以传参的方式传递值，否则只是在操作参数这个局部变量\n"); // 1 2
    
}


// 定义一个长度为10，数据类型为整型的数组，从键盘输入这10个数，要求，算出所有元素之和，并打印出来。
void work1(){

     // 定义一个长度为10，数据类型为整型的数组，
     int arr[10];
     // 用于存储所有元素之和
     int sum = 0;
 
     // 数组的长度 = 整个数组占用的字节数 / 每个元素占用的字节数
     int len = sizeof(arr)/sizeof(arr[0]);
 
     // 遍历数组
     for (int i = 0; i < len; i++)
     {
         printf("请输入第%d个数: \n", i + 1);
         // 从键盘输入这10个数
         scanf("%d", &arr[i]);
         // 将输入的数累加到sum中
         sum += arr[i];
     }
     
     // 打印原数组
     printf("原数组为: [");
     for (int i = 0; i < len; i++)
     {
         printf("%d", arr[i]);
         if (i < len - 1) printf(", ");
     }
     printf("]\n");
 
     // 打印所有元素之和
     printf("所有元素之和为: %d\n", sum);
}


// 定义一个长度为5的数组，输入5个元素，找出最大值和最小值。
void work2(){
    // 定义一个长度为5的数组
    int arr[5] = {};

    // 用于存储最大值和最小值
    int max, min;

    printf("请输入用空格隔开的5个数: \n");
    // 遍历数组
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);

        // 初始化最大最小值， 这样可以避免初始值为0 而纯负数比初始值小 找不到最大值的情况 
        if (i == 0) {
            max = arr[0];
            min = arr[0];
            // printf("最大值为: %d, 最小值为: %d\n", max, min);
            continue; // 第0位不需要比较，只需要赋值，跳过本次循环
        }

        if (arr[i] > max) max = arr[i]; // 最大值
        if (arr[i] < min) min = arr[i]; // 最小值
    }
  
    printf("原数组为: [");
    for (int i = 0; i < 5; i++)
    {
        printf("%d", arr[i]);
        if (i < 4) printf(", ");
    }
    printf("]\n");

    printf("最大值为: %d\n", max);
    printf("最小值为: %d\n", min);


}

//  输入两个整数，设计一个函数， 通过调用这个函数， 实现两个值的交换， 并在函数体内和函数体外打印交换的结果，怎么让这个结果一致？
void work3(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    printf("函数内互换: a=%d, b=%d\n", a, b); // 2 1
}


// 猴子吃桃问题:猴子第一天摘下若干个桃子，当即吃了一半，还不瘾，又多吃了一个，第二天早上又将剩下的桃子吃掉一半，又多吃了一个。以后每天早上都吃了前一天剩下的一半零一个。到第10天早上想高吃时，见只剩下一个桃子了。求第一天共摘了多少。
//
void 