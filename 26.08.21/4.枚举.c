#include <stdio.h>

enum week
{
    mon = 1
};

int main(int argc, char const *argv[])
{

    enum week a = mon;   // 1
    // int a = mon;  // 1
    printf("%d\n", a);
}