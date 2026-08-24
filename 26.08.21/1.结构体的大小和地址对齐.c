#include <stdio.h>

// 联合体的尺寸与基地址必须是m的倍数 ？


// 结构体的M值： 等于其成员中最大空间成员的M值, 结构体的存放要满足结构体的M值
// 成员各自的M值： 成员各自的M值约束其存放在结构体的空间中的位置，空闲空间会填充空闲值
// 成员在内存中的存放，按先后顺序

// m是几，基地址一定是m的倍数
// 模数是用来给地址对齐的， 而从这个基地址开始放多少位数据是看数据的大小
// 注意： 先在m的位置填充sizeof(数据)的数据，填充玩所有的数据再算大小， 最后一个数据不填充

// m值
// 32位：
// 64位：

// 画图示例的话， m等于几就画几列

struct student
{
    double b; // 8
    // short s;
    char a;
    // int i;
    // 包含数组？？看大小
};

#pragma pack(8) // 预处理命令   限定结构体"成员"m的最大值
// 公式：m_实际=min(原生m,n)  // 原生m,n其中最小的起作用,    也就是成员的m和设定的n, 其中最小的n生效
// 注意：只对 struct、union（结构体、共用体）"内部成员"的对齐生效
// 直到#pragma pack() 恢复结构体成员默认m
struct student2
{
    char name;                                // 原来的m为1， 配置的为2， 小的生效m为1
    int score;                                // 原来的m为4， 配置的为2， 小的生效m为2
    char a __attribute__((aligned(16 * 16))); // a的地址必为16*16的整数倍， 但是  m=min(16*16, 8), 生效的是8

    float average; // 原来的m为4， 配置的为2， 小的生效m为2
    double a;
};
#pragma pack() // 记得恢复结构体成员默认m

int main(int argc, char const *argv[])
{

    printf("%ld\n", sizeof(struct student));  // 16
    printf("%ld\n", sizeof(struct student2)); // 24


    long double a1 = 10; // m确实是16
    printf("%ld\n", sizeof(long double)); // 16
    printf("%p\n", &a1); // 地址是16的倍数， 而不是8的倍数

    // 修改类型的对齐模数，   语法：  attribute左右两下划线 aligned(模数)左右两个括号，
    char a __attribute__((aligned(16 * 16))); // a的地址必为16*16的整数倍
    printf("%ld\n", sizeof(a));               // 1

    // 一个变量的m值只能提升，不能减低， 且只能为正的2的n次幂;
}
