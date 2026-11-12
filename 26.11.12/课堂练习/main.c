#include "demo.h"

int main(int argc, char const *argv[])
{

    // 要执行的指令
    int keycode;

    // 初始化
    node_type_p head = init_list();

    struct student_info a = {100001, "张三", 90};
    struct student_info b = {.id = 100002, .name = "李四", .score = 92};

    // 头插
    insert_head(head, b);
    insert_head(head, a);

    // 显示所有节点
    // show_list(head);

    struct student_info c = {100003, "王五", 97};
    struct student_info d = {.id = 100004, .name = "六儿", .score = 99};

    // 尾插
    insert_tail(head, c);
    insert_tail(head, d);

    // 显示所有节点
    // show_list(head);

    while (1)
    {
        printf("功能菜单:\n1.录入学生信息\n2.按学号删除学生信息\n3.按学号查询学生信息\n4.打印所有学生信息\n5.退出\n");
        printf("请输入操作数:");
        scanf("%d", &keycode);
        printf("\n\n");

        switch (keycode)
        {
        case 1: // 录入学生信息
            struct student_info student;
            printf("输入学号:");
            scanf("%d", &student.id);
            printf("输入姓名:");
            scanf("%s", student.name); // char *name 或者 char name[] 类型本身就是基地址, 不需要取址符
            printf("输入分数:");
            scanf("%lf", &student.score);

            // 尾插
            if (insert_tail(head, student))
            {
                printf("添加成功\n\n");
            }
            break;

        case 2: // （按学号）删除学生信息
            int id1;
            printf("输入要删除的学生号:\n");
            scanf("%d", &id1);
            node_type_p delnode = remove_data(head, id1);
            // 如果返回了要删除的元素
            if(delnode){
                free(delnode); // 删除
                printf("!!!!!! 删除成功\n\n");
            }
            // 如果返回NULL, 则已经在移除函数中做了输出

            break;

        case 3: // （按学号）查询学生信息
            int id2;
            printf("输入要查询的学生号:\n");
            scanf("%d", &id2);
            // (为了适配"按学号删除信息功能",
            // 本查找函数返回查找到的元素的上一个元素,
            // 输出时记得next
            // 删除时通过id调用本函数,
            // 拿到返回值直接处理next指针并删除下一元素即可)
            node_type_p prev = search_data(head, id2);
            // 如果找得到
            if (prev)
            {
                printf("******查找到以下结果:\n\t学号:%d\n\t姓名:%s\n\t分数:%.2lf\n\n", prev->next->data.id, prev->next->data.name, prev->next->data.score);
            }
            break;

        case 4: // 打印所有学生信息
            show_list(head);
            break;

        case 5: // 退出
            // 释放内存
            bool res = destroy(head);
            if(res){
                printf("内存已释放，退出成功\n\n");
            }
            break;
        }

        // 退出循环
        if (keycode == 5)
        {
            break;
        }
    }
}