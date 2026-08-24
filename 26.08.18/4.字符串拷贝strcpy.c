#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    // 头文件 <string.h>
    // 函数原型 char *strcpy(char *dest, const char *src);
    // 说明：strcpy() 会将参数 src 字符串拷贝至参数 dest 所指的地址。
    // 返回值：返回参数 dest 的字符串起始地址。
    // 附加说明：如果参数 dest 所指的内存空间不够大，可能会造成缓冲溢出（buffer Overflow）的错误情况，在编写程序时请特别留意，或者用 strncpy() 来取代。

        


    // strcpy(char * dest, const char *src);
    // strncpy(char * dest, const char *src, size_t n);   拷贝n个有效字符, 如果n个里面包含\0就拷贝 否则不拷贝


    // 注意: strcpy函数会把第二个字符串的结束符一起拷贝，但是使用的时候，必须要保证前面字符串申请的地址空间要足够大 
        // 定义一个长度为10的字符串 "a x 10"
        char teststr[10] = "aaaaaaaaaa";
        printf("%s\n", teststr);

        // 拷贝 "hello" 到上面的字符串, 会拷贝末尾的\0
        char *afterstr = "hello";

        char *res = strcpy(teststr, afterstr);       

        // 以 %d, 查看字符串每一项的 ascii, 发现第六位是 0
        // printf("%s\n", teststr); // %s读取到\0就结束了， 所以得用 %c逐个查看， 否则只能读取到 "hello\0"
        // printf("%s\n", res);// %s读取到\0就结束了， 所以得用 %c逐个查看， 否则只能读取到 "hello\0"

        for (int i = 0; i < 10; i++)
        {
            printf("%c: %d\n", teststr[i], teststr[i]);  // 第6位读取到 \0 空字符串
            printf("%c: %d\n", res[i], res[i]);  // 第6位读取到 \0 空字符串
        }
    
    
        
    // 注意:不能拿字符指针常量来做为strcpy函数的第一个参数    (本质是把一个地址中的值, 拷贝赋值另一个地址,  常量地址是不可以修改的)

}