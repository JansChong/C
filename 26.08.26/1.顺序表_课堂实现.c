#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 顺序表中存储的元素类型， 这里typedef起别名， 用于设置 顺序表管理结构体 的顺序表指针
typedef int elementType_t;

/* 顺序表管理结构体 */
struct manager_t
{
    int size;              // 顺序表总长度 -- 元素个数
    int end_idx;           // 顺序表最末尾元素下标
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
 * @return Boolean
 */
bool Insert_Data_List_Tail(struct manager_t *manager, elementType_t data)
{
    // 判断顺序表是否存在
    if (manager == NULL)
    {
        printf("顺序表未创建\n");
        return false;
    }
    
    
    // 判断顺序表是否已满
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
 * @description: 删除元素
 * @param: {} manager 管理结构体指针， 插入哪个管理结构体
 * @param: {} data 需要删除的元素
 * @return boolean
 */
bool Delete_one_data(struct manager_t *manager, elementType_t data)
{
    // 判断顺序表是否存在
    if (manager == NULL)
    {
        printf("顺序表未创建\n");
        return false;
    }

    // 判断顺序表是否为空
    if (manager->end_idx == -1)
    {
        printf("isEmpty, delete fail\n");
        return false;
    }

    // 遍历顺序表 查找要删除的元素
    for (int i = 0; i <= manager->end_idx; i++)
    {
        // 如果要删除的元素 等于 当前的元素
        if (data == manager->list_p[i])
        {
            // 要删除元素 之后的数据往前挪动

            // 数据拷贝：
            // 头文件 #include <string.h>
            // 函数原型 void *memcpy(void *dest, const void *src, size_t n);
            // 说明：memcpy() 用来拷贝 src 所指的内存内容前 n 个字节到 dest 所指的内存地址上。与 strcpy() 不同的是，memcpy() 会完整地复制 n 个字节，不会因为遇到字符串结束 ‘\0’ 而结束。
            // 返回值：返回指向 dest 的指针。
            // 附加说明：指针 src 和 dest 所指的内存区域不可重叠。
            memcpy(
                &manager->list_p[i],                           // 目标地址
                &manager->list_p[i + 1],                       // 要拷贝的数据的起始地址
                sizeof(elementType_t) * (manager->end_idx - i) // 拷贝多少个字节数
            );

            // 删除元素， 最末尾元素下标前移一位
            manager->end_idx--;

            printf("顺序表结构删除元素成功！\n");
            return true;
        }
    }

    printf("要删除的元素不存在\n");
    return false;
}

/**
 * @description: 依次显示顺序表中的数据
 * @param: {} manager 管理结构体指针
 * @return void
 */
void Display_Sequence_List(struct manager_t *manager)
{

    // 判断顺序表是否存在
    if (manager == NULL)
    {
        printf("顺序表未创建\n");
        return;
    }

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

/**
 * @description: 销毁顺序表
 * @param: manager 管理结构体指针
 * @return void
 */
void destory_list(struct manager_t * manager)
{
    // 顺序表没有创建
    if (manager == NULL)
    {
        return;
    }

    free(manager->list_p); // 释放掉 所管理的顺序表空间
    free(manager);         // 释放掉 管理结构体空间

    // manager = NULL; // 这里设置为null 只是操作局部变量, 不会影响外面的manager

    printf("销毁成功!\n");
}

int main(int argc, char const *argv[])
{

    // 创建顺序表
    struct manager_t * manager = Create_Sequential_List(5);

#if 0
    // 插入数据
    Insert_Data_List_Tail(manager, 1);
    Insert_Data_List_Tail(manager, 2);
    Insert_Data_List_Tail(manager, 3);
    Insert_Data_List_Tail(manager, 4);
    Insert_Data_List_Tail(manager, 5);
    Insert_Data_List_Tail(manager, 78);
#endif

    // 操作顺序表
    char md = 0;  // 指令： i插入 d删除
    int data = 0; // 数据

    while (1)
    {
        scanf("%c %d", &md, &data);
        if (md == 'i')
        { // 插入数据
            Insert_Data_List_Tail(manager, data);
            // 显示顺序表数据
            Display_Sequence_List(manager);
        }
        else if (md == 'd') // 删除数据
        {
            // 删除数据
            Delete_one_data(manager, data);
            // 显示顺序表数据
            Display_Sequence_List(manager);
        }
        else if (md == 'e')
        {
            // 销毁顺序表
            destory_list(manager);
            // printf("%p\n", manager); 
            manager = NULL;
            // printf("%p\n", manager);
        }
    }

    
}