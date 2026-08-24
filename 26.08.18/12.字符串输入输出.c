#include <stdio.h>


int main(int argc, char const *argv[])
{


    // 输入： scanf()、   gets()、  fgets()
    // 输出：  printf()、   puts()


    // 【gets已废弃】 函数原型: char * gets(char *s)，  在键盘中获取字符串放到s中
    // char str1[100] = {0};
    // gets(str1);


    // 【fgets】 函数原型：char * fgets(char * s, int size, FILE * stream);  
    // fgets() 用来从参数 stream 所指的文件内读入字符并存到参数 s 所指的内存空间，直到出现换行字符、读到文件尾或是已读了 size-1 个字符为止，最后会加上 NULL 作为字符串结束。
    // fgets()若成功则返回s指针，返回 NULL 则表示有错误发生

    // 注意: fgets  可以获取输入的空白字符，会把换行也存入s所指的空间， 然后停止截取、停止输入
    //  scanf 的%s 遇到空白字符仅停止截取， 遇到\n才停止输入;     如果 %[^\n] 也可以截取空白字符，遇到\n停止

    char str1[100] = {0};
    char * p= fgets(str1, 100, stdin); // 在标准输入 欲读取100字节 放到数组str

    if(p == NULL) printf("操作失败\n");
    else  printf("%s%s", str1, p); // fgets 会把换行 也存入s所指的空间 所以不用\n



    // 【puts】 函数原型: puts(const char *s);  输出一个字符串(或字符)     并在末尾添加换行
    puts("abcd");
    puts("a");

    char a = 'A'; 
    puts(&a); // 这个取地址的操作， 是把 char 变成  char*， 以符合参数要求

    // 举例：
    for (int i = 0; i < 26; i++)
    {
        puts(&a);
        a++;
    }


    // 【fputs】 函数原型: int fputs(const char * s, FILE * stream);
    // 说明：fputs() 用来将参数 s 所指的字符串写入到参数 stream 所指的文件内。  没有自动添加换行
    // 返回值：若成功则返回写出的字符个数，返回 EOF 则表示有错误发生。
    fputs("hello world\n", stdout); // 把字符输出到 标准输出
    

    char a2 = 'A'; 
    fputs(&a2); // 这个取地址的操作， 是把 char 变成  char*， 以符合参数要求

}