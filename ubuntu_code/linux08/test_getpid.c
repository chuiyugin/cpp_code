#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    // ./test_getpid
    printf("pid=%d\n",getpid());
    printf("ppid=%d\n",getppid());

    sleep(10);
    return 0;
}