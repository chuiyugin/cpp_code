#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    // ./test_open file
    //参数校验
    if(argc != 2)
    {
        error(1, 0, "Usage %s file",argv[0]);
    }
    //打开文件，获取文件描述符
    int fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL , 0666);
    if(fd == -1)
    {
        error(1, errno, "Usage %s", argv[1]);
    }
    //打印获取到的文件描述符
    printf("%d\n",fd);

    return 0;
}