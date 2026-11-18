#include "main.h"
#include "flight_info.h"
#include "all_airline_info.h"

// 添加测试航班数据 函数声明
void add_test_flight_data(flight_info_type_p flight_info_manager);

int main(int argc, char const *argv[])
{

    // 初始化航班管理 （航班可以有很多，用链表存储 注意时间复杂度）
    flight_info_type_p flight_info_manager = flight_init_list();
    add_test_flight_data(flight_info_manager);

    // // 初始化航空信息 (限制只有10个航司)
    airlines_seq_type_p airline_info_manager = airline_init_list(10);

    // 测试插入航司信息
    airline_info_type CZ = {
        .air_name = "南航",
        .abbreviation = "CZ"};

    airline_info_type CA = {
        .air_name = "国航",
        .abbreviation = "CA"};

    airline_info_type MU = {
        .air_name = "东航",
        .abbreviation = "MU"};

    // 插入航司数据
    airline_insert_tail(airline_info_manager, CZ);
    airline_insert_tail(airline_info_manager, CA);
    airline_insert_tail(airline_info_manager, MU);

    // 显示
    airline_show_list(airline_info_manager);

    // Airline_Administrator

    // 航司管理员功能 （管理员限制20位，用顺序表存储结构体）
    // 1.管理员注册登录
    // a. 注册： 名称、密码、工号(自分配，用数组最后一个元素)、所属航司、
    // b. 登录成功 可以管理 其航司名下航班 + 其航司参与的联合航班，包括：
    // 2.航班信息录入： 允许管理员输入新航班的详细信息，包括航班号、目的地、出发地、出发时间和可用座位数，并将该航班信息存储到系统中。
    // 3.航班行程取消
    // 4.航班信息更新
    // 5.航班信息显示
    // 6.允许管理用户信息，包括添加新用户、删除用户、更新用户信息和查看用户列表。
    // 这里只能管理当前航司的用户，
    // 存在航司信息中 -- 如果坐了本航司的航班，就将该用户加入 航司客户表中 （并给该用户设置：姓名、飞行次数、 用户状态：0拉黑、 1正常、 是否会员：0否、1是）
    // 航司信息中要存储： 航司名称，航司员工, 航司客户表中，旗下航班（遍历航班信息数据链表），合作航班（遍历合作航班数据链表），TODO..航班状态[可预定、可购买、可值机、候机、航班起飞、航班到达]，
    // 7.系统退出

    // 用户

    // 超级管理员
}

// 添加测试航班数据 函数定义
void add_test_flight_data(flight_info_type_p flight_info_manager)
{
    // 测试插入航班信息
    flight_info_data_type flight_A = {
        .carrier_airline = "南航(CZ)", // 承载航司
        .flight_number = "CZ3037",     // 航班号
        .is_joint_flights = false,     // 是否为联合航班
        .seat_arr = {
            {.type = 0, .count = 10, .price = 1480.00}, // 头等
            {.type = 1, .count = 30, .price = 1080.00}, // 公务
            {.type = 2, .count = 60, .price = 780.00},  // 经济
        },
        .infrastructure_fuel_price = 380, // 基建燃油
        .set_off = "广州",
        .arrive = "昆明",
        .departure_time = "2026-11-19 12:15:00",
        .arrival_time = "2026-11-19 15:00:00"};

    flight_info_data_type flight_B = {
        .carrier_airline = "国航(CA)", // 承载航司
        .flight_number = "CA5033",     // 航班号
        .is_joint_flights = false,     // 是否为联合航班
        .seat_arr = {
            {.type = 0, .count = 10, .price = 1480.00}, // 头等
            {.type = 1, .count = 30, .price = 1080.00}, // 公务
            {.type = 2, .count = 60, .price = 780.00},  // 经济
        },
        .infrastructure_fuel_price = 380, // 基建燃油
        .set_off = "广州",
        .arrive = "重庆",
        .departure_time = "2026-11-19 14:15:00",
        .arrival_time = "2026-11-19 16:00:00"};

    flight_info_data_type flight_C = {
        .carrier_airline = "东航(MU)", // 承载航司
        .flight_number = "MU3037",     // 航班号
        .is_joint_flights = false,     // 是否为联合航班
        .seat_arr = {
            {.type = 0, .count = 10, .price = 1480.00}, // 头等
            {.type = 1, .count = 30, .price = 1080.00}, // 公务
            {.type = 2, .count = 60, .price = 780.00},  // 经济
        },
        .infrastructure_fuel_price = 380, // 基建燃油
        .set_off = "北京",
        .arrive = "广州",
        .departure_time = "2026-11-19 11:15:00",
        .arrival_time = "2026-11-19 15:40:00"};

    // 插入测试数据
    flight_insert_head(flight_info_manager, flight_A);
    flight_insert_head(flight_info_manager, flight_B);
    flight_insert_head(flight_info_manager, flight_C);

    // 显示
    flight_show_list(flight_info_manager);
}