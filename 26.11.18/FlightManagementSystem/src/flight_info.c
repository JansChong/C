// 航班信息链表 管理函数

// 导入main.h头文件
#include "main.h"

// 航班信息头文件 （这里担心如果在 main.h 导入各个头文件，会在编译时导入定义的其他模块的头文件， 所以分开导入）
#include "flight_info.h"

// 初始化
// 带头结点 -> 先初始化
// 不带头结点 -> 存入数据时初始化
flight_info_type_p flight_init_list(void)
{
    // 为头结点申请空间 (堆内存)
    flight_info_type_p head = (flight_info_type_p)malloc(sizeof(flight_info_type));

    // 如果申请成功
    if (head != NULL)
    {
        // 将头结点的next指针指向null
        head->next = NULL;
    }

    // 返回头结点 (失败返回null, 成功返回结构体指针head)
    return head;
}

/**
 * @description: 用航班信息结构体 创建 管理结构体 -- 然后把管理结构体插入链表
 * @param: {} value 航班信息数据 结构体
 * @return
 */
flight_info_type_p flight_create_node(flight_info_data_type value)
{
    // 航班信息 管理结构体 （单链表）
    flight_info_type_p node = (flight_info_type_p)malloc(sizeof(flight_info_type));

    // 如果申请成功
    if (node != NULL)
    {
        // node->data.name = value.name;   字符串不可以直接赋值

        // 航班号： 航司 + 编码
        strcpy(node->data.flight_number, value.flight_number);
        // 承载航司
        strcpy(node->data.carrier_airline, value.carrier_airline);
        // 是否为联合航班
        node->data.is_joint_flights = value.is_joint_flights;

        // TODO.. 如果是联合航班
        // if (0)数据要添加到联合航班链表
        // TODO.. 如果不是联合航班
        // else{
        // 把席位信息加入到结构体数组
        memcpy(node->data.seat_arr, value.seat_arr, sizeof(value.seat_arr));
        // 基建燃油
        node->data.infrastructure_fuel_price = value.infrastructure_fuel_price;
        // }

        // 出发地
        strcpy(node->data.set_off, value.set_off);
        // 目的地
        strcpy(node->data.arrive, value.arrive);
        // 出发时间 "yyyy-MM-dd hh:mm:ss"
        strcpy(node->data.departure_time, value.departure_time);
        // 到达时间 "yyyy-MM-dd hh:mm:ss"
        strcpy(node->data.arrival_time, value.arrival_time);

        // 将新结点的next指针指向null (后续用)
        node->next = NULL;
    }

    return node;
}

// 判断链表节点head是否正常初始化 (true表示错误, false相反)
static bool iswrong(flight_info_type_p head)
{
    return !head;
}

// 判断链表是否为空链表
static bool isEmpty(flight_info_type_p head)
{
    return !(head->next);
}

// 头插
bool flight_insert_head(flight_info_type_p head, flight_info_data_type value)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return false;
    }

    // 创建节点()
    flight_info_type_p node = flight_create_node(value);
    if (node != NULL)
    {
        // node 先存好 原本head指向的下一个节点
        node->next = head->next;
        // head的next 指向新创建的 node
        head->next = node;
        return true;
    }
    return false;
}

// 头删 设计成 把删除的节点地址返回 而不是 free
flight_info_type_p flight_remove_head(flight_info_type_p head)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化, 头删失败\n");
        return NULL;
    }

    // 如果链表为空
    if (isEmpty(head))
    {
        printf("链表中没有元素, 头删失败\n");
        return NULL;
    }

    // 需要存储要删除的节点 （因为要释放内存）
    flight_info_type_p temp = head->next;
    // 把head的next指向要删除的元素的next
    head->next = temp->next;

    // 释放
    // free(temp);
    // return true;

    // 建议设计成 把删除的节点地址返回 而不是释放
    temp->next = NULL;
    return temp;
}

// 按航班号 查找数据
// (为了适配"航班号删除信息功能",
// 本查找函数返回查找到的元素的上一个元素,
// 输出时记得next
// 删除时通过id调用本函数,
// 拿到返回值直接处理next指针并删除下一元素即可)
flight_info_type_p flight_search_by_flightnumber(flight_info_type_p head, char *flight_number)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return NULL;
    }

    // 如果链表为空
    if (isEmpty(head))
    {
        printf("链表中没有元素，查找失败\n");
        return NULL;
    }

    // 有可能找到第一个节点, 需要返回head
    flight_info_type_p temp = head;

    // 0  1  2  NULL
    while (temp->next != NULL)
    {
        // 如果找得到数据
        if (temp->next->data.flight_number == flight_number)
        {
            // printf("查找到数据 %d\n", temp->data.id);

            // TODO.. 找到节点以后需要判断当前航班是否有空座
            // 返回这个节点
            return temp;
        }
        // 否则指针后移
        temp = temp->next;
    }

    printf("******该航班没有数据\n\n");
    return NULL;
}

// 航班号移除数据
flight_info_type_p flight_remove_data(flight_info_type_p head, char *flight_number)
{
    // 调用查找函数, 会返回查找到的元素的上一个元素
    flight_info_type_p prev = flight_search_by_flightnumber(head, id);

    // 如果返回null说明要删除的数据不存在
    // 如果要删除的数据不存在
    if (!prev)
    {
        printf("******删除失败\n");
    }

    // 存储要删除的元素
    flight_info_type_p delnode = prev->next;

    // 0 1 2 3
    // 改变上一个元素的指向
    prev->next = delnode->next;

    // 避免用这个元素访问到后续节点，因为要返回
    delnode->next = NULL;
    return delnode;
}

// 显示所有航班
void flight_show_list(flight_info_type_p head)
{
    // 判断head参数是否合法
    if (iswrong(head))
    {
        printf("head结点没有成功初始化\n");
        return;
    }

    // 如果链表为空
    if (isEmpty(head))
    {
        printf("链表中没有元素，显示为空\n");
        return;
    }

    printf("############## 所有学生数据如下 ################\n");
    // 首节点无数据， 不输出
    flight_info_type_p temp = head->next;

    // 航班号     承载航司     出发地      目的地      出发时间        到达时间
    printf("%s\t%s\t%s\t%s\t%s\t%s\n", "航班号", "承载航司", "出发地", "目的地", "出发时间", "到达时间");

    // 只要下一个节点不为空
    while (temp != NULL)
    {
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", temp->data.flight_number, temp->data.carrier_airline, temp->data.set_off, temp->data.arrive, temp->data.departure_time, temp->data.arrival_time);

        // 就让下一个节点赋值并输出
        temp = temp->next;
    }

    printf("############## 学生信息输出结束 ################\n\n");
}

// 退出系统， 是否所有航班信息
bool flight_destroy(flight_info_type_p head)
{
    if (iswrong(head))
    {
        printf("head结点没有成功初始化, 无需销毁\n");
        return false;
    }

    // 临时存储
    flight_info_type_p p = head->next;

    // 从head开始，只要head->next不为空，都要删除，直到head->next为空
    // head   1    2    3    NULL
    while (p != NULL)
    {
        // 记录要删除的节点
        flight_info_type_p temp = p;
        // 头节点的next指向删除节点后一位
        p = p->next;
        // 销毁要删除的节点
        free(temp);
    }

    // 销毁head
    free(head);
    return true;
}
