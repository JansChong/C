#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main()
{

    // 1. 创建目录, 删除目录

    // 2. opendir() 打开参数 name 指定的目录，并返回 DIR* 形态的目录流，和 open() 类似，接下来对目录的读取和搜索都要使用此返回值。
    DIR *dir = opendir("."); //  打开目录以获得 DIR* 形态的目录流（目录指针）， 成功则返回 目录流， 失败返回null
    if (dir == NULL)
    {
        printf("open dir fail\n");
        return -1;
    }

    while (1)
    {
        // 循环读取目录流下的文件，用其返回值类型的变量接收函数的返回值：

        // 定义struct dirent * 结构体， 接收读取目录流后的返回值
        struct dirent *dp = readdir(dir); // 循环读取指定目录下的文件

        // 如果文件读取返回 NULL, 则表示读取失败
        if (dp == NULL)
        {
            printf("读取结束\n");
            break;
        }

        // struct dirent * 结构体, 其中：dp->d_ino=索引号， dp->d_type=文件类型， dp->d_name=目录名称
        // printf("i-node=%lu type=%hhu name=%s\n", dp->d_ino, dp->d_type, dp->d_name);

        // 可以用文件类型 dp->d_type 只输出需要的文件类型，比如：
        // DT_REG 是 C 语言中用于表示“普通文件”的常量‌，通常定义在 <dirent.h> 头文件里，值为 8
        if (dp->d_type == DT_REG)
        {
        }

        // 或者不输出文件名以 . 开头的文件
        if (dp->d_name[0] != '.')
        {
        }

        // 读取指定格式的文件
        if (dp->d_type == DT_REG)
        {
            // strchr() 从前往后找指定字符, 查找到返回其下标，否则返回NULL
            // strrchr()  从后往前找指定字符, 查找到返回其下标，否则返回NULL; 常用于提取文件名或获取字符串后缀
            // strstr() 在字符串中查找另一个字符串首次出现位置, 返回其下标, 找不到则返回 NULL
            // strcmp() 比较两个字符串, 返回其差值

            // 因为要找文件格式，所以需要从后往前找. ; 从其下标到文件末尾即为文件格式
            // 1.txt.bmp
            char *str = strrchr(dp->d_name, '.'); // 找到.的下标, char * 未读取到\0会一直往后读取，直到\0
            if (str != NULL && strcmp(str, ".c") == 0) // 这里是查找目录下所有的.c 文件
            {
                printf("i-node=%lu type=%hhu name=%s\n", dp->d_ino, dp->d_type, dp->d_name);
            }
        }
    }

    return 0;
}