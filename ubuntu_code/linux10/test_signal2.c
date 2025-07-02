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

int main(int argc, char* argv[])
{
    printf("pid = %d\n", getpid());

    // 忽略 SIGINT 信号
    void (*oldhandler)(int);  // 声明一个函数指针
    oldhandler = signal(SIGINT, SIG_IGN);
    if(oldhandler == SIG_ERR){
        error(1, errno, "signal %d", SIGINT);
    }
    sleep(5);

    printf("Wake up\n");

    signal(SIGINT, SIG_DFL);

    for(;;){
    }

    return 0;
}