#include "main.h"
#include "all_airline_info.h"
#include "airline_administrator.h"
#include "flight_info.h"
#include "user_link.h"

// 进入系统管理员系统
void super_manager_sys()
{
      while (1)
      {
            // 没有做超级管理员链表
            printf("欢迎进入航司管理员系统,请输入\n1.查看所有航司\n2.查看所有航司管理员\n3.查看所有航班\n4.查看所有用户信息\n5.退出\n请输入:");
            int keycode;
            scanf("%d", &keycode);
            printf("\n\n");

            switch (keycode)
            {
            case 1:
                  // 查看所有航司
                  airline_show_list(airline_info_manager);
                  break;
            case 2:
                  // 查看所有航司管理员
                  airline_administrator_seq_show_list(airline_admin_manager);
                  break;
            case 3:
                  // 查看所有航班
                  flight_show_list(flight_info_manager);
                  break;
            case 4:
                  // 查看所有用户信息
                  user_show_list(user_info_manager);
                  break;
            default:
                  return;
            }
      }
};