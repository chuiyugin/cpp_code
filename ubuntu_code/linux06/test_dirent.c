#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    // ./test_dirent dir
    //参数校验
    if(argc != 2)
    {
        error(1, 0, "Usage %s dir",argv[0]);
    }
    //打开目录流
    DIR* stream = opendir(argv[1]);
    if(!stream)
    {
        error(1, errno, "opendir %s",argv[1]);
    }
    //处理目录流
    errno = 0; // 等于0表示没出错
    struct dirent* pdirent;
    //readdir():读目录流，得到指向下一个目录项的指针。
    while((pdirent = readdir(stream)) != NULL)
    {
        printf("d_info=%ld, d_off=%ld, d_reclen=%hu, d_type=%d, d_name=%s\n",
        pdirent->d_ino,
        pdirent->d_off,
        pdirent->d_reclen,
        pdirent->d_type,
        pdirent->d_name);
    }
    if(errno != 0)
    {
        error(1, errno, "readdir %s",argv[1]);
    }
    //关闭目录流
    closedir(stream);

    return 0;
}