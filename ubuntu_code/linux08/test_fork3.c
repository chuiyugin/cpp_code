#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    // ./test_fork3
    printf("BEGIN:"); // stdout是行缓冲区

    //惯用法
    //父子进程都是从fork()返回
    //子进程不会执行前面的代码
    pid_t pid = fork(); 

    switch(pid){
        case -1:
            //出错
            error(1, errno, "fork");
        case 0:
            //子进程
            printf("I am a baby\n");
            exit(0);
        default:
            //父进程
            sleep(2);
            printf("Who's your daddy?\n");
            exit(0);
    }
    return 0;
}