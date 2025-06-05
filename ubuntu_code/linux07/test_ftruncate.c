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
    // ./test_ftruncate file length
    if(argc != 3){
        error(1, 0, "Usage: %s file length", argv[0]);
    }

    off_t length; // 要截断的文件长度
    sscanf(argv[2], "%ld", &length);

    int fd = open(argv[1], O_RDWR);
    if(fd == -1){
        error(1, errno, "open %s", argv[1]);
    }

    if(ftruncate(fd, length) == -1){
        error(1, errno, "ftruncate %d", fd);
    } // 截断成功

    close(fd);

    return 0;
}