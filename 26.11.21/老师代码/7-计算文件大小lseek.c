#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

int main()
{
    int fd = open("./1.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("open error\n");
        return -1;
    }

    int ret = lseek(fd, 0, SEEK_END);
    printf("ret = %d\n", ret);

    return 0;
}