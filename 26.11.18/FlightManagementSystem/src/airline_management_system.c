#include "main.h"
#include "all_airline_info.h"

// 注册函数
void airline_admin_register();
// 登陆函数
void airline_admin_login();

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
                  break;

            default:
                  return;
            }
      }
};

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
      strcpy (air_admin.u_name, u_name); 
      strcpy (air_admin.u_pass, u_pass); 
      strcpy (air_admin.Belonging_airline, belonging_airline);

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
            airline_administrator_seq_show_list(airline_admin_manager);
            // airline_show_list(airline_info_manager);

            // 用下标找到这个员工的密码, 然后比较密码
            if (strcmp(airline_admin_manager->data[pos].u_pass, u_pass) == 0)
            {
                  printf("登陆成功\n\n");
                  // TODO: 进入航司管理员系统
                  // 进入航司管理员系统
                  // airline_admin_system(airline_admin_manager->data[pos]);
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