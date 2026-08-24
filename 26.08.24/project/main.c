
// 头文件引用的时候，""和<>的区别？
// <>是直接在标准库里面去寻找头文件
// ""是先从当前工程目录指定位置去找，没有找到就会去标准库里面查找相应的头文件
// 所以，一般来说，我们要引用标准库头文件就用<>，引用自定义头文件就用""

// <stdio.h> 在 "calc.h" 中引用了
// 导入 "calc.h" 的文件会自动导入 <stdio.h>
#include "./include/calc.h"


int main(int argc, char const *argv[])
{

    printf("10 + 20 = %f\n", Add(10, 20));
    printf("50 - 60 = %f\n", Sub(10, 20));
}



// 编译:         gcc main.c ./src/calc.c -o ./bin/main -I ./include
// 编译多个文件： gcc main.c ./src/*.c -o ./bin/main -I ./include

// 编译命令：直接在project下面直接编译
// gcc main.c ./src/*.c -o ./bin/main -I ./include/    //不包含库文件夹
// gcc main.c ./src/*.c -o ./bin/main -I ./include/ -L ./lib/ -l库名     //包含库文件夹

// gcc 编译器名字
// main 主函数文件
// ./src/*c 编译所有src文件夹下的c文件
// -o ./bin/main  生成可执行文件到指定目录
// -I ./include   指定头文件所在路径   -I（杠大i） 


// Makefile: 和main.c在同级，通过命令 make编译, 通过 Make clean清除可执行文件
