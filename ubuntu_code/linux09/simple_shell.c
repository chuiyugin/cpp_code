#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define MAXLINE 1024
#define MAXRGS 128

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

// 解析命令行参数
void parse_parameters(char* message, char* argv[]){
    int i=0;
    argv[i] = strtok(message, " \t\n");
    while(argv[i] != NULL){
        i++;
        argv[i] = strtok(NULL, " \t\n");
    } // argv[i] == NULL
}

int main(int argc, char* argv[])
{
    char cmd[MAXLINE];
    char* parameters[MAXRGS];

    int status;

    for(;;){
        // 读取用户命令
        printf("Simple_shell > ");
        fgets(cmd, MAXLINE, stdin);
        // 如果cmd是exit，终止程序
        if(strcmp(cmd, "exit\n") == 0){
            exit(0);
        }
        // 创建子进程，让子进程执行命令
        pid_t pid = fork();

        switch(pid){
            case -1:
                error(1, errno, "fork");
            case 0: // 子进程
                // 解析命令行参数
                parse_parameters(cmd, parameters);
                if(execvp(parameters[0], parameters) == -1){
                    error(1, errno, "exevp");
                }
                break;
            default:
                if(waitpid(pid, &status, 0) == -1){
                    error(1, errno, "waitpid");
                }
                // 打印子进程的终止信息
                printf("%d terminated\n", pid);
                print_wstatus(status);
        }
    }
    return 0;
}