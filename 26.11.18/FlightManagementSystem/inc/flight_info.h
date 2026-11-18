// 航班信息
#ifndef _FLIGHT_INFO_H
#define _FLIGHT_INFO_H

#include "main.h"

// 航班管理 跨文件声明 在 main.c 中已定义
extern flight_info_type_p flight_info_manager; 

// 航班信息数据 数据结构体
typedef struct flight_info_data
{
    // 航班信息：

    // 航班号： 航司 + 编码
    char *flight_number;
    // 承载航司
    char *carrier_airline;
    // 是否为联合航班
    bool is_joint_flights;

    //  （合作航司）
    //  仓位席别+数量+价格：[{type, count, price}, {type, count, price}, {type, count, price}]
    struct seat_details seat_arr[3];
    //  基建燃油
    float infrastructure_fuel_price;

    // 出发地
    char *set_off;
    // 目的地
    char *arrive;
    // 出发时间 "yyyy-MM-dd hh:mm:ss"
    char *departure_time;
    // 到达时间 "yyyy-MM-dd hh:mm:ss"
    char *arrival_time;
} flight_info_data_type;

// 航班信息数据 管理链表  （航班可以有很多，这里用单链表）
typedef struct flight_info_link
{
    // 数据域
    flight_info_data_type data;
    // 指针域
    struct flight_info_link *next;

} flight_info_type, *flight_info_type_p;

// 初始化
flight_info_type_p flight_init_list(void);
// 用航班信息结构体 创建 管理结构体 -- 然后把管理结构体插入链表
flight_info_type_p flight_create_node(flight_info_data_type value);
// 头插
bool flight_insert_head(flight_info_type_p head, flight_info_data_type value);
// 头删 设计成 把删除的节点地址返回 而不是 free
flight_info_type_p flight_remove_head(flight_info_type_p head);
// 按航班号 查找数据
// (为了适配"航班号删除信息功能",
// 本查找函数返回查找到的元素的上一个元素,
// 输出时记得next
// 删除时通过id调用本函数,
// 拿到返回值直接处理next指针并删除下一元素即可)
flight_info_type_p flight_search_by_flightnumber(flight_info_type_p head, char *flight_number);
// 航班号移除数据
flight_info_type_p flight_remove_data(flight_info_type_p head, char *flight_number);
// 显示所有航班
void flight_show_list(flight_info_type_p head);
// 退出系统， 是否所有航班信息
bool flight_destroy(flight_info_type_p head);

#endif // !_FLIGHT_INFO_H