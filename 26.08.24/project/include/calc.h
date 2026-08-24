// 头文件的本质是 在预处理时 把头文件的内容 替换到 引用该头文件的代码位置
// 预处理命令： gcc main.c ./src/jishuan.c -E -I ./include


// 由于头文件可以嵌套包含别的头文件，还有就是多个源文件可能包含同一个头文件，为了防止头文件被重复引用，头文件的书写格式有一定的要求：
// 条件编译： 有没有定义过这个头文件， 如果没有， 就定义一个, 避免重复定义头文件的问题
#ifndef CALC_H_   // 条件编译 - 大写文件名.H
#define CALC_H_   // 宏定义 - 大写文件名.H

// 头文件中可以包含其他头文件
#include <stdio.h>  // 路径在  usr/include/stdio.h

// 头文件正文
//1、头文件的引用
//2、宏定义
//3、组合数据类型，全局变量声明
//4、静态函数或内敛函数的定义
//5、普通函数的声明

float Add(float a, float b); 
float Sub(float a, float b); 
// 注意：普通函数的定义不能放在头文件中，因为函数的定义可以跨文件使用， 当头文件被多个文件引用时， 会造成普通函数的重复定义



// 静态函数或内敛函数可以定义在头文件中  因为它们的定义不能跨文件调用
/**
 * 两数相乘
 * @param {float} a 第一个数
 * @param {float} b 第二个数
 * @return float
 */
static float Multiplication(float a, float b){
    return a * b;
};

inline void func2(){};  // inline 用gcc编译不能跨文件使用， 用g++编译可以


#endif            // 结束条件编译