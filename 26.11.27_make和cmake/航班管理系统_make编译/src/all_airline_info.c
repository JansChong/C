#include "main.h"
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
    if (list == NULL || list->last < 0 || list->data == NULL)
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
 * @description: 添加航司数据
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
        list->data[list->last].employee_list_length = 0; // 员工长度为0
        list->data[list->last].customer_list_length = 0; // 客户长度为0
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
                // printf("该元素下标为 %d\n", i);
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
    printf("%s\t%s\t\t%s\t\n", "航司名称", "缩写", "员工");
    // 不为空才显示顺序表， 为空已有输出
    if (!airline_isEmpty(list))
    {
        for (int i = 0; i <= list->last; i++)
        {
            printf("---------------------------\n%s\t\t%s\t\t", list->data[i].air_name, list->data[i].abbreviation);

            // 遍历员工信息
            for (int j = 0; j < list->data[i].employee_list_length; j++)
            {
                printf("%s\t", list->data[i].employee_list[j].u_name);
            }

            printf("\n\n本航司名下客户:\n");
            printf("%s\t%s\t%s\t%s\n", "客户", "乘坐本司航班次数", "客户状态", "会员");
            // 遍历客户信息
            for (int j = 0; j < list->data[i].customer_list_length; j++)
            {
                // printf("%s%d%s%s\n",  "客户", "乘坐本司航班次数", "客户状态", "会员");

                printf("%s\t%d\t\t\t%s\t\t%s\n",
                       list->data[i].customer_list[j].u_name,
                       list->data[i].customer_list[j].number_of_flights,
                       list->data[i].customer_list[j].user_status == 0 ? "拉黑" : "正常",
                       list->data[i].customer_list[j].ismember == 0 ? "否" : "是");
                       
            }
            printf("\n");

            // 遍历用户信息
        }
        printf("################ 所有航司数据end ################\n\n");
        return;
    }

    printf("当前没有航司\n\n");
}

// 显示航司简略数据 (航司名称, 缩写)
void airline_show_simple_list(airlines_seq_type_p list)
{
    // 航司名称  缩写
    printf("%s\t%s\t%s\t\n", "编号", "航司名称", "缩写");
    // 不为空才显示顺序表， 为空已有输出
    if (!airline_isEmpty(list))
    {
        for (int i = 0; i <= list->last; i++)
        {
            printf("%d\t%s\t\t%s\t\n", i+1, list->data[i].air_name, list->data[i].abbreviation);
        }
        printf("\n");
        return;
    }

    printf("当前没有航司\n\n");
};


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

// 把员工推入航司员工表中
bool push_employee_to_airline()
{
    // TODO..
    return false;
};

/**
 * 把用户推入航司用户表中
 * @param u_name 用户名
 * @param value 航班信息 {航班号, 席位}
 */
bool push_user_to_airline(char *u_name, ride_info_type value)
{
    // 把这个用户添加到航司的用户表中
    // 用缩写 查找某个航司(airlines_seq_type_p 航司链表, 航司缩写) => (返回下标 或者 -1)
    char code[3] = {0};                    // 存2个字符 + 结束符
    strncpy(code, value.flight_number, 2); // 缩写

    // 用缩写查找航司
    int idx = airline_find_value(airline_info_manager, code); // 查找指定航司

    // 找到航司
    if (idx != -1)
    {
        int flag = -1;

        // 先在 航司用户表中 查找是否有该用户, 有则数量+1, 无则新增一个用户
        // 遍历该航司的用户表, 看看该用户是否存在
        for (int i = 0; i < airline_info_manager->data[idx].customer_list_length; i++)
        {
            // 如果用户存在
            if (strcmp(airline_info_manager->data[idx].customer_list[i].u_name, u_name) == 0)
            {
                flag = i;
                break;
            }
        }

        // 航司中没有该用户
        if (flag == -1)
        {
            // 添加该用户
            strcpy(airline_info_manager->data[idx].customer_list[airline_info_manager->data[idx].customer_list_length].u_name, u_name); // 用户名
            airline_info_manager->data[idx].customer_list[airline_info_manager->data[idx].customer_list_length].number_of_flights = 1;  // 飞行次数
            airline_info_manager->data[idx].customer_list[airline_info_manager->data[idx].customer_list_length].user_status = 1;        // 会员状态
            airline_info_manager->data[idx].customer_list[airline_info_manager->data[idx].customer_list_length].ismember = 1;           // 是否会员

            // 管理航司用户长度
            airline_info_manager->data[idx].customer_list_length++;
        }
        // 如果存在该用户, 飞行次数+1
        else
        {
            airline_info_manager->data[idx].customer_list[flag].number_of_flights++; // 飞行次数+1
        }

        return true;
    }

    // 找不到该航司
    printf("找不到这个航司, 无法为航司插入新用户\n");
    return false;
};
