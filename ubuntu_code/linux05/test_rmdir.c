#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    // ./test_rmdir dir 
    //参数校验
    if(argc != 2)
    {
        error(1, 0, "Usage %s dir",argv[0]);
    }
    //功能实现
    if(rmdir(argv[1]) == -1)
    {
        error(1, errno, "rmdir %s",argv[1]);
    }

    return 0;
}