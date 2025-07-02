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

#define MAXLINE 1024

int main(int argc, char* argv[])
{
    int fd1 = open("./pipe1", O_RDONLY);
    if(fd1 == -1){
        error(1, errno, "open pipe1");
    }
    int fd2 = open("./pipe2", O_WRONLY);
    if(fd2 == -1){
        error(1, errno, "open pipe2");
    }
    printf("Established!\n");

    char recvline[MAXLINE];
    char sendline[MAXLINE];

    fd_set mainfds; //局部变量，1024的位图
    FD_ZERO(&mainfds); //将所有位置都置为0
    // 将感兴趣的文件描述符加入到mainfds中
    FD_SET(STDIN_FILENO, &mainfds);
    int max_fds = STDIN_FILENO;
    FD_SET(fd1, &mainfds);
    if(fd1 > max_fds){
        max_fds = fd2;
    }

    for(;;){
        fd_set readfds = mainfds; // 结构体的复制
        int events = select(max_fds+1, &readfds, NULL, NULL, NULL);
        switch(events){
        case -1: 
            error(1, errno, "select");
        case 0:
            //超时
            printf("TIMEOUT");
            continue;
        default:
            // STDIN_FILENO 就绪
            if(FD_ISSET(STDIN_FILENO, &readfds)){
                // 一定不会阻塞
                fgets(sendline, MAXLINE, stdin);
                write(fd2, sendline, strlen(sendline)+1); // +1 for '\0'
            }
            //fd1 就绪
            if(FD_ISSET(fd1, &readfds)){
                // 一定不会阻塞
                int nbytes = read(fd1, recvline, MAXLINE);
                if(nbytes == 0) // 管道写端关闭了
                    goto end;
                else if(nbytes == -1)
                    error(1, errno, "read pipe1");
                printf("From p1: %s", recvline);
            }
        }
    }
    end:
        close(fd1);
        close(fd2);
    return 0;
}