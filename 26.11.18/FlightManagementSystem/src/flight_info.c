// 航班信息链表 管理函数

// 导入main.h头文件
#include "main.h"

// 航班信息头文件 （这里担心如果在 main.h 导入各个头文件，会在编译时导入定义的其他模块的头文件， 所以分开导入）
#include "flight_info.h"

// 初始化
// 带头结点 -> 先初始化
// 不带头结点 -> 存入数据时初始化
flight_info_type_p init_list(void)
{
    // 为头结点申请空间 (堆内存)
    flight_info_type_p head = (flight_info_type_p)malloc(sizeof(flight_info_type));

    // 如果申请成功
    if (head != NULL)
    {
        // 将头结点的next指针指向null
        head->next = NULL;
    }

    // 返回头结点 (失败返回null, 成功返回结构体指针head)
    return head;
}

/**
 * @description: 用航班信息结构体 创建 管理结构体 -- 然后把管理结构体插入链表
 * @param: {} value 航班信息数据 结构体
 * @return
 */
flight_info_type_p create_node(flight_info_data_type value)
{
    // 航班信息 管理结构体 （单链表）
    flight_info_type_p node = (flight_info_type_p)malloc(sizeof(flight_info_type));

    // 如果申请成功
    if (node != NULL)
    {
        // node->data.name = value.name;   字符串不可以直接赋值

        // 航班号： 航司 + 编码
        strcpy(node->data.flight_number, value.flight_number);
        // 承载航司
        strcpy(node->data.carrier_airline, value.carrier_airline);
        // 是否为联合航班
        node->data.is_joint_flights = value.is_joint_flights;

        // TODO.. 如果是联合航班
        // if (0)数据要添加到联合航班链表
        // TODO.. 如果不是联合航班
        // else{
        // 把席位信息加入到结构体数组
        memcpy(node->data.seat_arr, value.seat_arr, sizeof(value.seat_arr));
        // 基建燃油
        node->data.infrastructure_fuel_price = value.infrastructure_fuel_price;
        // }

        // 出发地
        strcpy(node->data.set_off, value.set_off);
        // 目的地
        strcpy(node->data.arrive, value.arrive);
        // 出发时间 "yyyy-MM-dd hh:mm:ss"
        strcpy(node->data.departure_time, value.departure_time);
        // 到达时间 "yyyy-MM-dd hh:mm:ss"
        strcpy(node->data.arrival_time, value.arrival_time);

        // 将新结点的next指针指向null (后续用)
        node->next = NULL;
    }

    return node;
}