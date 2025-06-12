#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int simple_system(const char* command){
    pid_t childPid = fork();
    int status;

    switch(childPid){
        case -1: // 出错
            return -1;
        case 0:
            execl("/bin/sh", "sh", "-c", command, NULL);
            _exit(127); // 出错了直接退出，避免stdout输出两次
        default:
            if(waitpid(childPid, &status, 0) == -1){
                return -1;
            }
            else{
                return status;
            }
    }
}

int main(int argc, char* argv[])
{
    // ./test_system
    simple_system("ls");
    return 0;
}