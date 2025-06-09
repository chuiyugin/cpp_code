#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    // ./test_fork4
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    printf("origin_pos: %ld\n", lseek(fd, 0, SEEK_CUR));

    //惯用法
    //父子进程都是从fork()返回
    //子进程不会执行前面的代码
    pid_t pid = fork(); 
    int newfd;

    switch(pid){
        case -1:
            //出错
            error(1, errno, "fork");
        case 0:
            //子进程
            write(fd, "hello world", 11);
            printf("child_pos: %ld\n", lseek(fd, 0, SEEK_CUR));
            close(STDERR_FILENO);

            newfd = dup(fd); // newfd = 2
            printf("child_newfd = %d\n", newfd);
            exit(0);
        default:
            //父进程
            sleep(2);
            printf("parent_pos: %ld\n", lseek(fd, 0, SEEK_CUR));
            newfd = dup(fd); // newfd = 4
            printf("parent_newfd = %d\n", newfd);
            exit(0);
    }
    return 0;
}