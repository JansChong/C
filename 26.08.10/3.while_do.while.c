#include <stdio.h>
#include <unistd.h>  // 休眠函数
#include <stdbool.h> // 标准头文件，true会被定义为恒等于1的宏

int main(int argc, char const *argv[])
{

    // while(1)  写成  while(true) 需要导入标准头文件<stdbool.h>
    // while(true){
    //     printf("循环\n");
    //     sleep(1); // 秒
    //     usleep(50000); // 单位：微秒,  休眠 50 毫秒
    // }
    // return 0;

    // 4.1 循环输出1-20
    int a = 1;
    while (a <= 20)
    {
        printf("%d ", a);
        a++;
    }

    printf("\n");

    // 4.2、通过while循环输出26个小写字母，
    char b = 'a';
    while (b <= 'z')
    {
        printf("%c ", b);
        b++;
    }
    printf("\n");

    // 4.3、 do...while循环输出26个大写字母，输出完26个字母之后在换行
    int c = 'A';
    do
    {
        printf("%c ", c);
        c++;
    } while (c <= 'Z');
    printf("\n\n");

    
    // 4.4、利用while循环打印9*9乘法表
    int row = 1, col = 1;
    // 行
    while (row <= 9)
    {
        col = 1;
        // 列
        while (col <= row)
        {

            printf("%d * %d = %d\t", col, row, row * col);
            col++;
        }
        row++;
        printf("\n");
    }
}
