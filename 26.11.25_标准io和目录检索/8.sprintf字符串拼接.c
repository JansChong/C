#include <stdio.h>

int main(int argc, char const *argv[])
{
    char path_name[100] = {0};

    char path[10] = "/mnt/hgfs";
    char name[10] = "/image";
    char format[10] = "jpg";

    // sprintf() 多个字符串按指定格式拼接, 输出到 char * ;   (格式化字符串复制到字符串数组) 
    // 返回拼接的字符串长度
    int ret = sprintf(path_name, "%s%s.%s", path, name, format);

    printf("ret = %d\n", ret); // 19, 返回拼接的字符串长度
    printf("%s\n", path_name); // /mnt/hgfs/1.bmp

    return 0;

    // 拓展： snprintf
}