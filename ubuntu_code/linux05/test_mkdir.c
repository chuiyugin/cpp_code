#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    // ./test_mkdir dir mode(八进制)
    //参数校验
    if(argc != 3)
    {
        error(1, 0, "Usage %s dir mode",argv[0]);
    }

    //参数类型转换
    mode_t mode;
    sscanf(argv[2], "%o", &mode);
    int err = mkdir(argv[1], mode);
    if(err == -1)
    {
        error(1, errno, "mkdir %s",argv[1]);
    }

    return 0;
}