#include <stdio.h>

// 带参宏：计算个税，参数salary为税前工资
#define CALC_TAX(salary)({\
    double tax = 0.0;\
    double s = (salary);\
    if(s > 5000)\
    {\
        double over = s - 5000;\
        if(over <= 3000)\
        {\
            tax = over * 0.03;\
        }\
        else if(over <= 12000)\
        {\
            tax = 3000*0.03 + (over - 3000)*0.10;\
        }\
        else if(over <= 25000)\
        {\
            tax = 3000*0.03 + 9000*0.10 + (over - 12000)*0.20;\
        }\
        else if(over <= 35000)\
        {\
            tax = 3000*0.03 + 9000*0.10 +13000*0.20 + (over-25000)*0.25;\
        }\
        else if(over <= 55000)\
        {\
            tax = 3000*0.03 +9000*0.10 +13000*0.20 +10000*0.25 + (over-35000)*0.30;\
        }\
        else if(over <= 80000)\
        {\
            tax = 3000*0.03 +9000*0.10 +13000*0.20 +10000*0.25 +20000*0.30 + (over-55000)*0.35;\
        }\
        else\
        {\
            tax = 3000*0.03 +9000*0.10 +13000*0.20 +10000*0.25 +20000*0.30 +25000*0.35 + (over-80000)*0.45;\
        }\
    }\
    tax;\
})

// 税后工资宏：税前工资 - 个税
#define AFTER_SALARY(s) ((s) - CALC_TAX(s))

int main(void)
{
    double salary;
    printf("请输入税前工资：");
    scanf("%lf", &salary);

    if(salary < 0)
    {
        printf("工资不能为负数！\n");
        return 0;
    }

    double tax = CALC_TAX(salary); // 税额
    double after = AFTER_SALARY(salary); // 税后

    printf("税前工资：%.2lf\n", salary);
    printf("应缴个税：%.2lf\n", tax);
    printf("税后工资：%.2lf\n", after);

    return 0;
}
