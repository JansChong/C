#include "all_airline_info.h"


/**
 * @description: 初始化顺序表
 * @param: {} length 顺序表长度
 * @param: {}
 * @return Seq * 顺序表的指针
 */
airlines_seq_type_p airline_init_list(int length)
{
    // 为顺序表的结构体分配内存
    airlines_seq_type_p list = (airlines_seq_type_p)malloc(sizeof(airlines_seq_type));

    // malloc申请失败内存为空, 申请成功则不为空
    if (list != NULL)
    {
        // 顺序表中存储的元素个数
        list->length = length;
        // 尾元素下标
        list->last = -1;
        // 为顺序表的元素数组分配内存
        list->data = (airline_info_type *)malloc(length * sizeof(airline_info_type));
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
static bool airline_isEmpty(airlines_seq_type_p list)
{
    if (list == NULL || list->last < 0 ||  list->data == NULL)
    {
        printf("当前顺序表为空\n");
        return true; // 为空
    }

    return false; // 不为空
}

/**
 * 顺序表已满? 在插入时用上
 */
static bool airline_isFull(airlines_seq_type_p list)
{
    if (list->last == list->length - 1)
    {
        printf("顺序表已满\n");
        return true; // 已满
    }
    return false; // 未满
}

/**
 * @description: 尾插
 * @param: {} list 指向顺序表的指针
 * @param: {} value 新插入元素的值
 * @return boolean
 */
bool airline_insert_tail(airlines_seq_type_p list, airline_info_type value)
{
    // 顺序表未满
    if (!airline_isFull(list))
    {
        // 尾元素下标后移
        ++list->last;

        // 尾插
        list->data[list->last].air_name = value.air_name;
        list->data[list->last].abbreviation = value.abbreviation;
        list->data[list->last].employee_list_length = 0; // 长度为0
        // printf("尾插成功\n");
        return true;
    }

    printf("尾插失败\n");
    return false; // 插入失败
}

/**
 * 通过航司缩写删除航司
 * @param: {}
 * @param: {}
 * @return
 */
bool airline_delete_pos(airlines_seq_type_p list, char *abbreviation)
{
    // 查找航司
    int pos = airline_find_value(list, abbreviation);

    // pos 下标边界控制  -1也是超过边界
    if (pos < 0 || pos > list->last + 1)
    {
        printf("删除位置超过边界\n");
        return false;
    }

    // 顺序表不能为空
    else if (!airline_isEmpty(list))
    {
        // 从当前位置开始， 所有元素往当前位置挪动一位
        for (int i = pos; i < list->last; i++)
        {
            list->data[i] = list->data[i + 1];
        }
        printf("指定位置元素删除成功\n");
        list->last--;
        return true;
    }

    printf("指定位置删除失败\n");
    return false;
}

/**
 * 通过航司缩写 查找 航司, 找得到返回下标， 否则返回-1
 * @param: {} list 要查找的数据表
 * @param: {} value 要查找的数据
 * @return int 找得到返回下标， 找不到返回-1
 */
int airline_find_value(airlines_seq_type_p list, char *abbreviation)
{
    // 不为空
    if (!airline_isEmpty(list))
    {
        for (int i = 0; i <= list->last; i++)
        {
            // 字符串比较 int strcmp(const char *str1, const char *str2)
            if (strcmp(list->data[i].abbreviation, abbreviation) == 0)
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
 * 显示所有航司数据
 * @param: {} list 指向顺序表的指针
 * @return boolean
 */
void airline_show_list(airlines_seq_type_p list)
{
    printf("############### 所有航司数据begin ###############\n");
    // 航司名称  缩写  员工
    printf("%s\t%s\t\t%s\n", "航司名称", "缩写", "员工");
    // 不为空才显示顺序表， 为空已有输出
    if (!airline_isEmpty(list))
    {
        for (int i = 0; i <= list->last; i++)
        {
            printf("%s\t\t%s\t\t", list->data[i].air_name, list->data[i].abbreviation);

            // 遍历员工信息
            for (int j = 0; j < list->data[i].employee_list_length; j++)
            {
                printf("%s ", list->data[i].employee_list[j].u_name);
            }
            printf("\n");
        }
        printf("################ 所有航司数据end ################\n\n");
        return;
    }

    printf("当前没有航司\n\n");
}

/**
 * 销毁顺序表
 */
void airline_destroy_list(airlines_seq_type_p list)
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
