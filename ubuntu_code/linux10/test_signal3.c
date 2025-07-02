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
        case SIGKILL:
            printf("Caught SIGKILL\n");
            break;
        case SIGSTOP:
            printf("Caught SIGSTOP\n");
            break;
        default:
            printf("Unknown %d\n", signo);
    }
}

int main(int argc, char* argv[])
{
    //注册信号处理函数（捕获信号）
    void (*oldhandler)(int);  // 声明一个函数指针
    oldhandler = signal(SIGKILL, handler);
    if(oldhandler == SIG_ERR){
        error(0, errno, "signal SIGKILL");
    }
    oldhandler = signal(SIGSTOP, handler);
    if(oldhandler == SIG_ERR){
        error(0, errno, "signal SIGSTOP");
    }

    for(;;){
    }

    return 0;
}