#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    // ./orphen
    pid_t pid = fork();
    switch(pid){
        case -1:
            error(1, errno, "fork");
        case 0:
            //子进程
            sleep(2);
            printf("pid = %d, ppid = %d\n", getpid(), getppid());
            exit(0);
        default:
            //父进程
            printf("Parent: pid = %d, childpid = %d\n", getpid(), pid);
            exit(0);
    }
    return 0;
}