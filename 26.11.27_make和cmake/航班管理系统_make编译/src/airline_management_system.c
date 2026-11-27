#include "main.h"
#include "all_airline_info.h"

// 注册函数
void airline_admin_register();
// 登陆函数
void airline_admin_login();

// 登陆后员工进入航司系统
void airline_admin_system(char *abbreviation);

// 航司系统显示 所属航司 函数
void show_employee_login_airline(airlines_seq_type_p list, char *abbreviation);

// 进入航司管理员系统
void airline_management_system()
{
      while (1)
      {
            printf("欢迎进入航司管理员系统\n1.注册\n2.登陆\n3.返回上级目录\n请选择:");

            int keycode;
            scanf("%d", &keycode);

            switch (keycode)
            {
            case 1:
                  // 注册
                  airline_admin_register();
                  break;

            case 2:
                  // 登陆
                  airline_admin_login();
                  // break;
                  return; // 这里return会回到主系统, break则还是航司管理员系统

            default:
                  return;
            }
      }
}

// 航司管理员 注册
void airline_admin_register()
{
      printf("\n请选择你的航空公司:\n");
      // 在航司表中显示所有航司信息
      airline_show_simple_list(airline_info_manager);

      printf("请输入你要注册的航司编号:");
      int keycode;
      scanf("%d", &keycode);

      // 用输入的编号查找航司缩写
      char belonging_airline[3] = {0};
      if (keycode >= 1 && keycode <= airline_info_manager->last + 1)
      {
            strcpy(belonging_airline, airline_info_manager->data[keycode - 1].abbreviation);
            printf("你选择的航司缩写为: %s\n", belonging_airline);
      }

      printf("请输入你的用户名:");
      char u_name[15];
      scanf("%s", u_name);

      printf("请输入你的密码:");
      char u_pass[15];
      scanf("%s", u_pass);

      // 创建一个航司管理员结构体
      air_admin_type air_admin = {0}; // 整体清零（含 u_number）
      strcpy(air_admin.u_name, u_name);
      strcpy(air_admin.u_pass, u_pass);
      strcpy(air_admin.Belonging_airline, belonging_airline);

      // 插入员工数据
      airline_administrator_seq_insert_tail(airline_admin_manager, air_admin);

      // 显示所有员工数据
      airline_administrator_seq_show_list(airline_admin_manager);
      // 显示航司员工表中 是否有 员工
      // airline_show_list(airline_info_manager);
}

// 登陆
void airline_admin_login()
{

      // TODO.. 显示所有员工
      airline_administrator_seq_show_list(airline_admin_manager);
      // 显示所有航司
      // airline_show_list(airline_info_manager);

      printf("请输入你的用户名:");
      char u_name[15];
      scanf("%s", u_name);

      printf("请输入你的密码:");
      char u_pass[15];
      scanf("%s", u_pass);

      // 用u_name 查找 航司员工
      int pos = airline_administrator_seq_find_value(airline_admin_manager, u_name);

      if (pos != -1)
      {

            // 用下标找到这个员工的密码, 然后比较密码
            if (strcmp(airline_admin_manager->data[pos].u_pass, u_pass) == 0)
            {
                  printf("登陆成功\n");

                  // 拿到该员工的航司缩写
                  char abbreviation[8];
                  strcpy(abbreviation, airline_admin_manager->data[pos].Belonging_airline);

                  // 用该员工的航司缩写 进入 航司管理系统:
                  airline_admin_system(abbreviation);
                  return;
            }
            else
            {
                  printf("密码错误, 登陆失败\n\n");
                  return;
            }
      }
      else
      {
            printf("《用户名不存在》\n\n");
      }
}

/**
 * 员工登录进入的航司管理系统
 * abbreviation 员工所属的航司缩写
 */
void airline_admin_system(char *abbreviation)
{
      while (1)
      {

            // 用这条航司缩写 输出 当前航司的详情
            show_employee_login_airline(airline_info_manager, abbreviation);

            // 其他指令: 1.发布一条新航班  2.取消一条航班 3.客户升级为会员 4.拉黑客户
            printf("请输入指令:\n1.发布一条新航班\n2.取消一条航班\n3.客户升级为会员\n4.拉黑客户\n5.退出系统\n请输入:");

            int keycode;
            scanf("%d", &keycode);

            switch (keycode)
            {
            // 1.发布一条新航班
            case 1:
                  break;
            // 2.取消一条航班
            case 2:
                  break;
            // 3.客户升级为会员
            case 3:
                  break;
            // 4.拉黑客户
            case 4:
                  break;
            default:
                  return;
            }
            /* code */
      }
}

/**
 * 用这条航司缩写 输出 当前航司的详情
 * airline_info_manager 航司管理管理链表
 * abbreviation[8] 缩写
 */
void show_employee_login_airline(airlines_seq_type_p list, char *abbreviation)
{
      // 用缩写 查找当前航司的信息, 返回下标 (逻辑上一定能找到,因为注册时"缩写"是选择的不是输入的)
      int find_idx = airline_find_value(list, abbreviation);

      // 拿到这条航司的信息 list->data[find_idx];
      printf("---------------------------\n%s\t%s\t\t%s\t\n", "航司名称", "缩写", "员工");
      // 输出
      printf("%s\t\t%s\t\t", list->data[find_idx].air_name, list->data[find_idx].abbreviation);

      // 遍历员工信息
      for (int j = 0; j < list->data[find_idx].employee_list_length; j++)
      {
            printf("%s\t", list->data[find_idx].employee_list[j].u_name);
      }

      printf("\n----------\n本航司名下客户:\n");
      printf("%s\t%s\t%s\t%s\n", "客户", "乘坐本司航班次数", "客户状态", "会员");
      // 遍历客户信息
      for (int j = 0; j < list->data[find_idx].customer_list_length; j++)
      {
            // printf("%s%d%s%s\n",  "客户", "乘坐本司航班次数", "客户状态", "会员");

            printf("%s\t%d\t\t\t%s\t\t%s\n",
                   list->data[find_idx].customer_list[j].u_name,
                   list->data[find_idx].customer_list[j].number_of_flights,
                   list->data[find_idx].customer_list[j].user_status == 0 ? "拉黑" : "正常",
                   list->data[find_idx].customer_list[j].ismember == 0 ? "否" : "是");
      }
      printf("\n");
}
