#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close  read
#include <string.h> // strerror
#include <errno.h>  // 全局错误码声明所在的头文件

int main(int argc, char const *argv[])
{


    
// 文件偏移量： 
// 1. 可以在文件尾部继续向后偏移， 照成空洞， 可以在空洞后继续写入 （多线程写入同一个文件）
// 2. 可以先将指针挪移到头部(open文件 或者 [0,start] )  再将指针挪移到文件末尾， 指针从头到尾的挪动字节数（返回值） 就是文件的大小

}