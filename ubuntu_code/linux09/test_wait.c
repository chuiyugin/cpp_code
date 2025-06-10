#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>

void print_wstatus(int status){
    if(WIFEXITED(status)){
        int exit_code = WEXITSTATUS(status);
        printf("exit_code = %d", exit_code);
    }
    else if(WIFSIGNALED(status)){
        int signo = WTERMSIG(status);
        printf("term_sig = %d", signo);
    }
#ifdef WCOREDUMP
    if(WCOREDUMP(status)){
        printf(" (core dump) ");
    }
#endif
    printf("\n");
}

int main(int argc, char* argv[])
{
    pid_t pid = fork();
    switch(pid){
        case -1:
            error(1, errno, "fork");
        case 0:
            //子进程
            printf("CHILD: pid = %d\n", getpid());
            return 123;
        default:
            //父进程
            int status; // 保存子进程的终止状态信息，位图。
            pid_t childPid = waitpid(-1, &status, WNOHANG); // 阻塞点：一直等待，直到有子进程终止
            if(childPid > 0){
                printf("PARENT: %d terminated\n", childPid);
                print_wstatus(status);
            }
            else if(childPid == 0){
                printf("PARENT: no child changed state!\n");
            }
            else{
                error(1, 0, "waitpid");
            }
            exit(0);
    }
    return 0;
}