#include <stdio.h>


int main(int argc, char const *argv[])
{


    // strcat(char *dest, const char *src);    字符串拼接,  把第二个字符串拼接到第一个字符串的末尾, 并放在第一个字符串当中
    // 必须保证前面字符串申请的地址空间要足够大, 必须能容纳两个字符串, 否则会越界  (演示程序中, 第二个字符串world 只剩一个d了)
    // 第一个参数不能是字符指针常量   指针常量是一个常量数据， 不可以通过下标赋值， 不可以修改常量数据的指针


    // malloc申请的空间, 并且给这片空间拷贝字符串的, 可以作为第一个参数  (malloc不是常量地址, 是一个堆空间)


    char str[6] = "hello";
	char str1[20] = " world";
	
	// strcat(str, str1);
	strncat(str, str1, 3);


	// printf("%s\n", strcat(str, str1));
	printf("str = %s\n", str); // "hello wo"
	printf("str1 = %s\n", str1); // 只剩下wo,   因为上面是 "hello wo\0",  而str1地址相邻, 从基地址读取字符串 " wo\0" 就停止读取了


    
    // strncat(char *dest, const char *src, size_t n); // 把第二个字符串的n个字符, 拼接到第一个字符串的末尾
}