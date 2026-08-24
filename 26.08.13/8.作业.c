#include <stdio.h>

void work1(void);
int work2(int arr[], int keycode, long int len);
void work3(void);
void work4(int a[], int b[], int len);

int main(int argc, char const *argv[])
{

    // work1();

    /* work2: */
    // int arr[4] = {1, 2, 3, 4}; // 16字节
    // int keycode;
    // long int len = sizeof(arr) / sizeof(arr[0]);
    // printf("原数组：{1, 2, 3, 4}\n输入一个数字:");
    // scanf("%d",&keycode);
    // int i = work2(arr, keycode, len);
    // printf("结果为：%d\n", i);

    work3();

    // int a[] = {10, 20, 40, 80, 160};
    // int b[] = {1, 2, 3, 4, 5};
    // int len = sizeof(a) / sizeof(a[0]);
    // work4(a, b, len);

    // printf("原数组a: {10, 20, 40, 80, 160}\n原数组b: {1, 2, 3, 4, 5}\n");
    // printf("互换数组a: {");
    // for (int i = 0; i < len * 2; i++)
    // {
    //     if (i < len){ // 数组a输出
    //         printf("%d", a[i]);
    //         if (i != len - 1)  printf(", ");
    //         else printf("}\n互换数组b: {");
    //     }
    //     else{  // 数组b输出
    //         printf("%d", b[i - len]);
    //         if (i != 2 * len - 1) printf(", ");
    //     }
    // }
    // printf("}\n");
}

// 设计一个函数，传入两个数组a和b，(数组的长度一样)将两个数组的所有元素进行交换，在主函数中打印交换过后的两个数组的所有元素
void work4(int a[], int b[], int len)
{
    // 互换逻辑
    int temp;
    for (int i = 0; i < len; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

//  2/1 + 3/2 + 5/3+8/5+13/8...，前20项的和。
void work3(void)
{
    // {1,2,3,5,8,13......}

    // 数组头
    int arr[20] = {1, 2};
    // 求和
    float sum = 2;

    // 20项
    for (int i = 2; i <= 20; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
        // printf("%d\n", arr[i]);

        sum = sum + (1.0 * (arr[i]) / arr[i - 1]);
        printf("%d/%d \t要加的值：%f， 加完的sum: %f\n",  arr[i], arr[i-1],  (1.0 * (arr[i]) / arr[i - 1]), sum);
    }

    printf("最终的结果为: %f\n", sum);
}

// 6.6、设计一个函数，传入一个数组和一个整型变量，判断这个整数的值是不是数组中某个元素，如果是返回0，如果不是返回-1，并在主函数中打印出来
int work2(int arr[], int keycode, long int len)
{
    // 形参数组名arr 会退化为指向数组首元素的指针, 无法再通过 sizeof(arr)求原数组的大小
    // long int len = sizeof(arr) / sizeof(arr[0]);  // 数组元素个数 =  数组大小 / 数组第一项的大小

    for (int i = 0; i < len; i++)
    {
        if (arr[i] == keycode)
            return 0;
    }

    return -1;
}

// 班级竞选班长，共3个候选人，输入参加选举投票的人数n，然后输入每个人的投票内容(1.2,3)
// 要求用一个数组将所有投票信息存起来。统计，输出3个候选人的最终票数及无效票数。
void work1(void)
{
    // 候选人
    int candidate[] = {1, 2, 3};

    // 参加投票的人数
    int people;
    printf("参与选举投票的人数是：");
    scanf("%d", &people);

    // 要求用一个数组将所有投票信息存起来
    int read_tickets[people]; // 总票数  用变量定义数组，不可以初始化
    // 3位候选人得票数, 加1个无效票数,
    int candidate_votes[4] = {0}; // 没有初始化是随机值, 初始化0则全补0

    // 循环输入每一个人的投票内容（1，2，3） 并写入数组
    for (int i = 0; i < people; i++)
    {
        printf("第%d个人投给:", i + 1);
        // 要求用一个数组将所有投票信息存起来
        scanf("%d", &read_tickets[i]); // 输入的值 依次赋值到数组项
    }

    printf("读票: [");
    // 读取所有人的投票
    for (int i = 0; i < people; i++)
    {
        printf("%d", read_tickets[i]); // 1, 2, 2, 3, 0
        if (i < people - 1)
            printf(", "); // 数组尾部不追加 ','

        // 如果这张票是有效票  1，2，3
        if (read_tickets[i] >= 1 && read_tickets[i] <= 3)
            candidate_votes[read_tickets[i] - 1]++; // 存到各自对应的候选人得票的数组项
        else
            candidate_votes[3]++; // 无效票
    }
    printf("]\n");

    // 结果
    for (int i = 0;; i++)
    {
        if (i == 3)
        {
            printf("无效票: %d\n", candidate_votes[i]);
            return;
        }
        else
            printf("%d得票: %d\n", i + 1, candidate_votes[i]);
    }
}
