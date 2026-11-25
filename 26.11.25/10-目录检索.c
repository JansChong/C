#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main()
{

    // 1. 创建目录, 删除目录

    // 2. 打开目录以获得目录指针
    DIR *dir = opendir("/"); // 打开当前目录， 成功返回当前目录指针， 失败返回null
    if (dir == NULL)
    {
        printf("open dir fail\n");
        return -1;
    }

    while (1)
    {
        // 定义struct dirent * 结构体，  接收读取文件后的返回值
        struct dirent *dp = readdir(dir); // 读取指定目录下的文件

        // 如果文件读取返回 NULL, 则表示读取失败
        if (dp == NULL)
        {
            printf("读取结束\n");
            break;
        }

        // printf("i-node = %lu\n", dp->d_ino); // 索引号
        // printf("type = %hhu\n", dp->d_type); // 文件类型
        // printf("name = %s\n", dp->d_name);   // 目录名称
        // printf("i-node=%lu type=%hhu name=%s\n", dp->d_ino, dp->d_type, dp->d_name);

        // 可以用文件类型 dp->d_type 只输出需要的文件类型 ，不输出隐藏文件和特殊文件
        if (dp->d_type == DT_REG)
        {
            // printf("i-node=%lu type=%hhu name=%s\n", dp->d_ino, dp->d_type, dp->d_name);
        }

        // 或者不输出 . 开头的文件
        if (dp->d_name[0] != ".")
        {
            // printf("i-node=%lu type=%hhu name=%s\n", dp->d_ino, dp->d_type, dp->d_name);
        }

        // 读取指定格式的文件
        if (dp->d_type == DT_REG)
        {
            // strchr // 从前往后找指定字符    1.txt.bmp
            // strrchr // 从后往前找指定字符   1.txt.bmp   找后缀,即为文件格式
            // strstr // ?
            // strcmp // 比较两个字符串, 返回其差值

            char *str = strrchr(dp->d_name, '.');
            if (str != NULL && strcmp(str, ".c") == 0)
            {
                printf("i-node=%lu type=%hhu name=%s\n", dp->d_ino, dp->d_type, dp->d_name);
            }
        }
    }

    return 0;
}