// 航司管理员(航司员工)
#ifndef _AIRLINE_ADMINISTRATOR_H
#define _AIRLINE_ADMINISTRATOR_H

#include "main.h"

// 航司管理员(航司员工)信息数据 数据结构体
typedef struct airline_administrator_data
{
    char *u_name;            // 名字
    char *u_pass;            // 密码
    char *Belonging_airline; // 所属航空公司 (以上要插入 航司信息 - 航司员工中)
    char *u_number;          // 工号要在插入航司员工表后 自动设置：航司缩写 + sum(260000+员工下标+1)
} air_admin_type;

// 航司管理员(航司员工) 信息数据 管理链表 （这里限制20位航司管理员（公司只招20个岗位），用顺序表（但是删除员工数据时需要成片移动数据））
// 每次插入管理链表时（注册成功时，也插入到 航司信息-航司员工 表）
typedef struct
{
    // 顺序表 数组实现
    air_admin_type *data;
    int last;   // 最尾元素指针
    int length; // 最大员工数量
} airline_admin_seq_type, *airline_admin_seq_type_p;

#endif // !_AIRLINE_ADMINISTRATOR_H