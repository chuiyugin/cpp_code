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
    // ./test_kill signo pid ...
    if(argc < 3){
        error(1, 0, "Usage: %s signo pid ...", argv[0]);
    }

    int signo;
    sscanf(argv[1], "%d", &signo);

    for(int i=2; i<argc; i++){
        pid_t pid;
        sscanf(argv[i], "%d", &pid);
        if(kill(pid, signo) == -1){
            error(0, errno, "kill(%d %d)", pid, signo);
        }
    }
    return 0;
}