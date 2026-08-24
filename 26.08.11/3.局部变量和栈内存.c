#include <stdio.h>

// pc 计数器 ?
// 栈内存的特点：
// 函数被调用时， 内存会给函数分配一个栈空间， 这个栈空间会给形参分配空间并用实参初始化， 
// 当函数退出时，系统会自动回收其栈内存； 这个函数的栈空间会被释放，后续无法访问这个空间
// 系统为函数分配栈内存时，遵循从上（高地址）往下（低地址）分配的原则    (栈空间的生长方向： ubuntu从低地址往高地址生长，windows从高地址往低地址生长)

// 栈内存相对而言是比较小的， 不适合用来分配太大的变量
// 由于函数是分配的栈空间，(ubuntu)一个栈空间大概等于8MB(兆)， 在函数内定义较大长度的数组，可能会溢出 arr[8380000]   
// return 之后不可再访问函数的局部变量， 因此返回一个局部变量的地址通常是错误的



// { } 在main外部仅使用空括号会报错， 在main内部仅使用空括号则允许编译通过


// 函数声明
void test1(void);

void test2(void)
{
    // printf("test2函数访问变量val：%d\n", val); // 无法在变量声明之前访问变量 =>  error: ‘val’ undeclared (first use in this function)


}

// 全局变量：  (没有变量名提升/没有变量声明提前) 在变量声明之后可以访问这个变量， 在之前不能访问这个全局变量，在程序退出之前都有效
int val = 100;

void look(void)
{
    // 局部变量: 只能在 { } 内部使用
    int partial = 100;

    void test3(void)
    {
        printf("test3函数访问变量val：%d\n", partial); // 正常访问
    }
    test3();
}

int main(int argc, char const *argv[])
{

    printf("main函数访问变量val：%d\n", val); // 正常访问
    test1();                                  // 函数调用
    test2();                                    
}

// 函数定义
void test1(void)
{
    printf("test1函数访问变量val：%d\n", val); // 正常访问
}