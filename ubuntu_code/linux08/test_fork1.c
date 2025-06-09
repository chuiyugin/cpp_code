#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    // ./test_fork1 
    printf("BEGIN:\n");

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
            printf("child:pid = %d, ppid = %d\n", getpid(), getppid());
            break;
        default:
            //父进程
            printf("Who's your daddy?\n");
            printf("parent:pid = %d, chilpid = %d\n", getpid(), pid);
            break;
    }
    printf("BYE BYE!\n"); // 父子进程

    return 0;
}