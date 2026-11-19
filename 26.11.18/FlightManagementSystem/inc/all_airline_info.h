// 所有航空公司
#ifndef _ALL_AIRLINE_INFO_H
#define _ALL_AIRLINE_INFO_H

#include "main.h"
#include "airline_administrator.h"

// 航司客户 和 航司员工不一样, 有其他属性, 这里单独定义
// 给该用户设置：
typedef struct
{
    char u_name[15];       // 姓名
    int number_of_flights; // 飞行次数
    int user_status;       // 用户状态：0拉黑、 1正常
    int ismember;          // 是否会员：0否、1是
} customer_type;

// 航司信息：
typedef struct
{
    char *air_name;     // 航司名称
    char *abbreviation; // 缩写

    // 注册员工时, 会自动往其航司添加员工
    air_admin_type employee_list[20]; // 员工信息限制20个
    // 当前员工数量, 插入和判空用 （也可以用 sizeof(数组)/sizeof(数组项) = length ）
    int employee_list_length;

    // 用户选择乘坐航班时, 会自动往其航司的用户表中添加客户
    // 航司客户 // 简化版用数组  //  用链表 -- 这个属性需要初始化(数据域，指针域)， 这个属性需要 增删改查
    customer_type customer_list[20];
    int customer_list_length;

    // 存在航司信息中 -- 如果坐了本航司的航班，就将该用户加入 航司客户表中 （并给该用户设置：姓名、飞行次数、 用户状态：0拉黑、 1正常、 是否会员：0否、1是）
} airline_info_type;

// 使用顺序表（这里限制10个， 每一个航司是一个结构体）
typedef struct
{
    int length; // 这里固定为10
    int last;   // 尾元素下标
    airline_info_type *data;
} airlines_seq_type, *airlines_seq_type_p;

// 航司管理 跨文件声明 在 main.c 中已定义
extern airlines_seq_type_p airline_info_manager;

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

/**
 * 把用户推入航司用户表中
 * @param u_name 用户名
 * @param value 航班信息 {航班号, 席位}
 */
bool push_user_to_airline(char *u_name, ride_info_type value);


#endif // !_ALL_AIRLINE_INFO_H
