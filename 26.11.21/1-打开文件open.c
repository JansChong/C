#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h> // read

int main()
{
    // open() 打开/创建文件， 返回当前进程的文件描述符
    // open返回的文件描述符在进程内是唯一的，但不同进程可以有相同的fd值‌。
    // 进程启动时0、1、2分别被标准输入、输出、错误占用，所以第一个open通常返回3
    // API文档： https://getiot.tech/manual/linux-c-functions/file.html#open

    // int fd  = open("./2.txt", O_RDWR); // O_RDWR 以可读写方式打开文件 （2.txt此时不存在）
    int fd = open("./2.txt", O_RDWR | O_CREAT, 0777); // 如果2.txt不存在，那么就创建文件并给创建的文件设置权限
                                                      // 如果创建的文件在windows下, 不管设置权限多少，ls -l 查看权限都会是777
                                                      // 如果创建的文件在Linux下，设置的权限还要再减去Linux环境下的权限掩码 （系统umask值）
    // umask()函数 会将Linux系统 umask 值设成参数 mask&0777 后的值，然后将先前的 umask 值返回。在使用 open() 建立新文件时，该参数 mode 并非真正建立文件的权限，而是 (mode&~umask) 的权限值。例如，在建立文件时指定文件权限为 0666，通常 umask 值默认为 022，则该文件的真正权限则为 0666&~022=0644，也就是 rw-r–r–   返回值：此调用不会有错误值返回，返回值为原先系统的 umask 值。

    // 若所有欲核查的权限都通过了检查则返回 0 值，表示成功，只要有一个权限被禁止则返回 -1
    if (fd == -1)
    {
        perror("open error");
        return -1;
    }

    // 打开成功, 返回 文件标识符
    printf("%d\n", fd);

    // close() 关闭文件
    // 头文件：#include <unistd.h>
    // 函数原型： int close(int fd);
    // 说明：当使用完文件后若已不再需要则可使用 close() 关闭该文件，调用 close() 会让数据写回磁盘，并释放该文件所占用的资源。参数 fd 为先前由 open() 或 creat() 所返回的文件描述词。
    // 返回值：若文件顺利关闭则返回 0，发生错误时返回 - 1。
    // 附加说明：虽然在进程结束时，系统会自动关闭已打开的文件，但仍建议自行关闭文件，并确实检查返回值。
    close(fd);
    printf("%d\n", fd);
    return 0;
}