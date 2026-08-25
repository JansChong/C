#include <stdio.h>

// 1、工资范围在1-5000元之间的，包括5000元，适用个人所得税税率为0%;
#define First_gear 5000
#define second_gear 8000
#define third_gear 17000
#define Four_gear 30000
#define Five_gear 40000
#define Six_gear 60000
#define Seven_gear 85000


// 注意：这个作业是错的！ 因为计算上一档的个税时， 是用的实发工资减去上一档的起征点， 而不是用档位区间的高值减去起征点


// 2、工资范围在5000-8000元之间的，包括8000元，适用个人所得税税率为3%;
#define second_tax_rate ((salary - First_gear) * 0.03)
// 3、工资范围在8000-17000元之间的，包括17000元，适用个人所得税税率为10%;
#define third_tax_rate (((salary - second_gear) * 0.1) + second_tax_rate)
// 4、工资范围在17000-30000元之间的，包括30000元，适用个人所得税税率为20%;
#define Four_tax_rate (((salary - third_gear) * 0.2) + third_tax_rate)
// 5、工资范围在30000-40000元之间的，包括40000元，适用个人所得税税率为25%;
#define Five_tax_rate (((salary - Four_gear) * 0.25) + Four_tax_rate)
// 6、工资范围在40000-60000元之间的，包括60000元，适用个人所得税税率为30%;
#define Six_tax_rate (((salary - Five_gear) * 0.3) + Five_tax_rate)
// 7、工资范围在60000-85000元之间的，包括85000元，适用个人所得税税率为35%;
#define Seven_tax_rate (((salary - Six_gear) * 0.35) + Six_tax_rate)
// 8、工资范围在85000元以上的，适用个人所得税税率为45%。
#define exceed (((salary - Seven_gear) * 0.45) + Seven_tax_rate)

// 7、工资范围在60000-85000元之间的，包括85000元，适用个人所得税税率为35%;

#define after_tax_salary(salary) ({                        \
    float available_salary = 0;                            \
    if (salary >= 1 && salary <= First_gear)               \
        available_salary = salary;                         \
    else if (salary > First_gear && salary <= second_gear) \
        available_salary = salary - second_tax_rate;       \
    else if (salary > second_gear && salary <= third_gear) \
        available_salary = salary - third_tax_rate;        \
    else if (salary > third_gear && salary <= Four_gear)   \
        available_salary = salary - Four_tax_rate;         \
    else if (salary > Four_gear && salary <= Five_gear)    \
        available_salary = salary - Five_tax_rate;         \
    else if (salary > Five_gear && salary <= Six_gear)     \
        available_salary = salary - Six_tax_rate;          \
    else if (salary > Six_gear && salary <= Seven_gear)    \
        available_salary = salary - Seven_tax_rate;        \
    else if (salary > Seven_gear)                          \
        available_salary = salary - exceed;                \
    available_salary;                                      \
})

int main(int argc, char const *argv[])
{

    // 练习：利用带参宏，计算所得税后工资
    // 比如，从键盘输入工资
    // 1、工资范围在1-5000元之间的，包括5000元，适用个人所得税税率为0%;
    // 2、工资范围在5000-8000元之间的，包括8000元，适用个人所得税税率为3%;
    // 3、工资范围在8000-17000元之间的，包括17000元，适用个人所得税税率为10%;
    // 4、工资范围在17000-30000元之间的，包括30000元，适用个人所得税税率为20%;
    // 5、工资范围在30000-40000元之间的，包括40000元，适用个人所得税税率为25%;
    // 6、工资范围在40000-60000元之间的，包括60000元，适用个人所得税税率为30%;
    // 7、工资范围在60000-85000元之间的，包括85000元，适用个人所得税税率为35%;
    // 8、工资范围在85000元以上的，适用个人所得税税率为45%。
    // 例如：1-5000元，实际到手1-5000
    // 所发工资8000，8000-(8000-5000)*%3 = 7910，最终所得工资
    // 所发工资17000，17000-((17000-8000)*%10+(8000-5000*%3))
    // 所发工资30000，30000-((30000-17000)*%20)+((17000-8000)*%10+(8000-5000*%3))

    int salary;
    printf("输入税前工资：\n");
    scanf("%d", &salary);

    float res = after_tax_salary(salary);
    printf("最终所得工资：%f, 税额: %f\n", res, salary - res);
}