
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
bool insert_tail(airline_admin_seq_type_p list, air_admin_type value)
{
    // 顺序表未满
    if (!airline_administrator_seq_isFull(list))
    {
        list->last += 1;

        // 尾插
        list->data[list->last].u_name = value.u_name; // 输入名字
        list->data[list->last].u_pass = value.u_pass; // 输入密码

        // TODO.. 遍历输出航司信息中所有已经注册的航司，  这里用指令选择航司避免输入不存在的航司 （员工要加入已存在的航司）
        list->data[list->last].Belonging_airline = value.Belonging_airline; // 选择所属航司(缩写)

        // TODO.. 将该员工加入 指定航司信息 - 航司员工中
        // 航司信息 查找 ，  (查到返回下标 否则返回 -1)
        int find_idx = airline_find_value(airline_info_manager, value.Belonging_airline);
        // 如果找到 这个航司
        if (find_idx != -1)
        {   
            // 工号要在插入航司员工表后 自动设置：航司缩写 + sum(260000+员工下标+1)
            // TODO... list->data[list->last].u_number
            // 分配工号： 字符串拼接： (航司缩写 + 26000 + 当前员工下标 + 1)  如 CA260001
            sprintf(list->data[list->last].u_number, value.Belonging_airline, 26000 + airline_info_manager->data[find_idx].employee_list_length + 1);

            
            // TODO.. 整个 航司管理员(航司员工)信息数据 数据结构体 推入 当前航司-员工数组 中


            // 这个航司的员工数量+1
            airline_info_manager->data[find_idx].employee_list_length++;

        }

        printf("尾插成功\n");
        return true;
    }

    printf("尾插失败\n");
    return false; // 插入失败
}
