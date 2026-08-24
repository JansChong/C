#include <stdio.h>

char * func1(int a){
    printf("func1\n");
    return "ABC";
}

int func2(int a){
    printf("func2\n");
    return 123;
}

char * func3(int a){
    printf("func3\n");
    return "ABC";
}


int main(int argc, char const *argv[])
{


    // 各种指针的概念和初始化：

    // 指针函数： 返回值是指针的函数, 如 func1
    // char * p = func1(10);
    // printf("%s\n", p);// "ABC"
    

    // 函数指针： 指向函数入口地址的指针
    int (*p1)(int a) = func2;
    // int *p1(int) = func2; // 变量名可以省略
    // 通过函数指针调用函数
    p1(10);

    // 函数返回类型 (*指针变量名)(函数参数)
    char * (*p2)(int) = func1;  // 函数返回类型 (*指针变量名)(函数参数) = 函数  =>  char * (*p) (int)
    // 通过函数指针调用函数
    p2(10);


    // // 指针数组： 每个元素都是指针变量的数组
    // int x = 10; 
    // int y = 20; 
    // int * z = &x; 
    // char * str[] = {"hello", "world", &x, &y, z};
    // printf("%d %d %d\n", *str[0], *str[1], *str[2]);


    // // 数组指针： 用来存放数组的地址的指针
    int a[] = {1,2};
    int (*p)[] = &a; // 一定要带原数组的地址&a，如果不小心存了数组首元素的地址， 那么地址的偏移尺度不一样

    // printf("%d\n", **p);
    // printf("%d\n", *(*p+1));

    char *b[] = {"123", "abc"};
    char * (*q)[] = &b;
    printf("%p\n", q); // 整个数组的地址
    printf("%p\n", *q); // 拿数组首元素("123") 的地址, 
    printf("%s\n", **q); // 拿到数组首元素的值 "123"， 也就是1的地址， %s要输入首字符地址   (字符串拿到的地址也是它首字符的基地址， 就像数组地址的解引用等于首元素地址， %s读取字符串直到'\0')
    printf("%c\n", ***q); // 拿到"123"的首元素元素 “1” 


    // // 函数指针数组： 将每个 函数指针 存到数组中,   注意:数组的返回值要一样
    int (*a[])(int) = { func2, func3 }; // 等价于 {&func2, &func2}
    a[1](10); // 通过数组的方式调用函数


    // malloc 函数返回一个 void类型的指针

    
    
    // 如果 函数返回局部变量的地址， 函数执行完，局部变量的地址会被销毁，如果是'abc'等字符串常量的地址，则这种常量的地址外部仍然可以访问  （static和malloc也不会被销毁）
    // 回调函数√、多级指针√、特殊指针√、 头文件√、 malloc√


    
}