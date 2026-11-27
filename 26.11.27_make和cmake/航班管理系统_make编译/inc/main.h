// main.h 头文件
#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// #include "airline_administrator.h"
// #include "user_link.h"
// #include "all_airline_info.h"

// 仓位席别+数量+价格 （航班信息、联合航班信息）
struct seat_details
{
    short type;  // 0 头等舱    1 公务舱    2 经济舱
    int count;   // 座位数量
    float price; // 价格
};

// 行程记录
typedef struct
{
    // 航班号 CZ9901
    char flight_number[16];
    // 席位
    short type; // 0 头等舱    1 公务舱    2 经济舱

} ride_info_type; // // 乘坐信息

// 航司 国航(CA)、东航(MU)、南方(CZ)、海航(HU)、九元(NA)
// 航班号： 航司 + 编码

#endif // !_MAIN_H