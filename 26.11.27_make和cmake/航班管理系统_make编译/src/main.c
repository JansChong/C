#include "main.h"
#include "flight_info.h"
#include "all_airline_info.h"
#include "user_link.h"

// 管理系统 全局变量, 跨文件使用 extern 使用
flight_info_type_p flight_info_manager;         // 航班管理
airlines_seq_type_p airline_info_manager;       // 航司管理
airline_admin_seq_type_p airline_admin_manager; // 航司管理员管理
userinfo_type_p user_info_manager;              // 初始化用户表

// 初始化一些测试数据
void init();
// 测试 添加航班数据 函数声明
void add_test_flight_data(flight_info_type_p flight_info_manager);
// 测试 添加航司信息 函数声明
void add_test_airline_info(airlines_seq_type_p airline_info_manager);
// 测试 添加航司员工信息 函数定义 (航司员工管理, 航司信息管理)
void add_test_airline_admin(airline_admin_seq_type_p airline_admin_manager, airlines_seq_type_p airline_info_manager);
// 测试 添加用户 以及 为用户添加 行程
void add_test_user_and_itinerary(userinfo_type_p user_info_manager);

// 进入系统管理员系统
void super_manager_sys();
// 进入航司管理员系统
void airline_management_system();
// 进入用户系统
void user_system();

int main(int argc, char const *argv[])
{
    // 初始化的变量作为全局变量， 在main.h中 `extern` 声明跨文件使用

    /**
     * 初始化一些测试数据, 如果没有测试数据, 需要:
     * 1. 由超级管理员添加航空公司 (先有航司), 超级管理员可以看到各个航司的信息(含员工)
     * 2. 选择存在的航司 注册为该航司的员工
     * 3. 该航司的员工可以发布、查看、修改、删除 属于该航司旗下的行程 (含联合航班)
     * 4. 用户注册登陆、登陆后可查看所有行程, 选择或输入航班号 查看席位, 选择席位购买行程
     * 5. 用户可以 查看、退票 自己的当前行程
     */
    init();

    while (1)
    {
        printf("请选择身份进入系统: \n1. 系统管理员\n2. 航司管理员\n3. 用户或乘客\n4. 退出系统\n请输入:");
        int keycode;
        scanf("%d", &keycode);
        printf("\n\n");

        switch (keycode)
        {
        case 1:
            // 进入系统管理员系统
            super_manager_sys();
            break;
        case 2:
            // 进入航司管理员系统
            airline_management_system();
            break;
        case 3:
            // 进入用户系统
            user_system();
            break;
        default:
            return 0;
        }
    }
}

// 初始化一些测试数据
void init()
{
    // 初始化航班管理 （航班可以有很多，用链表存储 注意时间复杂度）
    flight_info_manager = flight_init_list();
    // 初始化航空信息 (限制只有10个航司)
    airline_info_manager = airline_init_list(10);
    // 初始化航司管理员顺序表 (限制20个员工)
    airline_admin_manager = airline_administrator_init_list(20);
    // 初始化用户表
    user_info_manager = user_init_list();

    // 测试 添加 航班 数据
    add_test_flight_data(flight_info_manager);
    // 测试 添加 航司 信息
    add_test_airline_info(airline_info_manager);
    // 测试 添加 航司员工 信息  (航司员工管理, 航司信息管理)
    add_test_airline_admin(airline_admin_manager, airline_info_manager);
    // 测试 添加用户 以及 为用户添加 行程
    add_test_user_and_itinerary(user_info_manager);
}

// 测试 添加航班数据 函数定义
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
    // flight_show_list(flight_info_manager);
}

// 测试 添加航司信息 函数定义
void add_test_airline_info(airlines_seq_type_p airline_info_manager)
{
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

    // 测试查找航班
    // int test = airline_find_value(airline_info_manager, "CA");
    // printf("%d\n", test);

    // 显示航司数据
    // airline_show_list(airline_info_manager);
}

// 测试 添加航司员工信息 函数定义  参数:(航司员工管理, 航司信息管理)
void add_test_airline_admin(airline_admin_seq_type_p airline_admin_manager, airlines_seq_type_p airline_info_manager)
{

    // 要先存在航司, 才可以给航司注册员工
    // air_admin_type 类型的员工参数
    air_admin_type air_admin_a = {
        .u_name = "jc",           // 名字
        .u_pass = "000001",       // 密码
        .Belonging_airline = "CZ" // 航司缩写
        // 工号由系统自动分配
    };
    air_admin_type air_admin_b = {
        .u_name = "wwwwwr",       // 名字
        .u_pass = "000002",       // 密码
        .Belonging_airline = "CA" // 航司缩写
        // 工号由系统自动分配
    };
    air_admin_type air_admin_c = {
        .u_name = "waga",         // 名字
        .u_pass = "000003",       // 密码
        .Belonging_airline = "MU" // 航司缩写
        // 工号由系统自动分配
    };
    air_admin_type air_admin_d = {
        .u_name = "董泪",         // 名字
        .u_pass = "000004",       // 密码
        .Belonging_airline = "CZ" // 航司缩写
        // 工号由系统自动分配
    };
    air_admin_type air_admin_e = {
        .u_name = "崔雅馨",       // 名字
        .u_pass = "000004",       // 密码
        .Belonging_airline = "CZ" // 航司缩写
        // 工号由系统自动分配
    };

    // 插入员工数据
    airline_administrator_seq_insert_tail(airline_admin_manager, air_admin_a);
    airline_administrator_seq_insert_tail(airline_admin_manager, air_admin_b);
    airline_administrator_seq_insert_tail(airline_admin_manager, air_admin_c);
    airline_administrator_seq_insert_tail(airline_admin_manager, air_admin_d);
    airline_administrator_seq_insert_tail(airline_admin_manager, air_admin_e);

    // 显示所有员工数据
    // airline_administrator_seq_show_list(airline_admin_manager);

    // 显示航司员工表中 是否有 员工
    // airline_show_list(airline_info_manager);
}

// 测试 添加用户 以及 为用户添加 行程
void add_test_user_and_itinerary(userinfo_type_p user_info_manager)
{
    // 测试添加用户: 只需要 用户名 密码
    userinfo user_a = {
        .u_name = "张三",
        .u_pass = "001"};
    userinfo user_b = {
        .u_name = "李四",
        .u_pass = "001"};
    userinfo user_c = {
        .u_name = "王五",
        .u_pass = "001"};

    // 用户插入到用户表
    user_insert_head(user_info_manager, user_a);
    user_insert_head(user_info_manager, user_b);
    user_insert_head(user_info_manager, user_c);
    // 输出所有用户
    // user_show_list(user_info_manager);

    // 创建一个测试行程
    ride_info_type temp_ride_a = {
        .flight_number = "CA5033", // 航班号
        .type = 0                  // 席位
    };
    // 给这个用户添加行程 (这里写死用户名, 后面登陆以后会获取到登陆的用户名)
    add_itinerary(user_info_manager, "李四", temp_ride_a);
    // 输出所有用户
    // user_show_list(user_info_manager);

    // 再添加三个测试行程
    ride_info_type temp_ride_b = {
        .flight_number = "MU3037", // 航班号
        .type = 2                  // 席位
    };
    ride_info_type temp_ride_c = {
        .flight_number = "CZ3037", // 航班号
        .type = 1                  // 席位
    };
    ride_info_type temp_ride_d = {
        .flight_number = "CZ3037", // 航班号
        .type = 1                  // 席位
    };
    // 给这个用户添加行程 (这里写死用户名, 后面登陆以后会获取到登陆的用户名)
    add_itinerary(user_info_manager, "李四", temp_ride_b);
    add_itinerary(user_info_manager, "李四", temp_ride_c);
    add_itinerary(user_info_manager, "王五", temp_ride_d);

    // 输出所有用户
    // user_show_list(user_info_manager);
    // 输出航司数据 (此时应该包含用户)
    // airline_show_list(airline_info_manager);
}
