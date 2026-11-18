// 航班信息
#ifndef _FLIGHT_INFO_H
#define _FLIGHT_INFO_H

// 航班信息数据 结构体 
typedef struct flight_info_data
{
    // 航班信息：

    // 航班号： 航司 + 编码
    char *flight_number;
    // 承载航司
    char *carrier_airline;
    // 是否为联合航班
    bool is_joint_flights;

    //     （合作航司）
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


// 航班信息数据 管理结构体  （单链表）
typedef struct flight_info_link
{
    // 数据域
    flight_info_data_type data;
    // 指针域
    struct flight_info_link *next;

} flight_info_type, flight_info_type_p;



#endif // !_FLIGHT_INFO_H