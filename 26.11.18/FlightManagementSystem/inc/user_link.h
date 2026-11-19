// 用户数据
#ifndef _USER_LINK_H
#define _USER_LINK_H

#include "main.h"

// 用户信息
typedef struct
{
      char u_name[15];           // 用户名
      char u_pass[15];           // 密码
      ride_info_type *itinerary; // 行程记录: [ {航班号, 1}, {航班号, 2}, {航班号, 0} ]
      int itinerary_count;       // 记录当前的行程数量
      // 如果坐了某航司的航班，就将该用户加入 该航司客户表中 （并给该用户设置：姓名、飞行次数、 用户状态：0拉黑、 1正常、 是否会员：0否、1是）
} userinfo;

// 用户管理 (用户不确定数量, 用单链表)
typedef struct _userinfo
{
      userinfo data;          // 数据域
      struct _userinfo *next; // 后驱指针

} userinfo_type, *userinfo_type_p;

// 用户管理链表 全局变量 (给super_manager_sys.c用)
extern userinfo_type_p user_info_manager;

// 初始化
userinfo_type_p user_init_list(void);

// 插入数据到链表
bool user_insert_head(userinfo_type_p head, userinfo value);
// 按名字 查找 用户数据
userinfo_type_p find_user_by_name(userinfo_type_p head, char *u_name);
// 用名字 删除用户
bool remove_user_data(userinfo_type_p head, char *u_name);
// 显示所有数据
void user_show_list(userinfo_type_p head);
// 退出系统，释放所有用户
bool user_destroy(userinfo_type_p head);

// 用户购买行程 =>
// 给某个用户添加行程信息  (用户表, 用户名, 航班信息, 席位);
bool add_itinerary(userinfo_type_p head, char *u_name, ride_info_type value);


#endif // !_USER_LINK_H