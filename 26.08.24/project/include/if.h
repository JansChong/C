#ifndef IF_H
#define IF_H


// 在头文件使用条件编译
#if 1
struct student
{
    int age;
    char name;
}
#endif // !IF_H


// 定义GPIO宏
#define GPIO 3

// 如果定义了GPIO这个宏， 那么引入本头文件的文件内部会有这个静态函数
#ifdef GPIO
static void gpio_set(void){

}
#endif 


#endif // !IF_H