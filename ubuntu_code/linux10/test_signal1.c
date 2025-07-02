#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void handler(int signo){
    switch(signo){
        case SIGINT:
            printf("Caught SIGINT\n");
            break;
        case SIGTSTP:
            printf("Caught SIGTSTP\n");
            break;
        default:
            printf("Unknown %d\n", signo);
    }
}

int main(int argc, char* argv[])
{
    //注册信号处理函数（捕获信号）
    void (*oldhandler)(int);  // 声明一个函数指针
    oldhandler = signal(SIGINT, handler);
    if(oldhandler == SIG_ERR){
        error(1, errno, "signal %d", SIGINT);
    }
    oldhandler = signal(SIGTSTP, handler);
    if(oldhandler == SIG_ERR){
        error(1, errno, "signal %d", SIGTSTP);
    }

    for(;;){
    }

    return 0;
}