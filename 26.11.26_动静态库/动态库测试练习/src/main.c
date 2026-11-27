#include <stdio.h>
#include "sub.h"
#include "sum.h"

int main(int argc, char const *argv[])
{
    int a = sum(100, 55);
    printf("%d\n", a);

    int b = sub(100, 55);
    printf("%d\n", b);

}