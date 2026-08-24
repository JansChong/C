#include <stdio.h>

// 每一个科目的详情
struct discipline_detail
{
    // char label[20];    //  这个 label不可以直接赋值, 因为 label是一个数组,  只能在初始化时可以直接列表初始化赋值,   后面要用下标或者strcpy赋值
    char *label; // 科目   // 这个 label可以直接赋值,  指向其他字符串的地址， 但是不能用scanf输入， 也不能用 strcpy 拷贝， 因为 没有初始化 而且 也不能修改常量数据的地址
    int score;   // 分数
};

// 科目
struct discipline
{
    // 简单写法：
    // int yuwen;  // 语文
    // int shuxue; // 数学
    // int yingyu; // 英语

    // 复杂写法:
    struct discipline_detail yuwen;  // 语文
    struct discipline_detail shuxue; // 数学
    struct discipline_detail yingyu; // 英语
};

// 学生
struct student
{
    long long number;                        // 学号 （考虑到学号比较长, 顺便用一下long long）
    char name[20];                           // 姓名
    int age;                                 // 年龄
    struct discipline desci;                 // 科目   这里可以试试结构体数组
    // struct discipline_detail desci_arr[3] // 试了一下 没有结构体直观， 毕竟 discipline 有属性名， 数组只有下标
};


void func (struct student a5[5]){

    for (int i = 0; i < 5; i++)
    {
        // 输出格式： 学生xxx, 年龄xx, 学号xxxxx, xx成绩xx分，xx成绩xx分，xx成绩xx分
        printf("学生%s, 年龄%d, 学号%lld, %s成绩%d分, %s成绩%d分,  %s成绩%d分\n",
             a5[i].name,
             a5[i].age,
             a5[i].number,
             a5[i].desci.yuwen.label,
             a5[i].desci.yuwen.score,
             a5[i].desci.shuxue.label,
             a5[i].desci.shuxue.score,
             a5[i].desci.yingyu.label,
             a5[i].desci.yingyu.score
        );
    }
    
}

int main(int argc, char const *argv[])
{

    // 练习2：
    // 定义一个学生类型结构体，
    // 结构体包含学号，姓名，年龄，成绩（语文，数学，英语），

    // 手动尝试 指定成员初始化
    // struct student myinfo =
    // {
    //     .number = 20151808308006,
    //     .name = "JC",
    //     .age = 28,
    //     .desci = {
    //             .yuwen = {
    //                 .label = "语文",
    //                 .score = 91},
    //             .shuxue = {
    //                 .label = "数学",
    //                 .score = 92},
    //             .yingyu = {
    //                 .label = "英语",
    //                 .score = 93}
    //         }
    //     // 试一下结构体数组
    //     .desci_arr = {{.label = "语文",.score = 91}, {.label = "数学",.score = 92},}, {.label = "英语", .score = 93}}
    // }

    // 定义5个学生的结构体数组，
    struct student five[5]; // { {}, {}, {} }

    // 通过键盘输入初始化，
    for (int i = 0; i < 5; i++)
    {
        // 输入第一个学生的
        printf("输入第%d个学生的信息：学号 名字 年龄：", i+1);
        scanf("%lld %s %d", &five[i].number, five[i].name, &five[i].age);

        five[i].desci.yuwen.label = "语文";
        five[i].desci.shuxue.label = "数学";
        five[i].desci.yingyu.label = "英语";

        printf("依次输入 语文、数学、英语 科目成绩：");
        scanf("%d %d %d", &five[i].desci.yuwen.score, &five[i].desci.shuxue.score, &five[i].desci.yingyu.score);
    }

    // 通过传参的方式，在函数里面打印所有的学生信息。
    func(five);
}




// 输入： 
// 输入第1个学生的信息：学号 名字 年龄
/* 20151808308006 zhuang 28 */
// 依次输入 语文、数学、英语 科目成绩：
/* 98 97 96 */

// 输入第2个学生的信息：学号 名字 年龄
/* 20151808308009 yang 27 */
// 依次输入 语文、数学、英语 科目成绩：
/* 91 92 93 */

// 输入第3个学生的信息：学号 名字 年龄
/* 20151808308011 xu 27 */
// 依次输入 语文、数学、英语 科目成绩：
/* 100 90 95 */

// 输入第4个学生的信息：学号 名字 年龄
/* 20151808308012 dong 25 */
// 依次输入 语文、数学、英语 科目成绩：
/* 90 91 92 */

// 输入第5个学生的信息：学号 名字 年龄
/* 20151808308013 chui 25 */
// 依次输入 语文、数学、英语 科目成绩：
/* 92 94 96 */


// 输出：
// 学生zhuang, 年龄28, 学号20151808308006, 语文成绩98分, 数学成绩97分,  英语成绩96分
// 学生yang, 年龄27, 学号20151808308009, 语文成绩91分, 数学成绩92分,  英语成绩93分
// 学生xu, 年龄27, 学号20151808308011, 语文成绩100分, 数学成绩90分,  英语成绩95分
// 学生dong, 年龄25, 学号20151808308012, 语文成绩90分, 数学成绩91分,  英语成绩92分
// 学生chui, 年龄25, 学号20151808308013, 语文成绩92分, 数学成绩94分,  英语成绩96分
