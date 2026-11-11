#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sequential.h"

/**
 * @description: 初始化顺序表
 * @param: {} length 顺序表长度
 * @param: {}
 * @return Seq * 顺序表的指针
 */
Seq_type_p init_list(int length)
{
    // 为顺序表的结构体分配内存
    Seq_type_p list = (Seq_type_p)malloc(sizeof(Seq_type));

    // malloc申请失败内存为空, 不为空则申请成功
    if (list != NULL)
    {
        // 顺序表中存储的元素个数
        list->length = length;
        // 尾元素下标
        list->last = -1;
        // 为顺序表的元素数组分配内存
        list->data = (int *)malloc(length * sizeof(int));
        // 如果申请失败
        if (list->data == NULL)
        {
            free(list); // 回收list申请的空间
            printf("初始化顺序表管理结构体失败\n");
            return NULL;
        }
    }

    // 返回顺序表结构体
    return list;
}

/**
 * 顺序表为空？ 在显示/删除时用上
 */
static bool isEmpty(Seq_type_p list)
{
    if (list->last == -1)
    {
        printf("当前顺序表为空\n");
        return true; // 为空
    }

    return false; // 不为空
}

/**
 * 顺序表已满? 在插入时用上
 */
static bool isFull(Seq_type_p list)
{
    if (list->last == list->length - 1)
    {
        printf("顺序表已满\n");
        return true; // 已满
    }
    return false; // 未满
}

/**
 * @description: 在顺序表的尾部插入一个元素
 * @param: {} list 指向顺序表的指针
 * @param: {} value 新插入元素的值
 * @return boolean
 */
bool insert_tail(Seq_type_p list, int value)
{
    // 顺序表未满
    if (!isFull(list))
    {
        // 尾插
        list->data[++list->last] = value;
        return true;
    }

    printf("尾插失败\n");
    return false; // 插入失败
}

/**
 * @description: 在顺序表的头部插入一个元素
 * @param: {} list 指向顺序表的指针
 * @param: {} value 新插入元素的值
 * @return boolean
 */
bool insert_head(Seq_type_p list, int value)
{
    // 判断顺序表是否已满，如果未满
    if (!isFull(list))
    {
        // 头插, 后续元素往后挪一位  （该条件已考虑顺序表为空的情况）
        for (int i = list->last; i >= 0; i--)
        {
            list->data[i + 1] = list->data[i];
        }

        // 头插
        list->data[0] = value;
        list->last++;
        return true;
    }

    // 否则顺序表已满，插入失败
    printf("头插失败\n");
    return false;
}


/**
* @description: 头部删除
* @param: {} list 指向顺序表的指针
* @return boolean
*/
bool delete_head(Seq_type_p list)
{
    // 不为空
    if (!isEmpty(list))
    {
        // 后一项挪到前一项
        for (int i = 0; i < list->last; i++)
        {
            list->data[i] = list->data[i + 1];
        }
        list->last--;
        printf("头部删除成功\n");
        return true;
    }

    printf("头部删除失败\n");
    return false;
}

// 尾部删除
bool delete_tail(Seq_type_p list)
{
    // 不为空
    if (!isEmpty(list))
    {
        list->last--;
        printf("尾部删除成功\n");
        return true;
    }

    // 删除失败
    printf("尾部删除元素失败\n");
    return false;
}

/**
 * 显示顺序表数据
 * @param: {} list 指向顺序表的指针
 * @return boolean
 */
void show_list(Seq_type_p list)
{ 
    printf("显示顺序表数据: ");
    // 不为空才显示顺序表， 为空已有输出
    if (!isEmpty(list))
    {
        for (int i = 0; i <= list->last; i++)
        {
            printf("%d ", list->data[i]);
        }
        printf("\n");
    }
}