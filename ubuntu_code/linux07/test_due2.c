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
    // 对 stderr 重定向
    int fd = open("application.log", O_RDWR | O_CREAT | O_APPEND, 0664);
    if (fd == -1){
        error(1, errno, "open application.log");
    }

    // STDERR_FILENO 标准错误输出的文件描述符
    write(STDERR_FILENO, "The first error massage\n", 24);
    
    //对 stderr 进行重定向
    //close(STDERR_FILENO);
    if(dup2(fd, STDERR_FILENO) == -1){
        error(1, errno, "dup2 %d %d", fd, STDERR_FILENO);
    }
    
    write(STDERR_FILENO, "The second error massage\n", 25);

    return 0;
}