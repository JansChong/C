#include <stdio.h>
#include <string.h>

// 练习1：有一个字符串，”hello world“，计算‘l’出现的次数
void work1(char *str)
{
    int count = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == 'l')
            count++;
    }
    printf("l出现了%d次\n", count); // l出现了3次
}

// 练习2：输入一个字符串，要求，分别统计出英文字符，数字字符，其他字符，空格，并显示统计结果
void work2(char *str)
{
    int en = 0, num = 0, other = 0, space = 0;

    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z')
            en++;
        else if (str[i] >= '0' && str[i] <= '9')
            num++;
        else if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r')
            space++;
        else
            other++;
    }

    printf("英文字符: %d\n", en);
    printf("数字字符: %d\n", num);
    printf("其他字符: %d\n", other);
    printf("空格: %d\n", space);
}

// 练习3：设计一个函数，传入一个字符串，将字符串中所有的大写字母，改写成小写字母，并且删除掉多个连续相同的字符（只保留一个）
// 比如输入：HELLo World            AAA BDBBCCC D
// 输出：helo world                a bdbc d
void work3(char *str)
{
    int j = 0;
    int len = strlen(str);
    char res[10] = "";

    for (int i = 0; i < len; i++)
    {
        //   printf("%c\n", str[i]); // H
        //   printf("%c\n", *(str+1)); // E
        //   printf("%c\n", str[i]+1); // I    // ？？？ 什么时候是地址偏移， 什么时候是字符串的值偏移
        // 是地址的时候，地址偏移，    是值的时候（比如char）,就是值偏移

        // 只要变量没有赋值，它的值就不会变， 那么它就是地址的偏移 （这是讲师说的，待验证）

        // 变小写
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            // printf("%c\n", str[i] + 32);
            str[i] = str[i] + 32; // str[i] 是一个char值, 在ascii表中，  所以大写字母+32 = 小写字母
        }

        // 去重
        // if (strchr(res, str[i]) == NULL)

        // 连续字符去重
        if (str[i] != str[i - 1])
        {
            // printf("%s  %s\n", res, str);
            // printf("%s\n", strcat(res, *(str+i)));
            // strncat(res, strchr(res, str[i]), 1);

            res[j++] = str[i];
        }
    }

    printf("%s\n", res);
}

// 练习4：回文字符串
// 回文字符串就是正读和反读都一样的字符串，比如”radar“，要求从键盘输入，判断是否是回文字符串
// klopl
void work4()
{
    // char * str;  // 段错误，  str指向常量数据地址，不可以操作常量数据地址(scanf是对地址操作)， 但是可以更换str的指向(赋值操作)
    char str[99];
    printf("输入字符串：\n");
    scanf("%99s", str); // 限制长度

    int len = strlen(str);

    // 不管奇偶， 匹配一半即可
    for (int i = 0; i < len / 2; i++)
    {
        // 首尾比较
        if (str[i]  !=  str[len-1-i])
            {
                printf("%s不是回文\n", str);
                return; // 退出函数
            }
    }

    // 没有退出函数即为回文
    printf("%s是回文\n", str);
}

// 练习5 在下一个文件夹


int main(int argc, char const *argv[])
{

    // char * str = "hello world";
    // work1(str);

    // char *str = "222aaa   -*_";
    // work2(str);

    // char str[] = "HELLo World"; // helo world   helo world
    // char str[] = "AAA BDBBCCC D"; // a bdbc d    a bdbc d
    // work3(str);

    work4();
}