#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sequential.h"

// 创建一个顺序表，
// 并从键盘接收数字输入，
// 将输入的正整数按从小到大的顺序插入顺序表，
// 并在输入负整数的时候将其绝对值数据删除。
// 每次输入后，将顺序表的内容打印到屏幕上。

// 初始化
Seq_type_p init_list(int length)
{

    // 管理结构体申请空间
    Seq_type_p list = (Seq_type_p)malloc(sizeof(Seq_type));

    if (list != NULL)
    {

        list->length = length;
        list->last = -1;
        list->data = (int *)malloc(sizeof(int) * length);

        // 如果申请失败
        if (list->data == NULL)
        {
            free(list);
            printf("顺序表管理结构体初始化失败\n");
            return NULL;
        }
    }

    // 返回顺序表结构体
    return list;
}

static bool isFull(Seq_type_p list)
{
    if (list->last == list->length - 1)
    {
        printf("顺序表已满\n");
        return true; // 已满
    }
    return false; // 未满
}

// list 参数需合法
bool insert_pos(Seq_type_p list, int value, int pos)
{

    // pos 下标边界控制 需要包含头插（pos等于0）和尾插（pos等于list->last + 1）
    if (pos < 0 || pos > list->last + 1)
    {
        printf("插入位置超过边界\n");
        return false;
    }

    // 顺序表未满
    else if (!isFull(list))
    {
        // 从末尾到该位置往后挪
        for (int i = list->last; i >= pos; i--)
        {
            list->data[i + 1] = list->data[i];
        }

        list->data[pos] = value;
        list->last++;

        printf("指定位置插入成功\n");
        return true;
    }

    printf("指定位置插入失败\n");
    return false;
}

// 从键盘接收数字输入，将输入的正整数按从小到大的顺序插入顺序表，并在输入负整数的时候将其绝对值数据删除。每次输入后，将顺序表的内容打印到屏幕上。
void input_and_show_list(Seq_type_p list)
{

    for (int i = 0; i < list->length; i++)
    {
        // 判断当前输入的是第几个数
        printf("请输入第%d个数: ", (list->length - (list->length - list->last)) + 2);
        // 输入的数
        int value;
        scanf("%d", &value);

        // 输入的正整数
        if (value >= 0)
        {
            // 按从小到大的顺序插入顺序表
            sort_insert(list, value);
        }
        // 输入负整数
        else
        {
            // TODO.. 在顺序表中删除这个数的绝对值
            bool res = delete_value(list, abs(value));

            // 如果删除成功, list-data则少了一条数据
            if (res)
            {
                // printf("%d删除成功\n", value);
                i--; // 补回少的这条数据
            }

            // 又因为本次输入占用了一次输入（即使没有删除到元素）， 所以要补回本次输入的次数
            i--;
        }

        // 显示最新的顺序表
        show_list(list);
    }
}

// 按从小到大的顺序插入顺序表
bool sort_insert(Seq_type_p list, int value)
{

    int inserted = 0;
    for (int i = 0; i < list->last + 1; i++)
    {
        if (value < list->data[i])
        {
            insert_pos(list, value, i);
            inserted = 1;
            break;
        }
    }
    if (inserted == 0)
    {
        insert_pos(list, value, list->last + 1);
    }
    // // 如果没有元素 或者 比表头小
    // if (list->last == -1 || value < list->data[0])
    // {
    //     // 头插： 从最后一个往前 直到 要插入的位置， 其元素往后挪动一位
    //     for (int i = list->last; i >= 0; i--)
    //     {
    //         list->data[i + 1] = list->data[i];
    //     }
    //     // 插入
    //     list->data[0] = value;
    //     list->last++;

    //     return true;
    // }
    // // 比尾大
    // else if (value >= list->data[list->last])
    // {
    //     list->data[++list->last] = value;
    //     return true;
    // }
    // // 在中间
    // else
    // {
    //     // 记录要插入的位置
    //     int flag;

    //     // 遍历表 -> 记录要插入的位置
    //     for (int i = 0; i < list->last; i++)
    //     {
    //         if (value >= list->data[i] && value < list->data[i + 1])
    //         {
    //             flag = i + 1;
    //             break;
    //         }
    //     }

    //     // 中间插入： 要插入的位置和之后的元素，往后挪动一位
    //     for (int i = list->last; i >= flag; i--)
    //     {
    //         list->data[i + 1] = list->data[i];
    //     }
    //     // 插入
    //     list->data[flag] = value;
    //     list->last++;
    //     return true;
    // }
}

// 删除目标值的绝对值
bool delete_value(Seq_type_p list, int value)
{
    // 定义要删除的元素的下标
    int flag = -1;

    // 查找该元素
    for (int i = 0; i <= list->last; i++)
    {
        if (value == list->data[i])
        {
            // 找到要删除的元素的下标
            flag = i;
            break;
        }
    }

    if (flag != -1)
    {
        // 不管头删，尾删，中间删，都用这个循环
        for (int i = flag; i < list->last; i++)
        {
            list->data[i] = list->data[i + 1];
        }
        list->last--;
        return true;
    }
    else
    {
        printf("找不到需要删除的元素\n");
        return false;
    }
}

// 显示顺序表
void show_list(Seq_type_p list)
{

    // todo.. list参数有效 且 list->data 不为空

    //
    printf("######### 顺序表更新：");
    for (int i = 0; i <= list->last; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}
