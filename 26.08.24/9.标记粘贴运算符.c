#include <stdio.h>

// 标记粘贴运算符:  ## 将两个字面量 黏贴为一个 标识符
#define PRIN1(a) printf("n" #a " = %d\n", n##a)

// ## 可以粘贴字面量 
#define PRIN2(a) printf("n" #a " = %d\n", n##123)




int main(int argc, char const *argv[])
{

    int n10 = 100; 
    int n123 = 123; 
    

    PRIN1(10); // 编译为： printf("n" "10" " = %d\n", n10);   结果为 "n10 = 100\n" 
    PRIN2(123); // 编译为： printf("n" "123" " = %d\n", n123);   结果为 "n123 = 123\n" 

}