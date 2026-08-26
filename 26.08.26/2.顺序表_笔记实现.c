#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 数据类型 起别名
typedef int elementType_t;

// 顺序表 管理结构体
// struct SequeueList_t {};

// 更正： 结构体类型 起别名
typedef struct
{
    int size;            // 可存储的元素个数
    int last_idx;        // 最末尾元素下标
    elementType_t *head; // 顺序表内存空间的起始地址 -- 相当于数组名称
} SequeueList_t;         // 类似于 js构造器

/**
 * @description: 初始化/创建 结构体
 * @param: { } size 可存储的元素个数
 * @return 顺序表内存空间的起始地址 -- 管理结构体（实例化对象manager）的地址
 */
SequeueList_t *create_list(int size)
{
    // 申请一个存储结构体的堆空间， 赋值给指针 manager
    // 类似于 通过构造器SequeueList_t 实例化 对象manager
    SequeueList_t *manager = malloc(sizeof(SequeueList_t)); // 刚好放得下结构体的空间

    if (manager == NULL)
    {
        printf("malloc manager error\n");
        return NULL;
    }

    // 初始化   类似于给实例化对象赋值
    manager->size = size;   // 可存储的元素个数
    manager->last_idx = -1; // 最末尾元素下标为-1, 后续存值时递增， 下标即为从0开始
    // 申请一片连续空间用于 结构体内的 head 存储数据
    // 类似于实例对象manager内有个数组head需要初始化
    manager->head = malloc(sizeof(elementType_t) * size);

    if (manager->head == NULL)
    {
        printf("malloc  manager -> head  error\n"); // 实例化对象manager的数组head 初始化失败
        free(manager);                              // 释放空间
        return NULL;
    }

    // 返回初始化完成的 管理结构体（实例化对象manager） 的地址
    return manager;
}

/**
 * @description 判断顺序表是否已满
 * @param: {} manager 要查询的结构体
 * @return boolean
 */
bool isFull(SequeueList_t *manager)
{

#if 0
    
    // 如果初始化完成后，插入元素时， 最末尾元素下标+1 等于 可存储的元素个数
    if(manager->last_idx+1 == manager->size){
        printf("isFull insert error\n"); // 结构体已满，插入失败
        return false;
    }
#endif

    // 简化
    // 如果初始化完成后，插入元素时， 最末尾元素下标+1 等于 可存储的元素个数, 即元素已满
    return (manager->last_idx + 1 == manager->size);
}

/**
 * @description: 尾插数据
 * @params: {} manager 管理结构体指针， 插入哪个管理结构体
 * @params: {} data 插入什么元素
 * @return  success return true;  fail return false;
 */
bool insert_data_to_tail(SequeueList_t *manager, elementType_t data)
{

    // 如果已存满
    if (isFull(manager))
    {
        printf("isFull insert error\n"); // 结构体已满，插入失败
        return false;
    }

    
#if 0
    // 把元素插入 管理结构体 末尾
    manager->head[manager->last_idx + 1] = data;
    // 最末尾元素下标递增
    manager->last_idx++
#endif

    // 简化：把元素插入 管理结构体 末尾, 最末尾元素下标递增
    manager->head[++manager->last_idx] = data;

    return true;
}

/**
 * @description: 遍历显示顺序表中的所有元素
 * @return {} manager
 * @return void
 */
void show_sequeue_list(SequeueList_t *manager)
{
    for (int i = 0; i <= manager->last_idx; i++)
    {
        printf("%d \n", manager->head[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
}