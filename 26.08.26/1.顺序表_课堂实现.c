#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 顺序表中存储的元素类型， 这里typedef起别名， 用于设置 顺序表管理结构体 的顺序表指针
typedef int elementType_t;

/* 顺序表管理结构体 */
struct manager_t
{
    int size;             // 顺序表总长度 -- 元素个数
    int end_idx;          // 顺序表最末尾元素下标
    elementType_t *list_p; // 顺序表指针(空间) -- 默认是顺序表的基地址   （顺序表中保存何种数据， 就定义何种数据类型的指针, 这里是表中存储int类型）
};

/**
 * @description: 创建顺序表
 * @param {int} size 顺序表的长度 -- 元素个数
 * @return  success return 管理结构体指针;  fail return NULL
 */
struct manager_t *Create_Sequential_List(int size)
{
    // 顺序表指针(空间)
    elementType_t *p = malloc(sizeof(elementType_t) * size); // 元素大小 * 元素个数 =  单位字节
    // fail
    if (p == NULL)
    {
        printf("fail: malloc error\n");
        return NULL;
    }

    // 定义管理结构体指针  （局部变量函数外无法访问，只能设置为指针）
    struct manager_t *manager = malloc(sizeof(struct manager_t));
    if (manager == NULL)
    {
        printf("fail: 创建顺序表管理结构体失败\n");
        return NULL;
    }

    manager->size = size;
    manager->end_idx = -1; // 这样第一个插入的元素就是 0
    manager->list_p = p;
    printf("顺序表初始化成功, 顺序表创建完成\n");
    return manager;
}

/**
 * @description: 在顺序表的末尾插入新的数据
 * @param: {} manager 管理结构体的指针
 * @param: {} data 要插入的数据
 * @return success: true；  fail: false
 */
bool Insert_Data_List_Tail(struct manager_t *manager, elementType_t data)
{
    // 如果最末尾元素下标 等于 元素个数-1
    if (manager->end_idx == manager->size - 1)
    {
        printf("顺序表已满\n");
        return false;
    }

    // 往list_p的[-1+1]位置 插入 data     如果是string要 strcpy
    (manager->list_p)[(manager->end_idx) + 1] = data;

    // 最末尾元素下标后移一位
    (manager->end_idx)++;

    printf("末尾插入新的数据成功\n");
    return true;
}

/**
 * @description: 依次显示顺序表中的数据
 * @param: {} manager 管理结构体指针
 * @return void
 */
void Display_Sequence_Table(struct manager_t *manager)
{
    // 判断顺序表中是否为空
    if (manager->end_idx == -1)
    {
        printf("顺序表为空\n");
        return;
    }

    printf("顺序表元素为：\n");
    // 循环遍历
    for (int i = 0; i <= manager->end_idx; i++)
    {
        printf("%d ", (manager->list_p)[i]);
    }

    printf("\n");
    return;
}

int main(int argc, char const *argv[])
{

    // 创建顺序表
    struct manager_t *manager = Create_Sequential_List(5);

    // 插入数据
    Insert_Data_List_Tail(manager, 1);
    Insert_Data_List_Tail(manager, 2);
    Insert_Data_List_Tail(manager, 3);
    Insert_Data_List_Tail(manager, 4);
    Insert_Data_List_Tail(manager, 5);
    Insert_Data_List_Tail(manager, 78);

    // 显示顺序表数据
    Display_Sequence_Table(manager);
}