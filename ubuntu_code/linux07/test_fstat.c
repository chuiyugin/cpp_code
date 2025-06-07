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
    // ./test_fstat file
    if(argc != 2){
        error(1, 0, "Usage %s file", argv[0]);
    }

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        error(1, errno, "open %s", argv[1]);
    }

    struct stat sb; // 存储文件元数据信息
    if(fstat(fd, &sb) == -1){
        error(1, errno, "fstat %d", fd);
    }

    // 打印 struct stat 里面的成员信息
    printf("st_ino=%ld\nst_mode=%lo\nst_nlink=%ld\nst_size=%ld\nst_blocks=%ld\n",
            (long)sb.st_ino,
            (long)sb.st_mode,
            (long)sb.st_nlink,
            (long)sb.st_size,
            (long)sb.st_blocks);

    return 0;
}