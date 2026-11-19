// 航司员工 头文件
#include "airline_administrator.h"

// 所有航司管理 头文件 （这里要把当前注册的员工 加入到 航司信息-航司员工 中， 所以跨文件读取航司信息）
#include "all_airline_info.h"

/**
 * @description: 初始化顺序表
 * @param: {} length 顺序表长度
 * @param: {}
 * @return 顺序表的指针
 */
airline_admin_seq_type_p airline_administrator_init_list(int length)
{
    // 为顺序表的结构体分配内存
    airline_admin_seq_type_p list = (airline_admin_seq_type_p)malloc(sizeof(airline_admin_seq_type));

    // malloc申请失败内存为空, 申请成功则不为空
    if (list != NULL)
    {
        // 顺序表中存储的元素个数
        list->length = length;
        // 尾元素下标
        list->last = -1;
        // 为顺序表的元素数组分配内存
        list->data = (air_admin_type *)malloc(length * sizeof(air_admin_type));
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
static bool airline_administrator_seq_isEmpty(airline_admin_seq_type_p list)
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
static bool airline_administrator_seq_isFull(airline_admin_seq_type_p list)
{
    if (list->last == list->length - 1)
    {
        printf("顺序表已满\n");
        return true; // 已满
    }
    return false; // 未满
}

/**
 * @description: 尾插 -- 注册 航司员工
 * @param: {} list 指向顺序表的指针
 * @param: {} value 新插入元素的值
 * @return boolean
 */
bool airline_administrator_seq_insert_tail(airline_admin_seq_type_p list, air_admin_type value)
{
    // 顺序表未满
    if (!airline_administrator_seq_isFull(list))
    {
        // TODO.. 将该员工加入 指定航司信息 - 航司员工中
        // 航司信息 查找 ，  (查到返回下标 否则返回 -1)
        int find_idx = airline_find_value(airline_info_manager, value.Belonging_airline);
        // 如果找到 这个航司
        if (find_idx != -1)
        {
            list->last += 1;

            // 尾插
            // list->data[list->last].u_name = value.u_name; // 输入名字
            // list->data[list->last].u_pass = value.u_pass; // 输入密码
            // // TODO.. 遍历输出航司信息中所有已经注册的航司，  这里用指令选择航司避免输入不存在的航司 （员工要加入已存在的航司）
            // list->data[list->last].Belonging_airline = value.Belonging_airline; // 选择所属航司(缩写)
            list->data[list->last] = value;

            // 工号要在插入航司员工表后 自动设置：航司缩写 + sum(26000+员工下标+1)
            // 分配工号： 字符串拼接： (航司缩写 + 26000 + 当前员工下标 + 1)  如 CA26001
            sprintf(list->data[list->last].u_number, "%s%d", value.Belonging_airline, 26000 + airline_info_manager->data[find_idx].employee_list_length + 1);

            // 先在 航司用户表中 查找是否有该员工, 没有再加入
            // 整个 航司管理员(航司员工)信息数据 数据结构体 推入 当前航司-员工数组 中
            // airline_info_manager->data[find_idx].employee_list[airline_info_manager->data[find_idx].employee_list_length].u_name = list->data[list->last].u_name;
            // airline_info_manager->data[find_idx].employee_list[airline_info_manager->data[find_idx].employee_list_length].u_pass = list->data[list->last].u_pass;
            // airline_info_manager->data[find_idx].employee_list[airline_info_manager->data[find_idx].employee_list_length].Belonging_airline = list->data[list->last].Belonging_airline;
            // strcpy(airline_info_manager->data[find_idx].employee_list[airline_info_manager->data[find_idx].employee_list_length].u_number, list->data[list->last].u_number);
            airline_info_manager->data[find_idx].employee_list[airline_info_manager->data[find_idx].employee_list_length] = list->data[list->last];
            // 这个航司的员工数量+1
            airline_info_manager->data[find_idx].employee_list_length++;

            // printf("尾插成功\n");
            return true;
        }
        else
        {
            printf("不存在该航空公司,请检查航空公司是否已创建!\n");
            return false;
        }
    }

    printf("尾插失败\n");
    return false; // 插入失败
}

/**
 * 用名字查找员工
 * @param: {} list 要查找的数据表
 * @param: {} value 要查找的数据
 * @return int 找得到返回下标， 找不到返回-1
 */
int airline_administrator_seq_find_value(airline_admin_seq_type_p list, char *u_name)
{
    // 不为空
    if (!airline_administrator_seq_isEmpty(list))
    {
        for (int i = 0; i <= list->last; i++)
        {
            // 如果找到
            if (strcmp(list->data[i].u_name, u_name) == 0)
            {
                // printf("该元素下标为 %d\n", i);
                return i;
            }
        }

        // printf("找不到该元素 %d\n", -1);
        return -1; // 找不到这个元素
    }

    // 顺序表为空
    else
        printf("顺序表为空 %d\n", -1);
    return -1;
}

/**
 * 用名称删除员工
 * @param: {}
 * @param: {}
 * @return
 */
// list 参数合法
bool airline_administrator_seq_delete_pos(airline_admin_seq_type_p list, char *u_name)
{
    int pos = airline_administrator_seq_find_value(list, u_name);

    // pos 下标边界控制
    if (pos < 0 || pos > list->last + 1)
    {
        printf("删除位置超过边界\n");
        return false;
    }

    // 顺序表不能为空
    else if (!airline_administrator_seq_isEmpty(list))
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
 * 显示顺序表数据
 * @param: {} list 指向顺序表的指针
 * @return boolean
 */
void airline_administrator_seq_show_list(airline_admin_seq_type_p list)
{
    // 不为空才显示顺序表， 为空已有输出
    if (!airline_administrator_seq_isEmpty(list))
    {
        printf("############## 所有员工begin ###############\n");
        for (int i = 0; i <= list->last; i++)
        {
            // 用航司缩写 查找 航司全名, 返回下标
            int find_idx = airline_find_value(airline_info_manager, list->data[i].Belonging_airline);
            // 不需要考虑 find_idx 等于-1 的情况, 因为添加员工时, 会让她再指定的航司中选择一个航司, 所以一定能找到该员工的服务航司
            // 用下标找航司的名字
            char *airline_name = airline_info_manager->data[find_idx].air_name;
            // 工号      名字     所属航空公司
            // printf("%s\t\t%s\t\t%s", list->data[i].u_number, list->data.u_name, list->data->Belonging_airline);
            printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", list->data[i].u_number, list->data[i].u_name, airline_name, list->data[i].Belonging_airline, list->data[i].u_pass);
        }
        printf("############## 所有员工end ###############\n\n");
    }
}

/**
 * 销毁顺序表
 */
void airline_administrator_seq_destroy_list(airline_admin_seq_type_p list)
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
