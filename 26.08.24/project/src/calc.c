// <> 是官方的头文件
#include <stdio.h>
// "" 是自己的头文件
#include "../include/calc.h" // 相对路径

// 头文件引用的时候，""和<>的区别？
// <>是直接在标准库里面去寻找头文件
// ""是先从当前工程目录指定位置去找，没有找到就会去标准库里面查找相应的头文件
// 所以，一般来说，我们要引用标准库头文件就用<>，引用自定义头文件就用""

/**
 * 两数相减 
 * @param {float} a 第一个加数
 * @param {float} b 第二个加数
 * @return float
 */
float Add(float a, float b)
{
    return a + b;
}


/**
 * @description: 
 * - 支持多行函数描述
 * - 此处为详细说明：
 * - 可含 Markdown
 * - 两数相减 
 * @param {float} a 第一个被减数
 * @param {float} b 第二个减数
 * @return float
 */
float Sub(float a, float b)
{
    return a - b;
}


// 把src中定义的函数 封装到头文件 calc.h
// 在需要使用函数的文件导入头文件， 就可以使用这两个封装的头函数




// 编译: gcc 主程序 定义函数文件 -o 输出可运行程序 -I 头文件所在路径的相对路径
// 编译: gcc main.c ./src/calc.c -o main -I ./include
// 运行：./main