#include "add.h"
#include "sub.h"
#include <stdio.h>

int main()
{
    int a = 20, b = 10, sum, dif;
    sum = add(a, b);
    dif = sub(a, b);
    printf("sum = %d\n", sum);
    printf("dif = %d\n", dif);
    return 0;
}
