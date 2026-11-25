#include <stdio.h>

int main()
{
    // 读取3.txt 写入 4.txt

    // 打开
    FILE *fp1 = fopen("3.txt", "r"); // 只读
    FILE *fp2 = fopen("4.txt", "w"); // 只写（清空）

    // 缓冲区，存储fp1中读取的内容
    size_t buf[100] = {0};

    // 读取
    size_t ret = fread(buf, 20, 5, fp1);
    printf("%ld\n", ret);

    // 读取的实际 层数 小于要读取的层数: 1.读完了， 2.出错了
    if (ret <= 5)
    {
        // 文件读取完，fp1的文件读写指针在文件末尾
        // 如果已到文件尾 feof则返回非零值，其他情况返回 0。
        if (feof(fp1) != 0)
        {
            printf("文件读取完毕\n");

            // size_t fwrite(const void * ptr, size_t size, size_t nmemb, FILE * stream);
            // buf写入fp2
            fwrite(buf, 20, ret, fp2); // TODO..少两个没有写入
        }

        // ferror 返回0没出错， 返回非0则出错
        if(ferror(fp1) != 0){
            perror("读取fp1出错\n");
            return -1;
        }
    }


}