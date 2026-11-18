// 航司管理员(航司员工)
#ifndef _AIRLINE_ADMINISTRATOR_H
#define _AIRLINE_ADMINISTRATOR_H

#include "main.h"

// 航司管理员(航司员工)信息数据 数据结构体
typedef struct airline_administrator_data{
    char *u_name; // 名字
    char *u_pass; // 密码
    char *Belonging_airline; // 所属航空公司 (这里要插入 航司信息 - 航司员工中)
    int u_number; // 工号 自分配  航司简写 + 6位数字
} air_admin_type ;


// 航司管理员(航司员工) 信息数据 管理链表 （这里限制20位航司管理员，用顺序表 （但是删除员工数据时需要成片移动数据））
// 每次插入管理链表时（注册成功时，也插入到 航司信息-航司员工 表）


#endif // !_AIRLINE_ADMINISTRATOR_H