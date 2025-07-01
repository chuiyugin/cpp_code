#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char* argv[])
{
    // 先创建管道pipe
    int fields[2]; // fields[0]读端、fields[1]写端
    if(pipe(fields) == -1)
        error(1, errno, "pipe");
    // 再fork
    pid_t pid = fork();
    switch(pid){
        case -1:
            error(1, errno, "fork");
        case 0: // 子进程
            close(fields[1]);
            char message[MAXLINE];
            read(fields[0], message, MAXLINE);
            printf("child: %s",message);
            break;
        default: // 父进程
            close(fields[0]);
            sleep(5); // 管道为空会阻塞子进程
            write(fields[1], "This is parent!\n", 16+1);// +1 for '\0'
            break;
    }
    return 0;
}