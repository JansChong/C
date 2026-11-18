#include "main.h"
#include "flight_info.h"

int main(int argc, char const *argv[])
{

    // 初始化航班管理
    flight_info_type_p flight_info_manager = flight_init_list();

    // 测试插入航班信息
    flight_info_data_type flight_A = {
        .carrier_airline = "南方(CZ)", // 承载航司
        .flight_number = "CZ3037", // 航班号
        .is_joint_flights = false, // 是否为联合航班
        .seat_arr[3] = {
            {.type = 0, .count = 10, .price = 1480.00}, // 头等
            {.type = 1, .count = 30, .price = 1080.00}, // 公务
            {.type = 2, .count = 60, .price = 780.00},  // 经济
        },
        .infrastructure_fuel_price = 380, // 基建燃油
        .set_off = "广州"
        .arrive = "昆明"
        .departure_time = "2026-11-19 12:15:00"
        .arrival_time = "2026-11-19 15:00:00"
    };

    flight_info_data_type flight_B = {
        .carrier_airline = "国航(CA)", // 承载航司
        .flight_number = "CA5033", // 航班号
        .is_joint_flights = false, // 是否为联合航班
        .seat_arr[3] = {
            {.type = 0, .count = 10, .price = 1480.00}, // 头等
            {.type = 1, .count = 30, .price = 1080.00}, // 公务
            {.type = 2, .count = 60, .price = 780.00},  // 经济
        },
        .infrastructure_fuel_price = 380, // 基建燃油
        .set_off = "广州"
        .arrive = "重庆"
        .departure_time = "2026-11-19 14:15:00"
        .arrival_time = "2026-11-19 16:00:00"
    };

    flight_info_data_type flight_C = {
        .carrier_airline = "东航(MU)", // 承载航司
        .flight_number = "MU3037", // 航班号
        .is_joint_flights = false, // 是否为联合航班
        .seat_arr[3] = {
            {.type = 0, .count = 10, .price = 1480.00}, // 头等
            {.type = 1, .count = 30, .price = 1080.00}, // 公务
            {.type = 2, .count = 60, .price = 780.00},  // 经济
        },
        .infrastructure_fuel_price = 380, // 基建燃油
        .set_off = "北京"
        .arrive = "广州"
        .departure_time = "2026-11-19 11:15:00"
        .arrival_time = "2026-11-19 15:40:00"
    };


    
}