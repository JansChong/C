#include <stdio.h>



// 比如学生中的成绩, 包含语文 数学 英语成绩

// 比如 我的个人信息中, 亲戚这一栏可以是结构体, 说明每一个亲戚的名字甚至再嵌套一个结构体说明每一个亲戚的个人信息


// 亲戚的简介
struct introduction{
    char *rel_name;  // 亲戚名称
    int rel_age; // 亲戚年龄
    int rel_weight; // 亲戚体重
}

// 亲戚
struct relatives
{
    // char *father;  // 父亲   这里只能写名字
    struct introduction father; // 这里具体父亲的信息

    // char *mother;  // 母亲  这里只能写名字
     struct introduction mother;  // 这里具体母亲的信息
};


// 掌握的技能
struct skill
{
    char *s_name;   //  技能名称
    char *proficiency;  // 熟练度: 了解   熟悉   掌握   精通  
};



// 玩家
struct player
{
    int age;  // 年龄
    char *gender;  // 性别
    char *name;  // 名字
    char hobby[99];  // 爱好
    struct relatives rel; // 亲戚
    
};




int main(int argc, char const *argv[])
{

    // 结构体嵌套， 内层结构体的初始化要使用 { } 


    // 普通初始化



    // 指定成员初始化 




    // 访问



    
}