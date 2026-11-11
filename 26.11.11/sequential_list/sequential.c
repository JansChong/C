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

    // malloc申请失败内存为空, 申请成功则不为空
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
    if (list->last < 0 || list == NULL || list->data == NULL)
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

// TODO.. 顺序表参数不合法， 如尾插时传递的 list为NULL(未初始化)

/**
 * @description: 尾插
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
        printf("尾插成功\n");
        return true;
    }

    printf("尾插失败\n");
    return false; // 插入失败
}

/**
 * @description: 头插
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
        printf("头插成功\n");
        return true;
    }

    // 否则顺序表已满，插入失败
    printf("头插失败\n");
    return false;
}

/**
 * 指定位置插入
 * @param: {}
 * @param: {}
 * @return
 */
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

/**
 * 指定位置删除
 * @param: {}
 * @param: {}
 * @return
 */
// list 参数合法


bool delete_pos(Seq_type_p list, int pos)
{
    // pos 下标边界控制
    if (pos < 0 || pos > list->last + 1)
    {
        printf("删除位置超过边界\n");
        return false;
    }

    // 顺序表不能为空
    else if(!isEmpty(list)){
        // 从当前位置开始， 所有元素往当前位置挪动一位
        for (int i = pos; i < list->last; i++)
        {
            list->data[i] = list->data[i+1];
        }
        printf("指定位置元素删除成功\n");
        list->last--;
        return true;
    }

   printf("指定位置删除失败\n");
   return false;
}

/**
 * 头删
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

/**
 * 尾删
 * @param: {} list 指向顺序表的指针
 * @return boolean
 */
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
 * 在顺序表中查找指定元素, 找得到返回下标， 否则返回-1
 * @param: {} list 要查找的数据表
 * @param: {} value 要查找的数据
 * @return int 找得到返回下标， 找不到返回-1
 */
int find_value(Seq_type_p list, int value)
{
    // 不为空
    if (!isEmpty(list))
    {
        for (int i = 0; i <= list->last; i++)
        {
            if (list->data[i] == value)
            {
                printf("该元素下标为 %d\n", i);
                return i;
            }
        }

        printf("找不到该元素 %d\n", -1);
        return -1; // 找不到这个元素
    }

    // 顺序表为空
    else
        printf("找不到该元素 %d\n", -1);
    return -1;
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

/**
 * 销毁顺序表
 */
void destroy_list(Seq_type_p list)
{

    // 顺序表没有创建
    if (list == NULL)
    {
        return;
    }

    // 释放内存
    free(list->data);
    free(list);
    printf("顺序表销毁成功\n");
    return;
}