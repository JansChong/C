// 所有航空公司
#ifndef _ALL_AIRLINE_INFO_H
#define _ALL_AIRLINE_INFO_H

#include "main.h"
#include "airline_administrator.h"

// 航司管理 跨文件声明 在 main.c 中已定义
extern airlines_seq_type_p airline_info_manager;

// 航司信息：
typedef struct
{
    char *air_name;     // 航司名称
    char *abbreviation; // 缩写

    air_admin_type employee_list[20]; // 员工信息限制20个
    // 当前员工数量, 插入和判空用 （也可以用 sizeof(数组)/sizeof(数组项) = length ）
    int employee_list_length;

    // TODO. 航司客户 // 这里用链表 -- 这个属性需要初始化(数据域，指针域)， 这个属性需要 增删改查
    // TODO. 航司客户 // 简化版用数组 (先用简化版？)

} airline_info_type;

// 使用顺序表（这里限制10个， 每一个航司是一个结构体）
typedef struct
{
    int length; // 这里固定为10
    int last;   // 尾元素下标
    airline_info_type *data;
} airlines_seq_type, *airlines_seq_type_p;

// 初始化顺序表
airlines_seq_type_p airline_init_list(int length);
// 尾插
bool airline_insert_tail(airlines_seq_type_p list, airline_info_type value);
// 通过航司缩写删除航司
bool airline_delete_pos(airlines_seq_type_p list, char *abbreviation);
// 通过航司缩写 查找 航司, 找得到返回下标， 否则返回-1
int airline_find_value(airlines_seq_type_p list, char *abbreviation);
// 显示所有航司数据
void airline_show_list(airlines_seq_type_p list);
// 销毁顺序表
void airline_destroy_list(airlines_seq_type_p list);

#endif // !_ALL_AIRLINE_INFO_H
