#include <stdio.h>

int main(int argc, char const *argv[])
{
// bzero‌是C语言里用来把一段内存前n个字节清零的函数，现在更推荐用memset(ptr, 0, n)替代它，跨平台更稳妥。‌‌

// 这个函数怎么用
// ‌基本写法‌：void bzero(void *s, int n);，把指针s指向的内存前n个字节全部置为0。
// ‌头文件‌：不同系统写法不一样，Linux/POSIX系统通常用#include <strings.h>，部分旧环境也能用<string.h>。
// ‌常见场景‌：初始化数组、结构体或socket地址结构时清零，避免残留随机值。‌‌
      
}
