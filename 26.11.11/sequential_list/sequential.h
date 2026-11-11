#ifndef _SEQUENTIAL_H
#define _SEQUENTIAL_H

typedef struct Seq
{
    int length;
    int last;
    int * data;
} Seq_type, *Seq_type_p;


// 函数声明

// 初始化
Seq_type_p init_list(int length); 

// 头插
bool insert_head(Seq_type_p list, int value);
// 尾插
bool insert_tail(Seq_type_p list, int value);
// 删除头部
bool delete_head(Seq_type_p list);

// 显示
void show_list(Seq_type_p list);



#endif // !_SEQUENTIAL_H