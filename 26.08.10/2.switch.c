#include <stdio.h>

int main(int argc, char const *argv[]) //   ./hello  1 2 3
{

    #if 0
    // **C 语言 `case` 后面必须是**整型常量表达式**，不能放变量、关系表达式（`a>5`、`a==5`这种）**
    int a = 10;
    switch (1)
    {
    case a > 5:  // C 语法要求 case 后必须是编译期就能确定的常量。
        break;
    case a == 5:
        break;
    case a < 5:
        break;
    default:
        break;
    }
    #endif


    
#if 0
    int rating;
    printf("输入一个成绩:\n");
    scanf("%d", &rating);

    switch (rating >= 60)
    {
        case 0:
            printf("不及格\n");
            break;
        case 1:
            printf("及格了\n");
            break;

        default: printf("所有case都不满足");
    }

    return 0;

#endif

#if 0
    // 练习：输入一个日期，计算这个日期是这一年的多少天
    int year, month, date, day = 0;

    printf("输入年月日\n");
    scanf("%d-%d-%d", &year, &month, &date);
    printf("%d-%d-%d", year, month, date);

    switch (month)
    {
    case 12:
        day = day + 30;
    case 11:
        day = day + 31;
    case 10:
        day = day + 30;
    case 9:
        day = day + 31;
    case 8:
        day = day + 31;
    case 7:
        day = day + 30;
    case 6:
        day = day + 31;
    case 5:
        day = day + 30;
    case 4:
        day = day + 31;
    case 3:
        int days = year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? 29 : 28;
        day = days + day;
    case 2:
        day = day + 31;
    case 1:
        day = day + date;
        printf("这是今年的第%d天\n", day);
    }
#endif
}
